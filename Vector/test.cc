#include "Queue.hh"
#include "Stack.cc"
#include <iostream>

using namespace std;

int main() {
  Vector<int> v;
  v.push_back(4);
  v.push_back(5);
  v.push_front(3);
  v.push_back(6);
  v.push_back(7);
  v.push_back(8);

  v.print();
  cout << endl << "Queue: " << endl;
  Queue<int> q;

  q.push(13);
  q.push(14);
  q.push(15);
  q.push(16);
  q.push(17);
  q.push(18);
  cout << endl;
  q.print();
  cout << endl;
  cout << "q size: " << q.size() << endl;

  q.pop();
  q.print();
  cout << endl;
  cout << "front: " << q.front() << endl;
  cout << "back: " << q.back() << endl;
  cout << endl;
  return 0;
}
