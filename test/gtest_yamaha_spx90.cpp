#include <midispec/core/hardware.hpp>
#include <midispec/yamaha_spx90.hpp>

namespace midispec {

struct gtest_yamaha_spx90 : public gtest_hardware {};

TEST_F(gtest_yamaha_spx90, no_test_to_run)
{
}

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}