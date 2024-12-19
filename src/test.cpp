#include <gtest/gtest.h>
#include "custom_vector.h"
#include <string>

void vector_init()
{
    ctm::vector<int> vec;
}

TEST(Initialization, int)
{
    EXPECT_NO_THROW(vector_init());
}