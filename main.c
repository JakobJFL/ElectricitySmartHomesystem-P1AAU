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
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); /*Der laves et struct over nuværende år, dag og time*/
    spotPrices* priceArray = (spotPrices*)malloc(SPOT_PRICES_LEN*sizeof(spotPrices));
    if (priceArray == NULL)
        printError(100, "priceArray");
    srand(time(NULL));

    askForNewData();
    printf("Charging electric cars: \n");
    if (readSpotPricesFile(priceArray, SPOT_PRICES_LEN)) 
        printError(409, "output.csv");

    newArrayLen = getArrayIndex(priceArray, SPOT_PRICES_LEN, tm);
    qsort(priceArray, newArrayLen, sizeof(spotPrices), compareSpotPrices);
    chargeEV(priceArray);
    free(priceArray);

    return 0;
}

/*Funktionen askForNewData spørger brugeren, om der skal hentes ny data og henter data, hvis det ønskes*/
void askForNewData(void) {
    char yn;
    printf("Do you want to get new data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') 
        system("APIGetElspotPrices\\ElspotPrices.exe"); /*Kører C#-program, der henter data fra API*/
}
