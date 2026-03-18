#include <stdio.h>
#include <stdlib.h>
#include "ftd2xx.h"
#include "define.h"

temp_t relever(FT_HANDLE ftHandle) {
    temp_t        temperature;
    temperature.interieure = 0.0f;
    temperature.exterieure = 0.0f;

    DWORD         EventDWord;
    DWORD         TxBytes;
    DWORD         RxBytes;
    DWORD         BytesReceived;
    unsigned char RxBuffer[256];

    // Timeout 5 secondes
    FT_SetTimeouts(ftHandle, 5000, 0);

    // Vérification des octets disponibles
    FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
    printf("Octets disponibles : %lu\n", (unsigned long)RxBytes);

    if (RxBytes == 0) {
        printf("Aucun octet disponible\n");
        return temperature;
    }

    FT_STATUS ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
    if (ftStatus != FT_OK) {
        printf("Erreur FT_Read\n");
        return temperature;
    }

    printf("Lecture OK : %lu octets reçus\n", (unsigned long)BytesReceived);

    // Décodage
    unsigned int SOT_ext = 0;
    unsigned int SOT_int = 0;
    int ext_ok = 0;
    int int_ok = 0;

    for (DWORD i = 0; i + 2 < BytesReceived; i++) {

        // Extérieure : préfixes 0x00, 0x10, 0x20
        if ((RxBuffer[i]   & 0xF0) == 0x00 &&
            (RxBuffer[i+1] & 0xF0) == 0x10 &&
            (RxBuffer[i+2] & 0xF0) == 0x20) {
            SOT_ext  = (RxBuffer[i]   & 0x0F) << 8;
            SOT_ext |= (RxBuffer[i+1] & 0x0F) << 4;
            SOT_ext |= (RxBuffer[i+2] & 0x0F);
            ext_ok = 1;
        }

        // Intérieure : préfixes 0x80, 0x90, 0xA0
        if ((RxBuffer[i]   & 0xF0) == 0x80 &&
            (RxBuffer[i+1] & 0xF0) == 0x90 &&
            (RxBuffer[i+2] & 0xF0) == 0xA0) {
            SOT_int  = (RxBuffer[i]   & 0x0F) << 8;
            SOT_int |= (RxBuffer[i+1] & 0x0F) << 4;
            SOT_int |= (RxBuffer[i+2] & 0x0F);
            int_ok = 1;
        }
    }

    if (ext_ok) {
        temperature.exterieure = -39.64f + 0.04f * (float)SOT_ext;
        printf("Temperature exterieure : %.2f C\n", temperature.exterieure);
    } else {
        printf("Temperature exterieure non trouvee\n");
    }

    if (int_ok) {
        temperature.interieure = -39.64f + 0.04f * (float)SOT_int;
        printf("Temperature interieure : %.2f C\n", temperature.interieure);
    } else {
        printf("Temperature interieure non trouvee\n");
    }

    return temperature;
}