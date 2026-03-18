#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ftd2xx.h"
#include "define.h"

#define BAUD_RATE 115200


int main(void) {
    
    FT_HANDLE ftHandle;
FT_STATUS ftStatus;


    // 1. Lister les périphériques disponibles
    ftStatus = FT_Open(0, &ftHandle);


if (ftStatus == FT_OK) {
// FT_Open OK, use ftHandle to access device
printf("Périphérique ouvert avec succès\n");
}
else {
printf("ca marche pas\n");
 FT_Close(ftHandle);
 return EXIT_FAILURE;
}


FT_SetBaudRate(ftHandle, 115200); // Set baud rate to 115200
if (ftStatus == FT_OK) {
// FT_SetBaudRate OK
printf("Baud rate défini à %d\n", BAUD_RATE);
}
else {
// FT_SetBaudRate Failed
printf("Erreur lors de la définition du baud rate\n");
FT_Close(ftHandle);
        return EXIT_FAILURE;


}

 // 8 bits, 1 stop, pas de parité
    ftStatus = FT_SetDataCharacteristics(ftHandle,
                                         FT_BITS_8,
                                         FT_STOP_BITS_1,
                                         FT_PARITY_NONE);
    if (ftStatus == FT_OK) {
        printf("Caractéristiques : 8 bits, 1 stop, pas de parité\n");
    } else {
        printf("Erreur FT_SetDataCharacteristics\n");
        FT_Close(ftHandle);
        return EXIT_FAILURE;
    }

    // Pas de contrôle de flux, autres paramètres à 0
    ftStatus = FT_SetFlowControl(ftHandle,
                                  FT_FLOW_NONE,
                                  0,     // XonChar  = 0
                                  0);    // XoffChar = 0
    if (ftStatus == FT_OK) {
        printf("Contrôle de flux : aucun\n");
    } else {
        printf("Erreur FT_SetFlowControl\n");
        FT_Close(ftHandle);
        return EXIT_FAILURE;
    }

    FT_Close(ftHandle);
    printf("Connexion fermée\n");

    return EXIT_SUCCESS;


}