// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#include "private/common/locked.hpp"
#include "private/libevent/reactor.hpp"

namespace mk {

/*static*/ Var<Reactor> Reactor::make() {
    return locked_global([]() { return Var<Reactor>{new libevent::Reactor<>}; });
}

Reactor::~Reactor() {}

void Reactor::run_with_initial_event(Callback<> &&cb) {
    call_soon(std::move(cb));
    run();
}

/*static*/ Var<Reactor> Reactor::global() {
    return locked_global([]() {
        static Var<Reactor> singleton = make();
        return singleton;
    });
}

} // namespace mk
