#include "heap.hh"
#include <iostream>

using namespace std;

int main() {
  Heap<int> H;

  H.insert(3);
  H.insert(15);
  H.insert(12);
  H.insert(20);
  H.insert(30);
  H.insert(8);
  H.insert(1);
  H.insert(18);
  H.insert(37);
  H.insert(8);

  H.Print();
  cout << endl;
  H.remove();
  cout << endl;

  H.Print();

  return 0;
}
