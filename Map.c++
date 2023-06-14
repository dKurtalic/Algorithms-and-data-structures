/*
Create an abstract generic class named Mapa (Map). Map is a commonly used abstract data type in programming. A map associates a data of one arbitrary type (key) with data of another arbitrary and not necessarily the same type (value). Programmers often perceive a map as a special type of array/vector where the key doesn't have to be of an integer type or be within a fixed range. For example, you could write:

ArrayMap<string, string> capital_cities;
capital_cities["Bosnia and Herzegovina"] = "Sarajevo";
capital_cities["Croatia"] = "Zagreb";
capital_cities["United States of America"] = "Washington";

An abstract class is needed in order to experiment with various strategies for implementing a Map. The abstract class Mapa should support the following methods:

A parameterless constructor that creates an empty map. Since Mapa is a generic class with two types (TipKljuca and TipVrijednosti), and the constructor has no parameters, when creating an object of type Mapa, both types must be specified as follows:
ArrayMap<string, float> m;

Overloaded square bracket operator [] (both constant and non-constant variations) to allow the map to be used in all situations like an array (see the example above). The default value of a map member (if the key does not exist in the map) should be TipVrijednosti().
A method int brojElemenata() that returns the number of elements currently stored in the map.
A method void obrisi() that deletes all elements from the map. After calling this method, the map should still be usable (new elements can be added).
A method void obrisi(const TipKljuca& kljuc) that deletes only one element from the map with the specified key. The reason for this method is that deleting an element is not the same as assigning it to zero or an empty string, as deleting frees up memory. If the key does not exist, an exception should be thrown.
For such a Map to be implemented, the type TipKljuca must be a comparable type (support comparison operators). Only a default constructor is required for TipVrijednosti, similar to creating an array. For example, the class std::vector has a defined default constructor but does not have a defined comparison operator.

*/

#include <iostream>
using namespace std;
template <typename tip1, typename tip2> class Mapa {
public:
  Mapa() {}
  virtual tip2 operator[](const tip1 k) const = 0;
  virtual tip2 &operator[](const tip1 &k) = 0;
  virtual int brojElemenata() const= 0;
  virtual void obrisi(const tip1 k) = 0;
  virtual void obrisi() = 0;
  virtual ~Mapa()=default;
};

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
void RezultatTesta(bool vrijednost) {
  if (vrijednost)
    cout << "OK\n";
  else
    cout << "TEST JE PAO!\n";
}
bool test1(){
    NizMapa<string,string> m;
    m["plava"]="blue";
    m["crvena"]="red";
    m["roze"]="pink";
    m["crna"]="black";
    m.obrisi("crna");
    return m.brojElemenata()==3 && m["plava"]=="blue" && m["roze"]=="pink";
}
bool test2(){
    NizMapa<int,int>m;
    m[0]=0;
    m[1]=-1;
    m[2]=-2;
    NizMapa<int,int>kopija(m);
    kopija.obrisi(2);
    return kopija.brojElemenata()==2 && m[0]==0 && m[1]==-1;

}
bool test3(){
    //test performansi
    NizMapa<int, int> m;
    for (int i=0; i<10000; i++) m[i]=i+1;
    return m.brojElemenata()==10000;
}
bool test4(){
    NizMapa<double,double>m;
    m[1.2]=2.2;
    m[-1.2]=-2.2;
    m[5]=6;
    return  m[10]==0 && m[1.2]==2.2 && m[-1.2]==-2.2 && m[5]==6;
}
bool test5(){
    NizMapa<char,char>m;
    m['c']='C';
    m['a']='A';
    m['g']='G';
    m['e']='E';
    return m.brojElemenata()==4 && m['c']=='C' && m['e']=='E';
}
int main() {
    RezultatTesta(test1());
    RezultatTesta(test2());
    RezultatTesta(test3());
    RezultatTesta(test4());
    RezultatTesta(test5());
  return 0;
}
