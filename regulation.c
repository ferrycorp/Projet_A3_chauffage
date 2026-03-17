#include "regulation.h"
#include "define.h"
#include <stdio.h>

float I = 0.0; // Variable globale pour l'intégrale du PID

float regulationTest(int regul, float consigne, float* tabT, int nT) 
{
    I = 0.0;
    float cmd = 100.0;
    
    float KP = 1.1;
    float KI = 0.2;
    float KD = 0.15;

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

                //if(I > 100.0) I -= KI * (etat.erreur + erreur)*10/2; // Anti-windup
                //if(I <= 0.0)   I -= KI * ((etat.erreur + erreur)*10/2);   // Anti-windup

                // Derivee
                D = KD * (erreur - etat.erreur)/10;

                cmd = P + I + D;

                // Saturation entre 0 et 100%
                if (cmd > 100.0f) cmd = 100.0f;
                if (cmd < 0.0f)   cmd = 0.0f;
            }

            // On sauvegarde l'erreur courante comme precedente
            etat.erreur = erreur;
        }
    }

    return cmd;
}