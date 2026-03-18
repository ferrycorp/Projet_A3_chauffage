#include "releve.h"
#include <stdio.h>
#include "ftd2xx.h"

temp_t releve() {
    temp_t temperature;
    temperature.interieure = 0.0f;
    temperature.exterieure = 0.0f;

    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD bytesRead;
    unsigned char octet;

    // Ouverture du port USB
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus != FT_OK) {
        printf("Erreur ouverture USB\n");
        return temperature;
    }

    // -------------------------------------------------------------------
    // Synchronisation + lecture temperature exterieure (3 octets)
    // Octet 1 : 0000xxxx (bits 11-8)
    // Octet 2 : 0001xxxx (bits 7-4)
    // Octet 3 : 0010xxxx (bits 3-0)
    // -------------------------------------------------------------------
    unsigned int SOT_ext = 0;
    int synchro = 0;

    while (!synchro) {
        FT_Read(ftHandle, &octet, 1, &bytesRead);

        // Cherche le premier octet de la temperature exterieure
        // identifie par les bits 7-4 = 0000
        if ((octet & 0xF0) == 0x00) {
            // Octet 1 : bits 11-8 du SOT
            SOT_ext = (octet & 0x0F) << 8;

            // Octet 2 : bits 7-4 du SOT
            FT_Read(ftHandle, &octet, 1, &bytesRead);
            if ((octet & 0xF0) != 0x10) continue; // resynchronisation
            SOT_ext |= (octet & 0x0F) << 4;

            // Octet 3 : bits 3-0 du SOT
            FT_Read(ftHandle, &octet, 1, &bytesRead);
            if ((octet & 0xF0) != 0x20) continue; // resynchronisation
            SOT_ext |= (octet & 0x0F);

            synchro = 1;
        }
    }

    // -------------------------------------------------------------------
    // Lecture temperature interieure (3 octets)
    // Octet 1 : 1000xxxx (bits 11-8)
    // Octet 2 : 1001xxxx (bits 7-4)
    // Octet 3 : 1010xxxx (bits 3-0)
    // -------------------------------------------------------------------
    unsigned int SOT_int = 0;
    synchro = 0;

    while (!synchro) {
        FT_Read(ftHandle, &octet, 1, &bytesRead);

        // Cherche le premier octet de la temperature interieure
        // identifie par les bits 7-4 = 1000
        if ((octet & 0xF0) == 0x80) {
            // Octet 1 : bits 11-8 du SOT
            SOT_int = (octet & 0x0F) << 8;

            // Octet 2 : bits 7-4 du SOT
            FT_Read(ftHandle, &octet, 1, &bytesRead);
            if ((octet & 0xF0) != 0x90) continue; // resynchronisation
            SOT_int |= (octet & 0x0F) << 4;

            // Octet 3 : bits 3-0 du SOT
            FT_Read(ftHandle, &octet, 1, &bytesRead);
            if ((octet & 0xF0) != 0xA0) continue; // resynchronisation
            SOT_int |= (octet & 0x0F);

            synchro = 1;
        }
    }

    // -------------------------------------------------------------------
    // Conversion SOT → temperature en degres Celsius
    // Temperature absolue en °C = -39.64 + 0.04 * SOT
    // -------------------------------------------------------------------
    temperature.exterieure = -39.64f + 0.04f * (float)SOT_ext;
    temperature.interieure = -39.64f + 0.04f * (float)SOT_int;

    FT_Close(ftHandle);

    return temperature;
}