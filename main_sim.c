#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "regulation.h"
#include "simulateur.h"
#include "consigne.h"

int main() {
    temp_t tempSimulee = {10.0f, 10.0f};
    struct simParam_s* simParam = simConstruct(tempSimulee);
    float tabT[1000];
    float consigne_f = 12.0f;
    float puissance_f = 0.0f;
    int i = 0;

    // Utilisation d'une boucle while pour gérer l'arrêt à 5°C
    while (consigne_f > 5.0f && i < 1000) {
        
        consigne_f = consigne(consigne_f); 

        puissance_f = regulationTest(2, consigne_f, tabT, i);

        visualisationC(puissance_f);

        tempSimulee = simCalc(puissance_f, simParam);
        tabT[i] = tempSimulee.interieure;
        visualisationT(tempSimulee);

        i++;
        //sleep(40); // Optionnel : pour cadencer à 40ms
    }

    puissance_f = 0.0f;
    visualisationC(puissance_f);
    // commande(puissance_f);
    printf("Arret du systeme (Consigne a 5 degres ou fin de simulation).\n");

    simDestruct(simParam);
    return EXIT_SUCCESS;
}