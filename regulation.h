#include <stdio.h>
#include <stdlib.h>
#include "define.h" 

#define KP 1.1f
#define KI 0.2f
#define KD 0.15f
    
float regulationTest(int regul,float consigne,float* tabT, int nT);