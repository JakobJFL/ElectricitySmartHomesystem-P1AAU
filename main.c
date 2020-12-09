#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "spotPrices.h"
#include "electricVehicle.h"
#include "allError.h"
#include "files.h"

void askForNewData(void);

int main (void) {
    int newArrayLen = 0;
    spotPrices* elPrArray = (spotPrices*)malloc(SPOT_PRICES_LEN*sizeof(spotPrices));
    if (elPrArray == NULL)
        printError(100);

    srand(time(NULL));
    askForNewData();
    printf("Reading file: \n");
    if (readSpotPricesFile(elPrArray, SPOT_PRICES_LEN)) 
        printError(402);

    newArrayLen = getArrayIndexForPricesNow(elPrArray, SPOT_PRICES_LEN);
    qsort(elPrArray, newArrayLen, sizeof(spotPrices), compareSpotPrices);
    chargeEV(elPrArray);
    free(elPrArray);

    return 0;
}

/*Funktionen askForNewData spørger brugeren, om der skal hentes ny data og henter data, hvis det ønskes*/
void askForNewData(void) {
    char yn;
    printf("Do you want to get new data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') 
        system("APIGetElspotPrices\\ElspotPrices.exe");/*Kører C#-program, der henter data fra API*/
}
