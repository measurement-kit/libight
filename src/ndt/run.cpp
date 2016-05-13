// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/mlabns.hpp>
#include "src/ndt/run_impl.hpp"

namespace mk {
namespace ndt {

void run_with_specific_server(std::string address, int port,
                              Callback<Error> callback, Settings settings,
                              Var<Logger> logger, Var<Reactor> reactor) {
    run_with_specific_server_impl<
        protocol::connect, protocol::send_extended_login,
        protocol::recv_and_ignore_kickoff, protocol::wait_in_queue,
        protocol::recv_version, protocol::recv_tests_id, protocol::run_tests,
        protocol::recv_results_and_logout, protocol::wait_close,
        protocol::disconnect_and_callback>(address, port, callback, settings,
                                           logger, reactor);
}

void run(Callback<Error> callback, Settings settings, Var<Logger> logger,
         Var<Reactor> reactor) {
    ErrorOr<int> port = settings.get_noexcept<int>("port", 3001);
    if (!port) {
        callback(port.as_error());
        return;
    }
    std::string address = settings.get<std::string>("address", "");
    if (address != "") {
        run_with_specific_server(address, *port, callback, settings,
                                 logger, reactor);
        return;
    }
    mlabns::query("ndt", [=](Error err, mlabns::Reply reply) {
        if (err) {
            callback(err);
            return;
        }
        run_with_specific_server(reply.fqdn, *port, callback, settings,
                                 logger, reactor);
    }, settings, reactor, logger);
}

} // namespace mk
} // namespace ndt
