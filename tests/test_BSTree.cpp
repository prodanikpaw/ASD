#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "BSTree.h"

TEST(BSTreeTest, EmptyTree) {
    BSTree<int, std::string> tree;

    EXPECT_TRUE(tree.isEmpty());
}

TEST(BSTreeTest, InsertOneElement) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");

    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.consist(5));
    EXPECT_EQ(tree.find(5), "five");
}

TEST(BSTreeTest, InsertMultipleElements) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");

    EXPECT_TRUE(tree.consist(5));
    EXPECT_TRUE(tree.consist(1));
    EXPECT_TRUE(tree.consist(3));
    EXPECT_TRUE(tree.consist(7));
    EXPECT_TRUE(tree.consist(2));
    EXPECT_TRUE(tree.consist(4));
}

TEST(BSTreeTest, FindExistingKey) {
    BSTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");

    EXPECT_EQ(tree.find(10), "ten");
    EXPECT_EQ(tree.find(20), "twenty");
    EXPECT_EQ(tree.find(30), "thirty");

    std::cout << "\n=== Вывод дерева ===\n";
    std::cout << "to_string (прямой обход): " << tree.to_string() << "\n";
    std::cout << "to_string_sorted (сортированный): " << tree.to_string_sorted() << "\n";
    std::cout << "====================\n";
}

TEST(BSTreeTest, FindNonExistingKey) {
    BSTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_THROW(tree.find(30), std::logic_error);
    EXPECT_THROW(tree.find(999), std::logic_error);
}

TEST(BSTreeTest, ConsistKey) {
    BSTree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_TRUE(tree.consist(10));
    EXPECT_TRUE(tree.consist(20));
    EXPECT_FALSE(tree.consist(30));
    EXPECT_FALSE(tree.consist(999));
}

TEST(BSTreeTest, UpdateExistingKey) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");

    EXPECT_THROW(tree.insert(5, "FIVE"), std::logic_error);
    EXPECT_EQ(tree.find(5), "five");

    tree.replace(5, "FIVE");
    EXPECT_EQ(tree.find(5), "FIVE");
}

TEST(BSTreeTest, EraseLeaf) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(4, "four");

    tree.erase(4);
    EXPECT_FALSE(tree.consist(4));
    EXPECT_TRUE(tree.consist(5));
    EXPECT_TRUE(tree.consist(3));
    EXPECT_TRUE(tree.consist(7));
    EXPECT_TRUE(tree.consist(1));
}

TEST(BSTreeTest, EraseNodeWithOneChild) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(4, "four");
    tree.insert(6, "six");


    tree.erase(7);
    EXPECT_FALSE(tree.consist(7));
    EXPECT_TRUE(tree.consist(6));
    EXPECT_TRUE(tree.consist(5));
    EXPECT_TRUE(tree.consist(3));
}

TEST(BSTreeTest, EraseNodeWithTwoChildren) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(1, "one");
    tree.insert(4, "four");
    tree.insert(6, "six");
    tree.insert(8, "eight");

    tree.erase(5);
    EXPECT_FALSE(tree.consist(5));
    EXPECT_TRUE(tree.consist(3));
    EXPECT_TRUE(tree.consist(7));
    EXPECT_TRUE(tree.consist(1));
    EXPECT_TRUE(tree.consist(4));
    EXPECT_TRUE(tree.consist(6));
    EXPECT_TRUE(tree.consist(8));
}

TEST(BSTreeTest, EraseOnlyNode) {
    BSTree<int, std::string> tree;

    tree.insert(42, "answer");

    tree.erase(42);
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_FALSE(tree.consist(42));
}

TEST(BSTreeTest, EraseNonExisting) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(10, "ten");

    EXPECT_THROW(tree.erase(999), std::logic_error);
}

TEST(BSTreeTest, PreorderTraversal) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");

    std::cout << "\n=== prints ===\n";
    std::cout << "to_string (line): " << tree.to_string() << "\n";
    std::cout << "to_string_sorted (sort): " << tree.to_string_sorted() << "\n";
    std::cout << "====================\n";
}

TEST(BSTreeTest, ManyElements) {
    BSTree<int, int> tree;

    for (int i = 0; i < 100; i++) {
        tree.insert(i, i * i);
    }

    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(tree.consist(i));
        EXPECT_EQ(tree.find(i), i * i);
    }
}

TEST(BSTreeTest, EraseAllElements) {
    BSTree<int, std::string> tree;

    for (int i = 0; i < 10; i++) {
        tree.insert(i, "value" + std::to_string(i));
    }

    for (int i = 0; i < 10; i++) {
        tree.erase(i);
    }

    EXPECT_TRUE(tree.isEmpty());
}

TEST(BSTreeTest, ComplexScenario) {
    BSTree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");

    tree.erase(7);
    EXPECT_FALSE(tree.consist(7));

    tree.erase(5);
    EXPECT_FALSE(tree.consist(5));

    EXPECT_TRUE(tree.consist(1));
    EXPECT_TRUE(tree.consist(3));
    EXPECT_TRUE(tree.consist(2));
    EXPECT_TRUE(tree.consist(4));

    tree.insert(8, "eight");
    tree.insert(9, "nine");

    EXPECT_TRUE(tree.consist(8));
    EXPECT_TRUE(tree.consist(9));
}

TEST(BSTreeTest, CopyConstructor) {
    BSTree<int, std::string> tree1;
    tree1.insert(5, "five");
    tree1.insert(3, "three");
    tree1.insert(7, "seven");

    BSTree<int, std::string> tree2(tree1);

    EXPECT_TRUE(tree2.consist(5));
    EXPECT_TRUE(tree2.consist(3));
    EXPECT_TRUE(tree2.consist(7));
    EXPECT_EQ(tree2.find(5), "five");

    tree2.replace(5, "FIVE");
    EXPECT_EQ(tree1.find(5), "five");
    EXPECT_EQ(tree2.find(5), "FIVE");
}

TEST(BSTreeTest, AssignmentOperator) {
    BSTree<int, std::string> tree1;
    tree1.insert(5, "five");
    tree1.insert(3, "three");

    BSTree<int, std::string> tree2;
    tree2.insert(10, "ten");

    tree2 = tree1;

    EXPECT_TRUE(tree2.consist(5));
    EXPECT_TRUE(tree2.consist(3));
    EXPECT_FALSE(tree2.consist(10));
}

TEST(BSTreeTest, ReplaceNonExistingKey) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");

    EXPECT_THROW(tree.replace(10, "ten"), std::logic_error);
}

TEST(BSTreeTest, FindInEmptyTree) {
    BSTree<int, std::string> tree;

    EXPECT_THROW(tree.find(5), std::logic_error);
}

TEST(BSTreeTest, EraseInEmptyTree) {
    BSTree<int, std::string> tree;

    EXPECT_THROW(tree.erase(5), std::logic_error);
}

TEST(BSTreeTest, InsertDuplicateKey) {
    BSTree<int, std::string> tree;
    tree.insert(5, "five");

    EXPECT_THROW(tree.insert(5, "FIVE"), std::logic_error);
    EXPECT_EQ(tree.find(5), "five");
}