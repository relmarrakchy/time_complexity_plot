#include <iostream>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

//outils
int *createArr(int); // Fonction pour creer un tableau dynamique
void insertArr(int *, int); // Fonction permet d'inserer des valeurs aleatoires dans notre tableau
void displayArr(int *, int); // Fonction permet d'afficher un tableau
void swap(int *, int *); //Fonction permet d'echanger deux elements
int partition(int *, int, int); //Outil pour Tri rapide
void tas(int *, int, int);//Outil pour Tri par tas

//Tri methodes
void triBulle(int *, int); // Fonction permet de tri par bulle
void triInsertion(int *, int); // Fonction permet de tri par insertion
void triSelection(int *, int); // Fonction permet de tri par sélection
void triFusion(int *, int, int, int); //Foction permet de tri par fusion
void triRapide(int *, int, int); //Fonction permet de tri rapide
void triTas(int *, int); //Fonction permet de tri par tas

//Calcul le temps d'éxecution de chaque methode avec une taille de tableau précisie
double tempsTriBulle(int);
double tempsTriInsertion(int);
double tempsTriSelection(int);
double tempsTriFusion(int);
double tempsTriRapide(int);
double tempsTriTas(int);


int *createArr(int n) { return (int *) malloc(sizeof(int) * n); } // new int(N) est toujours retouner un erreur

void insertArr(int *tab, int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % n + 1;
    }
}

void displayArr(int *tab, int n)
{
    cout << "Les valeurs de ce tableau est : " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << tab[i] << " ";
        if (!i)
            continue;
        if (!(i % 15))
            cout << endl;
    }
    cout << endl;
}

void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void triBulle(int *tab, int n)
{
    bool action = 1;  // Indique qu'il y a un echange
    int verified = 0; // Indique les cases qui sont triées
    while (action)
    {
        action = 0; // rend l'etat a 0
        for (int i = 0; i < n - 1 - verified; i++)
        {
            if (tab[i] > tab[i + 1])
            {
                action = 1; // rend l'etat a 1 car on dectecte un echange
                swap(&tab[i], &tab[i + 1]);
            }
        }
        verified++;
    }
}

void triInsertion(int *tab, int n)
{
    int swap; //Permet d'echanger les valeurs
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (tab[j] > tab[i])
            {
                swap = tab[i]; // On guarde la valeur minimale
                // Processus de décalage
                for (int k = i - 1; k >= j; k--)
                {
                    tab[k + 1] = tab[k];
                }
                tab[j] = swap;
            }
        }
    }
}

void triSelection(int *tab, int n)
{
    int min; // Permet d'indiquer la valeur la plus minimal, par défaut c'est la valeur de la permiere case
    int pos; // Permet de guarder la position de la case minimal
    for (int i = 0; i < n; i++)
    {
        min = tab[i];
        pos = i;
        for (int j = i + 1; j < n; j++)
        {
            if (min > tab[j])
            {
                min = tab[j];
                pos = j;
            }
        }
        swap(&tab[i], &tab[pos]);
    }
}

void triFusion(int *tab, int begin, int end, int n) {
    if (begin >= end) return; //Verifier que l'indice de début du tableau est inferieur que l'indice de fin 
    int mid = (begin + end) / 2; //Calcule de milieu
    int *tmp = createArr(n);

    //Processus de subdivision
    triFusion(tab, begin, mid, n);
    triFusion(tab, mid + 1, end, n);

    int debut_tab1 = begin, debut_tab2 = mid + 1; //Intialiser le début de chaque sous tableau
    int compt;

    //Processus de la fusion
    for(compt = begin; compt <= end; compt++) {
        if(debut_tab1 == mid+ 1) { 
            tmp[compt] = tab[debut_tab2];
            debut_tab2++;
        }else if (debut_tab2 == end + 1) { 
            tmp[compt] = tab[debut_tab1];
            debut_tab1++;
        }else if (tab[debut_tab1] < tab[debut_tab2]) {
            tmp[compt] = tab[debut_tab1];
            debut_tab1++;
        }else {
            tmp[compt] = tab[debut_tab2];
            debut_tab2++;
        }
    }

    //Copier les éléments de la table temporelle
    for(compt = begin; compt <= end; compt++) {
        tab[compt] = tmp[compt];
    }

    //Supprimer la table temporelle
    delete tmp;
}

int partition(int *tab, int low, int high) {
    int pivot = tab[high]; //Prend la valeur de pivot
    int i = low - 1; //Compter les valeurs qui sont inf que le pivot

    //Trier les elements qui sont inf que le pivot
    for (int j = low; j <= high; j++) {
        if (tab[j] < pivot) {
            i++;
            swap(&tab[i], &tab[j]);
        }
    }

    //Rendre le pivot a sa place correcte
    swap(&tab[i + 1], &tab[high]);

    //Retourner l'indice de pivot
    return i + 1;
}

void triRapide(int *tab, int low, int high) {
    if (low >= high) return ;
    int part = partition(tab, low, high);
    triRapide(tab, low, part - 1);
    triRapide(tab, part + 1, high);
}

void tas(int *tab, int n, int i) {
    int largest = i; // Initialiser la racine
    int l = 2 * i + 1; // Gauche = 2*i + 1
    int r = 2 * i + 2; // Droit = 2*i + 2
 
    // Si left child grand que la racine
    if (l < n && tab[l] >tab[largest]) largest = l;
 
    // Si right child grand que la racine
    if (r < n && tab[r] > tab[largest]) largest = r;
    
    if (largest != i) {
        swap(tab[i], tab[largest]);
        tas(tab, n, largest);
    }
}

void triTas(int *tab, int n) {
    // Creation d'un tas
    for (int i = n / 2 - 1; i >= 0; i--)
        tas(tab, n, i);
 
    for (int i = n - 1; i > 0; i--) {
        // Rendre la racine a la fin de tas
        swap(tab[0], tab[i]);
        tas(tab, i, 0);
    }
}

double tempsTriBulle(int size) {
    clock_t begin, end;
    int *tab = createArr(size); insertArr(tab, size);
    begin = clock();
    triBulle(tab, size);
    end = clock();

    return double (end - begin) / double (CLOCKS_PER_SEC);
}

double tempsTriInsertion(int size) {
    clock_t begin, end;
    int *tab = createArr(size); insertArr(tab, size);
    begin = clock();
    triInsertion(tab, size);
    end = clock();

    return double (end - begin) / double (CLOCKS_PER_SEC);
}

double tempsTriSelection(int size) {
    clock_t begin, end;
    int *tab = createArr(size); insertArr(tab, size);
    begin = clock();
    triSelection(tab, size);
    end = clock();

    return double (end - begin) / double (CLOCKS_PER_SEC);
}

double tempsTriFusion(int size) {
    clock_t begin, end;
    int *tab = createArr(size); insertArr(tab, size);
    begin = clock();
    triFusion(tab, 0, size - 1, size);
    end = clock();

    return double (end - begin) / double (CLOCKS_PER_SEC);
}

double tempsTriRapide(int size) {
    clock_t begin, end;
    int *tab = createArr(size); insertArr(tab, size);
    begin = clock();
    triRapide(tab, 0, size - 1);
    end = clock();

    return double (end - begin) / double (CLOCKS_PER_SEC);
}

double tempsTriTas(int size) {
    clock_t begin, end;
    int *tab = createArr(size); insertArr(tab, size);
    begin = clock();
    triTas(tab, size);
    end = clock();

    return double (end - begin) / double (CLOCKS_PER_SEC);
}