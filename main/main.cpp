// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
#include "../lib_Skiplist/Skiplist.h"
#include "../lib_easy_example/easy_example.h"
#include "../lib_TVector/Tvector.h"

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
}

#endif  // EASY_EXAMPLE
