#include <midispec/core/hardware.hpp>
#include <midispec/yamaha_tx81z.hpp>

namespace midispec {

struct gtest_yamaha_tx81z : public gtest_hardware {};

TEST_F(gtest_yamaha_tx81z, no_test_to_run)
{
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}