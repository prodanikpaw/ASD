// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include "../lib_TVector/Tvector.h"
#include "../lib_Hash_Tables/Hash_Table_C.h"
#include "../lib_Heap/Heap.h"
#include "../lib_Priority_Queue/Priority_Queue.h"

int main() 
{
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

  std::cout << "=== Heap Sort Demonstration ===" << std::endl;

  TVector<int> v1 = { 64, 34, 25, 12, 22, 11, 90 };
  std::cout << "Original: " << v1 << std::endl;
  heapSort(v1);
  std::cout << "Sorted asc: " << v1 << std::endl;

  TVector<int> v2 = { 5, 2, 8, 1, 9, 3 };
  std::cout << "\nOriginal: " << v2 << std::endl;
  heapSort(v2);
  std::cout << "Sorted asc: " << v2 << std::endl;

  std::cout << "\nMinHeap insert: 4, 10, 8, 5, 1" << std::endl;
  Heap<int> mh;
  mh.insert(4);
  mh.insert(10);
  mh.insert(8);
  mh.insert(5);
  mh.insert(1);
  std::cout << "Heap: ";
  mh.print();

  std::cout << "Erase root" << std::endl;
  mh.erase();
  std::cout << "Heap after erase: ";
  mh.print();

  std::cout << "Erase root again" << std::endl;
  mh.erase();
  std::cout << "Heap after erase: ";
  mh.print();

  std::cout << "Extract remaining: ";
  while (!mh.isEmpty()) {
      std::cout << mh.extractTop() << " ";
  }
  std::cout << std::endl;


  int times[] = { 0, 5, 20, 25, 40, 45, 95, 97, 120, 121, 140 };
  string names[] = { "Ivanov", "Petrov", "Voronin", "Sidorov", "Vasiliev",
                    "Mikhailov", "Borisov", "Vladimirov", "Fedorov", "Shishkin", "Nesterov" };
  int priorities[] = { 2, 3, 2, 1, 2, 3, 1, 1, 2, 1, 2 };

  int patientCount = 11;
  PriorityQueue<string> pq;
  TVector<string> receptionOrder;

  int currentTime = 0;
  int doctorFreeAt = 0;
  int nextPacient = 0;

  while (nextPacient < patientCount || !pq.empty()) {
      while (nextPacient < patientCount && times[nextPacient] <= currentTime) {
          pq.push(names[nextPacient], priorities[nextPacient]);
          nextPacient++;
      }
      if (currentTime >= doctorFreeAt && !pq.empty()) {
          receptionOrder.push_back(pq.extractTop());
          doctorFreeAt = currentTime + 20;
      }

      int nextTime;

      if (nextPacient < patientCount) {
          nextTime = times[nextPacient];
      }
      else {
          nextTime = 999999;
      }

      if (nextTime < doctorFreeAt) {
          currentTime = nextTime;
      }
      else {
          currentTime = doctorFreeAt;
      }
  }

  cout << "Patient reception order:\n";
  for (int i = 0; i < receptionOrder.getsize(); i++) {
      cout << receptionOrder[i] << endl;
    }

  return 0;
}

#endif  // EASY_EXAMPLE
