#include <cassert>
#include <iostream>

template <typename T> class Vector {
private:
  T *storage;   // Contains the elements
  int sz;       // Number of elements in the vector
  int capacity; // Number of elements that can be stored without resizing
public:
  Vector() {
    sz = 0;
    capacity = 5;
    storage = new T[capacity];
  }

  Vector(int c) {
    sz = 0;
    capacity = c;
    storage = new T[capacity];
  }

  /**
   * Returns the number of elements in the vector
   * Complexity: O(1)
   */
  int size() const { return sz; }
  /**
   * Returns the element at position p
   * Complexity: O(1)
   */
  T &at(int p) {
    assert(p >= 0 && p < sz);
    return storage[p];
  }
  const T &at(int p) const {
    assert(p >= 0 && p < sz);
    return storage[p];
  }
  /**
   * Inserts an element at the end.
   * Complexity:
   */
  void push_back(T e) {
    if (sz == capacity) {
      resize();
    }
    storage[sz] = e;
    sz++;
  }

  void push_front(T e) {
    if (sz == capacity) {
      resize();
    }

    int newCapacity = capacity;
    T *newStorage = new T[newCapacity];
    for (int i = 0; i < sz; i++) {
      newStorage[i + 1] = storage[i];
    }
    delete[] storage;
    capacity = newCapacity;
    storage = newStorage;

    storage[0] = e;
    sz++;
  }

  void pop_front() {
    assert(sz > 0);

    int newCapacity = capacity;
    T *newStorage = new T[newCapacity];
    for (int i = 0; i < sz; i++) {
      newStorage[i] = storage[i + 1];
    }
    delete[] storage;
    capacity = newCapacity;
    storage = newStorage;

    sz--;
  }

  void pop_back() {
    assert(sz > 0);
    sz--;
  }

private:
  void resize() {

    int newCapacity = capacity * 1.5;
    T *newStorage = new T[newCapacity];
    for (int i = 0; i < sz; i++) {
      newStorage[i] = storage[i];
    }
    delete[] storage;
    capacity = newCapacity;
    storage = newStorage;
  }

public:
  int waste() const { return capacity - sz; }

  T front() const { return storage[0]; }

  T back() const { return storage[sz - 1]; }

  void print() {
    for (int i = 0; i < sz; i++) {
      std::cout << storage[i] << " ";
    }
  }
};
