#include "commande.h"
#include <stdio.h>
#include "ftd2xx.h"

void envoyer_commande(FT_HANDLE ftHandle, float puissance) {
    FT_STATUS     ftStatus;
    DWORD         bytesWritten = 0;
    unsigned char octet_commande;

    // Saturation de la puissance entre 0 et 100%
    if (puissance < 0.0f)   puissance = 0.0f;
    if (puissance > 100.0f) puissance = 100.0f;

    // Calcul de la valeur sur 7 bits : PUIS = (puissance / 100) * 127
    octet_commande = (unsigned char)((puissance * 127.0f) / 100.0f);

    // Bit 7 à 0 : mode chauffage
    octet_commande &= 0x7F;

    printf("Puissance : %.1f%% -> octet : 0x%02X (%d)\n",
           puissance, octet_commande, octet_commande);

    // Envoi via FT_Write
    ftStatus = FT_Write(ftHandle, &octet_commande, 1, &bytesWritten);
    if (ftStatus == FT_OK && bytesWritten == 1) {
        printf("Octet envoyé avec succès\n");
    } else {
        fprintf(stderr, "Erreur FT_Write : status=%d, octets écrits=%lu\n",
                (int)ftStatus, (unsigned long)bytesWritten);
    }
}