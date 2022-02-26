#include <exception>
#include <vector>
#include <gtest/gtest.h>
#include "EncoderReader.h"

TEST(EncoderReader, OperationalTest)
{
    EncoderReader<int, 9> reader;

    // No Velocity, No Acceleration
    std::vector<int> rawEncoder {0, 0, 0};
    for (auto value: rawEncoder) {
        sleep(1);
        std::cout << "writting value " << value << std::endl;
        reader.writeValue(value);
    }
    
    ASSERT_EQ(reader.getVelocity(),0);
    ASSERT_EQ(reader.getAcceleration(),0);

    // Positive velocity and positive acceleration (speeding motor CW)
    rawEncoder.clear();
    rawEncoder = {1000, 1200, 1500};
        for (auto value: rawEncoder) {
        sleep(1);
        std::cout << "writting value " << value << std::endl;
        reader.writeValue(value);
    }

    ASSERT_GT(reader.getVelocity(),0);
    ASSERT_GT(reader.getAcceleration(),0);

    // Positive velocity and negative acceleration (braking motor CW)
    rawEncoder.clear();
    rawEncoder = {1600, 1650, 1680};
        for (auto value: rawEncoder) {
        sleep(1);
        std::cout << "writting value " << value << std::endl;
        reader.writeValue(value);
    }

    ASSERT_GT(reader.getVelocity(),0);
    ASSERT_LT(reader.getAcceleration(),0);

    // Negative velocity and negative acceleration (speeding motor CCW)
    rawEncoder.clear();
    rawEncoder = {1650, 1500, 1300};
        for (auto value: rawEncoder) {
        sleep(1);
        std::cout << "writting value " << value << std::endl;
        reader.writeValue(value);
    }

    ASSERT_LT(reader.getVelocity(),0);
    ASSERT_LT(reader.getAcceleration(),0);

    // Negative velocity and positive acceleration (braking motor CCW)
    rawEncoder.clear();
    rawEncoder = {1200, 1100, 1050};
        for (auto value: rawEncoder) {
        sleep(1);
        std::cout << "writting value " << value << std::endl;
        reader.writeValue(value);
    }

    ASSERT_LT(reader.getVelocity(),0);
    ASSERT_GT(reader.getAcceleration(),0);

    // Negative velocity and zero acceleration (constant velocity motor CCW)
    rawEncoder.clear();
    rawEncoder = {1000, 900, 800};
        for (auto value: rawEncoder) {
        sleep(1);
        std::cout << "writting value " << value << std::endl;
        reader.writeValue(value);
    }

    ASSERT_LT(reader.getVelocity(),0);
    ASSERT_EQ(reader.getAcceleration(),0);

}
