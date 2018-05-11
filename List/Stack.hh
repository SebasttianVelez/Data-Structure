#include "List.hh"

template <typename T>

class Stack {
private:
  List<T> storage;

public:
  Stack() : storage() {}

  int size() const { return storage.size(); }
  int push(T e) { storage.push_back(e); }
  void pop() { storage.pop_back(); }
  const T top() const { return storage.back(); }
  void print() { storage.print(); }
};
