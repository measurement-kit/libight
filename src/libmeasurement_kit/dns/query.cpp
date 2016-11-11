// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include "../dns/query.hpp"
#include "../libevent/dns.hpp"

namespace mk {
namespace dns {

void query(
        QueryClass dns_class,
        QueryType dns_type,
        std::string name,
        Callback<Error, Var<Message>> cb,
        Settings settings,
        Var<Reactor> reactor,
        Var<Logger> logger) {
    std::string engine = settings.get("dns/engine", std::string{"libevent"});
    if (engine == "cares") {
        cares::query(dns_class, dns_type, name, cb, settings, reactor, logger);
        return;
    }
    libevent::query(dns_class, dns_type, name, cb, settings, reactor, logger);
}

} // namespace dns
} // namespace mk
