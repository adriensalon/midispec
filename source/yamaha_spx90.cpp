#include <sysex/yamaha_spx90.hpp>

namespace sysex {
namespace yamaha_spx90 {

    void encode_reverb_hall_time(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data)
    {
    }

    void encode_reverb_hall_high_ratio(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data)
    {
    }

    void encode_reverb_hall_high_pre_delay(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data)
    {
    }

    void encode_reverb_hall_high_low_pass_filter(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data)
    {
    }

    void encode_reverb_hall_balance(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99, 99> data)
    {
    }

    void encode_reverb_hall_output_level(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99, 99> data)
    {
    }

    void encode_reverb_hall_program_name(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const std::array<char, 10>& data)
    {
    }

    void encode_program(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const program& data)
    {
    }

    void decode_program(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        program& data)
    {
    }
}
}