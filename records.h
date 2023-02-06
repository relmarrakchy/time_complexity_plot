//Cette biblio contient un structure qui calcul le temps d'execution de chaque methode avec un nombre des cases enregistrées
#include <vector>
#include <fstream>
#include "tri.h"

//Tableau contient les differents de tri
string methods[] = {"Tri par bulle", "Tri par insertion", "Tri par selection", "Tri par fusion", "Tri rapide", "Tri par tas"};

class time_record {
private:
    int nbr_cases;
    vector<double> records;

public:
    time_record() {};

    void set_nbrCases(int nbr_Cases) { this->nbr_cases = nbr_Cases; }
    int get_nbrCases() { return this->nbr_cases; }

    void set_timeRecord(vector<double> records) { this->records = records; }
    vector<double> get_timeRecord() { return this->records; }
};

class point {
private:
    int x; double y;
public:
    point (int x, double y) {
        this->x = x;
        this->y = y;
    };

    void setX(int x) { this->x = x; }
    int getX() { return this->x; }

    void setY(double y) { this->y = y; }
    double getY() { return this->y; }
};

time_record createRecords(int); //Fonction permet de creer un enregistrement de temps d'execution
vector<time_record> create_tabRecords(); //Fonction permet de creer un tableau des enregistrements de temps d'execution
void getFile_tabRecords(vector<time_record>); //Fonction permet de creer un fichier qui contient les informations d'execution (Pour verification)
vector<point> records_to_points(vector<time_record>); //Fonction permet de transformer les enregistrements a des points
void getFile_points(vector<point>); //Fonction permet de creer un fichier qui contient les coordonnees des points (Pour visualition de Gnuplot)


time_record createRecords(int nbr_cases) {
    time_record r;
    vector<double> records;
    r.set_nbrCases(nbr_cases);

    records.push_back(tempsTriBulle(nbr_cases));
    records.push_back(tempsTriInsertion(nbr_cases));
    records.push_back(tempsTriSelection(nbr_cases));
    records.push_back(tempsTriFusion(nbr_cases));
    records.push_back(tempsTriRapide(nbr_cases));
    records.push_back(tempsTriTas(nbr_cases));

    r.set_timeRecord(records);
    return r;
}

vector<time_record> create_tabRecords() {
    vector<time_record> tab;
    for(int cases = 1000; cases <= 100000; cases+= 5500) {
        tab.push_back(createRecords(cases));
    }
    return tab;
}
//Pourquoi 5500 comme un pas ?
//      On a au maximum 100000 champs et au minimum 1000
//      J'ai calculé nombre de champs estimé avec la relation (1 + 3.3 * log de base 10 de 100000) et j'ai obtenu 19 champs
//      et le pas c'est la diff entre min et max sur le nombre des champs


void getFile_tabRecords(vector<time_record> tab) {
    fstream records;

    records.open("records.txt", ios::out);
    if (!records) {
        cout << "Error de creation de fichier";
        return ;
    }

    for (int i = 0; i < tab.size(); i++) {
        records << "Nombre des cases : " << tab[i].get_nbrCases() << "\n ";
        for (int j = 0; j < tab[i].get_timeRecord().size(); j++) {
            records << "\t" << methods[j] << " : " << tab[i].get_timeRecord()[j] << " secondes" << "\n";
        }
    }
    records << "\n";
    records.close();
}

vector<point> records_to_points(vector<time_record> tab) {
    vector<point> points;

    for (int i = 0; i < tab.size(); i++)
    {
        for(int j = 0; j < tab[i].get_timeRecord().size(); j++) {
            points.push_back(point(tab[i].get_nbrCases(), tab[i].get_timeRecord()[j]));
        }
    }

    return points;
}

void getFile_points(vector<point> pts) {
    fstream points;

    points.open("points.dat", ios::out);
    if (!points) {
        cout << "Error de creation de fichier";
        return ;
    }
    for (int i = 0; i < pts.size(); i++) {
        points << pts[i].getX() << " " << pts[i].getY() << "\n";
    }

    points.close();
}