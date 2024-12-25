#include <gtest/gtest.h>
#include "custom_vector.h"
#include <string>

struct S
{
    int a_;
    double b_;
    std::string c_;

    S(int a, double b, std::string&& c):
        a_(a),
        b_(b),
        c_(std::move(c)) {}

    int a()
    {
        return a_;
    }

    double b()
    {
        return b_;
    }

    std::string c()
    {
        return c_;
    }
};

TEST(Constructor, default)
{
    ctm::vector<int> vec;
    ctm::vector<double> vec2;
    ctm::vector<std::string> vec3;
    ctm::vector<S> vec4; 
}

TEST(Constructor, count)
{
    int ssize = 5;
    ctm::vector<int> vec(ssize);
    EXPECT_EQ(vec.size(), ssize); 

}
