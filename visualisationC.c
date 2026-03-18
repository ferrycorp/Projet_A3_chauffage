#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"


void visualisationC(float puissance_f)
{
   FILE* verrou = fopen(".verrouData", "wx");
   if (verrou == NULL) {
      // Le fichier existe déjà, attendre qu'il soit libéré
      return;
   }
   fclose(verrou);

   char temoin[7];
   float tint = 0.0f, text = 0.0f;
   FILE* f = fopen("data.txt", "r");
   if (f != NULL) {
      fscanf(f, "%9s %f %f", temoin, &tint, &text);
      fclose(f);
   }

   const char* etat = (puissance_f > 0) ? "true" : "false";

   f = fopen("data.txt", "w");
   if (f != NULL) {
      fprintf(f, "%s\n%.2f\n%.2f\n", etat, tint, text);
      fclose(f);
   }

   remove(".verrouData");
}