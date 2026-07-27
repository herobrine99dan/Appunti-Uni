#include <iostream>
#include <string>

using namespace std;

/*

Allocazione Dinamica: Nel main, chiedi all'utente quanti veicoli vuole inserire. Crea un array allocato dinamicamente di puntatori a Veicolo (Veicolo** flotta = new Veicolo*[n]).

Gestione Memoria: Ricordati di liberare la memoria allocata con delete per ogni oggetto e delete[] per l'array.*/

class Veicolo
{
private:
    float speed;
    string marca;

public:
    Veicolo()
    {
        this->speed = 0;
        this->marca = "undefined";
    }
    Veicolo(string marca)
    {
        this->speed = 0;
        this->marca = marca;
    }
    float getSpeed()
    {
        return speed;
    }
    string getMarca()
    {
        return marca;
    }
    void setSpeed(float f)
    {
        if (f > 100 || f < -100)
        { // 100% o -100%
            this->speed = f;
        }
    }
    void setMarca(string s)
    {
        this->marca = s;
    }
    virtual void mostraDettagli()
    {
        cout << "Veicolo generico: " << marca << " con velocità " << speed << endl;
    }
    virtual ~Veicolo() {
        
    }
};

class Automobile : public Veicolo
{
private:
    const int numPorte;

public:
    Automobile(string marca, int numPorte) : Veicolo(marca), numPorte(numPorte)
    {
    }
    int getNumPorte()
    {
        return numPorte;
    }
    virtual void mostraDettagli()
    {
        cout << "Automobile marca: " << getMarca() << " con velocità " << getSpeed() << " e " << getNumPorte() << " porte" << endl;
    }
    virtual ~Automobile()
    {
    }
};

int main()
{
    Automobile *automobile = new Automobile("Pandina", 4);
    Veicolo &veicolo = *automobile;

    veicolo.mostraDettagli();
    int n;
    cout << "Quanti veicoli allocare? ";
    cin >> n;
    Veicolo** arr = new Veicolo*[n];
    for(int i = 0; i < n; i++) {
        arr[i] = new Automobile("Pandina", 4);
    }
    for(int i = 0; i < n; i++) {
        arr[i]->mostraDettagli();
    }

    //Cleaning phase
    for(int i = 0; i < n; i++) {
        delete arr[i];
    }
    delete[] arr;
    delete automobile;
}