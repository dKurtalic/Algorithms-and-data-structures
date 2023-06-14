/*

Write the following functions:
void bubble_sort(Type* array, int size)
void selection_sort(Type* array, int size)
void quick_sort(Type* array, int size)
void merge_sort(Type* array, int size)

Also, create the following function:
void ucitaj(string filename, int*& niz, int& vel)
This function reads a sequence of integers from the file specified by the filename parameter and stores them in the pointer niz (passed by reference to allow dynamic allocation within the function). The number of read elements is stored in the reference vel. The file format should consist of a sequence of numbers separated by spaces or newlines.


Create a function that:

Uses the ucitaj() function to read numbers into an array.
Allows the user to choose which sorting algorithm to use.
Calls the corresponding sorting function.
Prints the execution time of the function (in milliseconds).
Checks if the array is sorted correctly (by iterating through the array and checking if each element is greater than or equal to the previous one).
Writes the sorted array to a new output file.
For easier testing of the program, create the following function:
void generisi(string filename, int vel);  - void generate(string filename, int size)
This function generates vel randomly generated numbers and writes them to the file specified by the filename parameter. Additionally, add the option to call this function in the main() function.

*/


#include <cmath>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <chrono>
using namespace std;
void generisi(string datoteka, int vel) {
  ofstream dat(datoteka);
  for (int i = 0; i < vel; i++) {
    dat << rand() % 100;
    dat << " ";
  }
  dat.close();
}

void ucitaj(string filename, int *&niz, int &vel) {
  vel = 0;
  ifstream otvori(filename);
  if (!otvori)
    throw logic_error("Datoteka se ne može otvoriti");
  int pom;
    while (otvori>>pom) {
      vel++;
  }
  if (!otvori.eof())
    throw logic_error("Datoteka se ne može čitati");
  otvori.close();
  otvori.open(filename);
  niz = new int[vel];
  int broj;
  int i = 0;
  while (otvori >> broj && i<vel) {
    niz[i] = broj;
    i++;
  }
}
template <typename tip> void bubble_sort(tip *niz, int vel) {
  for (int i = 0; i < vel; i++) {
    for (int j = i; j < vel; j++) {
      if (*&niz[i] > *&niz[j]) {
        tip temp = niz[j];
        niz[j] = niz[i];
        niz[i] = temp;
      }
    }
  }
}

template <typename tip> void selection_sort(tip *niz, int vel) {
  for (int i = 0; i < vel; i++) {
    tip min = *&niz[i];
    int indeks = i;
    for (int j = i + 1; j < vel; j++) {
      if (*&niz[j] < min) {
        min = *&niz[j];
        indeks = j;
      }
    }
    niz[indeks] = niz[i];
    niz[i] = min;
  }
}

template <typename tip> int Particija(tip *niz, int prvi, int posljednji) {
  tip pivot = niz[prvi];
  int p = prvi + 1;
  while (p <= posljednji && niz[p] < pivot)
    p++;
  int i = p + 1;
  while (i <= posljednji) {
    if (niz[i] < pivot) {
      tip temp = niz[i];
      niz[i] = niz[p];
      niz[p] = temp;
      p++;
    }
    i++;
  }

  tip temp = niz[prvi];
  niz[prvi] = niz[p - 1];
  niz[p - 1] = temp;
  return p - 1;
}
template <typename tip> void quick_sort(tip *niz, int prvi, int posljednji) {
  if (prvi < posljednji) {
    int var = Particija(niz, prvi, posljednji);
    quick_sort(niz, prvi, var - 1);
    quick_sort(niz, var + 1, posljednji);
  }
}
template <typename tip> void quick_sort(tip *niz, int vel) {
  int prvi = 0;
  vel--;
  quick_sort(niz, prvi, vel);
}
template <typename tip>
void spoji(tip *niz, int pocetak, int p, int q, int posljednji) {
  
  int j = q - pocetak, k = pocetak, i = 0;
  tip *pom = new tip[posljednji - pocetak + 1];
  for (int a = 0; a <= posljednji - pocetak; a++)
    pom[a] = niz[pocetak + a];
  while (i <= (p - pocetak) && j <= (posljednji - pocetak)) {
    if (pom[i] < pom[j]) {
      niz[k] = pom[i];
      i++;
    } else {
      niz[k] = pom[j];
      j++;
    }
    k++;
  }
  for (; i <= p - pocetak; i++)
    niz[k] = pom[i], k++;
  for (; j <= posljednji - pocetak; j++)
    niz[k] = pom[j], k++;
  delete[] pom;
  pom = nullptr;
}
template <typename tip> void merge_sort(tip *niz, int prvi, int posljednji) {
  if (prvi < posljednji) {
    int p = trunc((prvi + posljednji - 1) / 2);
    int q = p + 1;

    merge_sort(niz, prvi, p);
    merge_sort(niz, q, posljednji);
    spoji(niz, prvi, p, q, posljednji);
  }
}
template <typename tip> void merge_sort(tip *niz, int vel) {
  int prvi = 0;
  vel--;
  merge_sort(niz, prvi, vel);
}

template<typename tip>
bool provjeriJeLiSortiran(tip *niz, int vel){
    for (int i=0; i<vel-1; i++){
            if (niz[i]>niz[i+1])
            return false;
        }
        return true;
    }
    
int main() {

  generisi("proba.txt",5);
  int *niz;
  int niz1[5];
  niz=niz1;
  int vel;
  ucitaj("proba.txt",niz ,vel);
  cout<<"Niz prije sortiranja glasi: ";
  for (int i=0; i<5;i++) cout<<niz[i]<<" ";
  cout<<endl<<"Odaberite koji algoritam zelite koristiti za sortiranje: \n1) Bubble sort \n2) Selection sort\n3) Quick sort\n4) Merge sort\n";
  int opcija;
  cin>>opcija;
  auto start=chrono::high_resolution_clock::now();
 
  switch(opcija){
     case 1: bubble_sort(niz, vel);
     case 2: selection_sort(niz, vel);
     case 3: quick_sort(niz, vel);
     case 4: merge_sort(niz, vel); 
  } 
  auto stop=chrono::high_resolution_clock::now();
         
  cout<<"Nakon sortiranja, niz glasi: \n";
  for (int i=0; i<vel; i++) cout<<niz[i]<<" ";
  cout<<"\nProvjera da li je niz soritran: "<<boolalpha<<provjeriJeLiSortiran(niz,vel);
  cout<<"\nVrijeme izvršenja: "<<(chrono::duration_cast<chrono::milliseconds>(stop-start)).count()<<" ms";
  ofstream otvori("zapis.txt");
  if (!otvori) throw logic_error ("Datoteka se ne moze otvoriti");
  for (int i=0; i<vel; i++) otvori<<niz[i]<<" ";
  cout<<"\nSortiran niz je zapisan u datoteku zapis.txt";
  return 0;
}
