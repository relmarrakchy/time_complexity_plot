#include "records.h"

int main(int argc, char const *argv[])
{
    vector<time_record> tab = create_tabRecords(); //Creation d'un tableau des enregistrements
    getFile_tabRecords(tab); //Placer le dans un fichier (Pour verfication)
    vector<point> pts = records_to_points(tab); //Tranformer le le tableau a des points
    getFile_points(pts); //Donner un fichier qui contient les coordonnees (points) pour les visualiser sur Gnuplot

    return 0;
}