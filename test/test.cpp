#include <gtest/gtest.h>
#include "custom_vector.h"
#include <string>

struct T
{
    int a_;
    double b_;
    std::string c_;

    T(int a, double b, std::string&& c):
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

TEST(Initialization, default)
{
    ctm::vector<int> vec;
    ctm::vector<double> vec2;
    ctm::vector<std::string> vec3;
    ctm::vector<T> vec4; 
}
