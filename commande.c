#include "commande.h"
#include <stdio.h>
#include "ftd2xx.h"

void commande(float puissance) {
    // Conversion puissance % → 7 bits
    // puissance en % = (PUIS / 127) * 100
    // donc PUIS = puissance * 127 / 100
    unsigned char PUIS = (unsigned char)(puissance * 127.0f / 100.0f);

    // Construction de l'octet de commande
    // Bit 7 = 0 (chauffage), Bits 6-0 = PUIS
    unsigned char octet = PUIS & 0x7F;  // bit 7 a 0 = chauffage

    // Envoi via USB
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD bytesWritten;

    // Ouverture du port USB
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("Erreur ouverture USB\n");
        return;
    }

    // Envoi de l'octet
    ftStatus = FT_Write(ftHandle, &octet, 1, &bytesWritten);
    if (ftStatus != FT_OK) {
        printf("Erreur envoi commande USB\n");
    }

    // Fermeture du port
    FT_Close(ftHandle);
}