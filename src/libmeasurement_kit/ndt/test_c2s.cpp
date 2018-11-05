// Part of Measurement Kit <https://measurement-kit.github.io/>.
// Measurement Kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.

#include "src/libmeasurement_kit/ndt/test_c2s_impl.hpp"

namespace mk {
namespace ndt {
namespace test_c2s {

void coroutine(SharedPtr<nlohmann::json> e, std::string address, int port, double runtime,
               Callback<Error, Continuation<Error>> cb, double timeout,
               Settings settings, SharedPtr<Reactor> reactor,
               SharedPtr<Logger> logger) {
    coroutine_impl(e, address, port, runtime, cb, timeout, settings, reactor,
                   logger);
}

void run(SharedPtr<Context> ctx, Callback<Error> callback) {
    run_impl(ctx, callback);
}

} // namespace test_c2s
} // namespace ndt
} // namespace mk
