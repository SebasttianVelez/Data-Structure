#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rotor {
private:
  char caracter;
  int conection;
  bool shading;

public:
  Rotor(char c, int p, bool s) {
    caracter = c;
    conection = p;
    shading = s;
  }

  char Caracter() { return caracter; }
  bool Shading() { return shading; }
};

#include "Rotors.hh"

vector<Rotor> Rotate(vector<Rotor> &ayuda) {
  Rotor a = ayuda.at(0);
  for (int i = 1; i < ayuda.size(); i++) {
    ayuda[i - 1] = ayuda[i];
  }
  ayuda.at(ayuda.size() - 1) = a;
  return ayuda;
}

void RotateN(int n) {
  for (int i = 0; i < n; i++) {
    if (RotorI[i].Shading()) {
      if (RotorII[i].Shading()) {
        if (RotorIII[i].Shading()) {
          // Rotate(RotorI);
          Rotate(RotorII); // TRES ROTORES
        }
        Rotate(RotorIII);
      }
      Rotate(RotorII);
    }
    Rotate(RotorI);
  }
}

void Print(vector<Rotor> &ayuda1, vector<Rotor> &ayuda2,
           vector<Rotor> &ayuda3) {
  Rotor a = ayuda1.at(0);
  for (int i = 0; i < ayuda1.size(); i++) {
    cout << ayuda1[i].Caracter() << "    ";
    cout << ayuda2[i].Caracter() << "    ";
    cout << ayuda3[i].Caracter() << endl;
  }
}

int main() {
  RotateN(29);
  Print(RotorIII, RotorII, RotorI);
  return 0;
}
