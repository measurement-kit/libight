// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include "src/ndt/test-s2c.hpp"

namespace mk {
namespace ndt {
namespace tests {

using namespace net;

void s2c_coroutine(std::string address, int port,
                   Callback<Continuation<double>> cb, double timeout,
                   Logger *logger, Poller *poller) {
    s2c_coroutine_impl(address, port, cb, timeout, logger, poller);
}

void finalizing_test(Var<Context> ctx, Callback<> callback) {
    finalizing_test_impl(ctx, callback);
}

void run_test_s2c(Var<Context> ctx, Callback<> callback) {
    run_test_s2c_impl(ctx, callback);
}

} // namespace tests
} // namespace ndt
} // namespace mk
