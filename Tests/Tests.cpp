#include <gtest/gtest.h>
#include "../Bubbles/Bubbles.hpp"

TEST(Bubbles_Tests, set_n_get)
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorSorter vs;
    vs.set_vec(v);
    std::vector<int> v1 = vs.get_vec();
    ASSERT_EQ(v.size(), v1.size());
    for (int i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v1[i], v1[i]);
    }
}

TEST(Bubbles_Tests, constructor)
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorSorter vs(vec);
    std::vector<int> vec1 = vs.get_vec();
    ASSERT_EQ(vec.size(), vec1.size());
    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], vec1[i]);
    }
}

TEST(Bubbles_Tests, copy_constructor)
{
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    VectorSorter vs(vec);
    VectorSorter vs1 = vs.get_vec();
    ASSERT_EQ(vs.size(), vs1.size());
    for (int i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vs.at(i), vs1.at(i));
    }
}

TEST(Bubbles_Tests, bubblesort)
{
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2{8, 7, 5, 9, 1, 2, 3, 6, 10, 4};
    VectorSorter vs(v2);
    vs.bubblesort();
    v2 = vs.get_vec();
    ASSERT_EQ(v1.size(), v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}

TEST(Bubbles_Tests, ins_sort)
{
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2{8, 7, 5, 9, 1, 2, 3, 6, 10, 4};
    VectorSorter vs(v2);
    vs.bubblesort();
    v2 = vs.get_vec();
    ASSERT_EQ(v1.size(), v2.size());
    for (int i = 0; i < v1.size(); ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}