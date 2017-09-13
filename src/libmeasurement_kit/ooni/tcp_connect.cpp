// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#include <measurement_kit/ooni.hpp>

namespace mk {
namespace ooni {

using namespace mk::report;

void tcp_connect(std::string input, Settings options,
                 Callback<SharedPtr<Entry>> callback, SharedPtr<Reactor> reactor,
                 SharedPtr<Logger> logger) {
    SharedPtr<Entry> entry(new Entry);
    (*entry)["connection"] = nullptr;
    // Note: unlike ooni-probe, here we also accept endpoints where the port
    // is not specified, defaulting to 80 in such case.
    ErrorOr<net::Endpoint> maybe_epnt = net::parse_endpoint(input, 80);
    if (!maybe_epnt) {
        (*entry)["connection"] = maybe_epnt.as_error().as_ooni_error();
        callback(entry);
        return;
    }
    options["host"] = maybe_epnt->hostname;
    options["port"] = maybe_epnt->port;
    templates::tcp_connect(options, [=](Error err, SharedPtr<net::Transport> txp) {
        logger->debug("tcp_connect: Got response to TCP connect test");
        if (err) {
            (*entry)["connection"] = err.as_ooni_error();
            callback(entry);
            return;
        }
        txp->close([=]() {
            (*entry)["connection"] = "success";
            callback(entry);
        });
    }, reactor, logger);
}

} // namespace ooni
} // namespace mk
