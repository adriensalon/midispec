#pragma once

#include <array>
#include <cstdint>
#include <vector>

#include <sysex/core/integral.hpp>

namespace sysex {

/// @brief
namespace yamaha_dx7 {

    /// @brief Named keyboard level-scaling curve.
    /// Range is [0, 3]
    enum struct op_keyboard_scaling_curve : std::uint8_t {
        neg_lin = 0,
        pos_lin = 1,
        neg_exp = 2,
        pos_exp = 3
    };

    /// @brief Named oscillator mode.
    /// Range is [0, 1]
    enum struct op_oscillator_mode : std::uint8_t {
        ratio = 0,
        fixed = 1
    };

    /// @brief Named waveform for the global LFO.
    /// Range is [0, 5]
    enum struct lfo_waveform : std::uint8_t {
        triangle = 0,
        saw_down = 1,
        saw_up = 2,
        square = 3,
        sine = 4,
        sample_hold = 5
    };

    // global/system

    struct pitch_bend { // global PB setup
        std::uint8_t up_semitones = 2; // 0..12
        std::uint8_t down_semitones = 2; // 0..12
        std::uint8_t step = 0; // 0..12 (0 = smooth)
    };

    struct portamento {
        bool enabled = false; // on/off
        std::uint8_t time = 0; // 0..99
        bool fingered = false; // fingered portamento mode
        bool glissando = false; // gliss on/off (Mk I step glide)
    };

    struct mono_poly {
        bool mono = false; // mono/poly
        bool unison = false; // unison on/off (Mk I stacks voices)
        std::uint8_t unison_detune = 0; // 0..7 (if applicable)
    };

    struct aftertouch {
        bool enable; // enable/disable AT to voice modulation
    };

    struct foot_controller {
        // DX7 Mk I lets you choose destinations like pitch/amp/bias; exact mapping in .cpp
        bool to_pitch = false;
        bool to_amp = false;
        bool to_bias = false;
        std::uint8_t depth = 0; // 0..99 if applicable
    };

    struct breath_controller {
        bool to_pitch = false;
        bool to_amp = false;
        bool to_bias = false;
        std::uint8_t depth = 0; // 0..99
    };

    struct mod_wheel {
        bool to_pitch = true;
        bool to_amp = false;
        bool to_bias = false;
        std::uint8_t depth = 0; // 0..99
    };

    struct master_tune {
        std::int16_t cents; // typical range about ±100 cents
    };

    struct function_block {
        pitch_bend block_pitch_bend;
        portamento block_portamento;
        mono_poly block_mono_poly;
        aftertouch block_aftertouch;
        foot_controller block_foot_controller;
        breath_controller block_breath_controller;
        mod_wheel block_mod_wheel;
        master_tune block_master_tune;
    };

    /// @brief
    struct patch {
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_rate_1;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_rate_2;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_rate_3;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_rate_4;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_level_1;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_level_2;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_level_3;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_eg_level_4;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_keyboard_scaling_breakpoint;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_keyboard_scaling_left_depth;
        std::array<integral<std::uint8_t, 0, 99>, 6> op_keyboard_scaling_right_depth;
        std::array<op_keyboard_scaling_curve, 6> op_keyboard_scaling_left_curve;
        std::array<op_keyboard_scaling_curve, 6> op_keyboard_scaling_right_curve;
        std::array<integral<std::uint8_t, 0, 7>, 6> ops_keyboard_scaling_rate;
        std::array<integral<std::uint8_t, 0, 3>, 6> ops_amplitude_modulation_sensitivity;
        std::array<integral<std::uint8_t, 0, 7>, 6> ops_velocity_sensitivity;
        std::array<integral<std::uint8_t, 0, 99, 99>, 6> ops_output_level;
        std::array<op_oscillator_mode, 6> ops_oscillator_mode;
        std::array<integral<std::uint8_t, 0, 31>, 6> ops_oscillator_coarse;
        std::array<integral<std::uint8_t, 0, 99>, 6> ops_oscillator_fine;
        std::array<integral<std::uint8_t, 0, 14, 7>, 6> ops_oscillator_detune;
        integral<std::uint8_t, 0, 99> pitch_envelope_rate_1;
        integral<std::uint8_t, 0, 99> pitch_envelope_rate_2;
        integral<std::uint8_t, 0, 99> pitch_envelope_rate_3;
        integral<std::uint8_t, 0, 99> pitch_envelope_rate_4;
        integral<std::uint8_t, 0, 99> pitch_envelope_level_1;
        integral<std::uint8_t, 0, 99> pitch_envelope_level_2;
        integral<std::uint8_t, 0, 99> pitch_envelope_level_3;
        integral<std::uint8_t, 0, 99> pitch_envelope_level_4;
        integral<std::uint8_t, 0, 31> algorithm_mode;
        integral<std::uint8_t, 0, 7> algorithm_feedback;
        bool oscillator_key_sync;
        lfo_waveform lfo_waveform;
        integral<std::uint8_t, 0, 99> lfo_speed;
        integral<std::uint8_t, 0, 99> lfo_delay;
        integral<std::uint8_t, 0, 99> lfo_pitch_modulation_depth;
        integral<std::uint8_t, 0, 99> lfo_amplitude_modulation_depth;
        bool lfo_sync;
        integral<std::uint8_t, 0, 7> pitch_modulation_sensitivity;
        integral<std::int8_t, -24, 24, 0> transpose_semitones;
        integral<std::uint8_t, 0x00, 0x3F, 0x3F> op_enable_mask;
        std::array<char, 10> patch_name;
    };

    // encode

    /// @brief Encodes an eg_rate_1 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_rate_1(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an eg_rate_2 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_rate_2(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an eg_rate_3 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_rate_3(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an eg_rate_4 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_rate_4(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an eg_level_1 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_level_1(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an eg_level_2 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_level_2(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an op_eg_level_3 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_level_3(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief Encodes an op_eg_level_4 parameter change message for the Yamaha DX7
    /// @param encoded is the vector to append the encoded sysex message
    /// @param device is the device to target
    /// @param op is the operator to target
    /// @param data is the parameter to encode
    void encode_op_eg_level_4(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param op
    /// @param data
    void encode_op_keyboard_scaling_breakpoint(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const integral<std::uint8_t, 0, 5> op,
        const integral<std::uint8_t, 0, 99> data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(
    //     std::vector<std::uint8_t>& encoded,
    //     const integral_parameter<std::uint8_t, 0, 15> device,
    //     const integral_parameter<std::uint8_t, 0, 5> op,
    //     const op_keyboard_scaling_left_depth& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(
    //     std::vector<std::uint8_t>& encoded,
    //     const integral_parameter<std::uint8_t, 0, 15> device,
    //     const integral_parameter<std::uint8_t, 0, 5> op,
    //     const op_keyboard_scaling_right_depth& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(
    //     std::vector<std::uint8_t>& encoded,
    //     const integral_parameter<std::uint8_t, 0, 15> device,
    //     const integral_parameter<std::uint8_t, 0, 5> op,
    //     const op_keyboard_scaling_left_curve& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_keyboard_scaling_right_curve& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_keyboard_scaling_rate& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_amplitude_modulation_sensitivity& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_velocity_sensitivity& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_output_level& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_oscillator_mode& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_oscillator_coarse& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_oscillator_fine& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param op
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const integral_parameter<std::uint8_t, 0, 5> op, const op_oscillator_detune& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_rate_1& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_rate_2& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_rate_3& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_rate_4& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_level_1& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_level_2& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_level_3& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_envelope_level_4& data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_algorithm_mode(
        std::vector<std::uint8_t>& encoded, 
        const integral<std::uint8_t, 0, 15> device, 
        const integral<std::uint8_t, 0, 31> data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const algorithm_feedback& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const oscillator_key_sync& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const lfo_waveform& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const lfo_speed& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const lfo_delay& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const lfo_pitch_modulation_depth data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const lfo_amplitude_modulation_depth data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const lfo_sync data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_modulation_sensitivity& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const transpose_semitones& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const op_enable_mask& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const patch_name& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const pitch_bend& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const portamento& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const mono_poly& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const aftertouch& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const foot_controller& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const breath_controller& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const mod_wheel& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const master_tune& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const function_block& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_1& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_2& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_3& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_4& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_5& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_6& data);

    // /// @brief
    // /// @param encoded
    // /// @param device
    // /// @param data
    // void encode(std::vector<std::uint8_t>& encoded, const integral_parameter<std::uint8_t, 0, 15> device, const button_7& data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_1(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_8(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_store(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_memory_protect_internal(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_memory_protect_cartridge(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_memory_select_internal(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_memory_select_cartridge(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_function(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_no(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_button_yes(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const bool data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_patch(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 15> device,
        const patch& data);

    /// @brief
    /// @param encoded
    /// @param device
    /// @param data
    void encode_bank(
        std::vector<std::uint8_t>& encoded, 
        const integral<std::uint8_t, 0, 15> device, 
        const std::array<patch, 32>& data);

    // decode

    /// @brief 
    /// @param encoded 
    /// @param device 
    /// @param data 
    /// @return 
    bool decode_bank(
        const std::vector<std::uint8_t>& encoded, 
        const integral<std::uint8_t, 0, 15> device, 
        std::array<patch, 32>& data);

}
}
