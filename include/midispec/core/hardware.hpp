#pragma once

#include <RtMidi.h>
#include <gtest/gtest.h>

#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>

namespace midispec {

/// @brief
struct gtest_hardware : public testing::Test {

    /// @brief
    /// @param encoded
    /// @param clear
    /// @param debounce
    inline static void send(
        std::vector<std::uint8_t>& encoded,
        const bool clear = true,
        const std::chrono::milliseconds debounce = std::chrono::milliseconds(50))
    {
        _midi_out->sendMessage(&encoded);
        if (clear) {
            encoded.clear();
        }
        std::this_thread::sleep_for(debounce);
    }

    /// @brief
    /// @param encoded
    /// @param timeout
    /// @return true on success
    inline static bool receive(
        std::vector<std::uint8_t>& encoded,
        const std::chrono::milliseconds timeout = std::chrono::milliseconds(5000))
    {
        std::unique_lock<std::mutex> _lock(_mutex);
        if (!_condition_variable.wait_for(_lock, timeout, [] { return _stop || !_queue.empty(); })) {
            return false;
        }

        const std::chrono::steady_clock::time_point _deadline = std::chrono::steady_clock::now() + timeout;
        while (!_stop) {
            if (!_queue.empty() && !_queue.front().empty() && _queue.front().front() == 0xF0) {
                encoded = std::move(_queue.front());
                _queue.pop_front();
                return true;
            }
            if (_queue.empty()) {
                const std::chrono::nanoseconds _left = _deadline - std::chrono::steady_clock::now();
                if (_left <= std::chrono::milliseconds(0)) {
                    break;
                }
                _condition_variable.wait_for(_lock, _left, [] { return _stop || !_queue.empty(); });
                continue;
            }
            _queue.pop_front();
        }

        return false;
    }

protected:
    inline static void SetUpTestSuite()
    {
        _midi_in = std::make_unique<RtMidiIn>();
        _midi_out = std::make_unique<RtMidiOut>();

        const unsigned in_count = _midi_in->getPortCount();
        const unsigned out_count = _midi_out->getPortCount();
        if (0 >= in_count)
            throw std::runtime_error("Invalid input MIDI port");
        if (1 >= out_count)
            throw std::runtime_error("Invalid output MIDI port");

        std::cout << std::endl;
        std::cout << "Using input MIDI port " << _midi_in->getPortName(0) << "\n";
        std::cout << "Using output MIDI port " << _midi_out->getPortName(1) << "\n";
        std::cout << std::endl;

        _midi_in->openPort(0);
        _midi_in->ignoreTypes(false, true, true);
        _midi_in->setCallback(&gtest_hardware::midi_in_cb, nullptr);
        _midi_out->openPort(1);
    }

    inline static void TearDownTestSuite()
    {
        {
            std::lock_guard<std::mutex> _lock(_mutex);
            _stop = true;
        }
        _condition_variable.notify_all();
        _midi_in.reset();
        _midi_out.reset();
    }

    inline void SetUp() override
    {
        std::lock_guard<std::mutex> _lock(_mutex);
        _queue.clear();
        _stop = false;
    }

    inline static std::mt19937 random_device;

private:
    inline static std::vector<std::uint8_t> _accumulated;
    inline static std::unique_ptr<RtMidiIn> _midi_in;
    inline static std::unique_ptr<RtMidiOut> _midi_out;
    inline static std::mutex _mutex;
    inline static std::condition_variable _condition_variable;
    inline static std::deque<std::vector<std::uint8_t>> _queue;
    inline static bool _stop;

    inline static void midi_in_cb(double, std::vector<std::uint8_t>* message, void*)
    {
        std::lock_guard<std::mutex> _lock(_mutex);

        for (const std::uint8_t _byte : *message) {
            if (_byte == 0xF8 || _byte == 0xFA || _byte == 0xFB || _byte == 0xFC || _byte == 0xFE) {
                continue;
            }

            if (_accumulated.empty()) {
                if (_byte != 0xF0) {
                    continue;
                }
                _accumulated.push_back(0xF0);
                continue;
            }

            _accumulated.push_back(_byte);

            if (_byte == 0xF7) {
                _queue.push_back(_accumulated);
                _accumulated.clear();
            }
        }

        _condition_variable.notify_one();
    }
};

}
