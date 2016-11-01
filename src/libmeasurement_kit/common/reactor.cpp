// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include "../common/check_connectivity.hpp"
#include "../libevent/poller.hpp"

namespace mk {

/*static*/ Var<Reactor> Reactor::make() {
    return Var<Reactor>(new libevent::Poller);
}

Reactor::~Reactor() {}

/*static*/ Var<Reactor> Reactor::global() {
    static Var<Reactor> singleton = make();
    return singleton;
}

void loop_with_initial_event_and_connectivity(std::function<void()> cb) {
    if (!CheckConnectivity::is_down()) {
        loop_with_initial_event(cb);
    } else {
        warn("Test skipped because network is down");
    }
}

void call_soon(Callback<> callback, Var<Reactor> reactor) {
    reactor->call_soon(callback);
}

void call_later(double delta, Callback<> callback, Var<Reactor> reactor) {
    reactor->call_later(delta, callback);
}

void loop_with_initial_event(Callback<> callback, Var<Reactor> reactor) {
    reactor->loop_with_initial_event(callback);
}

void loop(Var<Reactor> reactor) {
    reactor->loop();
}

void loop_once(Var<Reactor> reactor) {
    reactor->loop_once();
}

void break_loop(Var<Reactor> reactor) {
    reactor->break_loop();
}

} // namespace mk
