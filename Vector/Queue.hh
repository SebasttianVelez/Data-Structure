#include "Vector.hh"

template <typename T>

class Queue {
private:
  Vector<T> storage;

public:
  Queue() : storage() {}
  int size() { return storage.size(); }
  void push(T e) { storage.push_back(e); }
  const T front() const { return storage.front(); }
  void pop() { storage.pop_front(); }
  const T back() const { return storage.back(); }
  void print() { return storage.print(); }
};
