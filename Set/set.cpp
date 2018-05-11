#include "set.hh"

using namespace std;

int main() {
  Set<int> a;
  Set<int> b;

  a.insert(5);
  a.insert(15);
  a.insert(35);

  b.insert(2);
  b.insert(5);

  a.print();
  b.print();

  Set<int> u = a.Union(b);
  u.print();
  Set<int> n = a.Intersect(b);
  n.print();
}
