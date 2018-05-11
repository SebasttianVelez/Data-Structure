#include "set.hh"

using namespace std;

int main() {
  Set<int> a;
  Set<int> b;

  a.insert(5);
  b.insert(2);
  b.insert(5);

  Set<int> u = a.union(b);
  Set<int> n = a.intersect(b);
}
