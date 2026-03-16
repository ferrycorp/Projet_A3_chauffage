#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    FILE* verrou = fopen("verrou_data.txt", "wx");
    if (verrou == NULL) {
        // Le fichier existe déjà, attendre qu'il soit libéré
        return;
    }
    fclose(verrou);

    char temoin[10] = "false";
    FILE* f = fopen("data.txt", "r");
    if (f != NULL) {
        fscanf(f, "%9s", temoin);
        fclose(f);
    }

    FILE* f = fopen("data.txt", "w");
    if (f != NULL) {
        fprintf(f, "%s\n%.2f\n%.2f\n",
                temoin,
                myTemp.interieure,   // champ interieure en premier
                myTemp.exterieure);
        fclose(f);
    }

    remove(".verrouData");
}