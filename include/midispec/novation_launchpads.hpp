#pragma once

#include <array>
#include <vector>

#include <midispec/core/capabilities.hpp>
#include <midispec/core/integral.hpp>

namespace midispec {

/// @brief MIDI support for the Novation Launchpad S controller
struct novation_launchpads {

    // channel common (on this hardware all messages are exchanged on channel 0)

    /// @brief Encodes a note off message
    /// @param encoded Vector to append the encoded message to
    /// @param note MIDI note. In range [0, 127]
    static void encode_note_off(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 127> note);

    /// @brief Decodes a note off message
    /// @param encoded Vector to read the encoded message from
    /// @param note MIDI note. In range [0, 127]
    /// @return true on success
    static bool decode_note_off(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 127>& note);

    /// @brief Encodes a note on message
    /// @param encoded Vector to append the encoded message to
    /// @param note MIDI note. In range [0, 127]
    /// @param velocity MIDI velocity. In range [0, 127]
    static void encode_note_on(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 127> note,
        const integral<std::uint8_t, 0, 127> velocity);

    /// @brief Decodes a note on message
    /// @param encoded Vector to read the encoded message from
    /// @param note MIDI note. In range [0, 127]
    /// @param velocity MIDI velocity. In range [0, 127]
    /// @return true on success
    static bool decode_note_on(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 127>& note,
        integral<std::uint8_t, 0, 127>& velocity);

    // system common

    /// @brief Encodes a reset message
    /// @param encoded Vector to append the encoded message to
    static void encode_reset(std::vector<std::uint8_t>& encoded);

    /// @brief Encodes a all LEDs on message
    /// @param encoded Vector to append the encoded message to
    /// @param intensity Intensity to set LEDs to. In range [0, 2]
    static void encode_all_leds_on(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 2> intensity);

    /// @brief Encodes a button layout change message
    /// @param encoded Vector to append the encoded message to
    /// @param layout Layout mode to switch to
    static void encode_button_layout(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 1> layout);

    /// @brief Encodes a brightness change message
    /// @param encoded Vector to append the encoded message to
    /// @param numerator Numerator for brightness fraction. In range [0, 5]
    /// @param numerator Denominator for brightness fraction. In range [0, 5]
    static void encode_brightness(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 5> numerator,
        const integral<std::uint8_t, 0, 17> denominator);

    /// @brief Encodes a LED buffer mode change message
    /// @param encoded Vector to append the encoded message to
    static void encode_led_buffers_mode(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 5> mode);

    // system exclusive

    /// @brief Encodes a brightness change message
    /// @param encoded Vector to append the encoded message to
    /// @param text scrolling text data
    static void encode_scrolling_text(
        std::vector<std::uint8_t>& encoded,
        const std::string& text);

    /// @brief Encodes a universal inquiry request message
    /// @param encoded Vector to append the encoded SysEx message to
    /// @param device Target device number. In range [0, 127]
    static void encode_universal_inquiry_request(
        std::vector<std::uint8_t>& encoded,
        const integral<std::uint8_t, 0, 127> device);

    /// @brief Decodes a universal inquiry request message
    /// @param encoded Vector to read the encoded message from
    /// @param device Target device number. In range [0, 127]
    /// @param manufacturer MIDI hardware manufacturer info
    /// @param family MIDI hardware family info
    /// @param model MIDI hardware model info
    /// @param version MIDI hardware version info
    /// @return true on success
    static bool decode_universal_inquiry(
        const std::vector<std::uint8_t>& encoded,
        integral<std::uint8_t, 0, 127>& device,
        std::uint32_t& manufacturer,
        std::uint32_t& family,
        std::uint32_t& model,
        std::uint32_t& version);
};
}
