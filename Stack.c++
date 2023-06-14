/*Task.
Create a generic class named Stack with the following methods:

A constructor that creates an empty stack.
If necessary, a destructor, copy constructor, and assignment operator.
A method named brisi() (delete()) that clears all elements from the stack.
A method named stavi(const Tip& el) (put(const Tip& el)) that pushes an element onto the top of the stack.
A method named skini() (remove()) that returns the element at the top of the stack and removes it from the stack. It should throw an exception if the stack is empty.
A method named vrh() (top()) that returns a reference to the element at the top of the stack without removing it. It should throw an exception if the stack is empty.
A method named brojElemenata() that returns the number of elements currently on the stack.
You can implement this class in any way you like, but keep in mind that the performance of the solution (time and space complexity) will be evaluated. The size of the stack should not be limited.

You are allowed to use a previously implemented class named Lista in the background of the stack class, but you are not allowed to use the library class vector.

For each method of the class, you need to write a function that will demonstrate the correctness of that method
*/

#include <iostream>
using namespace std;
template <typename Tip> class Stek {
  struct Cvor {
    Tip element;
    Cvor *veza = nullptr;
    Cvor *protekli = nullptr;
  };
  Cvor *vrh1 = nullptr;
  Cvor *dno = nullptr;
  Cvor *tekuci;
  int velicina = 0;
  void Kopiraj(const Stek &s);

public:
  Stek() : vrh1(nullptr), dno(nullptr), tekuci(nullptr), velicina(0) {}
  Stek(const Stek &s) { Kopiraj(s); }
  ~Stek();
  Stek &operator=(const Stek &s);
  bool Prazan() const { return (vrh1 == nullptr); }
  void brisi();
  void stavi(const Tip &el);
  Tip skini();
  Tip &vrh() const;
  int brojElemenata() { return velicina; }
};
template <typename tip> tip &Stek<tip>::vrh() const {
  if (Prazan())
    throw range_error("Stek je prazan");
  return vrh1->element;
}
template <typename tip> tip Stek<tip>::skini() {
  if (Prazan())
    throw range_error("Stek je prazan!");
  if (velicina == 1) {
    tip pomocni = vrh1->element;
    delete vrh1;
    vrh1 = nullptr;
    dno = nullptr;
    tekuci = nullptr;
    velicina--;
    return pomocni;
  } else {
    tip el = vrh1->element;
    tekuci = vrh1->protekli;
    delete vrh1;
    vrh1 = tekuci;
    velicina--;
    return el;
  }
}
template <typename tip> void Stek<tip>::stavi(const tip &el) {
  if (velicina == 0) {
    vrh1 = new Cvor;
    vrh1->element = el;
    vrh1->veza = nullptr;
    tekuci = vrh1;
    dno = vrh1;
    velicina++;
  } else {
    auto pom = new Cvor;
    pom->element = el;
    pom->protekli = tekuci;
    vrh1 = pom;
    tekuci->veza = pom;
    tekuci = pom;
    dno = pom;
    pom = nullptr;
    velicina++;
  }
}
template <typename tip> void Stek<tip>::Kopiraj(const Stek &s) {
  Cvor *indeks = s.vrh1;
  for (int i = 0; i < s.velicina - 1; i++)
    indeks = indeks->protekli;
  while (indeks != nullptr) {
    stavi(indeks->element);
    indeks = indeks->veza;
  }
}
template <typename tip> Stek<tip>::~Stek() {
  if (velicina != 0)
    brisi();
}
template <typename tip> void Stek<tip>::brisi() {
  if (vrh1 != nullptr) {
    Cvor *p = vrh1;
    while (vrh1 != nullptr) {
      p = vrh1;
      vrh1 = vrh1->protekli;
      delete p;
      p = nullptr;
    }
    velicina = 0;
  }
}
template <typename tip> Stek<tip> &Stek<tip>::operator=(const Stek &s) {
  if (this == &s)
    return *this;
  brisi();
  Kopiraj(s);
  return *this;
}

void RezultatTesta(bool vrijednost) {
  if (vrijednost)
    cout << "OK\n";
  else
    cout << "TEST JE PAO!\n";
}
bool TestKonstruktor() {
  Stek<int> s;
  return (s.brojElemenata() == 0);
}
template <typename tip> bool TestVrh(const Stek<int> &s) {
  return (s.vrh() == 4);
}
template <typename tip> bool TestBrojElemenata(const Stek<int> &s) {
  return (s.vrh() == 5);
}
template <typename tip> bool TestPrazan(const Stek<int> praznistek) {
  return (praznistek.Prazan());
}
template <typename tip> bool TestBrisi(Stek<int> &s) {
  s.brisi();
  return (s.brojElemenata() == 0);
}
template <typename tip> bool TestStavi(Stek<int> &s) {
  for (int i=1; i<=5; i++) s.stavi(i);
  return (s.vrh() == 5 && s.brojElemenata()==5);
}
template <typename tip> bool TestSkini(Stek<int> &s) {
  s.skini();
  return (s.vrh() == 4);
}
template <typename tip> bool TestKopirajuciKonstruktor(const Stek<tip> &s) {
  Stek<int> ss;
  ss = s;
  int naVrhu = ss.vrh();
  ss.skini();
  ss.skini();
  ss.skini();
  ss.skini();
  int prviEl = ss.vrh();
  return (naVrhu == 5 && prviEl == 1);
}
template <typename tip> bool TestOperatorJednako(const Stek<tip> &s) {
  Stek<int> novi;
  novi = s;
  int naVrhu = novi.vrh();
  novi.skini();
  int jedanIspodVrha = novi.vrh();
  novi.skini();
  novi.skini();
  novi.skini();
  int prvi = novi.vrh();
  return (naVrhu == 5 && jedanIspodVrha == 4 && prvi == 1);
}

int main() {

  Stek<int> s;
  for (int i(1); i <= 5; i++)
    s.stavi(i);
  Stek<int> prazanstek;
  cout<<"Nalazi testova:\n";
  RezultatTesta(TestKonstruktor());
  RezultatTesta(TestKopirajuciKonstruktor(s));
  RezultatTesta(TestBrisi<int>(s));
  RezultatTesta(TestStavi<int>(s));
  RezultatTesta(TestBrojElemenata<int>(s));
  RezultatTesta(TestOperatorJednako(s));
  RezultatTesta(TestPrazan<int>(prazanstek)); 
  RezultatTesta(TestSkini<int>(s));
  RezultatTesta(TestVrh<int>(s));
  
  return 0;
}
