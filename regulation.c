#include "regulation.h"
#include "define.h"
#include <stdio.h>

float I = 0.0; // Variable globale pour l'intégrale du PID

float regulationTest(int regul, float consigne, float* tabT, int nT) 
{
    I = 0.0;
    float cmd = 100.0;
    
    float KP = 2.0;
    float KI = 0.1;
    float KD = 0.05;

    // Initialisation de la structure d'etat
    prec_t etat;
    etat.initFlag  = 0;    // 0 = premiere iteration pas encore faite
    etat.erreur    = 0.0; // erreur precedente

    for (int i = 0; i < nT; i++) {

        // Calcul de l'erreur courante : consigne - mesure
        float erreur = consigne - tabT[i];

        // --- Tout ou Rien ---
        if (regul == 1) {
            if (tabT[i] < consigne) {
                cmd = 50.0;
            } else {
                cmd = 0.0;
            }
        }

        // --- PID ---
        else if (regul == 2) {

            float P = KP * erreur;
            float D = 0.0;

            if (etat.initFlag == 0) {
                // Premiere iteration : I et D ignores
                cmd = P;
                etat.initFlag = 1;

            } else {
                // Integrale
                I += KI * ((etat.erreur + erreur)*10/2);

                if(I > 100.0) I -= KI * (etat.erreur + erreur)*10/2; // Anti-windup
                if(I <= 0.0)   I -= KI * ((etat.erreur + erreur)*10/2);   // Anti-windup

                // Derivee
                D = KD * (erreur - etat.erreur)/10;

                cmd = P + I + D;

                if (cmd > 100.0) cmd = 100.0;
                if (cmd < 0.0)   cmd = 0.1;

            }

            // On sauvegarde l'erreur courante comme precedente
            etat.erreur = erreur;
        }
    }

    return cmd;
}