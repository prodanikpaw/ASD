#include <gtest/gtest.h>
#include "TVector.h"

TEST(IteratorTest, EmptyVectorIteration) {
    TVector<int> emptyVec;

    EXPECT_EQ(emptyVec.begin(), emptyVec.end());

    EXPECT_EQ(emptyVec.end() - emptyVec.begin(), 0);
}

TEST(IteratorTest, IteratorCanRead) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    TVector<int>::Iterator beginIt = vec.begin();
    EXPECT_EQ(*beginIt, 1);

    TVector<int>::Iterator endIt = vec.end();
    TVector<int>::Iterator lastIt = endIt - 1;
    EXPECT_EQ(*lastIt, 5);

    ++beginIt;
    EXPECT_EQ(*beginIt, 2);
}

TEST(IteratorTest, IteratorCanWrite) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    TVector<int>::Iterator it = vec.begin();
    *it = 100;
    EXPECT_EQ(vec[0], 100);

    TVector<int>::Iterator lastIt = vec.end() - 1;
    *lastIt = 500;
    EXPECT_EQ(vec[4], 500);
}