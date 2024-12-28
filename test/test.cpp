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

    int a() const
    {
        return a_;
    }

    double b() const
    {
        return b_;
    }

    std::string c() const
    {
        return c_;
    }
};

TEST(Constructor, Default)
{
    ctm::vector<int> vec;
    ctm::vector<double> vec2;
    ctm::vector<std::string> vec3;
    ctm::vector<S> vec4; 
}

TEST(Constructor, Count)
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

TEST(Constructor, CountAndDefault)
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

TEST(Constructor, PassByReference)
{
    ctm::vector<int> vec{{1,2,3}};
    ctm::vector<int> vec2(vec);
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    EXPECT_EQ(vec.size(), vec2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec[i], vec2[i]);
    }

    ctm::vector<S> vec3{S{1, 2.0, "a"}, S{2, 4.0, "b"}};
    ctm::vector<S> vec4(vec3);
    EXPECT_EQ(vec3.capacity(), vec4.capacity());
    EXPECT_EQ(vec3.size(), vec4.size());

    for (int i = 0; i < vec3.size(); ++i)
    {
        EXPECT_EQ(vec3[i].a(), vec4[i].a());
        EXPECT_EQ(vec3[i].b(), vec4[i].b());
        EXPECT_EQ(vec3[i].c(), vec4[i].c());
    }
}

TEST(Constructor, MoveConstructor)
{
    ctm::vector<int> vec{{1,2,3}};
    ctm::vector<int> vec2(std::move(vec));
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    EXPECT_EQ(vec.size(), vec2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec[i], i+1);
    }

    ctm::vector<S> vec3{S{1, 2.0, "a"}, S{2, 4.0, "b"}};
    ctm::vector<S> vec4(std::move(vec3));
    EXPECT_EQ(vec3.capacity(), vec4.capacity());
    EXPECT_EQ(vec3.size(), vec4.size());

    for (int i = 0; i < vec4.size(); ++i)
    {
        if (i == 0) 
        {
            EXPECT_EQ(vec4[i].a(), 1);
            EXPECT_EQ(vec4[i].b(), 2.0);
            EXPECT_EQ(vec4[i].c(), "a");
        }
        else
        {
            EXPECT_EQ(vec4[i].a(), 2);
            EXPECT_EQ(vec4[i].b(), 4.0);
            EXPECT_EQ(vec4[i].c(), "b");
        }
    }
}

TEST(Constructor, InitializerList)
{
    std::initializer_list<int> initlist = {1,2,3};
    ctm::vector<int> vec{initlist};
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), initlist.size());

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], initlist.begin()[i]);
    }

    std::initializer_list<S> initlist2 = 
    {
        S{1, 2.0 , "a"},
        S{2, 4.0, "b"},
        S{3, 6.0, "c"}
    };

    ctm::vector<S> vec2(initlist2);
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), initlist2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        auto it = initlist2.begin()[i];
        EXPECT_EQ(vec2[i].a(), it.a());
        EXPECT_EQ(vec2[i].b(), it.b());
        EXPECT_EQ(vec2[i].c(), it.c());
    }
}

TEST(Destructor, Default)
{
    ctm::vector<int> vec{{1,2,3,4,5}};
    EXPECT_NO_THROW([&vec](){
        vec.~vector<int>();
    }());
}

TEST(OperatorEqual, PassByReference)
{
    ctm::vector<int> vec{{1,2,3}};
    ctm::vector<int> vec2 = vec;
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    EXPECT_EQ(vec.size(), vec2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec[i], vec2[i]);
    }

    ctm::vector<S> vec3{S{1, 2.0, "a"}, S{2, 4.0, "b"}};
    ctm::vector<S> vec4 = vec3;
    EXPECT_EQ(vec3.capacity(), vec4.capacity());
    EXPECT_EQ(vec3.size(), vec4.size());

    for (int i = 0; i < vec3.size(); ++i)
    {
        EXPECT_EQ(vec3[i].a(), vec4[i].a());
        EXPECT_EQ(vec3[i].b(), vec4[i].b());
        EXPECT_EQ(vec3[i].c(), vec4[i].c());
    }
}

TEST(OperatorEqual, MoveConstructor)
{
    ctm::vector<int> vec{{1,2,3}};
    ctm::vector<int> vec2 = std::move(vec);
    EXPECT_EQ(vec.capacity(), vec2.capacity());
    EXPECT_EQ(vec.size(), vec2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec[i], i+1);
    }

    ctm::vector<S> vec3{S{1, 2.0, "a"}, S{2, 4.0, "b"}};
    ctm::vector<S> vec4 = std::move(vec3);
    EXPECT_EQ(vec3.capacity(), vec4.capacity());
    EXPECT_EQ(vec3.size(), vec4.size());

    for (int i = 0; i < vec4.size(); ++i)
    {
        if (i == 0) 
        {
            EXPECT_EQ(vec4[i].a(), 1);
            EXPECT_EQ(vec4[i].b(), 2.0);
            EXPECT_EQ(vec4[i].c(), "a");
        }
        else
        {
            EXPECT_EQ(vec4[i].a(), 2);
            EXPECT_EQ(vec4[i].b(), 4.0);
            EXPECT_EQ(vec4[i].c(), "b");
        }
    }
}

TEST(OperatorEqual, InitializerList)
{
    std::initializer_list<int> initlist = {1,2,3};
    ctm::vector<int> vec = initlist;
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), initlist.size());

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], initlist.begin()[i]);
    }

    std::initializer_list<S> initlist2 = 
    {
        S{1, 2.0 , "a"},
        S{2, 4.0, "b"},
        S{3, 6.0, "c"}
    };

    ctm::vector<S> vec2 = initlist2;
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), initlist2.size());

    for (int i = 0; i < vec2.size(); ++i)
    {
        auto it = initlist2.begin()[i];
        EXPECT_EQ(vec2[i].a(), it.a());
        EXPECT_EQ(vec2[i].b(), it.b());
        EXPECT_EQ(vec2[i].c(), it.c());
    }
}

TEST(At, Default)
{
    ctm::vector<int> vec{5};

    for (int i = 0; i < vec.size(); ++i)
    {
        vec.at(i) = i+1;
    }

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec.at(i), i+1);
    }


    EXPECT_THROW([&vec](){
        int temp = vec.at(5);
    }(), std::out_of_range);

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2.at(i).a(), i+1);
        EXPECT_EQ(vec2.at(i).b(), 2.0*(i+1));
        EXPECT_EQ(vec2.at(i).c(), std::string(1, 'a'+i));
    }

    EXPECT_THROW([&vec2](){
        S temp = vec2.at(5);
    }(), std::out_of_range);
}

TEST(At, Const)
{
    const ctm::vector<int> vec{{1,2,3,4,5}};

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec.at(i), i+1);
    }

    EXPECT_THROW([&vec](){
        int temp = vec.at(5);
    }(), std::out_of_range);

    const ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2.at(i).a(), i+1);
        EXPECT_EQ(vec2.at(i).b(), 2.0*(i+1));
        EXPECT_EQ(vec2.at(i).c(), std::string(1, 'a'+i));
    }

    EXPECT_THROW([&vec2](){
        S temp = vec2.at(5);
    }(), std::out_of_range);
}

TEST(OperatorSquareBracket, Default)
{
    ctm::vector<int> vec{{1,2,3,4,5}};

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], i+1);
    }

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2[i].a(), i+1);
        EXPECT_EQ(vec2[i].b(), 2.0*(i+1));
        EXPECT_EQ(vec2[i].c(), std::string(1, 'a'+i));
    }
}

TEST(OperatorSquareBracket, Const)
{
    ctm::vector<int> vec{{1,2,3,4,5}};

    for (int i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], i+1);
    }

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};

    for (int i = 0; i < vec2.size(); ++i)
    {
        EXPECT_EQ(vec2[i].a(), i+1);
        EXPECT_EQ(vec2[i].b(), 2.0*(i+1));
        EXPECT_EQ(vec2[i].c(), std::string(1, 'a'+i));
    }
}

TEST(Front, Default)
{
    ctm::vector<int> vec{{1,2,3,4,5}};
    EXPECT_EQ(vec.front(), 1);

    vec.front() = 10;
    EXPECT_EQ(vec.front(), 10);

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};

    EXPECT_EQ(vec2.front().a(), 1);
    EXPECT_EQ(vec2.front().b(), 2.0);
    EXPECT_EQ(vec2.front().c(), "a");

    vec2.front() = S{4,8.0,"d"};
    EXPECT_EQ(vec2.front().a(), 4);
    EXPECT_EQ(vec2.front().b(), 8.0);
    EXPECT_EQ(vec2.front().c(), "d");
}

TEST(Back, Default)
{
    ctm::vector<int> vec{{1,2,3,4,5}};
    EXPECT_EQ(vec.back(), 5);

    vec.back() = 50;
    EXPECT_EQ(vec.back(), 50);

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};

    EXPECT_EQ(vec2.back().a(), 3);
    EXPECT_EQ(vec2.back().b(), 6.0);
    EXPECT_EQ(vec2.back().c(), "c");

    vec2.back() = S{4,8.0,"d"};
    EXPECT_EQ(vec2.back().a(), 4);
    EXPECT_EQ(vec2.back().b(), 8.0);
    EXPECT_EQ(vec2.back().c(), "d");
}
