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
    
    S():
        a_(0),
        b_(0.0),
        c_("") {}

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
    EXPECT_EQ(vec.capacity(), 8);
    EXPECT_EQ(vec.size(), ssize); 

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], 0);
    }

    ctm::vector<S> vec2(ssize);
    EXPECT_EQ(vec2.capacity(), 8);
    EXPECT_EQ(vec2.size(), ssize);

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2[i].a(), 0);
        EXPECT_EQ(vec2[i].b(), 0.0);
        EXPECT_EQ(vec2[i].c(), "");
    }
}

TEST(Constructor, count_default)
{
    int ssize = 5;
    int default_value = 2;
    ctm::vector<int> vec(ssize, 2);
    EXPECT_EQ(vec.capacity(), 8);
    EXPECT_EQ(vec.size(), ssize);

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], 2);
    }

    // S s{1, 2.0, "a"};
    ctm::vector<S> vec2(ssize, S{1, 2.0, "a"});
    EXPECT_EQ(vec2.capacity(), 8);
    EXPECT_EQ(vec2.size(), ssize);

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2[i].a(), 1);
        EXPECT_EQ(vec2[i].b(), 2.0);
        EXPECT_EQ(vec2[i].c(), "a");
    }
}

TEST(Constructor, InputIterator)
{
    std::initializer_list<int> z{1,2,3,4,5};
    ctm::vector<int> vec(z.begin(), z.end());
    EXPECT_EQ(vec.capacity(), 8);
    EXPECT_EQ(vec.size(), z.size());

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], z.begin()[i]);
    }

    std::initializer_list<S> z2{S{1, 2.0, "a"},
        S{2, 4.0, "b"},
        S{3, 6.0, "c"}};
    ctm::vector<S> vec2(z2.begin(), z2.end());
    EXPECT_EQ(vec2.capacity(), 4);
    EXPECT_EQ(vec2.size(), z2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        auto z2_it = z2.begin()[i];
        EXPECT_EQ(vec2[i].a(), z2_it.a());
        EXPECT_EQ(vec2[i].b(), z2_it.b());
        EXPECT_EQ(vec2[i].c(), z2_it.c());
    }
}
