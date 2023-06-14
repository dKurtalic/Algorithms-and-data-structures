
/*
Task 1:
Implement the function:
void radixSort(vector<int> &a)
which sorts the given vector 'a' using the radix sort algorithm. Assume that the maximum number of digits in the numbers in vector 'a' is unknown.

Task 2:
Implement the function:
void stvoriGomilu(vector<int> &a) (void createHeap(vector<int> &a))
which forms a heap from the given vector 'a'.

Additionally, implement the following functions:
void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina) (void insertIntoHeap(vector<int> &a, int inserted, int &size))
which adds the inserted element to the heap of size 'velicina' formed in vector 'a'.

int izbaciPrvi(vector<int> &a, int &velicina) (int removeFirst(vector<int> &a, int &size))
which removes the element from the root of the heap of size 'velicina' formed in vector 'a'.

void gomilaSort(vector<int> &a) (void heapSort(vector<int> &a))
which sorts the given vector 'a' using the heap sort algorithm.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

void radixSort(vector<int> &a) {
  int maks = *std::max_element(a.begin(), a.end());
  int r = 1;
  while (maks / r) {
    vector<vector<int>> pom(10, vector<int>());
    for (int broj : a) {
      int cifra = broj / r % 10;
      pom[cifra].push_back(broj);
    }
    int k = 0;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < pom[i].size(); j++)
        a[k] = pom[i][j], k++;
    }
    r *= 10;
  }
}

bool jeLiList(int velicina, int i) { return (i >= velicina / 2); }
void popraviDole(vector<int> &a, int i,int velicina) {
  while (!jeLiList(velicina,i)) {
    int lijevoDijete = 2 * i + 1;
    int desnoDijete = 2 * i + 2;
    if (desnoDijete < velicina && a[desnoDijete] > a[lijevoDijete]) {
      lijevoDijete = desnoDijete;
    }
    if (a[i] > a[lijevoDijete])
      return;
    else{
    int temp = a[i];
    a[i] = a[lijevoDijete];
    a[lijevoDijete] = temp;
    i = lijevoDijete;
  }
  }
}
void stvoriGomilu(vector<int> &a) {
  for (int i = (a.size() / 2) ; i >= 0; i--)
    popraviDole(a, i,a.size());
}
void popraviGore(vector<int> &a, int i) {
  while (a[i] > a[(i - 1) / 2] && i != 0) {
    int temp = a[i];
    a[i] = a[(i - 1) / 2];
    a[(i - 1) / 2] = temp;
    i =(i - 1) / 2;
  }
}

void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina) {
 a.resize(++velicina);
 a[velicina-1]=umetnuti;
 popraviGore(a, velicina-1);
}

int izbaciPrvi(vector<int> &a, int &velicina) {
  if (a.size() == 0)
    throw logic_error("Gomila je prazna");
  int temp = a[0];
  a[0] = a[--velicina];
  a[velicina] = temp;
  if (a.size()!=0)
    popraviDole(a, 0,velicina);
  return temp;
}
void gomilaSort(vector<int>&a){
    stvoriGomilu(a);
    int x,y;
    int velicina=a.size();
    for (int i=0; i<a.size();i++){
        if (!i)  y=a.size();
        x=izbaciPrvi(a,y);
    }
}
int main() {
     vector<int> a;
    a.push_back(546);
    a.push_back(1);
    a.push_back(31);
    a.push_back(1001);
    a.push_back(104351);
    a.push_back(7);
    a.push_back(6);
    a.push_back(60045);
    gomilaSort(a);
    for(int i(0);i<a.size();i++){
        cout<<a[i]<<" ";
    }

return 0;
}
