#include "algorithms.h"
#include <gtest/gtest.h>

TEST(BracketCheckerTest, valid_simple_expressions) {
    EXPECT_TRUE(check_breckets("()"));
    EXPECT_TRUE(check_breckets("[]"));
    EXPECT_TRUE(check_breckets("{}"));
}
TEST(BracketCheckerTest, valid_nested_expressions) {
    EXPECT_TRUE(check_breckets("({[]})"));
    EXPECT_TRUE(check_breckets("[({})]"));
    EXPECT_TRUE(check_breckets("{([])}"));
}
TEST(BracketCheckerTest, invalid_unmatched_closing) {
    EXPECT_FALSE(check_breckets(")"));
    EXPECT_FALSE(check_breckets("())"));
}

TEST(HasCycleTest, empty_list) {
    List<int> list;
    EXPECT_FALSE(has_cycle(list));
}

TEST(HasCycleTest, single_element_no_cycle) {
    List<int> list;
    list.push_back(1);
    EXPECT_FALSE(has_cycle(list));
}

TEST(HasCycleTest, multiple_elements_no_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_FALSE(has_cycle(list));
}

TEST(HasCycleTest, cycle_at_beginning) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    auto first = it.get_current();
    ++it; ++it;
    auto last = it.get_current(); 
    last->next = first;

    EXPECT_TRUE(has_cycle(list));
    last->next = nullptr;
}

TEST(HasCycleTest, cycle_in_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    // Создаем цикл: 4->2 (3->2 по индексам)
    auto it = list.begin();
    auto node2 = (++it).get_current();
    ++it; ++it;
    auto node4 = it.get_current();
    node4->next = node2;

    EXPECT_TRUE(has_cycle(list));

    node4->next = nullptr;
}

TEST(HasCycleTest, self_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    // Создаем цикл: 2->2
    auto it = list.begin();
    auto node2 = (++it).get_current();
    node2->next = node2; // Сам на себя

    EXPECT_TRUE(has_cycle(list));

    
    node2->next = nullptr;
}

TEST(HasCycleTest, two_elements_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    // Создаем цикл: 1->2->1
    auto it = list.begin();
    auto first = it.get_current(); 
    auto second = (++it).get_current();
    second->next = first; // 2 -> 1

    EXPECT_TRUE(has_cycle(list));

    
    second->next = nullptr;
}


TEST(HasCycleTest, long_list_no_cycle) {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.push_back(i);
    }
    EXPECT_FALSE(has_cycle(list));
}

TEST(HasCycleTest, long_list_with_cycle) {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.push_back(i);
    }

    // Создаем цикл в середине: 99 -> 50
    auto it = list.begin();
    // Находим узел 50 (индекс 50)
    for (int i = 0; i < 50; i++) ++it;
    auto middle = it.get_current();

    // Находим узел 99 (последний)
    it = list.begin();
    for (int i = 0; i < 99; i++) ++it;
    auto last = it.get_current();

    // Создаем цикл: 99 -> 50
    last->next = middle;

    EXPECT_TRUE(has_cycle(list));

    
    last->next = nullptr;
}
//------------------------
TEST(HasCycleReverseTest, simple_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    // Создаем цикл: 4->2
    auto it = list.begin();
    auto node2 = (++it).get_current();
    ++it; ++it;
    auto node4 = it.get_current();

    node4->next = node2; // 4 -> 2

    bool result = has_cycle_reverse(list);
    EXPECT_TRUE(result);

    // Разрываем цикл
    node4->next = nullptr;
}

TEST(HasCycleReverseTest, full_cycle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Создаем цикл: 3->1
    auto it = list.begin();
    auto first = it.get_current();
    ++it; ++it;
    auto last = it.get_current();

    last->next = first; // 3 -> 1

    bool result = has_cycle_reverse(list);
    EXPECT_TRUE(result);

    // Разрываем цикл
    last->next = nullptr;
}

TEST(HasCycleReverseTest, no_cycle_list) {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.push_back(i);
    }

    bool result = has_cycle_reverse(list);
    EXPECT_FALSE(result);
    // Нечего разрывать - цикла нет
}

/*TEST(HasCycleReverseTest, cycle_in_large_list) {
    List<int> list;
    const int SIZE = 50;

    for (int i = 0; i < SIZE; i++) {
        list.push_back(i);
    }

    // Создаем цикл: последний -> средний
    auto it = list.begin();
    for (int i = 0; i < SIZE / 2; i++) ++it;
    Node<int>* middle = it.get_current();

    it = list.begin();
    for (int i = 0; i < SIZE - 1; i++) ++it;
    Node<int>* last = it.get_current();

    last->next = middle; // Создаем цикл

    bool result = has_cycle_reverse(list);
    EXPECT_TRUE(result);

    // Разрываем цикл
    last->next = nullptr;
}*/

//----------------------------------------------------------

TEST(FindCycleNodeTest, empty_list) {
    List<int> list;
    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, nullptr);
}

TEST(FindCycleNodeTest, single_element_no_cycle) {
    List<int> list;
    list.push_back(1);
    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, nullptr);
}

// Основные тесты на циклы
TEST(FindCycleNodeTest, simple_cycle_3_elements) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Создаем цикл: 3 -> 2
    auto it = list.begin();
    auto node2 = (++it).get_current();
    ++it;
    auto node3 = it.get_current();

    node3->next = node2; // 3 -> 2

    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, node2);
    EXPECT_EQ(result->value, 2);

    // Разрываем цикл
    node3->next = nullptr;
}

TEST(FindCycleNodeTest, cycle_in_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    // Создаем цикл: 4 -> 2
    auto it = list.begin();
    auto node2 = (++it).get_current();
    ++it; ++it;
    auto node4 = it.get_current();

    node4->next = node2; // 4 -> 2

    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, node2);
    EXPECT_EQ(result->value, 2);

    // Разрываем цикл
    node4->next = nullptr;
}

TEST(FindCycleNodeTest, full_list_cycle) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Создаем цикл: 30 -> 10
    auto it = list.begin();
    auto first = it.get_current();
    ++it; ++it;
    auto last = it.get_current();

    last->next = first; // 30 -> 10

    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, first);
    EXPECT_EQ(result->value, 10);

    // Разрываем цикл
    last->next = nullptr;
}

// Тест на отсутствие цикла
TEST(FindCycleNodeTest, no_cycle_large_list) {
    List<int> list;
    for (int i = 0; i < 100; i++) {
        list.push_back(i);
    }
    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, nullptr);
    // Нечего разрывать - цикла нет
}

// Тест на цикл в большом списке
TEST(FindCycleNodeTest, cycle_in_large_list) {
    List<int> list;
    const int SIZE = 50;

    for (int i = 0; i < SIZE; i++) {
        list.push_back(i);
    }

    // Создаем цикл: последний -> средний элемент
    auto it = list.begin();
    for (int i = 0; i < SIZE / 2; i++) ++it;
    Node<int>* middle = it.get_current();

    it = list.begin();
    for (int i = 0; i < SIZE - 1; i++) ++it;
    Node<int>* last = it.get_current();

    last->next = middle; // Создаем цикл

    Node<int>* result = find_cycle_node(list);
    EXPECT_EQ(result, middle);
    EXPECT_EQ(result->value, SIZE / 2);

    // Разрываем цикл
    last->next = nullptr;
}