#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "spotPrices.h"
#include "electricVehicle.h"
#include "allErrorFile.h"

#define DATE_MAX_LENGTH 15

void askForNewData(void);
int readFile(spotPrices elPrArray[], int elPrArraylen);

int main (void) {
    int newArrayLen = 0;
    srand(10);

    askForNewData();

    spotPrices* elPrArray = (spotPrices*)malloc(SPOT_PRICES_LEN*sizeof(spotPrices)); 
    if (elPrArray == NULL) {
        printError(100);
    }

    printf("Reading file: \n");
    if (readFile(elPrArray, SPOT_PRICES_LEN)) {
        printError(404);
    }
    newArrayLen = getArrayIndexForPricesNow(elPrArray, SPOT_PRICES_LEN);

    qsort(elPrArray, newArrayLen, sizeof(spotPrices), comparespotPrices);
    //printspotPricesArray(elPrArray, newArrayLen);
    int evArrayLen = 17000;
    electricVehicle* evArray = (electricVehicle*)malloc(evArrayLen*sizeof(electricVehicle)); 
    if (evArray == NULL) {
        printError(100);
    }
    generateEvArray(evArray, evArrayLen);

    printf("EvArray:\n");
    //printEV(evArray, evArrayLen);
    chargeEV(evArray, evArrayLen, elPrArray);

    free(elPrArray);

    return 0;
}

void askForNewData(void) {
    char yn;
    printf("Do you want to get data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') {
        system("APIGetElspotPrices\\ElspotPrices.exe");
    }
}

int readFile(spotPrices elPrArray[], int elPrArrayLen) {
    FILE *fpointer;
    float price = 0;
    char date[DATE_MAX_CHARS];
    char singleline[25];
    int i = 0;
    int numOfLineData = 0;

    fpointer = fopen("output.csv", "r"); /* For at fortælle at vi vil gerne læse fra den fil, vi bruger derfor "r" */
    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, 25, fpointer); /* For at læse den linje pr. linje */
            numOfLineData = sscanf(singleline, "%[^;];%f", &date, &price);
            elPrArray[i] = makeElspotPrice(date, price);
            
            if (numOfLineData != 2) {
                printError(201);
            }
            i++;
        }
    }
    else 
        return 1;
    
    return fclose(fpointer);
}
