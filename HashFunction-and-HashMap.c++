#include <iostream>
#include <string>
#include <vector>
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

template <typename tip1, typename tip2> class NizMapa : public Mapa<tip1, tip2> {
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

template <typename tip1, typename tip2>NizMapa<tip1, tip2>::NizMapa(const NizMapa<tip1, tip2> &mapa) { velicina = mapa.velicina; brElemenata =
 mapa.brElemenata; trenutni = mapa.trenutni; niz = new std::pair<tip1, tip2>
 *[velicina]; for (int i = 0; i < brElemenata; i++) { niz[i] = new
 std::pair<tip1, tip2>(*mapa.niz[i]);
  }
 }
template <typename tip1, typename tip2> tip2 NizMapa<tip1,tip2>::operator[](const tip1 k) const { for (int i = 0; i < brElemenata; i++) {
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  return tip2();
 }
template <typename tip1, typename tip2>NizMapa<tip1, tip2> &NizMapa<tip1,tip2>::operator=(const NizMapa<tip1, tip2> &nm) { if (this == &nm) return *this;
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
  return *this;}
template <typename tip1, typename tip2> tip2 &NizMapa<tip1,tip2>::operator[](const tip1 &k) {
     for (int i = 0; i < brElemenata; i++) { if
 (niz[i]->first == k) return niz[i]->second;
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
template <typename tip1, typename tip2> void NizMapa<tip1, tip2>::obrisi(const tip1 k) { for (int i = 0; i < brElemenata; i++) { if (niz[i]->first == k) {
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
  brElemenata = 0;}


template <typename tip1, typename tip2> class HashMapa : public Mapa<tip1, tip2> {
  unsigned int (*hashFunkcija)(tip1 kljuc, unsigned int max);
  std::pair<tip1, tip2> **niz=nullptr;
  unsigned int max;
  int brElemenata;

 public:
  void definisiHashFunkciju(unsigned int (*fun)(tip1 ulaz, unsigned int max));
  HashMapa() : max(100), brElemenata(0), hashFunkcija(nullptr) {
    niz = new std::pair<tip1, tip2> *[max] {};
  }
  HashMapa(const HashMapa<tip1, tip2> &hm);
  int brojElemenata() const override { return brElemenata; }
  tip2 operator[](const tip1 k) const override;
  tip2 &operator[](const tip1 &k) override;
  void obrisi(const tip1 k) override;
  void obrisi() override;
  ~HashMapa() {
     for (int i=0; i<max; i++) {
         delete niz[i];
     niz[i]=nullptr;
     }
      delete[] niz;
      max=0;
      brElemenata=0;
      hashFunkcija=nullptr;
  }
  HashMapa &operator=(HashMapa<tip1,tip2> &&kopija);
    HashMapa operator=(const HashMapa<tip1,tip2> &kopija);
 };
template<typename tip1,typename tip2>HashMapa<tip1,tip2> HashMapa<tip1,tip2>::operator=(const HashMapa<tip1,tip2> &kopija){
    if (&kopija==this) return *this;
    else {

        hashFunkcija=nullptr;
        for (int i=0; i<max; i++) delete niz[i], niz[i]=nullptr;
        
           delete[] niz;
           brElemenata=kopija.brElemenata;
        max=kopija.max;
        niz=new std::pair<tip1,tip2> *[max];
        hashFunkcija=kopija.hashFunkcija;
        for (int i=0; i<max; i++){
            if (kopija.niz[i]){
                niz[i]=new std::pair<tip1,tip2>(*kopija.niz[i]);
            }
            else niz[i]=nullptr;
        }
        return *this;
    }}
template<typename tip1,typename tip2>HashMapa<tip1,tip2> &HashMapa<tip1,tip2>::operator=(HashMapa<tip1,tip2> &&kopija){
    if (&kopija== this) return *this;
    else {
        brElemenata=kopija.brojElemenata();
        delete[] niz;
        max=kopija.max;
        hashFunkcija=kopija.hashFunkcija;
        niz=new std::pair<tip1,tip2>[max];
        for (int i=0;i<max;i++) niz[i]=kopija.niz[i];
        return *this;
    }}
template <typename tip1, typename tip2>void HashMapa<tip1, tip2>::obrisi(const tip1 kljuc) {
  int posljednja = hashFunkcija(kljuc, max);
  if (niz[posljednja]->first == kljuc) {
    brElemenata--;
    delete niz[posljednja];
    niz[posljednja] = new std::pair<tip1, tip2>(tip1(), tip2());
    return;
  }
  bool prekini = false;
  for (int i = posljednja + 1; i < max; i++) {
    if (!niz[i]) {
      prekini = true;
      break;
    }
    if (niz[i]->first == kljuc) {
      brElemenata--;
      delete niz[i];
      niz[i] = new std::pair<tip1, tip2>(tip1(), tip2());
    }
  }
  for (int i = 0; i < posljednja; i++) {
    if (prekini)
      break;
    if (!niz[i]) {
      prekini = true;
      break;
    }
    if (niz[i]->first == kljuc) {
      brElemenata--;
      delete niz[i];
      niz[i] = new std::pair<tip1, tip2>(tip1(), tip2());
    }
  }}
template <typename tip1, typename tip2> tip2 HashMapa<tip1, tip2>::operator[](const tip1 k) const {
  if (hashFunkcija == nullptr)
    throw std::logic_error("Neispravna hash funkcija");
  bool prekini = false;
  unsigned int p = 0;
  p = hashFunkcija(k, max);
  for (int i = p; i < max; i++) {
    if (!niz[i]) {
      prekini = true;
      break;
    }
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  for (int i = 0; i < p; i++) {
    if (prekini)
      break;
    if (!niz[i]) {
      prekini = true;
      break;
    }
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  return tip2();}
template <typename tip1, typename tip2> tip2 &HashMapa<tip1, tip2>::operator[](const tip1 &k) {
  if (hashFunkcija == nullptr)
    throw std::logic_error("Nevalidna hash funkcija!");
    bool prekini=false;
  int stariMax = 0;
  std::pair<tip1, tip2> **pom=nullptr;
  int p = hashFunkcija(k, max);
  int pronadjeno = 0;
  for (int i = p; i < max; i++) {
    if (!niz[i]) {
      pronadjeno = 1;
      break;
    }
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  for (int i = 0; i < p; i++) {
     if (pronadjeno) break;
    if (!niz[i]) {
      pronadjeno = 1;
      break;
    }
    if (niz[i]->first == k)
      return niz[i]->second;
    if (niz[i]->first == k)
      return niz[i]->second;
  }
  if (max == brElemenata) {
    stariMax = max;
    int hash = hashFunkcija(k, max);
    if (hash < 0)
      hash = -hash;
    max = 2 * max + stariMax;
    pom = new std::pair<tip1, tip2> *[max] {};

    for (int i = 0; i < stariMax; i++) {
      auto izracunaj = hashFunkcija(niz[i]->first, max);
      if (niz[i]) {
        bool umetnuti = false;
        if (pom[izracunaj] == nullptr) {
          pom[izracunaj] =
              new std::pair<tip1, tip2>(niz[i]->first, niz[i]->second);
          umetnuti = true;
        } else {
          for (unsigned int l = 1 + hashFunkcija(k, max); l < max; l++) {
            if (umetnuti)
              break;
            if (pom[l] == nullptr) {
              umetnuti = true;
              pom[l] = new std::pair<tip1, tip2>(niz[i]->first, niz[i]->second);
            }
          }
          int pom2 = hashFunkcija(k, max);
          for (int l = 0; l < pom2; l++) {
            if (umetnuti)
              break;
            if (pom[l] == nullptr) {
              umetnuti = true;
              pom[l] = new std::pair<tip1, tip2>(niz[i]->first, niz[i]->second);
            }
          }
        }
      }
    }
    for (int i = 0; i < stariMax; i++)
     { delete niz[i]; niz[i] = nullptr;}

    delete[] niz;
    niz = pom;
  }
  auto vrijednost = hashFunkcija(k, max);
  if (niz[vrijednost] != nullptr) {
    for (int i = vrijednost + 1; i < max; i++) {
      if (niz[i] == nullptr ||
          (niz[i]->first == tip1() && niz[i]->second == tip2())) {
        niz[i] = new std::pair<tip1, tip2>(k, tip2());
        brElemenata++;
        return niz[i]->second;
      }
    }
    for (int i = 0; i < vrijednost; i++) {
      if (niz[i] == nullptr ||
          (niz[i]->first == tip1() && niz[i]->second == tip2())) {
        delete niz[i];
        niz[i] = new std::pair<tip1, tip2>(k, tip2());
        brElemenata++;
        return niz[i]->second;
      }
    }
  }
   brElemenata++;
  unsigned int var = hashFunkcija(k, max);
  niz[var] = new std::pair<tip1, tip2>(k, tip2());
  delete pom;
  pom=nullptr; 
  return niz[var]->second;}
template <typename tip1, typename tip2>HashMapa<tip1, tip2>::HashMapa(const HashMapa<tip1, tip2> &hm) {
  max = hm.max;
  brElemenata = hm.brElemenata;
  hashFunkcija = hm.hashFunkcija;
  niz = new std::pair<tip1, tip2> *[max] {};
  for (int i = 0; i < max; i++) {
 
    if (hm.niz[i] == nullptr)
      niz[i] = nullptr;
    else
      niz[i] = new std::pair<tip1, tip2>(*hm.niz[i]);
  }}
template <typename tip1, typename tip2>inline void HashMapa<tip1, tip2>::definisiHashFunkciju(
    unsigned int (*fun)(tip1 ulaz, unsigned int max)) {
  hashFunkcija = fun;}
template <typename tip1, typename tip2> void HashMapa<tip1, tip2>::obrisi() {
  for (int i = 0; i < max; i++)
    {delete niz[i]; niz[i] = nullptr;}
  delete [] niz;
  max = 100;
  brElemenata = 0;
  niz=new std::pair<tip1,tip2> *[max]{};}
int probnaFunkcija(int ulaz, int max) {
  int zbir = 100;
  zbir = zbir * 33 + ulaz;
  return zbir % max;}


int main(){
 
  
  return 0;
}
