//
// Created by rudi on 27/10/21.
//

#include <gtest/gtest.h>

#include "TestNestedStructure.hpp"
#include "TestPointerStructure.hpp"
#include "TestSimpleStructure.hpp"


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
