// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include <measurement_kit/nettests.hpp>
#include <measurement_kit/ooni.hpp>

namespace mk {
namespace nettests {

TcpConnect::TcpConnect() : BaseTest() {
    runnable.reset(new TcpConnectRunnable);
    runnable->test_name = "tcp_connect";
    runnable->test_version = "0.0.1";
    runnable->needs_input = true;
}

void TcpConnectRunnable::main(std::string input, Settings options,
                              Callback<report::Entry> cb) {
    ooni::tcp_connect(input, options, [=](Var<report::Entry> entry) {
        cb(*entry);
    }, reactor, logger);
}

} // namespace nettests
} // namespace mk
