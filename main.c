#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "electricVehicle.h"
#include "spotPrices.h"

#define DATE_MAX_LENGTH 15

void askForNewData(void);
int readFile(spotPrices elPrArray[], int elPrArraylen);

int main (void) {
    srand(10);

    askForNewData();

    spotPrices* elPrArray = (spotPrices*)malloc(SPOT_PRICES_LEN*sizeof(spotPrices)); 
    printf("Reading file: \n");
    if (readFile(elPrArray, SPOT_PRICES_LEN)) {
        printf("Error 404: file not found.\n");
    }

    qsort(elPrArray, SPOT_PRICES_LEN, sizeof(spotPrices), comparespotPrices);
    printspotPricesArray(elPrArray, SPOT_PRICES_LEN);
    int evArrayLen = 17000;
    electricVehicle* evArray = (electricVehicle*)malloc(evArrayLen*sizeof(electricVehicle)); 
    generateEvArray(evArray, evArrayLen);

    //findRelevantspotprices(elPrArray);

    printf("EvArray:\n");
    //printEV(evArray, evArrayLen);
    chargeEV(evArray, evArrayLen);

    free(elPrArray);

    return(0);
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

    fpointer = fopen("output.csv", "r"); /* For at fortælle at vi vil gerne læse fra den fil, vi bruger derfor "r" */
    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, 25, fpointer); /* For at læse den linje pr. linje */
            sscanf(singleline, "%[^;];%f", &date, &price);
            elPrArray[i] = makeElspotPrice(date, price);
            //printf("%s, %.2f\n", date, price);
            i++;
        }
    }
    else return 1;
    
    return fclose(fpointer);
}
