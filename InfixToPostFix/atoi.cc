#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
int main() {
  string str1 = ("42");
  const char *str2 = "3.14159";
  const char *str3 = "31337 with words";
  const char *str4 = "words and 2";

  // int num1 = atoi(str1);
  int num2 = atoi(str2);
  int num3 = atoi(str3);
  int num4 = atoi(str4);

  // cout << "atoi(\"" << str1 << "\") is " << num1 << '\n';

  int A = 20;
  int B = 30;
  int C = 14;
  char mas = '+';
  int r = A 'mas' B;
  cout << r << endl;
  string F = ("A+B");

  for (int i = 0; i < F.size(); i++) {
    if (F[i] == A)
      cout << "si" << endl;
    else
      cout << "no" << endl;
  }
}
