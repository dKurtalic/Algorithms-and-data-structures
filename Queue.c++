/*
Task 1
Create a generic class named Queue with the following methods:

A constructor that creates an empty queue.
If necessary, a destructor, copy constructor, and assignment operator.
A method named brisi() (delete()) that clears all elements from the queue.
A method named stavi(const Tip& el) (put(const Type& el)) that puts an element at the end of the queue.
A method named skini() (remove()) that returns the element at the front (beginning) of the queue and removes it from the queue. It should throw an exception if the queue is empty.
A method named celo() (top()) that returns a reference to the element at the front (beginning) of the queue without removing it. It should throw an exception if the queue is empty.
A method named brojElemenata()  (numberOfElements()) that returns the number of elements currently in the queue.

*/

#include <iostream>
using namespace std;

template<typename tip> class Red{
    struct Cvor {
        tip element;
        Cvor *prethodni=nullptr;
        Cvor *sljedeci=nullptr;
        Cvor(tip el):prethodni(nullptr), sljedeci(nullptr), element(el){};
    };
    Cvor *pocetak1=nullptr; Cvor *kraj1=nullptr; Cvor *trenutni=nullptr; 
    int velicina=0;
    public: 
    Red(){pocetak1=nullptr; kraj1=nullptr; trenutni=nullptr; velicina=0;}
    Red (const Red<tip> &r);
    int brojElemenata()const {return velicina;}
    void stavi(const tip &el);
    tip skini();
    tip& celo() const;
    void brisi();
    Red<tip> &operator=(const Red<tip> &r);
    
    ~Red() {if (velicina!=0) brisi();}
};

template<typename tip>
Red<tip> &Red<tip>::operator=(const Red<tip> &r){
    if (this==&r) return *this;
    Cvor *pocetakr=r.pocetak1;
    while (pocetakr!=nullptr){
        stavi(pocetakr->element);
      pocetakr=pocetakr->sljedeci;
   }
   return *this;
}
template<typename tip>
void Red<tip>::brisi(){
    if (velicina==0) throw range_error ("Red je prazan");
    while (velicina!=0) skini();
   
}
template<typename tip>
tip &Red<tip>::celo() const{
    if (velicina==0) throw range_error ("Red je prazan!");
    return pocetak1->element;
}
template<typename tip>
tip Red<tip>::skini(){
    if (velicina==0) throw range_error ("Red je prazan!");
    Cvor *pocetakreda=pocetak1;
    tip el=pocetakreda->element;
    pocetakreda=pocetakreda->sljedeci;
    delete pocetak1;
    pocetak1=nullptr;
    pocetak1=pocetakreda;
    velicina--; 
    return el;
}
template<typename tip>
void Red<tip>::stavi(const tip &el){
    if (pocetak1==nullptr){
        pocetak1=new Cvor(el);
        kraj1=pocetak1;
        trenutni=pocetak1;
        velicina++;
    }
    else{
        auto pom=new Cvor(el);
        trenutni->sljedeci=pom;
        pom->prethodni=trenutni;
        kraj1=pom;
        trenutni=pom;
        velicina++;
    }
}

template<typename tip>
Red<tip>::Red(const Red<tip> &r){
    if (this!=&r){ 
   auto pocetakr=r.pocetak1;
   while (pocetakr!=nullptr){
       stavi(pocetakr->element);
      pocetakr=pocetakr->sljedeci;
   }
    }
}
void RezultatTesta(bool vrijednost) {
  if (vrijednost)
    cout << "OK\n";
  else
    cout << "TEST JE PAO!\n";
}
bool TestKonstruktor(){
    Red<int>r;
    return (r.brojElemenata()==0);
}
bool TestKopirajuciKonstruktor(const Red<int> &original){
    Red<int>kopija(original);
    return kopija.brojElemenata()==5;
}
bool TestBrojElemenata(const Red<int> &r){
    return r.brojElemenata()==5;
}
bool TestStavi(Red<int> &r){
    r.stavi(6);
    return (r.brojElemenata()==6);
}
bool TestSkini(Red<int> &r){
    int skinutiEl=r.skini();
    return (r.brojElemenata()==5 && skinutiEl==1);
}
bool TestCelo(const Red<int>&r){
   return (r.celo()==2);
}
bool TestOperatorJednako(const Red<int>&original){
    Red<int> kopija;
    kopija=original;
    return (kopija.brojElemenata()==5 && kopija.celo()==2);
}
bool TestBrisi(Red<int>&original){
    original.brisi();
    return (original.brojElemenata()==0);
}
int main() {
    Red<int> r;
    for (int i(1); i<=5; i++)
	r.stavi(i);

    std::cout<<"Rezultati testova\n";
    RezultatTesta(TestKonstruktor());
    RezultatTesta(TestKopirajuciKonstruktor(r));
    RezultatTesta(TestBrojElemenata(r));
    RezultatTesta(TestStavi(r)); //1,2,3,4,5,6
    RezultatTesta(TestSkini(r)); //2,3,4,5,6
    RezultatTesta(TestCelo(r));
    RezultatTesta(TestOperatorJednako(r));
    RezultatTesta(TestBrisi(r));

    return 0;
}
