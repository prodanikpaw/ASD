// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
//#include "../lib_Skiplist/Skiplist.h"
#include "../lib_easy_example/easy_example.h"
//#include "../lib_TVector/Tvector.h"
//#include "../lib_Unsorted_Table_On_tree/Unsorted_Table_On_tree.h"
//#include "../lib_Tree/Tree.h"
#include "../lib_Hash_Tables/Hash_Table_C.h"

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
}

#endif  // EASY_EXAMPLE
