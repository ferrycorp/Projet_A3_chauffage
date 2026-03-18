#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "define.h"
#include "visualisationT.h"
#include "visualisationC.h"
#include "regulation.h"
#include "simulateur.h"
#include "consigne.h"

int main() {
    temp_t tempSimulee = {10.0, 10.0};
    struct simParam_s* simParam = simConstruct(tempSimulee);
    float tabT[10000];
    float consigne_f = 12.0;
    float puissance_f = 0.0;
    int i = 0;
    remove(".verrouData");
    remove("verrouConsigne");

    // Utilisation d'une boucle while pour gérer l'arrêt à 5°C
    while (i < 10000) {
        
        consigne_f = consigne(consigne_f); 

        puissance_f = regulationTest(2, consigne_f, tabT, i);

        visualisationC(puissance_f);

        tempSimulee = simCalc(puissance_f, simParam);
        tabT[i] = tempSimulee.interieure;
        visualisationT(tempSimulee);

        i++;
        usleep(150000);
    }

    puissance_f = 0.0;
    visualisationC(puissance_f);
    printf("Arret du systeme (Consigne a 5 degres ou fin de simulation).\n");

    simDestruct(simParam);
    return EXIT_SUCCESS;
}