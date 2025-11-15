#include <midispec/core/hardware.hpp>
#include <midispec/novation_launchpad.hpp>

namespace midispec {

struct gtest_novation_launchpad : public gtest_hardware {};

TEST_F(gtest_novation_launchpad, no_test_to_run)
{
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}