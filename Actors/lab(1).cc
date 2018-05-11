#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Actor {

private:
    string movie;
    string name;
    string character;
    int act;
public:
    Actor(const string& m, const string& n, const string& c)
        : movie(m), name(n), character(c) {}
    void print() {
        cout << "Name: " << name << " movie: " << movie << endl;
    }
    string getname(){
      return name;
    }
    string getmovie(){
      return movie;
    }

    int getact(){
      return act;
    }
    void setname (string newname){
      name = newname;
    }

    void setact(int veces){
      act = veces;
    }


};

#include "actors.hh"
#include "actresses.hh"




// Guarda el vector actors y actresses en un solo vector PEOPLE



vector<Actor> GuardarPersonas(){
  vector <Actor> people;
  for(int i=0;i<actors.size();i++){
  people.push_back(actors[i]);
  for(int i=0; i<actresses.size(); i++){
  }
  people.push_back(actresses[i]);
  }
  for(int i=0; i<people.size(); i++){
  people.push_back(actresses[i]);
  }
  //Imprimir nombres
  /*for(int i=0;i<people.size();i++){
  cout<<people[i].getmovie()<<endl;
}*/
  return people;
}
////////////

void SetVeces(int Veces, string name, vector <Actor> people){
  for (int i=0; i<people.size(); i++){
    if(people[i].getname() == name){
      people[i].setact(Veces);
    }
  }/*
  for (int i=0; i<people.size(); i++){
    cout << people[i].getact()<<endl;
  }*/

}
/////////

//Filtra los actores del vector people con respecto a una pelicula

void Filter(string movie, vector <Actor> people){
  vector <string> filter;
  for (int i=0; i<people.size(); i++){
    if(people[i].getmovie() == movie) filter.push_back(people[i].getname());
  }

  for(int i=0;i<filter.size();i++){
  cout<<filter[i]<<endl;
    }
}

//Quitar los actores repetidos y almacenarlos en un vector temporal:

vector <string> Temporal(vector <Actor> people){
  vector <string> temp;
  temp.push_back(people[0].getname());
  for (int i=0; i< people.size(); i++){
    if(people[i].getname() == people[i+1].getname()) i++;
    else {
      int veces = 0;
      for (int j=0; j< temp.size(); j++){
        if(people[i+1].getname() == temp [j]) veces++;
      }
      if(veces == 0){
      temp.push_back(people[i+1].getname());
      }
      veces = 0;
      }
    }
    return temp;
}

// Cuenta las veces en los actores  estan repetido

int Performance (vector <string> temp, vector <Actor> people){
  int Veces=0;
for (int j=0; j<temp.size(); j++){
  Veces = 0;
  for (int i=0; i<people.size(); i++){
    if(people[i].getname() == temp[j]) Veces++;
  }
    SetVeces(Veces, people[j].getname(), people);
  //cout<<"Numero de actuaciones de "<<temp[j]<<": "<<Veces<<endl;
  }
}

//cuanta las veces en la que un solo actor se repite

int Performance2 (string name, vector <Actor> people){
  int Veces=0;

  for (int i=0; i<people.size(); i++){
    if(people[i].getname() == name) Veces++;
  }
  return Veces;
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
  //cout<<v[q].getname()<<endl;
  v[p].setname(v[q].getname());
  //cout<<v[p].getname()<<endl;
  v[q].setname(tmp);
}

// Metodo de ordenamiento (retorna un vector de clase actor)

vector <Actor> bubbleSort(vector<Actor>& v) {
  int n = v.size();
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 0; j <= n - 2; j++) {
      if (v[j].getname() > v[j + 1].getname()) swap(v, j, j + 1);
    }
  }
  return v;
}

void swap1(vector<int>& v, int p, int q) {
  int tmp = v[p];
  v[p] = v[q];
  v[q] = tmp;
}


void merge(vector<int>& v,
           const vector<int>& left,
           const vector<int>& right) {
  int i = 0, j = 0, k = 0;
  while (i < left.size() && j < right.size()) {
    if (left[i] < right[j]) {
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

void mergeSort(vector<int>& v) {
  if (v.size() < 2) return;
  int mid = v.size() / 2;
  vector<int> left(mid, 0);
  vector<int> right(v.size() - mid, 0);
  for (int i = 0; i < left.size(); i++) left[i] = v[i];
  for (int i = mid; i < v.size(); i++) right[i - mid] = v[i];
  mergeSort(left);
  mergeSort(right);
  merge(v, left, right);
}

int partition(vector<int>& s, int lo, int hi) {
  int pivot = s[lo];
  int left = lo;
  int right = hi;

  while(left < right) {
    while(s[right] > pivot) right--;
    while((left < right) && (s[left] <= pivot)) left++;
    if(left < right) swap1(s,left,right);
  }

  swap1(s, right, lo);
  return right;
}

void quicksort(vector<int>& s, int lo, int hi) {
  if (lo < hi) {
    int p = partition(s,lo,hi);
    quicksort(s,lo, p-1);
    quicksort(s, p+1, hi);
  }
}

void PrintV(vector <Actor> v){
  for (int i=0; i<v.size(); i++){
    cout << v[i].getname()<<endl;
  }
}


int main (){
  vector <Actor> v= GuardarPersonas();
  vector <string> a = Temporal(v);

  //PrintI(v);
  //Filter("american beauty",v);
  Performance(Temporal(v), v);
  //PrintV(bubbleSort(v));
  //Performance2("scarlett johansson", v);
}
