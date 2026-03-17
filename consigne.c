#include "consigne.h"
#include <stdio.h>
#include <stdlib.h>

#define VERROU   ".verrouConsigne"
#define CONSIGNE "consigne.txt"

float consigne(float csgn){

    float thermostat_f = csgn;

    FILE *verrou = fopen(VERROU, "wx");
    if(verrou == NULL){
        return csgn;
    }
    fclose(verrou);

    FILE *f = fopen(CONSIGNE, "r");
    if(f != NULL){
        if(fscanf(f, "%f", &thermostat_f) != 1){
            thermostat_f = csgn;
        }
        fclose(f);
    }

    remove(VERROU);

    return thermostat_f;
}