// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.

#include "private/nettests/runnable.hpp"

#include <measurement_kit/nettests.hpp>
#include <measurement_kit/ooni.hpp>

namespace mk {
namespace nettests {

TelegramTest::TelegramTest() : BaseTest() {
    runnable.reset(new TelegramRunnable);
    runnable->test_name = "telegram";
    runnable->test_version = "0.0.1";
    runnable->needs_input = false;
}

void TelegramRunnable::main(std::string input, Settings options,
                            Callback<Var<report::Entry>> cb) {
    ooni::telegram(input, options, cb, reactor, logger);
}

} // namespace nettests
} // namespace mk
