// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/common.hpp>

#include <future>

namespace mk {

Runner::Runner() {}

void Runner::run(Callback<Continuation<>> kickoff) {
    if (!running) {
        std::promise<bool> promise;
        std::future<bool> future = promise.get_future();
        // WARNING: below we're passing `this` to the thread, which means that
        // the destructor MUST wait the thread. Otherwise, when the thread dies
        // many strange things could happen (I have seen SIGABRT).
        debug("runner: starting reactor in background...");
        thread = std::thread([&promise, this]() {
            reactor->loop_with_initial_event([&promise]() {
                debug("runner: starting reactor in background... ok");
                promise.set_value(true);
            });
        });
        future.wait();
        running = true;
    }
    active += 1;
    int task_id = active;
    debug("runner: scheduling %d", task_id);
    reactor->call_soon([=]() {
        debug("runner: starting %d", task_id);
        kickoff([=](Callback<> end) {
            debug("runner: ending %d", task_id);
            // For robustness, delay the final callback to the beginning of
            // next I/O cycle to prevent possible user after frees. This
            // could happen because, in our current position on the stack,
            // we have been called by `NetTest` code that may use `this`
            // after calling the callback. But this would be a problem
            // because `test` is most likely to be destroyed after `fn()`
            // returns. This, when unwinding the stack, the use after free
            // would happen.
            reactor->call_soon([=]() {
                debug("runner: callbacking %d", task_id);
                active -= 1;
                end();
            });
        });
    });
}

void Runner::run_test(Var<NetTest> test, std::function<void(Var<NetTest>)> fn) {
    run([=](Continuation<> complete) {
        test->begin([=](Error) {
            // TODO: do not ignore the error
            test->end([=](Error) {
                // TODO: do not ignore the error
                complete([=]() {
                    fn(test);
                });
            });
        });
    });
}

void Runner::break_loop() { reactor->break_loop(); }

bool Runner::empty() { return active == 0; }

void Runner::join() {
    if (running) {
        thread.join();
        running = false;
    }
}

Runner::~Runner() {
    // WARNING: This MUST be here to make sure we break the loop before we
    // stop the thread. Not doing that leads to undefined behavior.
    break_loop();
    join();
}

/*static*/ Var<Runner> Runner::global() {
    static Var<Runner> singleton(new Runner);
    return singleton;
}

} // namespace mk
