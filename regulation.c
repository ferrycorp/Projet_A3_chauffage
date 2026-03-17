#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

static float somme_erreurs = 0.0f;
static float erreur_precedente = 0.0f;

/* ========================= */
/* 2.3.2 REGULATEUR PID      */
/* ========================= */


float regulationTest(int regul, float consigne, float* tabT, int nT){
    float cmd = 0.0f;
    float sommeIntegrale = 0.0f;
    float erreurPrecedente = 0.0f;

     for (int i = 0; i < nT; i++) {
        float erreur = consigne - tabT[i];

        if (regul == 1) { // Mode TOUT OU RIEN (Source [1])
            if (tabT[i] < consigne) cmd = 50.0f;
            else cmd = 0.0f;
        } 
        else if (regul == 2) { // Mode PID (Source [1])
            float P = KP * erreur;
            sommeIntegrale+=(erreur+erreurPrecedente)/2.0f; // On accumule l'historique
            
            if (i == 0) {
                cmd = P; // Uniquement P à la 1ère itération (Source [1])
            } else {
                 // Méthode des trapèzes
                float I = KI * sommeIntegrale;
                float D = KD * (erreur - erreurPrecedente);
                cmd = P + I + D;
            }

            // Saturation entre 0 et 100 (Source [3, 4])
            if (cmd < 0.0f) cmd = 0.0f;
            else if (cmd > 100.0f) cmd = 100.0f;
        }
        
        erreurPrecedente = erreur; // Mise à jour de l'erreur pour la dérivée
    }

    return cmd; // Retourne la dernière commande calculée [1]
}