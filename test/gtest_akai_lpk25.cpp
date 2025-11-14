#include <midispec/akai_lpk25.hpp>
#include <midispec/core/hardware.hpp>

namespace midispec {

struct gtest_akai_lpk25 : public gtest_hardware {};

TEST_F(gtest_akai_lpk25, no_test_to_run)
{
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}