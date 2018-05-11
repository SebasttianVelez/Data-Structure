#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Actor {

private:
    string movie;
    string name;
    string character;
    int numPart;
public:
    Actor(const string& m, const string& n, const string& c)
        : movie(m), name(n), character(c), numPart(){}
    void print() {
        cout << "Name: " << name << " movie: " << movie << endl;
    }
    string getname(){
      return name;
    }

    string getmovie(){
      return movie;
    }

    int getnumPart(){
      return numPart;
    }
    void setname (string newname){
      name = newname;
    }

    void setnumPart (int newNum){
      numPart = newNum;
    }

};

#include "actors.hh"
#include "actresses.hh"

// Guarda el vector actors y actresses en un solo vector PEOPLE
/**
  *Complejidad O(n) donde n es el numero de actores + numero el numero de actrices
**/
vector<Actor> GuardarPersonas(){
  vector <Actor> people;
  for(int i=0;i<actors.size();i++){
  people.push_back(actors[i]);
  }
  for(int i=0; i<actresses.size(); i++){
  people.push_back(actresses[i]);
  //people[i]
  }
  //Imprimir nombres
  /*for(int i=0;i<people.size();i++){
  cout<<people[i].getmovie()<<endl;
}*/
  return people;
}

//Filtra los actores del vector people con respecto a una pelicula

void Filter(string movie, vector <Actor> people){
  vector <string> filter;
  for (int i=0; i<people.size(); i++){
    if(people[i].getmovie() == movie)
    filter.push_back(people[i].getname());
  }

  for(int i=0;i<filter.size();i++){
  cout<<filter[i]<<endl;
    }
}

//Quitar los actores repetidos y almacenarlos en un vector temporal:
/**
  *Complejidad O(n²) ya que el for que se encuantra dentri se ejecuta n veces el for externo
**/
vector<Actor> performance2(vector<Actor> &v){
  for(int i = 0;i<v.size();i++){
    int cont=0;
    for(int j=0;j<v.size(); j++){
      if(v[i].getname()==v[j].getname())
        cont++;
    }
    v[i].setnumPart(cont);
  }
  return v;
}

// Imprime vectores de cadena
void PrintC(vector <string> a){
  for(int i=0; i<a.size(); i++){
    cout<<a[i]<<endl;
  }
}

// Intercambia posiciones
void swap(vector<Actor>& v, int p, int q) {
  string tmp = v[p].getname();
  v[p].setname(v[q].getname());
  v[q].setname(tmp);
}

void swap3(vector<Actor>& people, int p, int q) {
  Actor tmp = people[p];
  people[p] = people[q];
  people[q] = tmp;
}

// Metodo de ordenamiento (retorna un vector de clase actor)

vector <Actor> bubbleSort(vector<Actor>& v) {

  int n = v.size();
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 0; j <= n - 2; j++) {
      if (v[j].getname() > v[j + 1].getname()) swap(v, j, j + 1);
    }
  }
}

void merge(vector<Actor> &v, vector<Actor> &left, vector<Actor> &right) {
  int i = 0, j = 0, k = 0;
  while (i < left.size() && j < right.size()) {
    if (left[i].getnumPart() < right[j].getnumPart()) {
      v[k] = left[i];
      i++;
    } else {
      v[k] = right[j];
      j++;
    }
    k++;
  }
  while (i < left.size()) {
    v[k] = left[i];
    i++;
    k++;
  }
  while (j < right.size()) {
    v[k] = right[j];
    j++;
    k++;
  }
}

void mergeSort(vector<Actor> &v) {
  if (v.size() < 2)
    return;
  int mid = v.size() / 2;
  vector<Actor> left;
  vector<Actor> right;
  for (int i = 0; i < mid; i++)
    left.push_back(v[i]);
  for (int i = mid; i < v.size(); i++)
    right.push_back(v[i]);
  mergeSort(left);
  mergeSort(right);
  merge(v, left, right);
}

int partition(vector<Actor> &v, int lo, int hi) {
  int pivot = v[lo].getnumPart();
  int left = lo;
  int right = hi;

  while (left < right) {
    while (v[right].getnumPart() > pivot)
      right--;
    while ((left < right) && (v[left].getnumPart() <= pivot))
      left++;
    if (left < right)
      swap3(v, left, right);
  }

  swap3(v, right, lo);
  return right;
}

void quicksort(vector<Actor> &people, int lo, int hi) {
  if (lo < hi) {
    int p = partition(people, lo, hi);
    quicksort(people, lo, p - 1);
    quicksort(people, p + 1, hi);
  }
}

// void PrintV(vector <Actor> v){
//   for (int i=0; i<v.size(); i++){
//     cout << v[i].getname()<<endl;
//   }
// }
//
int main (){
   vector <Actor> v = GuardarPersonas(); //Mezclando los 2vectores
  //  for(int i = 0;i<v.size();i++){ //Imprime vecotr mezclado
  //    cout<<v[i].getname()<<endl;
  //  }
  //Filter("untitled woody allen fall project 2006", v); //Llamadoo funcion filter
  //performance2(v);//llamado performance
  //bubbleSort(v);//llamado bubblesort
  mergeSort(v);//llamado merge

  //quicksort(v);//Llamado del quicksort

   for(int i = 0;i<v.size();i++){ impresion del quicsort
    cout<<v[i].getname()<<" " <<v[i].getnumPart()<<endl;
   }
}
