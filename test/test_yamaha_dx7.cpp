#include <sysex/core/hardware.hpp>
#include <sysex/yamaha_dx7.hpp>

namespace sysex {
namespace yamaha_dx7 {

    struct yamaha_dx7 : public hardware {

        inline static std::mt19937 random_device;

        void save_to_voice_1(const integral<std::uint8_t, 0, 15> device)
        {
            std::vector<std::uint8_t> _sent;

            encode_button_memory_select_internal(_sent, device, true);
            encode_button_memory_select_internal(_sent, device, false);
            encode_button_store(_sent, device, true);
            encode_button_1(_sent, device, true);
            encode_button_1(_sent, device, false);
            encode_button_store(_sent, device, false);
            send(_sent);
        }

        void transmit_bank_read_voice_1(const integral<std::uint8_t, 0, 15> device, patch& voice_1)
        {
            std::vector<std::uint8_t> _sent;
            std::vector<std::uint8_t> _received;
            std::array<patch, 32> _bank;

            encode_button_function(_sent, device, true);
            encode_button_function(_sent, device, false);
            encode_button_1(_sent, device, true);
            encode_button_1(_sent, device, false);
            for (std::size_t _index = 0; _index < 3; ++_index) {
                encode_button_8(_sent, device, true);
                encode_button_8(_sent, device, false);
            }
            encode_button_yes(_sent, device, true);
            encode_button_yes(_sent, device, false);
            send(_sent);

            receive(_received);
            EXPECT_TRUE(decode_bank(_received, device, _bank));
            voice_1 = _bank[0];
        }
    };

    TEST_F(yamaha_dx7, op_eg_rate_1)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_rate_1;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_rate_1 = _op_eg_rate_1.min_value;
        encode_op_eg_rate_1(_encoded, _device, _op, _op_eg_rate_1);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_1, _voice_1_data.op_eg_rate_1[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_rate_1 = _op_eg_rate_1.random(random_device);
        encode_op_eg_rate_1(_encoded, _device, _op, _op_eg_rate_1);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_1, _voice_1_data.op_eg_rate_1[_op.value()]);

        _op = _op.max_value;
        _op_eg_rate_1 = _op_eg_rate_1.max_value;
        encode_op_eg_rate_1(_encoded, _device, _op, _op_eg_rate_1);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_1, _voice_1_data.op_eg_rate_1[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_rate_2)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_rate_2;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_rate_2 = _op_eg_rate_2.min_value;
        encode_op_eg_rate_2(_encoded, _device, _op, _op_eg_rate_2);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_2, _voice_1_data.op_eg_rate_2[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_rate_2 = _op_eg_rate_2.random(random_device);
        encode_op_eg_rate_2(_encoded, _device, _op, _op_eg_rate_2);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_2, _voice_1_data.op_eg_rate_2[_op.value()]);

        _op = _op.max_value;
        _op_eg_rate_2 = _op_eg_rate_2.max_value;
        encode_op_eg_rate_2(_encoded, _device, _op, _op_eg_rate_2);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_2, _voice_1_data.op_eg_rate_2[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_rate_3)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_rate_3;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_rate_3 = _op_eg_rate_3.min_value;
        encode_op_eg_rate_3(_encoded, _device, _op, _op_eg_rate_3);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_3, _voice_1_data.op_eg_rate_3[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_rate_3 = _op_eg_rate_3.random(random_device);
        encode_op_eg_rate_3(_encoded, _device, _op, _op_eg_rate_3);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_3, _voice_1_data.op_eg_rate_3[_op.value()]);

        _op = _op.max_value;
        _op_eg_rate_3 = _op_eg_rate_3.max_value;
        encode_op_eg_rate_3(_encoded, _device, _op, _op_eg_rate_3);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_3, _voice_1_data.op_eg_rate_3[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_rate_4)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_rate_4;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_rate_4 = _op_eg_rate_4.min_value;
        encode_op_eg_rate_4(_encoded, _device, _op, _op_eg_rate_4);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_4, _voice_1_data.op_eg_rate_4[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_rate_4 = _op_eg_rate_4.random(random_device);
        encode_op_eg_rate_4(_encoded, _device, _op, _op_eg_rate_4);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_4, _voice_1_data.op_eg_rate_4[_op.value()]);

        _op = _op.max_value;
        _op_eg_rate_4 = _op_eg_rate_4.max_value;
        encode_op_eg_rate_4(_encoded, _device, _op, _op_eg_rate_4);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_rate_4, _voice_1_data.op_eg_rate_4[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_level_1)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_level_1;
        patch _voice_1_data;
        
        _op = _op.min_value;
        _op_eg_level_1 = _op_eg_level_1.min_value;
        encode_op_eg_level_1(_encoded, _device, _op, _op_eg_level_1);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_1, _voice_1_data.op_eg_level_1[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_level_1 = _op_eg_level_1.random(random_device);
        encode_op_eg_level_1(_encoded, _device, _op, _op_eg_level_1);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_1, _voice_1_data.op_eg_level_1[_op.value()]);

        _op = _op.max_value;
        _op_eg_level_1 = _op_eg_level_1.max_value;
        encode_op_eg_level_1(_encoded, _device, _op, _op_eg_level_1);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_1, _voice_1_data.op_eg_level_1[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_level_2)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_level_2;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_level_2 = _op_eg_level_2.min_value;
        encode_op_eg_level_2(_encoded, _device, _op, _op_eg_level_2);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_2, _voice_1_data.op_eg_level_2[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_level_2 = _op_eg_level_2.random(random_device);
        encode_op_eg_level_2(_encoded, _device, _op, _op_eg_level_2);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_2, _voice_1_data.op_eg_level_2[_op.value()]);

        _op = _op.max_value;
        _op_eg_level_2 = _op_eg_level_2.max_value;
        encode_op_eg_level_2(_encoded, _device, _op, _op_eg_level_2);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_2, _voice_1_data.op_eg_level_2[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_level_3)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_level_3;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_level_3 = _op_eg_level_3.min_value;
        encode_op_eg_level_3(_encoded, _device, _op, _op_eg_level_3);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_3, _voice_1_data.op_eg_level_3[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_level_3 = _op_eg_level_3.random(random_device);
        encode_op_eg_level_3(_encoded, _device, _op, _op_eg_level_3);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_3, _voice_1_data.op_eg_level_3[_op.value()]);

        _op = _op.max_value;
        _op_eg_level_3 = _op_eg_level_3.max_value;
        encode_op_eg_level_3(_encoded, _device, _op, _op_eg_level_3);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_3, _voice_1_data.op_eg_level_3[_op.value()]);
    }

    TEST_F(yamaha_dx7, op_eg_level_4)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 5> _op;
        integral<std::uint8_t, 0, 99> _op_eg_level_4;
        patch _voice_1_data;

        _op = _op.min_value;
        _op_eg_level_4 = _op_eg_level_4.min_value;
        encode_op_eg_level_4(_encoded, _device, _op, _op_eg_level_4);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_4, _voice_1_data.op_eg_level_4[_op.value()]);

        _op = _op.random(random_device);
        _op_eg_level_4 = _op_eg_level_4.random(random_device);
        encode_op_eg_level_4(_encoded, _device, _op, _op_eg_level_4);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_4, _voice_1_data.op_eg_level_4[_op.value()]);

        _op = _op.max_value;
        _op_eg_level_4 = _op_eg_level_4.max_value;
        encode_op_eg_level_4(_encoded, _device, _op, _op_eg_level_4);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_op_eg_level_4, _voice_1_data.op_eg_level_4[_op.value()]);
    }

    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //

    TEST_F(yamaha_dx7, algorithm_mode)
    {
        std::vector<std::uint8_t> _encoded;
        integral<std::uint8_t, 0, 15> _device = 0;
        integral<std::uint8_t, 0, 31> _algorithm_mode;
        patch _voice_1_data;

        _algorithm_mode = _algorithm_mode.min_value;
        encode_algorithm_mode(_encoded, _device, _algorithm_mode);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_algorithm_mode, _voice_1_data.algorithm_mode);

        _algorithm_mode = _algorithm_mode.random(random_device);
        encode_algorithm_mode(_encoded, _device, _algorithm_mode);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_algorithm_mode, _voice_1_data.algorithm_mode);

        _algorithm_mode = _algorithm_mode.max_value;
        encode_algorithm_mode(_encoded, _device, _algorithm_mode);
        send(_encoded);
        save_to_voice_1(_device);
        transmit_bank_read_voice_1(_device, _voice_1_data);
        EXPECT_EQ(_algorithm_mode, _voice_1_data.algorithm_mode);
    }
}
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}