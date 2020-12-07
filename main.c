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

    srand(10);
    askForNewData();
    printf("Reading file: \n");
    if (readFile(elPrArray, SPOT_PRICES_LEN)) 
        printError(402);

    newArrayLen = getArrayIndexForPricesNow(elPrArray, SPOT_PRICES_LEN);
    qsort(elPrArray, newArrayLen, sizeof(spotPrices), compareSpotPrices);
    printAndchargeEV(elPrArray);
    /*printspotPricesArray(elPrArray, newArrayLen); */

    return 0;
}

void askForNewData(void) {
    char yn;
    printf("Do you want to get data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') 
        system("APIGetElspotPrices\\ElspotPrices.exe");
}
