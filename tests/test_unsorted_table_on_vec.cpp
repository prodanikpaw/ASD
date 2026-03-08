#include <gtest/gtest.h>
#include "Unsorted_Table_On_Vec.h"
#include <string>


TEST(UnsortedTableTest, ConstructorAndEmpty) {
    Unsorted_Table_On_Vec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}


TEST(UnsortedTableTest, Insert) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_FALSE(table.is_empty());
    EXPECT_EQ(table.size(), 3);
}


TEST(UnsortedTableTest, Find) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_TRUE(table.find(3).empty()); // Несуществующий ключ
}


TEST(UnsortedTableTest, Consist) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(2));
    EXPECT_FALSE(table.consist(3));
}

// Тест для замены существующего элемента (insert с существующим ключом)
TEST(UnsortedTableTest, InsertExistingKey) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.insert(1, "uno"); // Замена значения

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "uno");
}

// Тест для replace метода
TEST(UnsortedTableTest, Replace) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.replace(1, "uno");

    EXPECT_EQ(table.find(1), "uno");

    // Попытка заменить несуществующий ключ
    table.replace(2, "two");
    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.consist(2));
}


TEST(UnsortedTableTest, Erase) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    table.erase(2);

    EXPECT_EQ(table.size(), 2);
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));

    // Удаление несуществующего ключа
    table.erase(4);
    EXPECT_EQ(table.size(), 2);
}


TEST(UnsortedTableTest, Clear) {
    Unsorted_Table_On_Vec<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.size(), 3);

    table.clear();

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_FALSE(table.consist(1));
}

// Тест с ключами типа string
TEST(UnsortedTableTest, StringKeys) {
    Unsorted_Table_On_Vec<std::string, int> table;

    table.insert("one", 1);
    table.insert("two", 2);
    table.insert("three", 3);

    EXPECT_EQ(table.size(), 3);
    EXPECT_TRUE(table.consist("two"));
    EXPECT_EQ(table.find("two"), 2);

    table.erase("two");
    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist("two"));
}


TEST(UnsortedTableTest, DoubleValues) {
    Unsorted_Table_On_Vec<int, double> table;

    table.insert(1, 1.5);
    table.insert(2, 2.7);

    EXPECT_DOUBLE_EQ(table.find(1), 1.5);
    EXPECT_DOUBLE_EQ(table.find(2), 2.7);
}

// Комплексный тест с несколькими операциями
TEST(UnsortedTableTest, ComplexOperations) {
    Unsorted_Table_On_Vec<int, std::string> table;

    // Вставка элементов
    for (int i = 0; i < 5; ++i) {
        table.insert(i, "value_" + std::to_string(i));
    }

    EXPECT_EQ(table.size(), 5);

    // Проверка всех элементов
    for (int i = 0; i < 5; ++i) {
        EXPECT_TRUE(table.consist(i));
        EXPECT_EQ(table.find(i), "value_" + std::to_string(i));
    }

    // Замена некоторых элементов
    table.replace(1, "new_value_1");
    table.replace(3, "new_value_3");

    EXPECT_EQ(table.find(1), "new_value_1");
    EXPECT_EQ(table.find(3), "new_value_3");

    // Удаление четных элементов
    for (int i = 0; i < 5; i += 2) {
        table.erase(i);
    }

    EXPECT_EQ(table.size(), 2);
    EXPECT_FALSE(table.consist(0));
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(3));
    EXPECT_FALSE(table.consist(4));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}