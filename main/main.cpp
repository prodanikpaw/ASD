// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include "../lib_TVector/Tvector.h"
#include "../lib_Unsorted_Table_On_tree/Unsorted_Table_On_tree.h"
#include "../lib_Tree/Tree.h"

int main() {
  int a, b;
  float result;

  a = 1; b = 4;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  a = 1; b = 0;

  try {
      result = division(a, b);
      std::cout << a << " / " << b << " = "
          << std::setprecision(2) << result << std::endl;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }

  return 0;
  std::cout << "\n=== TESTING SKIP LIST WITH AUTOMATIC LEVEL GENERATION ===\n\n";

  SkipList<std::string, double> skipList(5);

  std::cout << "Inserting 10 elements with random levels:\n";

  skipList.insert("key1", 12.15);
  skipList.insert("key2", 4.0);
  skipList.insert("key3", 15.3);
  skipList.insert("key4", 40.4);
  skipList.insert("key5", 50.5);
  skipList.insert("key6", 7.523);
  skipList.insert("key7", 70.7);
  skipList.insert("key8", 80.8);
  skipList.insert("key9", 90.9);
  skipList.insert("key10", 100.0);

  std::cout << "Total inserted: 10 elements\n";
  std::cout << "Current maximum level: " << skipList.getCurrentLevel() << "\n\n";

  std::cout << "=== RESULT ===\n";
  skipList.print();

  std::cout << "\n=== SEARCH ===\n";
  std::string keys[] = { "key3", "key6", "key11" };

  for (const auto& key : keys) {
      std::cout << "Searching for '" << key << "': ";
      auto found = skipList.find(key);
      if (found) {
          std::cout << "FOUND -> " << found->data.first << " : "
              << found->data.second << " (level " << found->level << ")\n";
      }
      else {
          std::cout << "NOT FOUND\n";
      }
  }

  std::cout << "\n=== UPDATE ===\n";
  std::cout << "Updating key5 from 50.5 to 55.5\n";
  skipList.insert("key5", 55.5);

  auto found = skipList.find("key5");
  if (found) {
      std::cout << "New value: " << found->data.second << "\n";
  }


  std::cout << "===============================================\n";
  std::cout << "  НЕУПОРЯДОЧЕННАЯ ТАБЛИЦА НА ДЕРЕВЕ\n";
  std::cout << "  ДЕМОНСТРАЦИЯ ВСЕХ 4 ОБХОДОВ\n";
  std::cout << "===============================================\n\n";

  // ==================== СОЗДАНИЕ ТАБЛИЦЫ ====================
  UnorderedTreeTable<int, std::string> table;

  // ==================== ВСТАВКА ЭЛЕМЕНТОВ ====================
  std::cout << "1. ВСТАВКА ЭЛЕМЕНТОВ\n";
  std::cout << "   Вставляем: 5->five, 1->one, 3->three, 7->seven, 2->two, 4->four\n";

  try {
      table.insert(5, "five");
      table.insert(1, "one");
      table.insert(3, "three");
      table.insert(7, "seven");
      table.insert(2, "two");
      table.insert(4, "four");

      std::cout << "   ✓ Все элементы вставлены успешно\n";
      std::cout << "   Размер таблицы: " << table.size() << "\n\n";
  }
  catch (const std::exception& e) {
      std::cout << "   ✗ Ошибка: " << e.what() << "\n\n";
  }

  // ==================== КРАСИВЫЙ ВЫВОД ДЕРЕВА ====================
  std::cout << "2. СТРУКТУРА ДЕРЕВА\n";
  table.printTree();

  // ==================== ВСЕ 4 ОБХОДА ====================
  std::cout << "3. ВСЕ 4 ВИДА ОБХОДА\n";
  std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

  std::cout << "   [1] ПРЯМОЙ ОБХОД (Pre-order):     ";
  table.printAllTraversals();
  std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

}

#endif  // EASY_EXAMPLE
