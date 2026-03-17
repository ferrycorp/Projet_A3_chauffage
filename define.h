#ifndef DEFINE_H
#define DEFINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/********************************************************************/




/********************************************************************/

typedef struct {
	float interieure;
	float exterieure;
}temp_t;

typedef struct {
	int initFlag;// drapeau initialisation 
	float erreur;// precedente erreur
	float integrale;// precedente integrale
}prec_t;

#endif