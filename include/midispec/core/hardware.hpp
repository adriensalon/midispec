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

        const std::size_t _in_count = _midi_in->getPortCount();
        EXPECT_GT(_in_count, 0);
        const std::size_t _out_count = _midi_out->getPortCount();
        EXPECT_GT(_out_count, 0);

        std::cout << "\nAvailable MIDI input ports:" << std::endl;
        for (unsigned i = 0; i < _in_count; ++i) {
            std::cout << "  [" << i << "] " << _midi_in->getPortName(i) << std::endl;
        }
        std::cout << "\nAvailable MIDI output ports:" << std::endl;
        for (unsigned i = 0; i < _out_count; ++i) {
            std::cout << "  [" << i << "] " << _midi_out->getPortName(i) << std::endl;
        }
        
        std::cout << std::endl;
        std::size_t _in_index = 0;
        std::size_t _out_index = 0;
        std::cout << "Select input port index: ";
        std::cin >> _in_index;
        EXPECT_LT(_in_index, _in_count);
        std::cout << "Select output port index: ";
        std::cin >> _out_index;
        EXPECT_LT(_out_index, _out_count);

        std::cout << "\nUsing input: " << _midi_in->getPortName(_in_index) << "\n";
        std::cout << "Using output: " << _midi_out->getPortName(_out_index) << "\n\n";

        _midi_in->openPort(_in_index);
        _midi_in->ignoreTypes(false, true, true);
        _midi_in->setCallback(&gtest_hardware::midi_in_cb, nullptr);
        _midi_out->openPort(_out_index);
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
