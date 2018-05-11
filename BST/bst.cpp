#include "bst.hh"

int main(void) {
  cout << "BST examples!" << endl;
  BST<int> cormen122;
  cormen122.insert(15);
  cormen122.insert(6);
  cormen122.insert(18);
  cormen122.insert(3);
  cormen122.insert(7);
  cormen122.insert(17);
  cormen122.insert(20);
  cormen122.insert(2);
  cormen122.insert(4);
  cormen122.insert(13);
  cormen122.insert(9);

  cout << cormen122.successor(20).first << endl;
  cout << cormen122.successor(17).first << endl;
  cout << cormen122.height() << endl;

  BST<int> t;
  for (int i = 0; i < 100; i++)
    t.insert(i);
  cout << t.height() << endl;

  return 0;
}
