/*
Implement the function:
void pretraga(Stek<vector<int> >& s, int trazeni)
The function takes a stack s and a parameter trazeni (the element to search for). 
The function should find the element in one of the vectors that are on the stack. 
Once the appropriate vector is found, further searching should be done using binary search within that vector. 
The stack should remain unchanged after the function call. 
If the element is not found in any of the vectors, it should print "Nema elementa" (No element found). 
If the element is found, it should print the index of the element in the found vector and the number of vectors below the found vector on the stack. Assume that the elements in each vector are sorted in ascending order, and all elements in each vector are smaller than all elements in the vector above it on the stack.


Example: For the input parameters (the first element is at the bottom of the stack):
s = {{1,2,3,4,5},{6,8},{9,10,130},{157,226,3424}}
trazeni = 10
*/


#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstring>

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
  // sad je indeks pok na pocetak steka s
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
int brojac=0;
int velicinaSteka=0;
bool nadjen=false;
std::string ispisi="";

void pretraga(Stek<std::vector<int>> &s, int trazeni) {
    
    if (brojac!=0 && s.brojElemenata()==0) {cout<<"Nema elementa"; ispisi+="Nema elementa";}
    else if (s.brojElemenata() == 0){
        cout<<"Nema elementa"; ispisi+="Nema elementa";
    }
    else{

        if (brojac==0) velicinaSteka=s.brojElemenata();
        int velicina = s.brojElemenata();
    
        std::vector<int> pomocni = s.skini();

        int vrh = pomocni.size() - 1;
    
        if ( pomocni.size()!=0 && pomocni[0]<=trazeni && pomocni[vrh]>=trazeni ) {
                //cout<<"USAO "<<pomocni[0]<<endl;
                int dno = 0;
                int sredina;
                while (vrh > dno) {
                sredina = (vrh + dno) / 2;

                if (pomocni[sredina] < trazeni)
                    dno = sredina + 1;
                else
                    vrh = sredina;
                }
            
                if (pomocni[vrh] == trazeni) {
                    nadjen=true;
                    cout << vrh <<" ";
                    ispisi+=vrh+'0';
                    }
            }
            brojac++;
            if (!nadjen) { pretraga(s,trazeni); }
            s.stavi(pomocni);

            if (velicinaSteka==s.brojElemenata() && nadjen){
                cout<<velicinaSteka-brojac; 
                ispisi+=" "; ispisi+=velicinaSteka-brojac+'0';
            }

    }

}

void RezultatTesta(bool vrijednost) {
  if (vrijednost)
    cout << "OK\n";
  else
    cout << "TEST JE PAO!\n";
}

bool Test1(Stek<std::vector<int>> &s){ 
    ispisi="";
    nadjen=false;
    velicinaSteka=0;
    brojac=0;
    cout<<"Dobijeni rezultat: ";
    pretraga(s,2);
    std::string test="1 0";
    cout<<"\t| Ocekivani rezultat: "<<ispisi;
    cout<<" --> Nalaz testa1: ";
    return (ispisi==test);
}
bool Test2(Stek<std::vector<int>> &s){ 
    ispisi="";
    nadjen=false;
    velicinaSteka=0;
    brojac=0;
    cout<<"Dobijeni rezultat: ";
    pretraga(s,98);
    std::string test="Nema elementa";
    cout<<" | Ocekivani rezultat: "<<ispisi;
    cout<<" --> Nalaz testa1: ";
    return (ispisi==test);
}
bool Test3(Stek<std::vector<int>> &s){ 
    ispisi="";
    nadjen=false;
    velicinaSteka=0;
    brojac=0;
    cout<<"Dobijeni rezultat: ";
    pretraga(s,15);
    std::string test="2 1";
    cout<<" | Ocekivani rezultat: "<<ispisi;
    cout<<" --> Nalaz testa1: ";
    return (ispisi==test);
}
int main() {
        Stek<vector<int> > s;
        std::vector<int> v1{1,2,3,4}, v2{5, 10, 15}, v3{100,200,300};
        s.stavi(v1); s.stavi(v2); s.stavi(v3);
        
        std::vector<int> prazni{0};
        s.stavi(prazni);

        RezultatTesta(Test1(s)); 
        RezultatTesta(Test2(s));
        RezultatTesta(Test3(s));
 
  return 0;
}


