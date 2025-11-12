#include <gtest/gtest.h>
#include"dsu.h"

TEST(DSUTest, BasicOperations) {
    DSU dsu(5);

  
    EXPECT_EQ(dsu.find(0), 0);
    EXPECT_EQ(dsu.find(1), 1);
    EXPECT_EQ(dsu.find(2), 2);

    
    dsu.unite(0, 1);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_NE(dsu.find(0), dsu.find(2));

    
    dsu.unite(1, 2);
    EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(DSUTest, SelfUnion) {
    DSU dsu(3);

    dsu.unite(1, 1);
    EXPECT_EQ(dsu.find(1), 1);
}

TEST(DSUTest, OutOfBounds) {
    DSU dsu(3);


    EXPECT_THROW(dsu.find(-1), std::out_of_range);
    EXPECT_THROW(dsu.find(5), std::out_of_range);
    EXPECT_THROW(dsu.unite(0, 10), std::out_of_range);
}

TEST(DSUTest, RankOptimization) {
    DSU dsu(100);

    for (int i = 0; i < 50; i++) {
        dsu.unite(i, i + 1);
    }

    
    int root = dsu.find(0);
    for (int i = 1; i <= 50; i++) {
        EXPECT_EQ(dsu.find(i), root);
    }
}
TEST(DSUTest, PathCompression) {
    DSU dsu(10);

    
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    
    int root4 = dsu.find_op(4);

   
    EXPECT_EQ(dsu.find_op(0), root4);
    EXPECT_EQ(dsu.find_op(1), root4);
    EXPECT_EQ(dsu.find_op(2), root4);
    EXPECT_EQ(dsu.find_op(3), root4);
    EXPECT_EQ(dsu.find_op(4), root4);
}

TEST(DSUTest, PathCompressionComplexTree) {
    DSU dsu(20);

    
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    
    dsu.unite(5, 6);
    dsu.unite(6, 7);
    dsu.unite(7, 8);

    
    dsu.unite(2, 7);

    int root = dsu.find_op(8);

    
    for (int i = 0; i <= 8; i++) {
        EXPECT_EQ(dsu.find_op(i), root);
    }
}

TEST(DSUTest, PathCompressionEfficiency) {
    DSU dsu(1000);

    // Создаем длинную цепочку
    for (int i = 0; i < 999; i++) {
        dsu.unite(i, i + 1);
    }

    
    int lastRoot = dsu.find_op(999);

    
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(dsu.find_op(i), lastRoot);
    }
}

TEST(DSUTest, PathCompressionAfterMultipleOperations) {
    DSU dsu(10);

    
    dsu.unite(0, 1);
    dsu.unite(2, 3);
    dsu.unite(4, 5);
    dsu.unite(6, 7);

   
    int root1 = dsu.find_op(1);
    int root3 = dsu.find_op(3);

    
    dsu.unite(1, 3);
    dsu.unite(5, 7);
    dsu.unite(1, 5);

    
    int finalRoot = dsu.find_op(7);

    
    for (int i = 0; i <= 7; i++) {
        EXPECT_EQ(dsu.find_op(i), finalRoot);
    }
}

TEST(DSUTest, PathCompressionWithRank) {
    DSU dsu(10);

    
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    
    dsu.unite(5, 6);
    dsu.unite(6, 7);
    dsu.unite(7, 8);

    
    dsu.unite(0, 5);

    
    int root1 = dsu.find_op(0);
    int root2 = dsu.find_op(4);
    int root3 = dsu.find_op(5);
    int root4 = dsu.find_op(8);

    EXPECT_EQ(root1, root2);
    EXPECT_EQ(root1, root3);
    EXPECT_EQ(root1, root4);

    
    EXPECT_NE(dsu.find_op(9), root1);
}

TEST(DSUTest, CompareFindAndFindOp) {
    DSU dsu(10);

   
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(4, 5);
    dsu.unite(0, 3);

   
    EXPECT_EQ(dsu.find(0), dsu.find_op(0));
    EXPECT_EQ(dsu.find(1), dsu.find_op(1));
    EXPECT_EQ(dsu.find(2), dsu.find_op(2));
    EXPECT_EQ(dsu.find(3), dsu.find_op(3));
    EXPECT_EQ(dsu.find(4), dsu.find_op(4));
    EXPECT_EQ(dsu.find(5), dsu.find_op(5));
}