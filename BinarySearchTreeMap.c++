/*
Task 1:
Create a class named "BinarySearchTreeMap" derived from the "Map" class that you defined in previous exercises. The "BinarySearchTreeMap" class implements a map using a binary search tree. Each tree node should contain two data elements (key and value), and the tree should be organized based on the key for faster search. In addition to pointers to the left and right subtrees, each node should have a pointer to its parent.

Task 2:
Include the "ArrayMap" class that you developed in the previous tutorial in Task 1.
Create a test program that compares the performance of "ArrayMap" and "BinarySearchTreeMap". The program should populate both types of maps with a large amount of randomly generated data and then measure the average time for:

Adding a new element to the map
Accessing an existing element in the map.
Comment on the measured results using comments in the code.
*/


#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

template <typename tip1, typename tip2> class Mapa {
public:
  Mapa() {}
  virtual tip2 operator[](const tip1 k) const = 0;
  virtual tip2 &operator[](const tip1 &k) = 0;
  virtual int brojElemenata() const = 0;
  virtual void obrisi(const tip1 k) = 0;
  virtual void obrisi() = 0;
  virtual ~Mapa() = default;
};
template <typename tip1, typename tip2> struct Cvor {
  tip1 kljuc;
  tip2 vrijednost;
  Cvor *lijevoDijete;
  Cvor *desnoDijete;
  Cvor *roditelj;
};

template <typename tip1, typename tip2>
class BinStabloMapa : public Mapa<tip1, tip2> {
  int brElemenata = 0;
  Cvor<tip1, tip2> *root = nullptr;

public:
  BinStabloMapa() {}
  BinStabloMapa(const BinStabloMapa &bsm);
  Cvor<tip1, tip2> *kopiraj(Cvor<tip1, tip2> *c);
  int brojElemenata() const override { return brElemenata; }
  ~BinStabloMapa() {
    brElemenata = 0;
    brisanje(root);
  }
  tip2 &operator[](const tip1 &k) override;
  tip2 operator[](const tip1 k) const override;
  void obrisi(const tip1 k) override;
  void obrisi() override {
    brisanje(root);
    brElemenata = 0;
    root = nullptr;
  }
  void brisanje(Cvor<tip1, tip2> *c);
  BinStabloMapa &operator=(const BinStabloMapa<tip1, tip2> &bsm);
};
template <typename tip1, typename tip2>
BinStabloMapa<tip1, tip2> &
BinStabloMapa<tip1, tip2>::operator=(const BinStabloMapa<tip1, tip2> &bsm) {
  if (&bsm == this)
    return *this;
  else {
    obrisi();
    brElemenata = bsm.brElemenata;
    root = kopiraj(bsm.root);
    return *this;
  }
}
template <typename tip1, typename tip2>
void BinStabloMapa<tip1, tip2>::obrisi(const tip1 k) {
  Cvor<tip1, tip2> *glavni = nullptr;
  Cvor<tip1, tip2> *pom = root;
  while (k != pom->kljuc && pom != nullptr) {
    glavni = pom;
    if (k > pom->kljuc) {
      pom = pom->desnoDijete;
    } else
      pom = pom->lijevoDijete;
  }
  if (pom == nullptr)
    return;
  Cvor<tip1, tip2> *temp = nullptr;
  if (pom->desnoDijete == nullptr)
    temp = pom->lijevoDijete;
  else if (pom->lijevoDijete == nullptr)
    temp = pom->desnoDijete;
  else {
    Cvor<tip1, tip2> *temp2 = pom;
    Cvor<tip1, tip2> *temp3 = nullptr;
    temp = pom->lijevoDijete;
    temp3 = temp->desnoDijete;
    while (temp3 != nullptr) {
      temp2 = temp;
      temp = temp3;
      temp3 = temp->desnoDijete;
    }
    if (temp2 != pom) {
      temp2->desnoDijete = temp->lijevoDijete;
      temp->lijevoDijete = pom->lijevoDijete;
    }

    temp->desnoDijete = pom->desnoDijete;
  }
  if (glavni == nullptr)
    root = temp;
  else if (pom == glavni->lijevoDijete)
    glavni->lijevoDijete = temp;
  else {
    glavni->desnoDijete = temp;
  }
  brElemenata--;
  delete pom;
  pom = nullptr;
  glavni = nullptr;
  temp = nullptr;
}
template <typename tip1, typename tip2>
tip2 BinStabloMapa<tip1, tip2>::operator[](const tip1 k) const {
  if (root != nullptr) {
    Cvor<tip1, tip2> *glavni = nullptr;
    Cvor<tip1, tip2> *pom = root;
    while (pom != nullptr) {
      if (pom->kljuc == k)
        return pom->vrijednost;
      else if (k > pom->kljuc) {
        glavni = pom;
        pom = pom->desnoDijete;
      } else {
        glavni = pom;
        pom = pom->lijevoDijete;
      }
    }
    return tip2();
  }
  return tip2();
}
template <typename tip1, typename tip2>
void BinStabloMapa<tip1, tip2>::brisanje(Cvor<tip1, tip2> *c) {

  if (c != nullptr) {
    brisanje(c->lijevoDijete);
    brisanje(c->desnoDijete);
    delete c;
    c = nullptr;
  }
}
template <typename tip1, typename tip2>
BinStabloMapa<tip1, tip2>::BinStabloMapa(const BinStabloMapa<tip1, tip2> &bsm) {

  if (bsm.root != nullptr)
    brElemenata = bsm.brElemenata,root= kopiraj(bsm.root);
}

template <typename tip1, typename tip2>
Cvor<tip1, tip2> *BinStabloMapa<tip1, tip2>::kopiraj(Cvor<tip1, tip2> *c) {
  if (c != nullptr) {
    Cvor<tip1, tip2> *pom = new Cvor<tip1, tip2>;
    pom->lijevoDijete = nullptr;
    pom->desnoDijete = nullptr;
    pom->vrijednost = c->vrijednost;
    pom->kljuc = c->kljuc;
    pom->desnoDijete = kopiraj(c->desnoDijete);
    pom->lijevoDijete = kopiraj(c->lijevoDijete);
    return pom;
  }
  return nullptr;
}

template <typename tip1, typename tip2>
tip2 &BinStabloMapa<tip1, tip2>::operator[](const tip1 &k) {
  if (root == nullptr) {
    brElemenata++;
    root = new Cvor<tip1, tip2>;
    root->lijevoDijete = nullptr;
    root->desnoDijete = nullptr;
    root->roditelj = nullptr;
    root->vrijednost = tip2();
    root->kljuc = k;
    return root->vrijednost;
  } else {
    Cvor<tip1, tip2> *glavni;
    Cvor<tip1, tip2> *pom = root;
    while (pom) {
      if (pom->kljuc == k)
        return pom->vrijednost;
      else if (k > pom->kljuc) {
        glavni = pom;
        pom = pom->desnoDijete;
      } else {
        glavni = pom;
        pom = pom->lijevoDijete;
      }
    }

    if (k > glavni->kljuc) {
      brElemenata++;
      Cvor<tip1, tip2> *temp = new Cvor<tip1, tip2>;
      temp->kljuc = k;
      temp->vrijednost = tip2();
      temp->lijevoDijete = nullptr;
      temp->desnoDijete = nullptr;
      temp->roditelj = nullptr;
      glavni->desnoDijete = temp;
      return temp->vrijednost;
    } else if (k < glavni->kljuc) {
      brElemenata++;
      Cvor<tip1, tip2> *temp = new Cvor<tip1, tip2>;
      temp->kljuc = k;
      temp->lijevoDijete = nullptr;
      temp->desnoDijete = nullptr;
      temp->roditelj = nullptr;
      temp->vrijednost = tip2();
      glavni->lijevoDijete = temp;
      return temp->vrijednost;
    }
  }
  return root->vrijednost;
}
template <typename tip1, typename tip2>
class NizMapa : public Mapa<tip1, tip2> {
  std::pair<tip1, tip2> **niz = nullptr;
  int velicina = 0;
  int brElemenata = 0;
  int trenutni = 0;

public:
  NizMapa() {
    velicina = 1;
    niz = new std::pair<tip1, tip2> *[velicina];
  }
  NizMapa(const NizMapa<tip1, tip2> &mapa);
  int brojElemenata() const{ return brElemenata; }
  tip2 operator[](const tip1 k) const;
  tip2 &operator[](const tip1 &k);
  NizMapa<tip1, tip2> &operator=(const NizMapa<tip1, tip2> &nm);
  void obrisi(const tip1 k);
  void obrisi();
  ~NizMapa() { obrisi(); };
};

template <typename tip1, typename tip2>
NizMapa<tip1, tip2>::NizMapa(const NizMapa<tip1, tip2> &mapa) {
  velicina = mapa.velicina;
  brElemenata = mapa.brElemenata;
  trenutni = mapa.trenutni;
  niz = new std::pair<tip1, tip2> *[velicina];
  for (int i = 0; i < brElemenata; i++) {
    niz[i] = new std::pair<tip1, tip2>(*mapa.niz[i]);
  }
}
template <typename tip1, typename tip2>
tip2 NizMapa<tip1, tip2>::operator[](const tip1 k) const {
  for (int i = 0; i < brElemenata; i++) {
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  return tip2();
}
template <typename tip1, typename tip2>
NizMapa<tip1, tip2> &
NizMapa<tip1, tip2>::operator=(const NizMapa<tip1, tip2> &nm) {
  if (this == &nm)
    return *this;
  if (velicina != 0) {
    obrisi();
  }
  velicina = nm.velicina;
  brElemenata = nm.brElemenata;
  niz = new std::pair<tip1, tip2> *[velicina];
  for (int i = 0; i <brElemenata; i++) {
    niz[i] = new std::pair<tip1, tip2>(*nm.niz[i]);
  }
  trenutni = nm.trenutni;
  return *this;
}
template <typename tip1, typename tip2>
tip2 &NizMapa<tip1, tip2>::operator[](const tip1 &k) {
  for (int i = 0; i < brElemenata; i++) {
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  if (brElemenata == velicina && brElemenata != 0) {
    velicina = 2 * (velicina + 1);
    std::pair<tip1, tip2> **pom = new std::pair<tip1, tip2> *[velicina];
    for (int i = 0; i < brElemenata; i++)
      pom[i] = niz[i];
    delete[] niz;
    niz = pom;
  }
  if (brElemenata == 0) {
    trenutni = 0;
    brElemenata++;
    velicina = 1;
    if (!niz)
      niz = new std::pair<tip1, tip2> *[velicina];
    niz[trenutni] = new std::pair<tip1, tip2>();
    niz[trenutni]->second = tip2();
    niz[trenutni]->first = k;
    return niz[trenutni]->second;
  }

  else {
    trenutni++;
    brElemenata++;
    niz[trenutni] = new std::pair<tip1, tip2>();
    niz[trenutni]->second = tip2();
    niz[trenutni]->first = k;
    return niz[trenutni]->second;
  }
}

template <typename tip1, typename tip2>
void NizMapa<tip1, tip2>::obrisi(const tip1 k) {
  for (int i = 0; i < brElemenata; i++) {
    if (niz[i]->first == k) {
      delete niz[i];
      brElemenata--;
      trenutni--;
      for (int j = i + 1; j < brElemenata + 1; j++) {
        niz[i] = niz[j];
        i++;
      }
    }
  }
}

template <typename tip1, typename tip2> void NizMapa<tip1, tip2>::obrisi() {
  for (int i = 0; i < brElemenata; i++) {
    delete niz[i];
    niz[i] = nullptr;
  }
  delete[] niz;
  niz = nullptr;
  velicina = 0;
  trenutni = 0;
  brElemenata = 0;
}

void getExecutionTime(double t1,double t2,string msg){
    double time_spent = double(t2 - t1) / double(CLOCKS_PER_SEC/1000);
  cout<<msg<<time_spent<<setprecision(10)<<" ms"<<endl;
}
int main() {

  BinStabloMapa<int,int> bsm;
  NizMapa<int,int> nm;
  clock_t startBsm,endBsm,startNm,endNm;
  
  startBsm=clock();
  for (int i=0; i<1000; i++){
      bsm[i]=rand()%100;
  }
  endBsm=clock();
  getExecutionTime(startBsm,endBsm,"Vrijeme potrebno za dodavanje 1000 elemenata u BinStabloMapa: ");
  startNm=clock();
  for (int i=0; i<1000; i++){
      nm[i]=rand()%100;
  }
  endNm=clock();
  getExecutionTime(startNm,endNm,"Vrijeme potrebno za dodavanje 1000 elemenata u NizMapa: ");

  startBsm=clock();
  int pom=bsm[0];
  endBsm=clock();
  getExecutionTime(startBsm,endBsm,"Vrijeme potrebno za pristup elementu u BinStabloMapa: ");

  startNm=clock();
  pom=nm[0];
  endNm=clock();
  getExecutionTime(startNm,endNm,"Vrijeme potrebno za pristup elementu u NizMapa: ");


  return 0;
}
