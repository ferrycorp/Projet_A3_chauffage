#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

static float regulationTOR(float tint, float csgn) {
    if (tint < csgn) {
        return 50.0f;
    }
    return 0.0f;
}

static float regulationPID(float erreur, float erreurPrecedente, float* sommeIntegrale, int premiereIteration){
    float P = 0.0f;
    float I = 0.0f;
    float D = 0.0f;

    // Terme proportionnel : toujours calcule
    P = KP * erreur;

    if (!premiereIteration) {
        // Terme integral : somme des erreurs precedentes
        *sommeIntegrale += erreur;
        I = KI * (*sommeIntegrale);

        // Terme derive : variation de l'erreur entre deux iterations
        D = KD * (erreur - erreurPrecedente);
    }

    float pid = P + I + D;

    // Saturation entre 0 et 100%
    if (pid < 0.0f) {
        pid = 0.0f;
    }
    if (pid > 100.0f) {
        pid = 100.0f;
    }

    return pid;
}

float regulationTest(int regul,float consigne,float* tabT, int nT){
	float cmd = 100.0f;

    float sommeIntegrale   = 0.0f;
    float erreurPrecedente = 0.0f;

    for (int i = 0; i < nT; i++) {
        float erreur = consigne - tabT[i];
        int premiereIteration = (i == 0);

        if (regul == 1) {
            cmd = regulationTOR(tabT[i], consigne);
        } else if (regul == 2) {
            cmd = regulationPID(erreur, erreurPrecedente,&sommeIntegrale, premiereIteration);
        }

        erreurPrecedente = erreur;
    }

	return cmd;
}