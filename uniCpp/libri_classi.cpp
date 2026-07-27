// Scrivere un programma in C++ per gestire un archivio di libri

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const int MAX_LIBRI = 100;
const int BUF_LEN = 21;

class Libro {
public:
    Libro() {}
    Libro(const string& titolo, const string& autore, int annoPubblicazione, float prezzo, const char* genere);

    string getTitolo();

    void memorizza(ofstream& s);
    void carica(ifstream& s);
    void stampa();

private:
    string titolo_;
    string autore_;
    int annoPubblicazione_;
    float prezzo_;
    char genere_[BUF_LEN];
};

class Archivio 
{
public:
    Archivio();

    bool inserimento(const Libro& libro);
    void visualizza();
    void cerca(string titolo);
    bool memorizza(string nomefile);
    bool carica(string nomefile);

private:
    Libro libri_[MAX_LIBRI];
    int num_libri_;
};

int main() {
    Archivio archivio;

    if (!archivio.carica("archivio2.txt"))
        cout << "Archivio non presente" << endl;

    int scelta;
    do {
        cout << "_____________________________________________________" << endl;
        cout << "1. Inserisci un libro" << endl;
        cout << "2. Stampa tutti i libri dell'archivio" << endl;
        cout << "3. Cerca un libro per titolo" << endl;
        cout << "4. Memorizza l'archivio su file" << endl;
        cout << "5. Carica l'archivio da file" << endl;
        cout << "0. Termina il programma" << endl;
        cout << "_____________________________________________________" << endl;
        cout << "Scegli l'operazione: ";
        cin >> scelta;
        cin.get();
        cout << endl;

        string titolo;
        string autore;
        int annoPubblicazione;
        float prezzo;
        char genere[BUF_LEN];

        switch (scelta) {
            case 1:
                cout << "Inserisci il titolo: ";
                getline(cin, titolo);

                cout << "Inserisci l'autore: ";
                getline(cin, autore);
                
                cout << "Inserisci l'anno di pubblicazione: ";
                while (true) {
                    string input_string;
                    getline(cin,input_string);
                    istringstream input_stream(input_string);
                    input_stream >> annoPubblicazione;
                    if (input_stream.fail())
                        cout << "Errore. Devi inserire un numero intero: ";
                    else
                        break;
                }

                cout << "Inserisci il prezzo: ";
                while (true) {
                    string input_string;
                    getline(cin,input_string);
                    istringstream input_stream(input_string);
                    input_stream >> prezzo;
                    if (input_stream.fail())
                        cout << "Errore. Devi inserire un numero decimale: ";
                    else
                        break;
                }

                cout << "Inserisci il genere: ";
                cin.getline(genere, BUF_LEN);
                cout << endl;

                if (!archivio.inserimento(Libro(titolo,autore,annoPubblicazione,prezzo,genere)))
                    cout << "Archivio pieno. Impossibile inserire" << endl;
                else
                    cout << "Libro inserito" << endl;
                break;

            case 2:
                archivio.visualizza();
                break;

            case 3:
                cout << "Inserisci il titolo del libro da cercare: ";
                getline(cin, titolo);
                cout << endl;
                archivio.cerca(titolo);
                break;

            case 4:
                cout << "Memorizzo l'archivio su file" << endl;
                if (!archivio.memorizza("archivio2.txt"))
                    cout << "Errore nel salvataggio dell'archivio" << endl;
                break;

            case 5:
                cout << "Carico l'archivio da file" << endl;
                if (!archivio.carica("archivio.txt"))
                    cout << "Errore nel caricamento dell'archivio" << endl;
                break;

            case 0:
                break;

            default:
                cout << "Scelta non valida" << endl;
        }
    } while (scelta != 0);

    cout << "A presto" << endl << endl;
    return 0;
}

Libro::Libro(const string& titolo, const string& autore, int annoPubblicazione, float prezzo, const char* genere)
{
    titolo_ = titolo;
    autore_ = autore;
    annoPubblicazione_ = annoPubblicazione;
    prezzo_ = prezzo;
    strncpy(genere_,genere,BUF_LEN);
    genere_[BUF_LEN-1] = '\0'; //Assicuriamoci che la stringa abbia lunghezza BUF_LEN
}

string Libro::getTitolo() 
{
    return titolo_;
}

void Libro::memorizza(ofstream& s)
{
    s << titolo_ << endl;
    s << autore_ << endl;
    s << annoPubblicazione_ << endl;
    s << prezzo_ << endl;
    s << genere_ << endl;
}

void Libro::carica(ifstream& s)
{
    getline(s, titolo_);
    getline(s, autore_);
    s >> annoPubblicazione_;
    s.get();
    s >> prezzo_;
    s.get();
    s.getline(genere_, BUF_LEN);
}

void Libro::stampa() {
    cout << "Titolo: " << titolo_ << endl;
    cout << "Autore: " << autore_ << endl;
    cout << "Anno di pubblicazione: " << annoPubblicazione_ << endl;
    cout << "Prezzo: " << prezzo_ << endl;
    cout << "Genere: " << genere_ << endl;
    cout << endl;
}

Archivio::Archivio() : num_libri_(0)
{
} 

bool Archivio::inserimento(const Libro& libro)
{
    if (num_libri_ >= MAX_LIBRI)
        return false;

    libri_[num_libri_] = libro;

    //libri[num_libri].titolo = libro.titolo;
    //libri[num_libri].autore = libro.autore;
    //libri[num_libri].annoPubblicazione = libro.annoPubblicazione;
    //libri[num_libri].prezzo = libro.prezzo;
    //strncpy(libri[num_libri].genere, libro.genere, BUF_LEN);
    
    num_libri_++;
    return true;
}

void Archivio::visualizza()
{
    cout << "L'archivio contiene " << num_libri_ << " libri" << endl;
    for (int i = 0; i < num_libri_; i++) {
        cout << "-------- Libro " << setw(3) << setfill('0') << i+1 << " --------" << endl;
        libri_[i].stampa();
    }
}

void Archivio::cerca(string titolo)
{
    for (int i = 0; i < num_libri_; i++) {
        if (titolo == libri_[i].getTitolo()) {
            cout << "Libro trovato:" << endl;
            libri_[i].stampa();
            return;
        }
    }

    cout << "Libro non trovato" << endl;
    cout << endl;
}

bool Archivio::memorizza(string nomefile)
{
    ofstream file(nomefile.c_str(), ios::out);
    if (file.fail())
        return false;

    file << num_libri_ << endl;
    for (int i = 0; i < num_libri_; i++) {
        libri_[i].memorizza(file);
    }

    file.close();
    return true;
}

bool Archivio::carica(string nomefile)
{
    ifstream file(nomefile.c_str(), ios::in);
    if (file.fail())
        return false;

    file >> num_libri_;
    file.get();

    if (num_libri_ > MAX_LIBRI)
        num_libri_ = MAX_LIBRI;

    for (int i = 0; (!file.eof()) && (i < MAX_LIBRI); i++) {
        libri_[i].carica(file);
    }

    file.close();
    return true;
}
