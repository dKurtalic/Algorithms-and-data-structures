/*
Implement the class DvostraniRed, which has the characteristics of the library class deque. 
In addition to the constructor, destructor, copy constructor, assignment operator, brisi() - delete(), and brojElemenata() - numberOfElements() methods, the class DvostraniRed should have the following methods:

staviNaVrh() (put at the top) 
skiniSaVrha() (take from the top)
staviNaCelo() (put at the front)
skiniSaCela() (take from the front)
vrh() (top)
celo() (front)
These methods should have the same number and types of parameters as the methods of the Stek and Red classes. All methods should have a complexity of O(1), except for the brisi() method. When implementing the DvostraniRed class, the use of library classes such as stack, queue, deque, and vector is not allowed.
*/

#include <iostream>
#include <new>
using namespace std;
template <typename tip> class DvostraniRed {
  struct Cvor {
    tip element;
    Cvor *prethodni = nullptr;
    Cvor *sljedeci = nullptr;
    Cvor(tip el) : prethodni(nullptr), sljedeci(nullptr), element(el) {}
  };
  Cvor *pocetak, *kraj;
  int velicina = 0;

public:
  DvostraniRed<tip>() : pocetak(nullptr), kraj(nullptr), velicina(0) {}
  DvostraniRed<tip>(const DvostraniRed<tip> &red);
  void staviNaVrh(tip el);
  tip skiniSaVrha();
  void staviNaCelo(tip el);
  tip skiniSaCela();
  tip vrh() const { if (kraj==nullptr) throw range_error ("Red je prazan"); return kraj->element; }
  tip celo() const { if (pocetak==nullptr) throw range_error ("Red je prazan");  return pocetak->element; }
  int brojElemenata() const { return velicina; }
  int brojElemanata() {return velicina;}
  DvostraniRed<tip> &operator=(const DvostraniRed<tip> &r);
  void brisi();
  ~DvostraniRed<tip>() {
    if (velicina != 0)
      brisi();
  }
};
template <typename tip> void DvostraniRed<tip>::staviNaVrh(tip el) {
  Cvor *pom = new Cvor(el);

  if (velicina == 0) {
    pocetak = pom;
    kraj = pom;
    velicina++;
  } else {
    Cvor *pom2 = kraj;
    kraj->sljedeci = pom;
    kraj = pom;
    kraj->prethodni = pom2;
    velicina++;
  }
}

template <typename tip> tip DvostraniRed<tip>::skiniSaVrha() {
  if (velicina == 0)
    throw range_error("Red je prazan");
  Cvor *pom = kraj->prethodni;
  tip vrati = kraj->element;
  delete kraj;
  kraj = pom;
  pom = nullptr;
  velicina--;
    if (velicina==0){
        pocetak=nullptr; kraj=nullptr;
    }
  return vrati;
}

template <typename tip> void DvostraniRed<tip>::staviNaCelo(tip el) {
  Cvor *pom = new Cvor(el);
  if (velicina == 0) {
    pocetak = pom;
    kraj = pom;
    velicina++;
  } else {
    Cvor *pom2 = pocetak;
    pocetak->prethodni = pom;
    pocetak = pom;
    pocetak->sljedeci = pom2;
    velicina++;
  }
}

template <typename tip> tip DvostraniRed<tip>::skiniSaCela() {
  if (velicina == 0)
    throw range_error("Red je prazan");
    Cvor *pom = pocetak->sljedeci;
    tip rez = pocetak->element;
    delete pocetak;
    pocetak = pom;
    pom = nullptr;
    velicina--;
    if (velicina==0){
        pocetak=nullptr; kraj=nullptr;
    }
    return rez;
}

template <typename tip>
DvostraniRed<tip>::DvostraniRed(const DvostraniRed<tip> &r) {
  int vel = r.brojElemenata();
  Cvor *trenutniR = r.pocetak;
  for (int i = 0; i < vel; i++) {
    staviNaVrh(trenutniR->element);
    trenutniR = trenutniR->sljedeci;
  }
}

template <typename tip>
DvostraniRed<tip> &DvostraniRed<tip>::operator=(const DvostraniRed<tip> &r) {
  if (this == &r)
    return *this;

  while (velicina != 0) {
    skiniSaVrha();
  }
  pocetak = nullptr;
  kraj = nullptr;

  int vel = r.brojElemenata();
  Cvor *trenutniR = r.pocetak;
  for (int i = 0; i < vel; i++) {
    staviNaVrh(trenutniR->element);
    trenutniR = trenutniR->sljedeci;
  }
  return *this;
}

template <typename tip> void DvostraniRed<tip>::brisi() {
  if (velicina == 0)
    throw range_error("Red je prazan");
  while (velicina != 0)
    skiniSaVrha();
}
void RezultatTesta(bool vrijednost) {
  if (vrijednost)
    cout << "OK\n";
  else
    cout << "TEST JE PAO!\n";
}
bool TestKonstruktor(){
    DvostraniRed<int> r; return true;
}
bool TestKopirajuciKonstruktor(DvostraniRed<int> &r){
    DvostraniRed<int> kopija(r); return true;
}
bool TestStaviNaCelo(DvostraniRed<int> &r){
    for (int i=5; i>=1;i--) r.staviNaCelo(i);
    return (r.brojElemanata()==5 && r.celo()==1 && r.vrh()==5);
}
bool TestStaviNaVrh(DvostraniRed<int> &r){
    for (int i=6; i<=10;i++) r.staviNaVrh(i);
    return (r.brojElemenata()==10 && r.celo()==1 && r.vrh()==10);
}
bool TestBrojElemenata(const DvostraniRed<int> &r){
    return (r.brojElemenata()==10);
}
bool TestOperatorJednako(DvostraniRed<int> &r){
    DvostraniRed <int> kopija;
    kopija=r;
    return (r.brojElemenata()==10 && r.vrh()==10 && r.celo()==1);
}
bool TestSkiniSaVrha(DvostraniRed<int> &r){
    int skinuti=r.skiniSaVrha();
    return (r.brojElemanata()==9 && skinuti==10);
}
bool TestSkiniSaCela(DvostraniRed<int> &r){
    int skinuti=r.skiniSaCela();
    return (r.brojElemenata()==8 && skinuti==1);
}
bool TestVrh(const DvostraniRed<int> &r){
    return r.vrh()==9;
}
bool TestCelo(const DvostraniRed<int> &r){
    return r.celo()==2;
}
bool TestBrisi(DvostraniRed<int> &r){
    r.brisi();
    return (r.brojElemenata()==0);
}

int main() {    
    DvostraniRed<int> r;
 
    cout<<"Rezultati testova za prvi zadatak:\n";
    RezultatTesta(TestKonstruktor());
    RezultatTesta(TestStaviNaCelo(r)); 
    RezultatTesta(TestStaviNaVrh(r)); 
    RezultatTesta(TestKopirajuciKonstruktor(r));
    RezultatTesta(TestBrojElemenata(r));
    RezultatTesta(TestOperatorJednako(r));
    RezultatTesta(TestSkiniSaVrha(r)); 
    RezultatTesta(TestSkiniSaCela(r));
    RezultatTesta(TestVrh(r));
    RezultatTesta(TestCelo(r));
    RezultatTesta(TestBrisi(r));
  return 0;
}
