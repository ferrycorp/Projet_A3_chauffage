#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    FILE* verrou = fopen(".verrouData", "wx");
    if (verrou == NULL) {
        // Le fichier existe déjà, attendre qu'il soit libéré
        return;
    }
    fclose(verrou);

    char etat[5] = "false";
    float tint = 0.0f, text = 0.0f;

    FILE* f = fopen("data.txt", "r");
    if (f != NULL) {
        fscanf(f, "%9s", etat);
        fclose(f);
    }

    f = fopen("data.txt", "w");
    if (f != NULL) {
        fprintf(f, "%s\n%.2f\n%.2f\n",
                etat,
                myTemp.interieure,
                myTemp.exterieure);
        fclose(f);
    }

    remove(".verrouData");
}