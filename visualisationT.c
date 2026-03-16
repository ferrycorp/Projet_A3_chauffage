#include "visualisationT.h"

void visualisationT(temp_t myTemp)
{
    FILE* verrou = fopen("verrou_data.txt", "wx");
    if (verrou == NULL) {
        // Le fichier existe déjà, attendre qu'il soit libéré
        return;
    }
    fclose(verrou);

    

    remove(".verrouData");
}
