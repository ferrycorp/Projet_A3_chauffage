#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"


   void visualisationC(float puissance_f)
   {
      FILE* verrou = fopen("verrou_data.txt", "wx");
      if (verrou == NULL) {
         // Le fichier existe déjà, attendre qu'il soit libéré
         return;
      }
      fclose(verrou);
   
      // Lecture des températures existantes
      char temoin[10];
      float tint = 0.0f, text = 0.0f;
      FILE* f = fopen("data.txt", "r");
      if (f != NULL) {
         fscanf(f, "%9s %f %f", temoin, &tint, &text);
         fclose(f);
      }

      // Détermination du témoin selon la puissance
      const char* etat = (puissance_f != 0) ? "true" : "false";

      // Réécriture complète de data.txt
      if (f != NULL) {
         fprintf(f, "%s\n%.2f\n%.2f\n", etat, tint, text);
         fclose(f);
      }

      remove(".verrouData");
   }
