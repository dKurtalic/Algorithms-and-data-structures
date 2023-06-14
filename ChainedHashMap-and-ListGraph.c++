/*
Task 1:
Create a class named "ChainedHashMap" where the collision problem is solved using the method of chaining, where linked lists are sorted by key for better search performance.

Task 2:
Create a class named "ListGraph" derived from the previously given abstract class "DirectedGraph" that implements a graph using an adjacency list. Then implement methods for breadth-first search (BFS) and depth-first search (DFS).

All previously provided methods should work with objects of type "ListGraph" as well as objects of type "MatrixGraph", including objects of type "Node", "Edge", and "EdgeIterator".

*/


#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;
template <typename tip1, typename tip2> struct CvorStr {
  tip1 kljuc;
  tip2 vrijednost;
  CvorStr *sljedeci = nullptr;
};
template <typename tip1, typename tip2> class Mapa {
public:
  Mapa() {}
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tip1 &k) = 0;
  virtual tip2 operator[](tip1 k) const = 0;
  virtual tip2 &operator[](tip1 k) = 0;
  virtual ~Mapa() {}
};

template <typename tip> class GranaIterator;
template <typename tip> class Grana;
template <typename tip> class Cvor;

template <typename tip1, typename tip2>
class HashMapaLan : public Mapa<tip1, tip2> {
  unsigned int (*f)(tip1, unsigned int) = 0;
  unsigned int brojEl = 0, maksimum = 100;
  CvorStr<tip1, tip2> **niz = nullptr;

public:
  HashMapaLan() : maksimum(100), brojEl(0), niz(nullptr) {}
  HashMapaLan(HashMapaLan<tip1, tip2> &kopija);
  HashMapaLan(HashMapaLan<tip1, tip2> &&kopija);
  HashMapaLan &operator=(const HashMapaLan<tip1, tip2> &kopija);
  HashMapaLan &operator=(HashMapaLan<tip1, tip2> &&kopija);
  ~HashMapaLan();
  tip2 &operator[](tip1 klj);
  void obrisi();
  void obrisi(const tip1 &klj);
  int brojElemenata() const;
  void definisiHashFunkciju(unsigned int (*funkcija)(tip1, unsigned int));
  tip2 operator[](tip1 k) const;
};
template <typename tip1, typename tip2>
tip2 HashMapaLan<tip1, tip2>::operator[](tip1 k) const {
  if (f == nullptr)
    throw std::logic_error("Hash funkcija nije definisana");
  unsigned int adr = f(k, maksimum);
  if (niz[adr] != nullptr) {
    auto p = niz[adr];
    while (p != nullptr) {
      if (p->kljuc == k)
        return p->vrijednost;
      p = p->sljedeci;
    }
  }
  return tip2();
}
template <typename tip1, typename tip2>
HashMapaLan<tip1, tip2>::HashMapaLan(HashMapaLan<tip1, tip2> &kopija) {
  maksimum = kopija.maksimum;
  f = kopija.f;
  brojEl = kopija.brojEl;
  niz = new CvorStr<tip1, tip2> *[maksimum];
  for (int i = 0; i < maksimum; i++)
    niz[i] = nullptr;
  for (int i = 0; i < kopija.maksimum; i++) {
    if (kopija.niz[i] != nullptr) {
      niz[i] = new CvorStr<tip1, tip2>();
      niz[i]->vrijednost = kopija.niz[i]->vrijednost;
      niz[i]->kljuc = kopija.niz[i]->kljuc;
      auto pr = kopija.niz[i];
      auto str = niz[i];
      while (pr->sljedeci != nullptr) {
        str->sljedeci = new CvorStr<tip1, tip2>();
        pr = pr->sljedeci;
        str->sljedeci->kljuc = pr->kljuc;
        str->sljedeci->vrijednost = pr->vrijednost;
      }
    }
  }
}
template <typename tip1, typename tip2>
inline HashMapaLan<tip1, tip2>::HashMapaLan(HashMapaLan<tip1, tip2> &&kopija) {
  brojEl = kopija.brojEl, niz = kopija.niz, maksimum = kopija.maksimum,
  f = kopija.f;
}
template <typename tip1, typename tip2>
HashMapaLan<tip1, tip2> &
HashMapaLan<tip1, tip2>::operator=(const HashMapaLan<tip1, tip2> &kopija) {
  if (&kopija == this)
    return *this;
  else {
    for (int i = 0; i < maksimum; i++) {
      if (niz[i] != nullptr) {
        while (niz[i] != nullptr) {
          auto trenutni = niz[i];
          niz[i] = niz[i]->sljedeci;
          delete trenutni;
        }
        niz[i] = nullptr;
      }
    }
    delete[] niz;
    f = kopija.f;
    maksimum = kopija.maksimum;
    brojEl = kopija.brojEl;
    niz = new CvorStr<tip1, tip2> *[maksimum];
    for (int i = 0; i < maksimum; i++)
      niz[i] = nullptr;
    for (int i = 0; i < kopija.maksimum; i++) {
      if (kopija.niz[i] != nullptr) {
        niz[i] = new CvorStr<tip1, tip2>();
        niz[i]->kljuc = kopija.niz[i]->kljuc;
        niz[i]->vrijednost = kopija.niz[i]->vrijednost;
        auto pr = kopija.niz[i];
        auto str = niz[i];
        while (pr->sljedeci != nullptr) {
          str->sljedeci = new CvorStr<tip1, tip2>();
          pr = pr->sljedeci;
          str->sljedeci->kljuc = pr->kljuc;
          str->sljedeci->vrijednost = pr->vrijednost;
        }
      }
    }
  }
  return *this;
}
template <typename tip1, typename tip2>
HashMapaLan<tip1, tip2> &
HashMapaLan<tip1, tip2>::operator=(HashMapaLan<tip1, tip2> &&kopija) {
  if (this == &kopija)
    return *this;
  for (int i = 0; i < maksimum; i++) {
    if (niz[i] != nullptr) {
      while (niz[i]->sljedeci != nullptr) {
        auto trenutni = niz[i];
        niz[i] = niz[i]->sljedeci;
        delete trenutni;
      }
      delete niz[i];
    }
  }
  delete[] niz;
  niz = kopija.niz;
  brojEl = kopija.brojEl;
  maksimum = kopija.maksimum;
  f = kopija.f;
  return *this;
}
template <typename tip1, typename tip2>
HashMapaLan<tip1, tip2>::~HashMapaLan() {
  this->obrisi();
}
template <typename tip1, typename tip2>
tip2 &HashMapaLan<tip1, tip2>::operator[](tip1 k) {
  if (f == nullptr)
    throw std::logic_error("Hash funkcija nije definisana");
  unsigned int adr = f(k, maksimum);
  if (brojEl == 0) {
    niz = new CvorStr<tip1, tip2> *[maksimum];
    niz[adr] = new CvorStr<tip1, tip2>();
    niz[adr]->kljuc = k;
    niz[adr]->vrijednost = tip2();
    brojEl++;
    for (int i = 0; i < maksimum; i++)
      if (i != adr)
        niz[i] = nullptr;
    return niz[adr]->vrijednost;

  } else {
    if (niz[adr] != nullptr) {
      auto pr = niz[adr];
      while (pr != nullptr) {
        if (pr->kljuc == k)
          return pr->vrijednost;
        pr = pr->sljedeci;
      }
    }
    if (niz[adr] == nullptr) {
      niz[adr] = new CvorStr<tip1, tip2>();
      niz[adr]->kljuc = k;
      niz[adr]->vrijednost = tip2();
      brojEl++;
      return niz[adr]->vrijednost;

    } else {
      if (k < niz[adr]->kljuc) {
        auto pom = niz[adr];
        niz[adr] = new CvorStr<tip1, tip2>();
        niz[adr]->kljuc = k;
        niz[adr]->vrijednost = tip2();
        niz[adr]->sljedeci = pom;
        brojEl++;
        return niz[adr]->vrijednost;
      }

      auto prv = niz[adr];
      auto tmp = niz[adr];
      while (tmp->sljedeci != nullptr && k > tmp->kljuc) {
        prv = tmp;
        tmp = tmp->sljedeci;
      }
      if (tmp->sljedeci == nullptr) {
        tmp->sljedeci = new CvorStr<tip1, tip2>();
        tmp->sljedeci->kljuc = k;
        tmp->sljedeci->vrijednost = tip2();
        brojEl++;
        return tmp->sljedeci->vrijednost;
      } else {
        auto p1 = new CvorStr<tip1, tip2>();
        p1->kljuc = k;
        p1->vrijednost = tip2();
        p1->sljedeci = niz[adr];
        prv->sljedeci = p1;

        brojEl++;
        return p1->vrijednost;
      }
    }
  }
}
template <typename tip1, typename tip2> void HashMapaLan<tip1, tip2>::obrisi() {
  if (brojEl == 0)
    return;
  for (int i = 0; i < maksimum; i++) {
    if (niz[i] != nullptr) {
      while (niz[i] != nullptr) {
        auto trenutni = niz[i];
        niz[i] = niz[i]->sljedeci;
        delete trenutni;
      }
      niz[i] = nullptr;
    }
  }
  delete[] niz;
  niz = nullptr;
  maksimum = 100;
  brojEl = 0;
}
template <typename tip1, typename tip2>
void HashMapaLan<tip1, tip2>::obrisi(const tip1 &k) {
  if (brojEl == 0)
    throw std::logic_error("Broj elemenata ne smije biti 0");
  unsigned int adr = f(k, maksimum);
  bool prisutan = false;
  if (niz[adr] != nullptr) {
    if (niz[adr]->kljuc == k) {

      niz[adr]->vrijednost = tip2();
      brojEl--;
      prisutan = true;
      return;
    }
    auto pok = niz[adr];
    while (pok != nullptr) {
      if (pok->sljedeci != nullptr) {
        auto tmp = pok->sljedeci;
        if (k == tmp->kljuc) {
          prisutan = true;
          tmp->vrijednost = tip2();
          break;
        }
      }
      pok = pok->sljedeci;
    }
    brojEl--;
  }
  if (!prisutan)
    throw std::logic_error("Element nije pronadjen");
}
template <typename tip1, typename tip2>
inline int HashMapaLan<tip1, tip2>::brojElemenata() const {
  return brojEl;
}
template <typename tip1, typename tip2>
void HashMapaLan<tip1, tip2>::definisiHashFunkciju(
    unsigned int (*funkcija)(tip1, unsigned int)) {
  if (funkcija == nullptr)
    throw std::logic_error("Hash funkcija nije definisana");
  f = funkcija;
}

template <typename tip> class UsmjereniGraf {
public:
  UsmjereniGraf(){};
  virtual void obrisiGranu(int polazni, int drugi) = 0;
  virtual void postaviBrojCvorova(int broj) = 0;
  virtual Grana<tip> &dajGranu(int pocetak, int drugi) = 0;
  virtual bool postojiGrana(int pocetak, int drugi) = 0;
  virtual Cvor<tip> &dajCvor(int broj) = 0;
  virtual void postaviTezinuGrane(int pocetak, int drugi,
                                  double tezina = 0) = 0;
  virtual double dajTezinuGrane(int pocetak, int drugi) = 0;
  virtual void dodajGranu(int pocetak, int drugi, double tezina = 0) = 0;
  virtual void postaviOznakuGrane(int pocetak, int drugi, tip oznaka) = 0;
  virtual tip dajOznakuGrane(int pocetak, int drugi) = 0;
  virtual void postaviOznakuCvora(int broj, tip oznaka) = 0;
  virtual tip dajOznakuCvora(int broj) = 0;
  virtual ~UsmjereniGraf() {}
  virtual GranaIterator<tip> dajGranePocetak() = 0;
  virtual GranaIterator<tip> dajGraneKraj() = 0;
  virtual int dajBrojCvorova() = 0;
};

template <typename tip> class GranaIterator {
  int drugi, pocetak, poz;
  std::vector<Grana<tip>> grane1;
  UsmjereniGraf<tip> *graf = nullptr;

public:
  GranaIterator(UsmjereniGraf<tip> &g, std::vector<Grana<tip>> gr, int p, int d,
                int poz);
  GranaIterator(const GranaIterator<tip> &grana);
  Grana<tip> operator*();
  GranaIterator<tip> &operator=(const GranaIterator<tip> &g);
  GranaIterator operator++(int);
  GranaIterator &operator++();
  bool operator==(const GranaIterator<tip> &u) const;
  bool operator!=(const GranaIterator<tip> &u) const;
};
template <typename tip>
inline GranaIterator<tip>::GranaIterator(UsmjereniGraf<tip> &g,
                                         std::vector<Grana<tip>> gr, int prvi,
                                         int drugi, int poz) {
  grane1 = gr, poz = poz, graf = &g, drugi = drugi, pocetak = prvi;
}
template <typename tip> Grana<tip> GranaIterator<tip>::operator*() {
  int br = 0;
  for (int i = 0; i < graf->dajBrojCvorova(); i++) {
    for (int j = 0; j < graf->dajBrojCvorova(); j++) {
      if (graf->postojiGrana(i, j) && br < poz) {
        br++;
      } else if (graf->postojiGrana(i, j) && br >= poz) {
        return graf->dajGranu(i, j);
      }
    }
  }
  throw std::logic_error("Nepostojeća grana");
}
template <typename tip>
GranaIterator<tip>::GranaIterator(const GranaIterator<tip> &g) {
  drugi = g.drugi, pocetak = g.pocetak, grane1 = g.grane1, poz = g.poz;
}
template <typename tip>
bool GranaIterator<tip>::operator==(const GranaIterator<tip> &it) const {
  return (pocetak == it.pocetak && drugi == it.drugi);
}

template <typename tip>
inline GranaIterator<tip> &
GranaIterator<tip>::operator=(const GranaIterator<tip> &g) {
  drugi = g.drugi, poz = g.poz, grane1 = g.grane1, pocetak = g.pocetak;
}
template <typename tip> GranaIterator<tip> GranaIterator<tip>::operator++(int) {
  poz++;
  return *this;
}
template <typename tip> GranaIterator<tip> &GranaIterator<tip>::operator++() {
  poz++;
  return *this;
}
template <typename tip>
bool GranaIterator<tip>::operator!=(const GranaIterator<tip> &it) const {
  return (pocetak == it.pocetak && drugi == it.drugi);
}

template <typename tip> class Grana {
  int prva, druga;
  double tezina = 0;
  tip oznaka;
  UsmjereniGraf<tip> *graf = nullptr;

public:
  Grana(const Grana<tip> &grancica);
  Grana(int a, int b, UsmjereniGraf<tip> &grancica, double tez = 0);

  bool operator==(Grana<tip> gr);
  bool operator!=(Grana<tip> gr);

  void postaviTezinu(double t = 0);
  double dajTezinu();

  tip dajOznaku();
  void postaviOznaku(tip ozn);

  Cvor<tip> dajPolazniCvor();
  Cvor<tip> dajDolazniCvor();
};

template <typename tip>
inline Grana<tip>::Grana(int a, int b, UsmjereniGraf<tip> &grancica,
                         double tez) {
  prva = a, druga = b, graf = &grancica, tezina = tez;
}
template <typename tip> inline Grana<tip>::Grana(const Grana<tip> &g) {
  prva = g.prva, druga = g.druga, graf = g.graf, oznaka = g.oznaka,
  tezina = g.tezina;
}
template <typename tip> inline double Grana<tip>::dajTezinu() { return tezina; }
template <typename tip> inline void Grana<tip>::postaviTezinu(double t) {
  graf->dajGranu(prva, druga).tezina = t, tezina = t;
}
template <typename tip> inline tip Grana<tip>::dajOznaku() { return oznaka; }
template <typename tip> inline void Grana<tip>::postaviOznaku(tip ozn) {
  graf->dajGranu(prva, druga).oznaka = ozn, oznaka = ozn;
}
template <typename tip> bool Grana<tip>::operator!=(Grana<tip> gr) {
  return (gr.p == prva && gr.d == druga);
}
template <typename tip> bool Grana<tip>::operator==(Grana<tip> gr) {
  return (gr.prva == prva && gr.druga == druga);
}
template <typename tip> inline Cvor<tip> Grana<tip>::dajDolazniCvor() {
  return graf->dajCvor(druga);
}
template <typename tip> inline Cvor<tip> Grana<tip>::dajPolazniCvor() {
  return graf->dajCvor(prva);
}

template <typename tip> class Cvor {
  int redniBroj;
  tip oznaka;
  UsmjereniGraf<tip> *graf = nullptr;

public:
  Cvor(int rbroj, UsmjereniGraf<tip> &g);
  int dajRedniBroj() const;
  tip dajOznaku() const;
  void postaviOznaku(tip ozn);
};
template <typename tip>
inline Cvor<tip>::Cvor(int rbroj, UsmjereniGraf<tip> &g) {
  redniBroj = rbroj, graf = &g;
}
template <typename tip> inline int Cvor<tip>::dajRedniBroj() const {
  return redniBroj;
}
template <typename tip> inline void Cvor<tip>::postaviOznaku(tip ozn) {
  oznaka = ozn;
}
template <typename tip> inline tip Cvor<tip>::dajOznaku() const {
  return oznaka;
}

template <typename tip> class ListaGraf : public UsmjereniGraf<tip> {
  std::vector<Grana<tip>> grane1;
  std::vector<std::vector<int>> lista;
  std::vector<Cvor<tip>> cvorovii;

public:
  ListaGraf(int broj);
  ListaGraf(const ListaGraf<tip> &kopija);
  ListaGraf<tip> &operator=(const ListaGraf<tip> &kopija);
  int dajBrojCvorova();
  void postaviBrojCvorova(int broj);
  void dodajGranu(int pocetak, int drugi, double tezina = 0);
  void obrisiGranu(int prvi, int drugi);
  void postaviOznakuCvora(int broj, tip oznaka);
  tip dajOznakuCvora(int broj);
  void postaviOznakuGrane(int prvi, int drugi, tip oznaka);
  Cvor<tip> &dajCvor(int broj);
  Grana<tip> &dajGranu(int prvi, int drugi);
  double dajTezinuGrane(int prvi, int drugi);
  void postaviTezinuGrane(int prvi, int drugi, double tezina = 0);
  tip dajOznakuGrane(int prvi, int drugi);
  bool postojiGrana(int prvi, int drugi);
  GranaIterator<tip> dajGranePocetak();
  GranaIterator<tip> dajGraneKraj();
  ~ListaGraf() {}
};
template <typename tip> ListaGraf<tip>::ListaGraf(int broj) {
  if (broj <= 0)
    throw std::logic_error("Broj ne može biti manji / jednak nuli");
  for (int i = 0; i < broj; i++) {
    cvorovii.push_back(Cvor<tip>(i, *this));
    lista.push_back(std::vector<int>());
  }
}
template <typename tip>
inline ListaGraf<tip>::ListaGraf(const ListaGraf<tip> &kopija) {
  lista = kopija.lista, cvorovii = kopija.cvorovii, grane1 = kopija.grane1;
}
template <typename tip>
ListaGraf<tip> &ListaGraf<tip>::operator=(const ListaGraf<tip> &kopija) {
  if (&kopija == this)
    return *this;
  else
    {
      lista = kopija.lista;
      cvorovii = kopija.cvorovii;
      grane1 = kopija.grane1;
    }
  return *this;
}
template <typename tip> inline int ListaGraf<tip>::dajBrojCvorova() {
  return cvorovii.size();
}
template <typename tip> void ListaGraf<tip>::postaviBrojCvorova(int broj) {
  if (broj < lista.size())
    throw std::domain_error("Error");
  int prosla = lista.size();
  for (int i = prosla; i < broj; i++) {
    cvorovii.push_back(Cvor<tip>(i, *this));
    lista.push_back(std::vector<int>());
  }
}
template <typename tip>
void ListaGraf<tip>::dodajGranu(int prvi, int drugi, double tezina) {
  if (prvi >= cvorovii.size() || prvi < 0 || drugi >= cvorovii.size() ||
      drugi < 0)
    throw std::domain_error("Cvor nije validan");

  for (int j = 0; j < lista[prvi].size(); j++) {
    if (lista[prvi][j] == drugi) {
      throw std::domain_error("Grana je vec pronadjena");
    }
  }
  lista[prvi].push_back(drugi);
  grane1.push_back(Grana<tip>(prvi, drugi, *this, tezina));
}
template <typename tip> void ListaGraf<tip>::obrisiGranu(int prvi, int drugi) {
  for (int j = 0; j < lista[prvi].size(); j++) {
    if (drugi == lista[prvi][j]) {
      lista[prvi].erase(lista[prvi].begin() + j);
      break;
    }
  }
  for (int i = 0; i < grane1.size(); i++) {
    if (Grana<tip>(prvi, drugi, *this, 0) == grane1[i]) {
      grane1.erase(grane1.begin() + i);
      return;
    }
  }
}
template <typename tip>
void ListaGraf<tip>::postaviTezinuGrane(int prvi, int drugi, double tezina) {
  for (int i = 0; i < grane1.size(); i++) {
    if (grane1[i] == Grana<tip>(prvi, drugi, *this, tezina)) {
      grane1[i].postaviTezinu(tezina);
      return;
    }
  }
  throw std::logic_error("Nepostojeca grana");
}
template <typename tip>
double ListaGraf<tip>::dajTezinuGrane(int prvi, int drugi) {
  for (int i = 0; i < grane1.size(); i++) {
    if (grane1[i] == Grana<tip>(prvi, drugi, *this, 0)) {
      return grane1[i].dajTezinu();
    }
  }
  throw std::logic_error("Nepostojeca grana");
}
template <typename tip> bool ListaGraf<tip>::postojiGrana(int prvi, int drugi) {
  for (int j = 0; j < lista[prvi].size(); j++) {
    if (drugi == lista[prvi][j]) {
      return true;
    }
  }
  return false;
}
template <typename tip>
void ListaGraf<tip>::postaviOznakuCvora(int broj, tip oznaka) {
  if (broj >= cvorovii.size() || broj < 0) {
    throw std::logic_error("Cvor ne postoji");
  }
  cvorovii[broj].postaviOznaku(oznaka);
}
template <typename tip>
void ListaGraf<tip>::postaviOznakuGrane(int prvi, int drugi, tip oznaka) {
  for (int i = 0; i < grane1.size(); i++) {
    if (grane1[i] == Grana<tip>(prvi, drugi, *this, 0)) {
      grane1[i].postaviOznaku(oznaka);
      return;
    }
  }
  throw std::domain_error("Grana nije nadjena");
}
template <typename tip> tip ListaGraf<tip>::dajOznakuCvora(int broj) {
  if (broj >= cvorovii.size() || broj < 0) {
    throw std::domain_error("Cvor ne postoji");
  }
  return cvorovii[broj].dajOznaku();
}
template <typename tip> inline Cvor<tip> &ListaGraf<tip>::dajCvor(int broj) {
  return cvorovii[broj];
}
template <typename tip> GranaIterator<tip> ListaGraf<tip>::dajGraneKraj() {
  return GranaIterator<tip>(
      *this, grane1, grane1[grane1.size() - 1].dajPolazniCvor().dajRedniBroj(),
      grane1[grane1.size() - 1].dajDolazniCvor().dajRedniBroj(),
      grane1.size() - 1);
}
template <typename tip> GranaIterator<tip> ListaGraf<tip>::dajGranePocetak() {
  return GranaIterator<tip>(*this, grane1,
                            grane1[0].dajPolazniCvor().dajRedniBroj(),
                            grane1[0].dajDolazniCvor().dajRedniBroj(), 0);
}
template <typename tip>
Grana<tip> &ListaGraf<tip>::dajGranu(int prvi, int drugi) {
  for (int i = 0; i < grane1.size(); i++) {
    if (grane1[i] == Grana<tip>(prvi, drugi, *this, 0)) {
      return grane1[i];
    }
  }
  throw std::domain_error("Nije nadjena");
}
template <typename tip>
tip ListaGraf<tip>::dajOznakuGrane(int prvi, int drugi) {
  for (int i = 0; i < grane1.size(); i++) {
    if (grane1[i] == Grana<tip>(prvi, drugi, *this, 0)) {
      return grane1[i].dajOznaku();
    }
  }
  throw std::domain_error("Grana nije nadjena");
}

template <typename tip>
void bfs(UsmjereniGraf<tip> *graf, vector<Cvor<tip>> &bfs_obilazak,
         Cvor<tip> pocetni_cvor) {
  std::queue<Cvor<tip>> red;
  red.push(pocetni_cvor);
  bfs_obilazak.push_back(pocetni_cvor);

  while (bfs_obilazak.size() != graf->dajBrojCvorova() && red.empty() != true) {
    Cvor<tip> cvor = red.front();
    red.pop();
    bool vecBio = false;
    vector<Cvor<tip>> izlaz;

    for (int i = 0; i < graf->dajBrojCvorova(); i++) {
      if (graf->postojiGrana(cvor.dajRedniBroj(), i)) {
        izlaz.push_back(graf->dajCvor(i));
        red.push(graf->dajCvor(i));
      }
    }

    for (int i = 0; i < izlaz.size(); i++) {
      vecBio = false;
      for (int j = 0; j < bfs_obilazak.size(); j++) {
        if (izlaz[i].dajRedniBroj() == bfs_obilazak[j].dajRedniBroj())
          vecBio = true;
      }
      if (!vecBio)
        bfs_obilazak.push_back(izlaz[i]);
    }
  }
}
template <typename tip>
void dfs(UsmjereniGraf<tip> *graf, vector<Cvor<tip>> &dfs_obilazak,
         Cvor<tip> cvor) {
  bool vecBio = false;
  for (int i = 0; i < dfs_obilazak.size(); i++) {
    if (dfs_obilazak[i].dajRedniBroj() == cvor.dajRedniBroj()) {
      vecBio = true;
      break;
    }
  }
  if (!vecBio)
    dfs_obilazak.push_back(cvor);
  for (int i = 0; i < graf->dajBrojCvorova(); i++) {
    if (graf->postojiGrana(cvor.dajRedniBroj(), i) && !vecBio) {
      dfs(graf, dfs_obilazak, graf->dajCvor(i));
    }
  }
}

int main() {
  
  return 0;
}
