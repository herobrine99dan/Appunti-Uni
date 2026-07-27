#include <iostream>
#include <string>

using namespace std;

class Veicolo
{
private:
    string targa;
    int kmPercorsi;

public:
    Veicolo(string targa, int kmPercorsi)
    {
        this->targa = targa;
        this->kmPercorsi = kmPercorsi;
    }
    string getTarga()
    {
        return targa;
    }
    void setTarga(string s)
    {
        targa = s;
    }
    int getKmPercorsi()
    {
        return kmPercorsi;
    }
    void setKmPercorsi(int i)
    {
        this->kmPercorsi = i;
    }
    virtual void descrivi()
    {
        cout << "Veicolo generico con targa " << targa << " e " << kmPercorsi << " kmPercorsi. " << endl;
    };
    virtual ~Veicolo() {

    }
};

class Moto : public Veicolo
{
private:
    int cilindrata;

public:
    Moto(string targa, int kmPercorsi, int cilindrata) : Veicolo(targa, kmPercorsi)
    {
        this->cilindrata = cilindrata;
    }
    int getCilindrata()
    {
        return cilindrata;
    }
    void setCilindrata(int i)
    {
        this->cilindrata = i;
    }
    virtual void descrivi()
    {
        cout << "Moto con targa " << getTarga() << " e " << getKmPercorsi() << " kmPercorsi e cilindrata " << cilindrata << endl;
    }
};

class Auto : public Veicolo
{
private:
    int numPorte;

public:
    Auto(string targa, int kmPercorsi, int numPorte) : Veicolo(targa, kmPercorsi)
    {
        this->numPorte = numPorte;
    }
    int getNumPorte()
    {
        return numPorte;
    }
    void setNumPorte(int i)
    {
        this->numPorte = i;
    }
    virtual void descrivi()
    {
        cout << "Auto con targa " << getTarga() << " e " << getKmPercorsi() << " kmPercorsi e numPorte " << numPorte << endl;
    }
};

class Camion : public Veicolo
{
private:
    int portataTon;

public:
    Camion(string targa, int kmPercorsi, int portataTon) : Veicolo(targa, kmPercorsi)
    {
        this->portataTon = portataTon;
    }
    int getPortataTon()
    {
        return portataTon;
    }
    void setPortataTon(int i)
    {
        this->portataTon = i;
    }
    virtual void descrivi()
    {
        cout << "Camion con targa " << getTarga() << " e " << getKmPercorsi() << " kmPercorsi e portataTon " << portataTon << endl;
    }
    
};

int main() {
    Veicolo** arr = new Veicolo*[3];
    Veicolo* a = new Auto("hwfiigfwe", 5, 4);
    Veicolo* b = new Moto("jeoiqfjqe",6,32);
    Veicolo* c = new Camion("whuuhwwrgh",0,10);
    Veicolo aDiverso = *a;
    aDiverso.descrivi();
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[0]->descrivi();
    arr[1]->descrivi();
    arr[2]->descrivi();
    delete arr[0];
    delete arr[1];
    delete arr[2];
    delete[] arr;
}