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

TEST(Data, Default)
{
    ctm::vector<int> vec({1,2,3,4,5});
    EXPECT_EQ(vec.data(), vec.begin());
}

TEST(Iterators, Default)
{
    ctm::vector<int> vec({1,2,3,4,5});

    auto it = vec.begin();
    auto it_end = vec.end();
    EXPECT_EQ(*(it_end-1), 5);
    int i = 0;

    while (it != it_end)
    {
        EXPECT_EQ(*it, vec[i]);
        ++it;
        ++i;
    }

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};
    
    auto it2 = vec2.begin();
    auto it2_end = vec2.end();
    EXPECT_EQ((it2_end-1)->a(), 3);
    EXPECT_EQ((it2_end-1)->b(), 6.0);
    EXPECT_EQ((it2_end-1)->c(), "c");

    for (std::size_t i2=0; i2<vec2.size(); ++i2)
    {
        EXPECT_EQ(it2 -> a(), vec2[i2].a());
        EXPECT_EQ(it2 -> b(), vec2[i2].b());
        EXPECT_EQ(it2 -> c(), vec2[i2].c());
        ++it2;
    }
}

// Capacity
TEST(Empty, Default)
{
    ctm::vector<int> vec({1,2,3,4,5});
    EXPECT_FALSE(vec.empty());
    
    ctm::vector<int> vec2{};
    EXPECT_TRUE(vec2.empty());

    ctm::vector<int> vec3 = {};
    EXPECT_TRUE(vec3.empty());

    ctm::vector<int> vec4 = {1};
    EXPECT_FALSE(vec4.empty());
}

TEST(Size, Default)
{
    ctm::vector<int> vec{{1,2,3,4,5}};
    EXPECT_EQ(vec.size(), 5);

    vec.push_back(6);
    EXPECT_EQ(vec.size(), 6);

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
        EXPECT_EQ(vec.size(), i+7);
    }

    int size = vec.size();

    for (int i = 0; i < 10; ++i)
    {
        vec.pop_back();
        EXPECT_EQ(vec.size(), size-(i+1));
    }
}

// max size not tested as it is a constant to type T

TEST(ReserveAndCapacity, Default)
{   
    ctm::vector<int> vec{};
    EXPECT_EQ(vec.capacity(), 0);

    vec.push_back(1);
    EXPECT_EQ(vec.capacity(), 1);

    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.capacity(), 4);
    vec.push_back(4);
    EXPECT_EQ(vec.capacity(), 4);

    vec.reserve(10);
    EXPECT_EQ(vec.capacity(), 10);

    for (int i = 0; i < 6; ++i)
    {
        vec.push_back(i);
        EXPECT_EQ(vec.capacity(), 10);
    }

    vec.push_back(11);
    EXPECT_EQ(vec.capacity(), 20);
}

// Modifiers

TEST(Clear, Default)
{
    ctm::vector<int> vec{{1,2,3,4,5}};
    EXPECT_EQ(vec.capacity(), 8);
    EXPECT_EQ(vec.size(), 5);
    vec.clear();
    EXPECT_EQ(vec.capacity(), 8);
    EXPECT_EQ(vec.size(), 0);

    for (int i = 0; i < 100; ++i)
    {
        vec.push_back(i);
    }

    EXPECT_EQ(vec.capacity(), 128);
    EXPECT_EQ(vec.size(), 100);
    vec.clear();
    EXPECT_EQ(vec.capacity(), 128);
    EXPECT_EQ(vec.size(), 0);

    ctm::vector<S> vec2{S{1,2.0,"a"},
        S{2,4.0,"b"},
        S{3,6.0,"c"}};
    EXPECT_EQ(vec2.capacity(), 4);
    EXPECT_EQ(vec2.size(), 3);
    vec2.clear();
    EXPECT_EQ(vec2.capacity(), 4);
    EXPECT_EQ(vec2.size(), 0);
}

TEST(Insert, PassByReference)
{
    ctm::vector<int> vec{{1,2}};
    int a = 5;
    vec.insert(vec.begin(), a);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);

    int b = 10;
    vec.insert(vec.end(), b);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 10);
}

TEST(Insert, PassByMove)
{
    ctm::vector<int> vec{{1,2}};
    vec.insert(vec.begin(), 5);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);

    vec.insert(vec.end(), 10);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 4);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 10);
}

TEST(Insert, CountAndValue)
{
    ctm::vector<int> vec{{1,2}};
    vec.insert(vec.begin(), 2, 5);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 4);


    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 1);
    EXPECT_EQ(vec[3], 2);

    vec.insert(vec.end(), 2, 10);
    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec.capacity(), 8);

    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 1);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 10);
    EXPECT_EQ(vec[5], 10);
}

TEST(Insert, InputIt)
{
    ctm::vector<int> vec;
    std::initializer_list init = {1,2,3,4};
    vec.insert(vec.begin(), init.begin(), init.end());

    for (int i = 0; i < init.size(); ++i)
    {
        EXPECT_EQ(vec[i], init.begin()[i]); 
    }
    EXPECT_EQ(vec.size(), init.size());
    EXPECT_EQ(vec.capacity(), 4);

    std::initializer_list init2 = {5,6,7};
    vec.insert(vec.begin()+1, init2.begin(), init2.end()-1);

    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec.capacity(), 8);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 6);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 3);
    EXPECT_EQ(vec[5], 4);

    vec.insert(vec.end(), init2.begin()+1, init2.end());
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 6);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 3);
    EXPECT_EQ(vec[5], 4);
    EXPECT_EQ(vec[6], 6);
    EXPECT_EQ(vec[7], 7);
}

TEST(Insert, InitializerList)
{
    ctm::vector<int> vec;
    std::initializer_list init = {1,2,3,4};
    vec.insert(vec.begin(), init);

    for (int i = 0; i < init.size(); ++i)
    {
        EXPECT_EQ(vec[i], init.begin()[i]); 
    }
    EXPECT_EQ(vec.size(), init.size());
    EXPECT_EQ(vec.capacity(), 4);

    std::initializer_list init2 = {5,6};
    vec.insert(vec.begin()+1, init2);

    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec.capacity(), 8);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 6);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 3);
    EXPECT_EQ(vec[5], 4);

    vec.insert(vec.end(), {6,7});
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 6);
    EXPECT_EQ(vec[3], 2);
    EXPECT_EQ(vec[4], 3);
    EXPECT_EQ(vec[5], 4);
    EXPECT_EQ(vec[6], 6);
    EXPECT_EQ(vec[7], 7);
}

TEST(Emplace, Default)
{
    ctm::vector<S> vec;
    vec.emplace(vec.begin(), 2, 4.0, "b");
    vec.emplace(vec.begin(), 1, 2.0, "a");
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.capacity(), 2);
    EXPECT_EQ(vec[0].a(), 1);
    EXPECT_EQ(vec[0].b(), 2.0);
    EXPECT_EQ(vec[0].c(), "a");
    EXPECT_EQ(vec[1].a(), 2);
    EXPECT_EQ(vec[1].b(), 4.0);
    EXPECT_EQ(vec[1].c(), "b");

    ctm::vector<S> vec2{{1, 2.0, "a"}};
    vec2.emplace(vec2.end(), 2, 4.0, "b");
    vec2.emplace(vec2.end(), 3, 6.0, "c");
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2.capacity(), 4);
    EXPECT_EQ(vec2[0].a(), 1);
    EXPECT_EQ(vec2[0].b(), 2.0);
    EXPECT_EQ(vec2[0].c(), "a");
    EXPECT_EQ(vec2[1].a(), 2);
    EXPECT_EQ(vec2[1].b(), 4.0);
    EXPECT_EQ(vec2[1].c(), "b");
    EXPECT_EQ(vec2[2].a(), 3);
    EXPECT_EQ(vec2[2].b(), 6.0);
    EXPECT_EQ(vec2[2].c(), "c");
}

TEST(Erase, Default)
{
    ctm::vector<int> vec{{1,2,3,4}};

    vec.erase(vec.begin());
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
}

TEST(Erase, Iterator)
{
    ctm::vector<int> vec{{1,2,3,4,5,6}};
    vec.erase(vec.begin()+1, vec.begin()+3);
    EXPECT_EQ(vec.size(),4);
    EXPECT_EQ(vec.capacity(), 8);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 5);
    EXPECT_EQ(vec[3], 6);
}

TEST(PushBack, Default)
{
    ctm::vector<int> vec;

    for (int i = 0; i < 50; ++i)
    {
        vec.push_back(i);
        EXPECT_EQ(vec.size(), i+1);
        
        if  (vec.size() == 1)
        {
            EXPECT_EQ(vec.capacity(), 1);
        }
        else if (vec.size() <= 2)
        {
            EXPECT_EQ(vec.capacity(), 2);
        }
        else if (vec.size() <= 4)
        {
            EXPECT_EQ(vec.capacity(), 4);
        }
        else if (vec.size() <= 8)
        {
            EXPECT_EQ(vec.capacity(), 8);
        }
        else if (vec.size() <= 16)
        {
            EXPECT_EQ(vec.capacity(), 16);
        }
        else if (vec.size() <= 32)
        {
            EXPECT_EQ(vec.capacity(), 32);
        }
        else
        {
            EXPECT_EQ(vec.capacity(), 64);
        }
    }

    for (int i = 0; i < 50; ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(PushBack, MoveOperator)
{
    ctm::vector<int> vec;

    for (int i = 0; i < 50; ++i)
    {
        int a = i;
        vec.push_back(std::move(a));
        EXPECT_EQ(vec.size(), i+1);
        
        if  (vec.size() == 1)
        {
            EXPECT_EQ(vec.capacity(), 1);
        }
        else if (vec.size() <= 2)
        {
            EXPECT_EQ(vec.capacity(), 2);
        }
        else if (vec.size() <= 4)
        {
            EXPECT_EQ(vec.capacity(), 4);
        }
        else if (vec.size() <= 8)
        {
            EXPECT_EQ(vec.capacity(), 8);
        }
        else if (vec.size() <= 16)
        {
            EXPECT_EQ(vec.capacity(), 16);
        }
        else if (vec.size() <= 32)
        {
            EXPECT_EQ(vec.capacity(), 32);
        }
        else
        {
            EXPECT_EQ(vec.capacity(), 64);
        }
    }

    for (int i = 0; i < 50; ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(EmplaceBack, Default)
{
    ctm::vector<S> vec{{1, 2.0, "a"}, {2, 4.0, "b"}};

    S& added_s = vec.emplace_back(3, 6.0, "c");
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), 3);

    EXPECT_EQ(vec[0].a(), 1);
    EXPECT_EQ(vec[0].b(), 2.0);
    EXPECT_EQ(vec[0].c(), "a");
    EXPECT_EQ(vec[1].a(), 2);
    EXPECT_EQ(vec[1].b(), 4.0);
    EXPECT_EQ(vec[1].c(), "b");
    EXPECT_EQ(vec[2].a(), 3);
    EXPECT_EQ(vec[2].b(), 6.0);
    EXPECT_EQ(vec[2].c(), "c");

    EXPECT_EQ(added_s.a(), 3);
    EXPECT_EQ(added_s.b(), 6.0);
    EXPECT_EQ(added_s.c(), "c");

    added_s.a_ = 5;
    EXPECT_EQ(vec[2].a(), 5);
}

TEST(PopBack, Default)
{
    ctm::vector<int> vec;

    for (int i = 0; i < 50; ++i)
    {
        vec.push_back(i);
    }

    for (int i = 0; i < 50; ++i)
    {
        vec.pop_back();
        EXPECT_EQ(vec.size(), 50-i-1);
        EXPECT_EQ(vec.capacity(), 64);
    }
}

TEST(Resize, Default)
{
    //test reduce and increase size;
    ctm::vector<int> vec;

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    vec.resize(20);
    EXPECT_EQ(vec.size(), 20);
    EXPECT_EQ(vec.capacity(), 32);

    for (int i = 0; i < 20; ++i)
    {
        if (i < 10)
        {
            EXPECT_EQ(vec[i], i);
        }
        else
        {
            EXPECT_EQ(vec[i], 0);
        }
    }

    ctm::vector<int> vec2;

    for (int i = 0; i < 20; ++i)
    {
        vec2.push_back(i);
    }

    vec2.resize(10);
    EXPECT_EQ(vec2.size(), 10);
    EXPECT_EQ(vec2.capacity(), 32);

    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(Resize, CountWithDefault)
{
    //test reduce and increase size;
    ctm::vector<int> vec;

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    vec.resize(20, 5);
    EXPECT_EQ(vec.size(), 20);
    EXPECT_EQ(vec.capacity(), 32);

    for (int i = 0; i < 20; ++i)
    {
        if (i < 10)
        {
            EXPECT_EQ(vec[i], i);
        }
        else
        {
            EXPECT_EQ(vec[i], 5);
        }
    }

    ctm::vector<int> vec2;

    for (int i = 0; i < 20; ++i)
    {
        vec2.push_back(i);
    }

    vec2.resize(10, 5);
    EXPECT_EQ(vec2.size(), 10);
    EXPECT_EQ(vec2.capacity(), 32);

    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(Swap, Default)
{
    ctm::vector<int> vec, vec2;

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    for (int i = 0; i < 100; ++i)
    {
        vec2.push_back(i+100);
    }

    vec.swap(vec2);
    
    EXPECT_EQ(vec.size(), 100);
    EXPECT_EQ(vec.capacity(), 128);
    EXPECT_EQ(vec2.size(), 10);
    EXPECT_EQ(vec2.capacity(), 16);

    for (int i = 0; i < 100; ++i)
    {
        EXPECT_EQ(vec[i], i+100);
    }

    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(vec2[i], i);
    }
}




