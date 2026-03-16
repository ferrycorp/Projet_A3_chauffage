#include "consigne.h"
#include <stdio.h>
#include <stdlib.h>

#define VERROU   "verrouconsigne.txt"
#define CONSIGNE "consigne.txt"



   float consigne(float thermostatPrec_f){
      float thermostat_f=0;

      FILE *Verrouconsigne = fopen(VERROU, "WX");
      if(Verrouconsigne == NULL){
         printf("Le fichier consigne est deja utiliser\n");
      }close(Verrouconsigne);

      FILE *consigne = fopen(CONSIGNE, "r");
      if(consigne == NULL){
         printf("erreur ouverture fichier\n");
      }close(consigne);

      if(consigne != NULL){
         fscanf(consigne, "%f", &thermostat_f);
      }

      fclose(consigne);
      remove(VERROU);
     
      return thermostat_f;
   
   }
