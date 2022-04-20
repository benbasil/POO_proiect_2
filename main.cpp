#include <iostream>
#include <cmath>

using namespace std;


// Acesta este un programel care lucreaza pe o lista de trei posibile forme geometrice: Dreptunghi, Triunghi, Cerc;
// Folosind interfata din consola, puteti adauga, sterge sau printa aceasta lista de forme geometrice;




// ------------------------------------------ clase -------------------------------------------------------- //;
class FormaGeometrica{
protected:
    string nume_forma;
public:

    FormaGeometrica(string nume_forma){
        this->nume_forma = nume_forma;
        numar_forme++;
    }
    FormaGeometrica(const FormaGeometrica& forma){
        nume_forma = forma.nume_forma;
    }
    FormaGeometrica(){
        nume_forma = "";
    }
    virtual ~FormaGeometrica(){
        nume_forma.clear();
        numar_forme--;
    }

    virtual double arie() = 0;
    virtual double perimetru() = 0;

    friend istream& operator >>(istream &i, const FormaGeometrica &p);
    friend ostream& operator <<(ostream &o, const FormaGeometrica &p);

    virtual void citire (istream &i) {}
    virtual void afisare(ostream &o) const{
        o << nume_forma << ' ';
    }

    int static getNumar_Forme(){
        return numar_forme;
    }

private:
    int static numar_forme;

};

class Dreptunghi:public FormaGeometrica{

public:
    double arie (){
        return l * L;
    }
    double perimetru (){
        return 2*(L + l);
    }
    Dreptunghi(double l = 0, double L = 0):FormaGeometrica("Dreptunghi"){
        this->l = l;
        this->L = L;
    }
    ~Dreptunghi(){
        l = 0;
        L = 0;
    }
    void citire(istream &i) {
        FormaGeometrica::citire(i);
        i >> l >> L;
    }
    virtual void afisare(ostream &o) const{
        FormaGeometrica::afisare(o);
        o << l << ' ' << L;
    }

private:
    double l, L;
};

class Triunghi:public FormaGeometrica{
public:
    double arie (){
        double semiperimetru = latura1 + latura2 + latura3;
        semiperimetru /= 2;
        return sqrt(semiperimetru*(semiperimetru - latura1)*(semiperimetru - latura2)*(semiperimetru - latura3)); //Calculul ariei triunghiului prin formula lui Heron;
    }
    double perimetru(){
        return latura1 + latura2 + latura3;
    }
    Triunghi(double latura1 = 0, double latura2 = 0, double latura3 = 0):FormaGeometrica("Triunghi"){
        this->latura1 = latura1;
        this->latura2 = latura2;
        this->latura3 = latura3;
    }

    ~Triunghi(){
        latura1 = 0;
        latura2 = 0;
        latura3 = 0;
    }
    void citire(istream &i) {
        FormaGeometrica::citire(i);
        i >> latura1 >> latura2 >> latura3;
    }
    virtual void afisare(ostream &o) const{
        FormaGeometrica::afisare(o);
        o << latura1 << ' ' << latura2 << ' ' << latura3;
    }
private:
    double latura1, latura2, latura3;
};

class Cerc:public FormaGeometrica{
public:
    double arie(){
        return 3.14 * r * r;
    }
    double perimetru(){
        return 3.14 * 2 * r;
    }
    Cerc (double r):FormaGeometrica("Cerc"){
        this->r = r;
    }
    ~Cerc(){
        r = 0;
    }
    void citire(istream &i) {
        FormaGeometrica::citire(i);
        i >> r;
    }
    virtual void afisare(ostream &o) const{
        FormaGeometrica::afisare(o);
        o << r;
    }
private:
    double r;
};


istream &operator >> (istream& i, FormaGeometrica &p){
    p.citire(i);
    return i;
}

ostream &operator << (ostream& o, const FormaGeometrica &p){
    p.afisare(o);
    return o;
}

int FormaGeometrica::numar_forme = 0;

// ------------------------------------------ intefata -------------------------------------------------------- //;
FormaGeometrica *lista[20];

void printare(){
    for (int i = 1; i <= lista[1]->getNumar_Forme(); i++)
        cout <<"Obiectul "<< i << ": " <<*lista[i] << ' ' <<" || Perimetru: "<< lista[i]->perimetru() << ' ' <<" || Arie: "<< lista[i]->arie() << endl;
}

void adaugare_forma(){
    int forma;
    int n = lista[1]->getNumar_Forme();
    cout << "Tastati obiectul pe care il doriti adaugat (Dreptunghi = 1, Triunghi = 2, Cerc = 3) ";
    cin >> forma;
    switch(forma){
    case 1:
        cout << "Tastati latimea si lungimea: ";
        lista[n+1] = new Dreptunghi(0, 0);
        cin >> *lista[n+1];
        break;
    case 2:
        cout << "Tastati cele trei laturi: ";
        lista[n+1] = new Triunghi(0, 0, 0);
        cin >> *lista[n+1];
        break;
    case 3:
        cout << "Tastati raza: ";
        lista[n+1] = new Cerc(0);
        cin >> *lista[n+1];
        break;
    }

}

void stergere_forma(){
    int n = lista[1]->getNumar_Forme();
    int numar;
    cout << "Tastati numarul obiectului pe care il vreti sters: ";
    cin >> numar;
    delete lista[numar];
    if (numar != n)
        for (int i = numar + 1; i <= n; i++)
            lista[i-1] = lista[i];

}


void interfata(){
    int comanda;
    cout << endl << "=======================================" << endl;
    cout << "Optiuni:" <<endl;
    cout << "1. Printati formele geometrice existente" <<endl;
    cout << "2. Adaugati forma geometrica" <<endl;
    cout << "3. Stergeti forma geometrica" <<endl;
    cout << "4. Help!" <<endl;
    cout << "5. Quit" <<endl;
    cout << "Tastati numarul comenzii: ";

    cin >> comanda;

    switch (comanda) {
    case 1:
        printare();
        interfata();
        break;
    case 2:
        adaugare_forma();
        interfata();
    case 3:
        stergere_forma();
        interfata();
    case 4:
        cout << "In acest programel puteti introduce trei tipuri de forme geometrice intr-o lista care va va calcula automat aria si perimetrul obiectelor!" <<endl;
        cout << "Introduceti, stergeti si printati-va lista alegand din cele 5 optiuni!"<<endl<<endl;
        interfata();
    case 5:
        break;


    }
}


// ------------------------------------------ main -------------------------------------------------------- //;

int main()
{
    // adaug 5 valori default in lista de forme geometrice
    for (int i = 1; i <= 5; i++){
        if (i == 1 || i == 3)
            lista[i] = new Cerc(i*10);
        else{
            if (i % 2 == 0)
                lista[i] = new Dreptunghi(i*20 + 3, i*10 + 7);
            else
                lista[i] = new Triunghi(i*10, i*20,i*30-10);
        }
    }

    interfata();
    return 0;
}
