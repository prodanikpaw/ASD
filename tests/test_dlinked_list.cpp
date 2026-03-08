#include <gtest/gtest.h>
#include <vector>
#include "dlinked_list.h"

// ==================== “≈—“€ Œœ“»Ã»«»–Œ¬¿ÕÕ€’ Ã≈“ŒƒŒ¬ ====================

TEST(DLinkedListOptimized, PopBackIsO1) {
    DLinkedList<int> list;
    for (int i = 0; i < 1000; i++) {
        list.push_back(i);
    }

    list.pop_back();
    EXPECT_EQ(list.size(), 999);

    if (!list.is_empty()) {
        auto it = list.rbegin();
        EXPECT_EQ(*it, 998);
    }
}

TEST(DLinkedListOptimized, PopByNodeIsO1) {
    DLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    auto node = list.find(3);
    ASSERT_NE(node, nullptr);

    list.pop(node);
    EXPECT_EQ(list.size(), 3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 4);
}

TEST(DLinkedListOptimized, InsertBeforeNodeIsO1) {
    DLinkedList<int> list;
    list.push_back(1);
    list.push_back(3);
    list.push_back(4);

    auto node = list.find(3);
    ASSERT_NE(node, nullptr);

    list.insert(node, 2);
    EXPECT_EQ(list.size(), 4);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
}

TEST(DLinkedListOptimized, InsertOptimizedByDistance) {
    DLinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i * 10);
    }

    list.insert(1, 5);
    EXPECT_EQ(list.size(), 11);

    list.insert(9, 85);
    EXPECT_EQ(list.size(), 12);

    auto it = list.begin();
    ++it; 
    EXPECT_EQ(*it, 5);

    it = list.begin();
    for (int i = 0; i < 9; i++) {
        ++it;
    }
    EXPECT_EQ(*it, 85);
}


TEST(DLinkedListOptimized, PopOptimizedByDistance) {
    DLinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }

    list.pop(1);
    EXPECT_EQ(list.size(), 9);

    list.pop(7);
    EXPECT_EQ(list.size(), 8);

    auto it = list.begin();
    ++it; 
    EXPECT_EQ(*it, 2);

    it = list.begin();
    for (int i = 0; i < 7; i++) {
        ++it;
    }
    EXPECT_EQ(*it, 9);
}

// ==================== “≈—“€ »“≈–¿“Œ–Œ¬ ====================


TEST(DLinkedListIterator, EmptyList) {
    DLinkedList<int> empty_list;

    EXPECT_EQ(empty_list.begin(), empty_list.end());

    auto it = empty_list.begin();
    EXPECT_THROW(*it, std::logic_error);
}

TEST(DLinkedListIterator, CanRead) {
    DLinkedList<int> list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i + 1);  // 1, 2, 3, ..., 10
    }

    int expected_val = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected_val);
        expected_val++;
    }
    EXPECT_EQ(expected_val, 11);

}

TEST(DLinkedListIterator, CanWrite) {
    DLinkedList<int> list;

    for (int i = 0; i < 5; i++) {
        list.push_back(i);
    }

    int multiplier = 10;
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = *it * multiplier;
    }

    auto it = list.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20); 
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 40);  
}

#include <gtest/gtest.h>
#include <vector>



TEST(DLinkedListIterator, ReadFromBeforeEnd) {
    DLinkedList<int> list;

    list.push_back(5);
    list.push_back(10);
    list.push_back(15);
    list.push_back(20);
    list.push_back(25);

    int val = 25;
    for (auto it = list.rbegin();it != list.rend();it--)
    {

        EXPECT_EQ(*it, val);
        val -= 5;
    }

    /*++it;
    ++it; 
    ++it; 
    ++it;

    EXPECT_EQ(*it, 25); 
    --it;
    EXPECT_EQ(*it, 20);

    
    --it; 
    EXPECT_EQ(*it, 15);

    --it;  
    EXPECT_EQ(*it, 10);

    --it;  
    EXPECT_EQ(*it, 5);
    */
    
}


TEST(DLinkedListIterator, WriteFromMiddleBackward) {
    DLinkedList<int> list;

    
    for (int i = 1; i <= 5; i++) {
        list.push_back(i);
    }

   
    auto it = list.begin();
    ++it;
    ++it;

    EXPECT_EQ(*it, 3);

   
    *it = 300;
    EXPECT_EQ(*it, 300);

    --it;
    *it = 200; 
    EXPECT_EQ(*it, 200);

    --it; 
    *it = 100;
    EXPECT_EQ(*it, 100);

    auto check_it = list.begin();
    EXPECT_EQ(*check_it, 100);    
    ++check_it;
    EXPECT_EQ(*check_it, 200);   
    ++check_it;
    EXPECT_EQ(*check_it, 300);   
    ++check_it;
    EXPECT_EQ(*check_it, 4);     
    ++check_it;
    EXPECT_EQ(*check_it, 5);    
}