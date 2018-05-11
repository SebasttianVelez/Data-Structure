#include "List.hh"
#include <iostream>
template <typename T>

class Queue {
private:
  List<T> storage;

public:
  Queue() : storage() {}

  int size() const { return storage.size(); }
  int push(T e) { storage.push_back(e); }
  const T front() const { return storage.front(); }
  void pop() { storage.pop_front(); }
  const T back() const { return storage.back(); }
  void print() { storage.print(); }
};
