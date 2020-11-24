//todo: 36 linjer data.

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DATE_MAX_LENGTH 15

typedef struct {
    char date[DATE_MAX_LENGTH];
    float price;
}elspotPrices;

int readFile(elspotPrices elPrArray[], int elPrArraylen);
void generateEvArray(float evArray[], int evArrayLen, int batCapacity);
elspotPrices makeElspotPrice(char date[DATE_MAX_LENGTH], float price);
double sumOfbatCharged(float evArray[], int evArrayLen);
int compareElspotPrices(const void *ep1, const void *ep2);
int chargeEvOneHour(float evArray[], int evArrayLen, float batThreshold, float batChargeSpeed, int evToCharge, float batCapacity);
void printElspotPricesArray(elspotPrices array[], int arrayLength);
void printFloatArray(float array[], int arrayLength);

int main (void) {
    srand(10);

    char yn;
    int elPrArrayLen = 31;

    printf("Do you want to get data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') {
        system("APIGetelspotPrices\\elspotPrices.exe");
    }
    elspotPrices* elPrArray = (elspotPrices*)malloc(elPrArrayLen*sizeof(elspotPrices)); 
    printf("Reading file: \n");

    if (readFile(elPrArray, elPrArrayLen)) {
        printf("Error 404: file not found.\n");
    }
    qsort(elPrArray, elPrArrayLen, sizeof(elspotPrices), compareElspotPrices);
    printElspotPricesArray(elPrArray, elPrArrayLen);

    int evArrayLen = 500000;
    float* evArray = (float*)malloc(evArrayLen*sizeof(float)); 

    generateEvArray(evArray, evArrayLen, 65);

    printf("EvArray:\n");
    //printFloatArray(evArray, evArrayLen);
    double sum1 = sumOfbatCharged(evArray, evArrayLen);

    int numOfEvCharged = 1;
    int hourCount = 0;
    int evToChargeThreshold = (evArrayLen/15)*(50/11);
    while (numOfEvCharged > 0) {
        hourCount++;
        numOfEvCharged = chargeEvOneHour(evArray, evArrayLen, 50, 11, evToChargeThreshold*hourCount, 65);
        printf("Time %d: batCharged: %.2f | eVCharging %d \n", hourCount, sumOfbatCharged(evArray, evArrayLen)-sum1, numOfEvCharged);
    }
    printf("After EvArray:\n");
    printf("det tog: %d timer\n", hourCount);
    double sum2 = sumOfbatCharged(evArray, evArrayLen);
    printf("sum: %f", sum2-sum1);
    free(elPrArray);
    return(0);
}

int readFile(elspotPrices elPrArray[], int elPrArrayLen) {
    FILE *fpointer;
    float price = 0;
    char date[DATE_MAX_LENGTH];
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
    else 
        return 1;
    
    return fclose(fpointer);
}

elspotPrices makeElspotPrice(char date[DATE_MAX_LENGTH], float price) {
    elspotPrices elPr;
    strcpy(elPr.date, date);
    elPr.price = price;
    return elPr;
}

double sumOfbatCharged(float evArray[], int evArrayLen) {
    int i;
    double sum = 0;
    for(i = 0; i < evArrayLen; i++) {
        sum += evArray[i];
    }
    return sum;
}

void generateEvArray(float evArray[], int evArrayLen, int batCapacity){
    int i;
    for (i = 0; i < evArrayLen; i++){
        evArray[i] = rand() % (batCapacity-10) + 10;
    }
}

int chargeEvOneHour(float evArray[], int evArrayLen, float batThreshold, float batChargeSpeed, int evToCharge, float batCapacity) {
    int i;
    int numOfEvCharged = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i] < batThreshold && i <= evToCharge) {
            evArray[i] += batChargeSpeed;
            if (evArray[i] > batCapacity) {
                evArray[i] = batCapacity;
            }
            numOfEvCharged++;
        }
    }
    return numOfEvCharged;
}

int compareElspotPrices(const void *p1, const void *p2) {
    const elspotPrices *elem1 = p1;    
    const elspotPrices *elem2 = p2;

    if (elem1->price < elem2->price)
            return -1;
        else if (elem1->price > elem2->price)
            return 1;
        else
            return 0; 
}

void printFloatArray(float array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf(" %.2f, ", array[i]);
    }
    printf("\n");
}

void printElspotPricesArray(elspotPrices array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf("%s, ", array[i].date);
        printf("%.2f\n", array[i].price);
    }
}


