#include <midispec/novation_launchpads.hpp>

/// User manual at
/// https://fael-downloads-prod.focusrite.com/customer/dev/s3fs-public/novation/downloads/10753/launchpad-s-prm.pdf

namespace midispec {

static_assert(has_note_off_v<novation_launchpads, capability::receive, capability::transmit>);
static_assert(has_note_on_v<novation_launchpads, capability::receive, capability::transmit>);
static_assert(has_reset_v<novation_launchpads, capability::receive>);
static_assert(has_universal_inquiry_v<novation_launchpads, capability::request, capability::transmit>);

// channel common

namespace {
    static constexpr std::uint8_t CHANNEL_LAUNCHPAD = 0;
}

void novation_launchpads::encode_note_off(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 127> note)
{
    encoded.push_back(0x90 | CHANNEL_LAUNCHPAD);
    encoded.push_back(static_cast<std::uint8_t>(note));
    encoded.push_back(0x00);
}

bool novation_launchpads::decode_note_off(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 127>& note)
{
    if (encoded.size() != 3) {
        return false;
    }
    if ((encoded[0] & 0x0F) != CHANNEL_LAUNCHPAD) {
        return false;
    }
    if (((encoded[0] & 0xF0) != 0x90) || (encoded[2] != 0)) {
        return false;
    }

    note = encoded[1];
    return true;
}

void novation_launchpads::encode_note_on(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 127> note,
    const integral<std::uint8_t, 0, 127> velocity)
{
    encoded.push_back(0x90 | CHANNEL_LAUNCHPAD);
    encoded.push_back(note.value());
    encoded.push_back(velocity.value());
}

bool novation_launchpads::decode_note_on(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 127>& note,
    integral<std::uint8_t, 0, 127>& velocity)
{
    if (encoded.size() != 3) {
        return false;
    }
    if ((encoded[0] & 0x0F) != CHANNEL_LAUNCHPAD) {
        return false;
    }
    if (((encoded[0] & 0xF0) != 0x90) || (encoded[2] == 0)) {
        return false;
    }

    note = encoded[1];
    velocity = encoded[2];
    return true;
}

// system common

void novation_launchpads::encode_reset(std::vector<std::uint8_t>& encoded)
{
    encoded.push_back(0xB0 | CHANNEL_LAUNCHPAD);
    encoded.push_back(0x00);
    encoded.push_back(0x00);
}

void novation_launchpads::encode_all_leds_on(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 2> intensity)
{
    static constexpr std::uint8_t _led_intensity_mode[3] = {
        0x7D, // 0: Low brightness
        0x7E, // 1: Medium brightness
        0x7F //  2: High brightness
    };

    encoded.push_back(0xB0 | CHANNEL_LAUNCHPAD);
    encoded.push_back(0x00);
    encoded.push_back(_led_intensity_mode[intensity.value()]);
}

void novation_launchpads::encode_button_layout(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 1> layout)
{
    encoded.push_back(0xB0 | CHANNEL_LAUNCHPAD);
    encoded.push_back(0x00);
    encoded.push_back(layout.value() + 1);
}

void novation_launchpads::encode_brightness(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 5> numerator,
    const integral<std::uint8_t, 0, 17> denominator)
{
    encoded.push_back(0xB0 | CHANNEL_LAUNCHPAD);
    encoded.push_back(0x1E);
    encoded.push_back((numerator.value() << 4) | (denominator.value() & 0x0F));
}

void novation_launchpads::encode_led_buffers_mode(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 5> mode)
{
    static constexpr std::uint8_t _led_buffer_modes[6] = {
        0x20, // 0: Simple
        0x24, // 1: Buffered 0
        0x21, // 2: Buffered 1
        0x34, // 3: Buffered 0 + Copy
        0x31, // 4: Buffered 1 + Copy
        0x28 //  5: Flash
    };

    encoded.push_back(0xB0 | CHANNEL_LAUNCHPAD);
    encoded.push_back(0x00);
    encoded.push_back(_led_buffer_modes[mode.value()]);
}

// system exclusive

namespace {
    static constexpr std::uint8_t SYSEX_START = 0xF0;
    static constexpr std::uint8_t SYSEX_END = 0xF7;
    static constexpr std::uint8_t SYSEX_AKAI = 0x7E;
}

void novation_launchpads::encode_scrolling_text(
    std::vector<std::uint8_t>& encoded,
    const std::string& text)
{
}

void novation_launchpads::encode_universal_inquiry_request(
    std::vector<std::uint8_t>& encoded,
    const integral<std::uint8_t, 0, 127> device)
{
}

bool novation_launchpads::decode_universal_inquiry(
    const std::vector<std::uint8_t>& encoded,
    integral<std::uint8_t, 0, 127>& device,
    std::uint32_t& manufacturer,
    std::uint32_t& family,
    std::uint32_t& model,
    std::uint32_t& version)
{
    return true;
}

}