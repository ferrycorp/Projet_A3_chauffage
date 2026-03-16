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
    FILE* fr = fopen("data.txt", "r");
    if (fr != NULL) {
        fscanf(fr, "%9s", temoin);
        fclose(fr);
    }

    FILE* fw = fopen("data.txt", "w");
    if (fw != NULL) {
        fprintf(fw, "%s\n%.2f\n%.2f\n",
                temoin,
                myTemp.interieure,   // champ interieure en premier
                myTemp.exterieure);
        fclose(fw);
    }

    remove(".verrouData");
}