#include "Vector.hh"
#include <cassert>
#include <iostream>

using namespace std;
template <typename T>

class Heap {
private:
  Vector<T> storage;

public:
  // Constructors
  Heap() : storage() {}

  // Complexity O(1)
  bool empty() { return (storage.size() > 0); }

  // Complexity O(1)
  T root() {
    assert(empty());
    return storage.at(0);
  }

  // Complexity O(1);
  bool HaveChildrens(int Pos) { return ((2 * Pos + 2) < storage.size()); }
  bool HaveLeftChildren(int Pos) { return ((2 * Pos + 1) < storage.size()); }
  // Complexity O(1);
  T LeftSon(int n) {
    assert(empty());
    assert((2 * n + 1) < storage.size());
    return storage.at(2 * n + 1);
  }
  // Complexity O(1);

  int LeftSonPosition(int n) {
    assert(empty());
    assert((2 * n + 1) < storage.size());
    return (2 * n + 1);
  }

  // Complexity O(1);

  T RightSon(int n) {
    assert(empty());
    assert((2 * n + 2) < storage.size());
    return storage.at(2 * n + 2);
  }
  // Complexity O(1);

  int RightSonPosition(int n) {
    assert(empty());
    assert((2 * n + 2) < storage.size());
    return (2 * n + 2);
  }
  // Complexity O(1);

  T FatherOf(int n) {
    assert(n < storage.size());
    if (n == 0) {
      return storage.at(0);
    } else {
      int pos = ((n - 1) / 2);
      return storage.at(pos);
    }
  }
  // Complexity O(1);

  int FatherOfPosition(int n) {
    assert(n < storage.size());
    if (n == 0) {
      return storage.at(0);
    } else {
      int pos = ((n - 1) / 2);
      return pos;
    }
  }
  // Complexity O(1);

  int YoungerSonP(int Father) {
    assert(HaveLeftChildren(Father));
    if (HaveChildrens(Father)) {
      if (RightSon(Father) < LeftSon(Father))
        return RightSonPosition(Father);
      else
        return LeftSonPosition(Father);
    } else
      return LeftSonPosition(Father);
  }
  // Complexity O(1);

  T YoungerSon(int Father) { return storage.at(YoungerSonP(Father)); }
  // Complexity O(1);

  int OlderSonP(int Father) {
    assert(HaveLeftChildren(Father));
    if (HaveChildrens(Father)) {
      if (RightSon(Father) >= LeftSon(Father))
        return RightSonPosition(Father);
      else
        return LeftSonPosition(Father);
    } else
      return LeftSonPosition(Father);
  }
  // Complexity O(1);

  T OlderSon(int Father) { return storage.at(OlderSonP(Father)); }

  // Complexity O(Log2(n))
  void insert(T a) {
    storage.push_back(a);
    if (FatherOf(storage.size() - 1) > a)
      insert(storage.size() - 1, a);
  }

private:
  void insert(int Pos, T a) {
    int Fath = FatherOfPosition(Pos);
    T temp = storage.at(Fath);
    storage.at(Fath) = a;
    storage.at(Pos) = temp;
    if (FatherOf(Fath) > storage.at(Fath))
      insert(Fath, a);
  }

public:
  // Remove root of Heap
  // Complexity O(Log2(n))
  void remove() {
    storage.at(0) = (storage.at(storage.size() - 1));
    storage.pop_back();
    if (HaveLeftChildren(0)) {
      // Si es menor no tomarlo para ahorro de complejidad.
      if (storage.at(0) > OlderSon(0))

        remove(0);
    }
  }

private:
  void remove(int Pos) {
    T Temp = storage.at(Pos);
    int Temp2 = YoungerSonP(Pos);
    storage.at(Pos) = YoungerSon(Pos);
    storage.at(Temp2) = Temp;
    if (HaveLeftChildren(Temp2)) {
      if (storage.at(Temp2) > OlderSon(Temp2)) {
        remove(Temp2);
      }
    }
  }

public:
  void Print() {
    for (int i = 0; i < storage.size(); i++) {
      cout << storage.at(i) << " ";
    }
  }
};
