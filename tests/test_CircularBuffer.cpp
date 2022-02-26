#include <exception>
#include <vector>
#include <gtest/gtest.h>
#include "CircularBuffer.h"


TEST(CircularBuffer, DefaultConstructorTimeType)
{
    CircularBuffer<std::time_t, 3> buffer;
    ASSERT_EQ(buffer.size(),0);
    ASSERT_TRUE(buffer.empty());
    ASSERT_FALSE(buffer.full());

    std::time_t t = std::time(nullptr);
    buffer.push(t);
    ASSERT_EQ(buffer.size(),1);
    ASSERT_FALSE(buffer.empty());
    ASSERT_FALSE(buffer.full());
    ASSERT_EQ(buffer.front(), t);
}

TEST(CircularBuffer, DefaultConstructorUintType)
{
    CircularBuffer<uint, 3> buffer;
    ASSERT_EQ(buffer.size(),0);
    ASSERT_TRUE(buffer.empty());
    ASSERT_FALSE(buffer.full());

    uint value = 10;
    buffer.push(value);
    ASSERT_EQ(buffer.size(),1);
    ASSERT_FALSE(buffer.empty());
    ASSERT_FALSE(buffer.full());
    ASSERT_EQ(buffer.front(), value);
}


TEST(CircularBuffer, PushAndPopOperations)
{
    CircularBuffer<int, 3> buffer;

    // Fill all the buffer
    std::vector<int> values {1,2,3};

    for (auto val: values) {
        buffer.push(val);
        std::cout << buffer << std::endl;
        ASSERT_EQ(buffer.front(),val);
        ASSERT_FALSE(buffer.empty());
    }
    
    // Now the vector should be full
    ASSERT_TRUE(buffer.full());
    ASSERT_EQ(buffer.size(),3);
    ASSERT_EQ(buffer.getTail(),buffer.getHead());

    // Add more values to overwrite the current ones
    std::vector<int> values2 {4,5,6};

    for (auto val: values2) {
        buffer.push(val);
        std::cout << buffer << std::endl;
        ASSERT_EQ(buffer.front(),val);
        ASSERT_FALSE(buffer.empty());
        ASSERT_TRUE(buffer.full());
        // Tail and Head should be equal
        ASSERT_EQ(buffer.getTail(),buffer.getHead());
    }

    // Now read the values and free the buffer
    for (int i=0; i<3; i++) {
        int tail_value = buffer.back();
        std::cout << buffer << std::endl;
        ASSERT_EQ(buffer.pop(),tail_value);
    }

    // Buffer should be empty
    std::cout << buffer << std::endl;
    ASSERT_TRUE(buffer.empty());
    ASSERT_EQ(buffer.getTail(),buffer.getHead());
}

TEST(CircularBuffer, getElementsAllCases)
{
    CircularBuffer<uint, 6> buffer;
    std::vector<uint> v_test;

    std::vector<int> values {1,2,3,4,5,6,7,8,9,10};

    for (uint i=0; i<values.size(); i++) {
        buffer.push(values[i]);
        std::cout << buffer << std::endl;

        v_test.clear();
        if (values[i] == 1 || values[i] == 2){
            // Should return false, not enough elements
            ASSERT_FALSE(buffer.getElements(v_test,3));
        } else {
            ASSERT_TRUE(buffer.getElements(v_test,3));
            std::cout << ">>> " 
                << v_test[0] << ","
                << v_test[1] << ","
                << v_test[2] << std::endl;
            ASSERT_EQ(v_test[0],values[i]);
            ASSERT_EQ(v_test[1],values[i-1]);
            ASSERT_EQ(v_test[2],values[i-2]);
        }
    }
}