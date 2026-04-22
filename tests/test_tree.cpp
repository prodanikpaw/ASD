#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "Tree.h"

// ==================== реярш дкъ депебю ====================

TEST(TreeTest, EmptyTree) {
    Tree<int, std::string> tree;

    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
}

TEST(TreeTest, InsertOneElement) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");

    EXPECT_EQ(tree.size(), 1);
    EXPECT_FALSE(tree.empty());
    EXPECT_TRUE(tree.consist(5));
    EXPECT_EQ(tree.find(5), "five");
}

TEST(TreeTest, InsertMultipleElements) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");

    EXPECT_EQ(tree.size(), 6);
    EXPECT_TRUE(tree.consist(5));
    EXPECT_TRUE(tree.consist(1));
    EXPECT_TRUE(tree.consist(3));
    EXPECT_TRUE(tree.consist(7));
    EXPECT_TRUE(tree.consist(2));
    EXPECT_TRUE(tree.consist(4));
}

TEST(TreeTest, FindExistingKey) {
    Tree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");
    tree.insert(30, "thirty");

    EXPECT_EQ(tree.find(10), "ten");
    EXPECT_EQ(tree.find(20), "twenty");
    EXPECT_EQ(tree.find(30), "thirty");
    std::cout << "\n=== 4 printes ===\n";

    std::cout << "1. base (D1): ";
    tree.print_D1();
    std::cout << "\n";

    std::cout << "2. simmetryc (D2): ";
    tree.print_D2();
    std::cout << "\n";

    std::cout << "3. REverse (D3): ";
    tree.print_D3();
    std::cout << "\n";

    std::cout << "4. Wide (W): ";
    tree.print_W();
    std::cout << "\n============\n";


    tree.printTree();
}

TEST(TreeTest, FindNonExistingKey) {
    Tree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_THROW(tree.find(30), std::out_of_range);
    EXPECT_THROW(tree.find(999), std::out_of_range);
}

TEST(TreeTest, ConsistKey) {
    Tree<int, std::string> tree;

    tree.insert(10, "ten");
    tree.insert(20, "twenty");

    EXPECT_TRUE(tree.consist(10));
    EXPECT_TRUE(tree.consist(20));
    EXPECT_FALSE(tree.consist(30));
    EXPECT_FALSE(tree.consist(999));
}

TEST(TreeTest, UpdateExistingKey) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    EXPECT_EQ(tree.size(), 1);

    EXPECT_THROW(tree.insert(5, "FIVE"), std::logic_error);
    EXPECT_EQ(tree.find(5), "five");

    tree.replace(5, "FIVE");
    EXPECT_EQ(tree.find(5), "FIVE");
    EXPECT_EQ(tree.size(), 1);
}

TEST(TreeTest, EraseSimple) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");

    EXPECT_EQ(tree.size(), 3);

    bool erased = tree.erase(1);
    EXPECT_TRUE(erased);
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.consist(1));
    EXPECT_TRUE(tree.consist(5));
    EXPECT_TRUE(tree.consist(3));
}

TEST(TreeTest, EraseRoot) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");

    EXPECT_EQ(tree.size(), 3);

    bool erased = tree.erase(5);
    EXPECT_TRUE(erased);
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.consist(5));
    EXPECT_TRUE(tree.consist(1));
    EXPECT_TRUE(tree.consist(3));
}

TEST(TreeTest, EraseOnlyNode) {
    Tree<int, std::string> tree;

    tree.insert(42, "answer");
    EXPECT_EQ(tree.size(), 1);

    bool erased = tree.erase(42);
    EXPECT_TRUE(erased);
    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
    EXPECT_FALSE(tree.consist(42));
}

TEST(TreeTest, EraseNonExisting) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(10, "ten");

    bool erased = tree.erase(999);
    EXPECT_FALSE(erased);
    EXPECT_EQ(tree.size(), 2);
}


TEST(TreeTest, ClearTree) {
    Tree<int, std::string> tree;

    tree.insert(1, "one");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(4, "four");

    EXPECT_EQ(tree.size(), 4);

    tree.clear();
    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
    EXPECT_FALSE(tree.consist(1));
    EXPECT_FALSE(tree.consist(2));
}

TEST(TreeTest, PreorderTraversal) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");


    std::cout << "\n=== 4 printes ===\n";

    std::cout << "1. base (D1): ";
    tree.print_D1();
    std::cout << "\n";

    std::cout << "2. simmetryc (D2): ";
    tree.print_D2();
    std::cout << "\n";

    std::cout << "3. REverse (D3): ";
    tree.print_D3();
    std::cout << "\n";

    std::cout << "4. Wide (W): ";
    tree.print_W();
    std::cout << "\n============\n";


    tree.printTree();
}


TEST(TreeTest, ManyElements) {
    Tree<int, int> tree;

    for (int i = 0; i < 100; i++) {
        tree.insert(i, i * i);
    }

    EXPECT_EQ(tree.size(), 100);

    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(tree.consist(i));
        EXPECT_EQ(tree.find(i), i * i);
    }
}


TEST(TreeTest, EraseAllElements) {
    Tree<int, std::string> tree;

    for (int i = 0; i < 10; i++) {
        tree.insert(i, "value" + std::to_string(i));
    }

    EXPECT_EQ(tree.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(tree.erase(i));
    }

    EXPECT_TRUE(tree.empty());
}

TEST(TreeTest, ComplexScenario) {
    Tree<int, std::string> tree;

    tree.insert(5, "five");
    tree.insert(1, "one");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(2, "two");
    tree.insert(4, "four");

    EXPECT_EQ(tree.size(), 6);

    EXPECT_TRUE(tree.erase(7));
    EXPECT_EQ(tree.size(), 5);
    EXPECT_FALSE(tree.consist(7));

    EXPECT_TRUE(tree.erase(5));
    EXPECT_EQ(tree.size(), 4);
    EXPECT_FALSE(tree.consist(5));

    EXPECT_TRUE(tree.consist(1));
    EXPECT_TRUE(tree.consist(3));
    EXPECT_TRUE(tree.consist(2));
    EXPECT_TRUE(tree.consist(4));

    tree.insert(8, "eight");
    tree.insert(9, "nine");

    EXPECT_EQ(tree.size(), 6);
    EXPECT_TRUE(tree.consist(8));
    EXPECT_TRUE(tree.consist(9));
}