#include <cassert>
#include <iostream>

template <typename T>

class List {
private:
  class Node {
  private:
    T data;
    Node *next;

  public:
    Node(T d) : data(d), next(nullptr) {}
    bool hasNext() const { return next != nullptr; }
    void setNext(Node *n) { next = n; }
    Node *getNext() { return next; }
    const T &getData() const { return data; }
    T &getData() { return data; }
  };

  Node *first;
  Node *last;
  int sz;

public:
  List() : first(nullptr), last(nullptr), sz(0) {}

  bool empty() const { return last == nullptr; }

  int size() const { return sz; }

  void push_back(T e) {
    Node *n = new Node(e);
    if (empty()) {
      first = n;
    } else {
      last->setNext(n);
    }
    sz++;
    last = n;
  }

  const T &at(int p) const {
    assert(!empty() && p >= 0 && p < sz);
    Node *t = first;
    int i = 0;
    while (i < p) {
      t = t->getNext();
      i++;
    }
    return t->getData();
  }

  void push_front(T e) {
    if (empty()) {
      push_back(e);
    } else {
      Node *n = new Node(e);
      n->setNext(first);
      first = n;
      sz++;
    }
  }

  void pop_front() {
    assert(!empty());
    Node *t = first;
    first = t->getNext();
    delete t;
    if (first == nullptr)
      last = nullptr;
    sz--;
  }

  void pop_back() { assert(!empty()); }

  void print() {
    if (empty()) {
      std::cout << "{}" << std::endl;
    } else {
      Node *t = first;
      std::cout << "{";
      while (t != nullptr) {
        std::cout << " " << t->getData();
        t = t->getNext();
      }
      std::cout << "}" << std::endl;
    }
  }

  void insert(T e, int p) {
    assert(p >= 0 && p <= sz);
    Node *n = new Node(e);
    Node *t = first;
    if (empty()) {
      push_front(e);
    } else {
      int i = 0;

      while (i < p - 1) {
        t = t->getNext();
        i++;
      }
      n->setNext(t->getNext());
      t->setNext(n);
      sz++;
    }
  }

  void remove(int p) {
    assert(!empty() && p >= 0 && p < sz);
    if (p == 0)
      pop_front();
    else {
      Node *t = first;
      Node *s = first;
      int i = 0;

      while (i < p) {
        s = t;
        t = t->getNext();
        i++;
      }
      s->setNext(t->getNext());
      sz--;
      delete t;
    }
  }
  /* PARCIAL */
  /*
    void swap1(List<int> &s) {
      Node *uno = first;
      Node *dos = first;
      for (int i = 0; i < 1; i++) {
        uno = uno->getNext();
      }
      for (int i = 0; i < 4; i++) {
        dos = dos->getNext();
      }
    }

    void swap(Node *t, Node *k) {
      Node *aux = t->getNext();
      Node *aux2 = first;
      Node *aux3 = first;
      Node *aux4 = aux->getNext();

      while (aux2 != t) {
        aux3 = aux2;
        aux2 = aux2->getNext();
      }

      aux3->setNext(k);
      t->setNext(k->getNext());
      k->setNext(aux);
      aux->setNext(aux4);
      aux4->setNext(t);
    }
  */
  T front() const { return first->getData(); }
  T back() const { return last->getData(); }
};
