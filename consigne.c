#include "consigne.h"
#include <stdio.h>
#include <stdlib.h>

#define VERROU   "verrouconsigne.txt"
#define CONSIGNE "consigne.txt"

float consigne(float thermostatPrec_f){

    float thermostat_f = thermostatPrec_f;

    FILE *Verrouconsigne = fopen(VERROU, "wx");
    if(Verrouconsigne == NULL){
        printf("Le fichier consigne est deja utilise\n");
        return thermostatPrec_f;
    }
    fclose(Verrouconsigne);

    FILE *f = fopen(CONSIGNE, "r");
    if(f == NULL){
        printf("Erreur ouverture fichier\n");
    }
    else{
        fscanf(f, "%f", &thermostat_f);
        fclose(f);
    }

    remove(VERROU);

    return thermostat_f;
}