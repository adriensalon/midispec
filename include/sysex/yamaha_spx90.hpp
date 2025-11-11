#pragma once

#include <array>
#include <variant>
#include <vector>

#include <sysex/core/integral.hpp>

namespace sysex {

/// @brief
namespace yamaha_spx90 {

    enum struct lfo_waveform : std::uint8_t {
        sine = 0,
        triangle = 1,
        square = 2,
        saw_up = 3,
        saw_down = 4,
    };

    enum struct freeze_trigger_mode : std::uint8_t {
        manual = 0,
        midi = 1,
        level = 2,
        automatic = 3,
    };

    enum struct stereo_mode : std::uint8_t {
        mono = 0,
        stereo = 1,
        ping_pong = 2,
    };

    enum struct phase_relation : std::uint8_t {
        in_phase = 0,
        quarter_turn = 1,
        half_turn = 2,
    };

    enum struct tone_curve_mode : std::uint8_t {
        low_pass = 0,
        high_pass = 1,
    };

    struct reverb_hall_program {
        integral<std::uint8_t, 0, 99> time; // UI: ~0.3..99.0 s
        integral<std::uint8_t, 0, 99> high_ratio; // UI: 0.10..1.00
        integral<std::uint8_t, 0, 99> pre_delay; // UI: 0.1..50.0 ms
        integral<std::uint8_t, 0, 99> low_pass_filter; // HF damping / LP tilt
        integral<std::uint8_t, 0, 99, 99> balance; // dry↔wet
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct reverb_room_program {
        integral<std::uint8_t, 0, 99> time;
        integral<std::uint8_t, 0, 99> high_ratio;
        integral<std::uint8_t, 0, 99> pre_delay;
        integral<std::uint8_t, 0, 99> room_size;
        integral<std::uint8_t, 0, 99> low_pass_filter;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct reverb_plate_program {
        integral<std::uint8_t, 0, 99> time;
        integral<std::uint8_t, 0, 99> high_ratio;
        integral<std::uint8_t, 0, 99> pre_delay;
        integral<std::uint8_t, 0, 99> diffusion;
        integral<std::uint8_t, 0, 99> low_pass_filter;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct early_reflections_program {
        // er_pattern pattern; // 0..7 (or wider if confirmed)
        integral<std::uint8_t, 0, 99> delay; // ~1..100 ms (UI)
        integral<std::uint8_t, 0, 99> room_size; // 0..99
        integral<std::uint8_t, 0, 99> low_pass_filter; // tone
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct gate_reverb_program {
        integral<std::uint8_t, 0, 99> gate_time; // ms scale
        integral<std::uint8_t, 0, 99> character; // envelope/shape
        integral<std::uint8_t, 0, 99> pre_delay; // ms
        integral<std::uint8_t, 0, 99> low_pass_filter;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct chorus_program {
        integral<std::uint8_t, 0, 99> speed; // Hz (UI)
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> delay; // base delay in ms
        phase_relation phase; // inter-channel phase
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct flanger_program {
        integral<std::uint8_t, 0, 99> speed; // Hz
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> delay; // very short ms
        integral<std::uint8_t, 0, 99> feedback_gain; // regeneration
        integral<std::uint8_t, 0, 99> manual; // static offset
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct phaser_program {
        integral<std::uint8_t, 0, 99> speed; // Hz
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> delay_time; // ~0.1..8.0 ms (UI)
        integral<std::uint8_t, 0, 99> feedback_gain; // if exposed
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct tremolo_program {
        integral<std::uint8_t, 0, 99> speed;
        integral<std::uint8_t, 0, 99> depth;
        // Optional waveform per firmware
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct vibrato_program {
        integral<std::uint8_t, 0, 99> speed;
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct symphonic_program {
        integral<std::uint8_t, 0, 99> speed;
        integral<std::uint8_t, 0, 99> depth;
        integral<std::uint8_t, 0, 99> detune;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct delay_program {
        stereo_mode mode; // mono/stereo/ping-pong
        integral<std::uint8_t, 0, 99> delay_time; // ms (algorithm may scale up)
        integral<std::uint8_t, 0, 99> feedback;
        integral<std::uint8_t, 0, 99> hpf; // tone
        integral<std::uint8_t, 0, 99> low_pass_filter; // tone
        integral<std::uint8_t, 0, 99> mod_speed; // Hz (if available)
        integral<std::uint8_t, 0, 99> mod_depth;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct echo_program {
        stereo_mode mode; // mono/stereo/ping-pong
        integral<std::uint8_t, 0, 99> delay_time_l;
        integral<std::uint8_t, 0, 99> delay_time_r;
        integral<std::uint8_t, 0, 99> feedback;
        integral<std::uint8_t, 0, 99> low_pass_filter;
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct pitch_change_program {
        integral<std::int8_t, -12, 12, 0> coarse; // semitones
        integral<std::int16_t, -100, 100, 0> fine; // cents
        integral<std::uint8_t, 0, 99> delay; // ms before shifted signal
        integral<std::uint8_t, 0, 99> tone; // LP/HP tilt for shifted voice
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    struct freeze_program {
        freeze_trigger_mode trigger_mode; // manual/midi/level/auto
        integral<std::uint8_t, 0, 99> length; // capture length (scaled)
        integral<std::uint8_t, 0, 99> lowpass; // tone
        integral<std::uint8_t, 0, 99, 99> balance;
        integral<std::uint8_t, 0, 99, 99> output_level;
        std::array<char, 10> program_name;
    };

    using program = std::variant<
        reverb_hall_program,
        reverb_room_program,
        reverb_plate_program,
        early_reflections_program,
        gate_reverb_program,
        chorus_program,
        flanger_program,
        phaser_program,
        tremolo_program,
        vibrato_program,
        symphonic_program,
        delay_program,
        echo_program,
        pitch_change_program,
        freeze_program>;

    void encode_reverb_hall_time(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    void encode_reverb_hall_high_ratio(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    void encode_reverb_hall_high_pre_delay(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    void encode_reverb_hall_high_low_pass_filter(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99> data);

    void encode_reverb_hall_balance(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99, 99> data);

    void encode_reverb_hall_output_level(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 99, 99> data);

    void encode_reverb_hall_program_name(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const std::array<char, 10>& data);

    void encode_program(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const program& data);

    void decode_program(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        program& data);

}
}
