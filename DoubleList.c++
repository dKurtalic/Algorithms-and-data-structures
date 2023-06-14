/*
1. Implement a DoubleList class that contains a dynamically allocated doubly linked list. 
This class should be inherited from the abstract generic class List
2. Create a function that receives a constant reference to the List class and returns its largest member: template<typename Type>
Type giveMaximum(const List<Type>& n) The function should work for the DoubleList class. 
During the implementation of this task, it is not allowed to introduce new methods or to change the way existing functions work. 
It is necessary to write a function that will prove the correctness of the dajMaximum function
*/


#include <iostream>
using namespace std;
template <typename tip> class Iterator;

template <typename tip> class Lista {
public:
  Lista(){};
  virtual int brojElemenata() const = 0;
  virtual tip &trenutni() = 0;
  virtual tip trenutni() const = 0;
  virtual bool prethodni() = 0;
  virtual bool sljedeci() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void dodajIspred(const tip &el) = 0;
  virtual void dodajIza(const tip &el) = 0;
  virtual void obrisi() = 0;
  virtual tip &operator[](int indeks) = 0;
  virtual tip &operator[](int indeks) const = 0;
  virtual ~Lista() {}
};

template <typename tip> class DvostrukaLista : public Lista<tip> {
  struct Cvor {
    tip element;
    Cvor *prethodni = nullptr;
    Cvor *sljedeci = nullptr;
  };
  Cvor *pocetak1 = nullptr;
  Cvor *kraj1 = nullptr;
  Cvor *trenutni1 = nullptr;
  int velicina = 0;
  Cvor *dajPocetak() const { return pocetak1; }

public:
  DvostrukaLista<tip>() {
    pocetak1 = nullptr;
    kraj1 = nullptr;
    trenutni1 = nullptr;
  }
  DvostrukaLista<tip>(const DvostrukaLista &l);
  int brojElemenata() const override { return velicina; }

  tip &trenutni() override { return trenutni1->element; }
  tip trenutni() const override { return trenutni1->element; }
  bool prethodni() override;
  bool sljedeci() override;
  void pocetak() override { trenutni1 = pocetak1; }
  void kraj() override { trenutni1 = kraj1; }
  void dodajIspred(const tip &el) override;
  void dodajIza(const tip &el) override;
  void obrisi() override;
  tip &operator[](int indeks) override;
  tip &operator[](int indeks) const override;
  DvostrukaLista<tip> &operator=(const DvostrukaLista &l);
  ~DvostrukaLista() {
    if (pocetak1 != nullptr && trenutni1 != nullptr) {
      while (velicina != 0)
        obrisi();
    }
  }
  friend class Iterator<tip>;
};
template <typename tip>
DvostrukaLista<tip> &DvostrukaLista<tip>::operator=(const DvostrukaLista &l) {
  if (this == &l)
    return *this;
  for (auto tr = l.pocetak1; tr != nullptr; tr = tr->sljedeci) {
    dodajIza(tr->element);
    kraj();
  }
  return *this;
}
template <typename tip> bool DvostrukaLista<tip>::prethodni() {
  if (pocetak1 == nullptr)
    return false;
  trenutni1 = trenutni1->prethodni;
  return true;
}
template <typename tip> bool DvostrukaLista<tip>::sljedeci() {
  if (kraj1 == trenutni1)
    return false;
  trenutni1 = trenutni1->sljedeci;
  return true;
}
template <typename tip>
DvostrukaLista<tip>::DvostrukaLista(const DvostrukaLista &l) {

  for (auto tr = l.pocetak1; tr != nullptr; tr = tr->sljedeci) {
    dodajIza(tr->element);
    kraj();
  }
}
template <typename tip> void DvostrukaLista<tip>::dodajIspred(const tip &el) {
  Cvor *pom = new Cvor;
  pom->element = el;
  pom->prethodni = nullptr;
  pom->sljedeci = nullptr;
  if (pocetak1 == nullptr) {
    // pocetak1=new Cvor;
    pocetak1 = pom;
    kraj1 = pocetak1;
    trenutni1 = pocetak1;
    velicina++;
  } else if (velicina == 1 || trenutni1 == pocetak1) {
    // Cvor*pom=new Cvor;
    // pom->element=el;
    trenutni1->prethodni = pom;
    pom->sljedeci = trenutni1;
    pocetak1 = pom;
    velicina++;
  } else {
   
    Cvor *pomocnaveza = trenutni1->prethodni;
    trenutni1->prethodni = pom;
    pom->sljedeci = trenutni1;
    pom->prethodni = pomocnaveza;
    pomocnaveza->sljedeci = pom;
    pomocnaveza = nullptr;
    velicina++;
  }
  pom = nullptr;
}

template <typename tip> void DvostrukaLista<tip>::dodajIza(const tip &el) {

  Cvor *pom = new Cvor;
  pom->element = el;
  pom->sljedeci = nullptr;
  pom->prethodni = nullptr;
  if (pocetak1 == nullptr) {
    pocetak1 = pom;
    kraj1 = pom;
    trenutni1 = pocetak1;
    velicina++;
  } else if (velicina == 1) {
    trenutni1->sljedeci = pom;
    pom->prethodni = trenutni1;
    kraj1 = pom;
    velicina++;
  } else if (trenutni1 == kraj1) {
    trenutni1->sljedeci = pom;
    pom->prethodni = trenutni1;
    kraj1 = pom;
    velicina++;
  } else {
    Cvor *pomocnaveza = trenutni1->sljedeci;
    trenutni1->sljedeci = pom;
    pom->prethodni = trenutni1;
    pom->sljedeci = pomocnaveza;
    pomocnaveza->prethodni = pom;
    pomocnaveza = nullptr;
    velicina++;
  }
  pom = nullptr;
}
template <typename tip> void DvostrukaLista<tip>::obrisi() {
  if (trenutni1 == pocetak1)
    kraj();
  
  if (velicina == 0)
    throw;
  else if (velicina == 1) {
    delete trenutni1;
    trenutni1 = nullptr;
    pocetak1 = nullptr;
    kraj1 = nullptr;
    velicina = 0;
  } else if (trenutni1 == pocetak1) {
    Cvor *pom = nullptr;
    trenutni1 = trenutni1->sljedeci;
    pocetak1 = trenutni1;
    delete pom;
    trenutni1->sljedeci = nullptr;
    velicina--;
  } else if (trenutni1 == kraj1) {
    Cvor *pom = trenutni1;
    trenutni1 = trenutni1->prethodni;
    kraj1 = trenutni1;
    delete pom;
    trenutni1->sljedeci = nullptr;
    velicina--;
  } else {
    trenutni1->prethodni->sljedeci = trenutni1->sljedeci;
    auto predji = trenutni1->sljedeci;
    auto pom = trenutni1;
    trenutni1->sljedeci->prethodni = trenutni1->prethodni;
    delete pom;
    trenutni1 = nullptr;
    trenutni1 = predji;
    velicina--;
  }
}
template <typename tip> tip &DvostrukaLista<tip>::operator[](int indeks) {
  if (velicina == 0)
    throw;
  else if (indeks < 0 || indeks > velicina)
    throw range_error("Nedozvoljen indeks");
  else {
    Cvor *pomocniIndeks = dajPocetak();
    for (int i = 0; i < indeks; i++) {
      pomocniIndeks = pomocniIndeks->sljedeci;
    }
    return pomocniIndeks->element;
  }
}
template <typename tip> tip &DvostrukaLista<tip>::operator[](int indeks) const {
  if (velicina == 0)
    throw;
  else if (indeks < 0 || indeks > velicina)
    throw range_error("Nedozvoljen indeks");
  else {
    Cvor *pomocniIndeks = dajPocetak();
    for (int i = 0; i < indeks; i++) {
      pomocniIndeks = pomocniIndeks->sljedeci;
    }
    return pomocniIndeks->element;
  }
}
void RezultatTesta(bool vrijednost) {
  if (vrijednost)
    cout << "OK\n";
  else
    cout << "TEST JE PAO!\n";
}
bool TestKonstruktor() {
  DvostrukaLista<int> l;
  return true;
}
bool TestDodajIza(DvostrukaLista<int> &l) {
  for (int i(1); i <= 5; i++) {
    l.dodajIza(i);
  }
  l.kraj();
  int kraj = l.trenutni();
  l.pocetak();
  int pocetak = l.trenutni();
  return (l.brojElemenata() == 5 && kraj == 2 && pocetak == 1);
}
bool TestPocetak(DvostrukaLista<int> &l) {
  l.pocetak();
  return (l.trenutni() == 1);
}
bool TestDodajIspred(DvostrukaLista<int> &l) {
  l.pocetak();
  l.dodajIspred(12);
  l.pocetak();
  return (l.brojElemenata() == 6 && l.trenutni() == 12);
}
bool TestKraj(DvostrukaLista<int> &l) {
  l.kraj();
  return (l.trenutni() == 2);
}
bool TestTrenutni(DvostrukaLista<int> &l) { return (l.trenutni() == 2); }
bool TestBrojElemenata(DvostrukaLista<int> &l) {
  return l.brojElemenata() == 6;
}
bool TestPrethodni(DvostrukaLista<int> &l) {
  l.kraj();
  l.prethodni();
  int test1 = l.trenutni();
  l.prethodni();
  int test2 = l.trenutni();
  return test1 == 3 && test2 == 4;
}
bool TestSljedeci(DvostrukaLista<int> &l) {
  l.pocetak();
  l.sljedeci();
  int test1 = l.trenutni();
  l.sljedeci();
  int test2 = l.trenutni();
  return test1 == 1 && test2 == 5;
}
bool TestOperatorUglasteZagrade(DvostrukaLista<int> &l) {
  int test1 = l[0];
  int test2 = l[5];
  int test3 = l[3];
  return test1 == 12 && test2 == 2 && test3 == 4;
}
template <typename tip> bool TestOperatorJednako(DvostrukaLista<tip> &l) {
  DvostrukaLista<tip> kopija;
  kopija = l;
  kopija.pocetak();
  int pocetak = kopija.trenutni();
  kopija.kraj();
  int kraj = kopija.trenutni();
  int ElementUSredini = kopija[3];
  return (kopija.brojElemenata() == 6 && pocetak == 12 && kraj == 2 &&
          ElementUSredini == 4);
}
/////////////////second assignment//////////////////
template <typename tip> class Iterator {
  const DvostrukaLista<tip> *pokna2L = nullptr;
  int velicina = 0;
  typename DvostrukaLista<tip>::Cvor *trenutniElement;

public:
  Iterator(const DvostrukaLista<tip> &l) {
    pokna2L = &l;
    trenutniElement = l.trenutni1;
  }
  Iterator(const Lista<tip> &l){
      pokna2L=(DvostrukaLista<tip>*)&l;
      trenutniElement=pokna2L->pocetak1;
  }
  tip trenutni();
  bool sljedeci();
  bool prethodni();
  bool pocetak();
  bool kraj();
};

template <typename tip> 
tip Iterator<tip>::trenutni() {
  if (pokna2L->pocetak1 == nullptr) throw range_error ("opseg premasen");
  return trenutniElement->element;
}
template <typename tip> 
bool Iterator<tip>::sljedeci() {
  if (pokna2L->pocetak1 == nullptr) return false;
  if (pokna2L->kraj1->prethodni == pokna2L->trenutni1) return false;
  trenutniElement = trenutniElement->sljedeci;
  return true;
}
template <typename tip> 
bool Iterator<tip>::prethodni() {
  if (pokna2L->pocetak1 == nullptr)return false;
  if (pokna2L->pocetak1->sljedeci == pokna2L->trenutni1)return false;
  trenutniElement = trenutniElement->prethodni;
  return true;
}
template <typename tip> 
bool Iterator<tip>::pocetak() {
  if (pokna2L->pocetak1 == nullptr)return false;
  trenutniElement = pokna2L->pocetak1;
  return true;
}
template <typename tip> bool Iterator<tip>::kraj() {
  if (pokna2L->pocetak1 == nullptr)return false;
  trenutniElement = pokna2L->kraj1;
  return  true;
}

////////test for iterator class////////////////////////
bool TestIteratorKonstruktor(const DvostrukaLista<int> &l){
    Iterator<int>it(l); return true;
}
bool TestIteratorKraj(Iterator<int> &it){
    it.kraj();
    return it.trenutni()==2;
}
bool TestIteratorPocetak(Iterator<int>&it){
    it.pocetak();
    return it.trenutni()==12;
}
bool TestIteratorTrenutni(Iterator<int>&it){ return it.trenutni()==12;}
bool TestIteratorSljedeci(Iterator<int>&it) {it.sljedeci(); return it.trenutni()==1;}
bool TestIteratorPrethodni(Iterator<int>&it) {it.prethodni(); return it.trenutni()==12;}

template<typename tip>
tip dajMaksimum(const Lista<tip> &n){
    tip max=n[0];
    int vel=n.brojElemenata();
    Iterator<tip> it=n;
    for (int i=0; i<vel; i++){
        if (it.trenutni()>max) max=it.trenutni();
        it.sljedeci();
    }
    return max;
}

int main() {
  DvostrukaLista<int> n;
  
  cout << "Rezultati testova za prvi zadatak:\n";
  RezultatTesta(TestKonstruktor());
  RezultatTesta(TestDodajIza(n)); // 1 5 4 3 2
  RezultatTesta(TestPocetak(n));
  RezultatTesta(TestDodajIspred(n));  // 12 1 5 4 3 2
  RezultatTesta(TestKraj(n));
  RezultatTesta(TestTrenutni(n));
  RezultatTesta(TestBrojElemenata(n));
  RezultatTesta(TestPrethodni(n));
  RezultatTesta(TestSljedeci(n));
  RezultatTesta(TestOperatorUglasteZagrade(n));
  RezultatTesta(TestOperatorJednako(n));

  cout<<"Rezultati testova za klasu Iterator: \n";
  Iterator<int> it (n);
  RezultatTesta(TestIteratorKonstruktor(n));
  RezultatTesta(TestIteratorKraj(it));
  RezultatTesta(TestIteratorPocetak(it));
  RezultatTesta(TestIteratorTrenutni(it));
  RezultatTesta(TestIteratorSljedeci(it));
  RezultatTesta(TestIteratorPrethodni(it));

  cout<<"Najveci element je "<<dajMaksimum(n);
  
  return 0;
}