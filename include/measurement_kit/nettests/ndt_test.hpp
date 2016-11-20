// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef MEASUREMENT_KIT_NETTESTS_NDT_TEST_HPP
#define MEASUREMENT_KIT_NETTESTS_NDT_TEST_HPP

#include <measurement_kit/nettests/base_test.hpp>

namespace mk {
namespace nettests {

class NdtTest : public BaseTest {
  public:
    NdtTest();
};

class NdtRunnable : public Runnable {
  public:
    void main(std::string, Settings, Callback<report::Entry>) override;
};

} // namespace nettests
} // namespace mk
#endif
