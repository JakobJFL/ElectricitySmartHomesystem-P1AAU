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
double sumOfbatChargedNeeded(float evArray[], int evArrayLen, int batCapacity);
int compareElspotPrices(const void *ep1, const void *ep2);
int chargeEvOneHour(float evArray[], int evArrayLen, float batThreshold, float batChargeSpeed);
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

    int evArrayLen = 100;
    float* evArray = (float*)malloc(evArrayLen*sizeof(float)); 

    generateEvArray(evArray, evArrayLen, 50);

    printf("EvArray:\n");
    printFloatArray(evArray, evArrayLen);
    printf("sum: %f", sumOfbatChargedNeeded(evArray, evArrayLen, 50));

    int numOfEvCharged = 1;
    int hourCount = 0;
    while (numOfEvCharged > 0) {
        numOfEvCharged = chargeEvOneHour(evArray, evArrayLen, 40, 11);
        hourCount++;
    }
    printf("After EvArray:\n");
    printFloatArray(evArray, evArrayLen);
    printf("det tog: %d\n", hourCount);
    printf("sum: %f", sumOfbatChargedNeeded(evArray, evArrayLen, 50));
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

double sumOfbatChargedNeeded(float evArray[], int evArrayLen, int batCapacity) {
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

int chargeEvOneHour(float evArray[], int evArrayLen, float batThreshold, float batChargeSpeed) {
    int i;
    int numOfEvCharged = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i] < batThreshold) {
            evArray[i] += batChargeSpeed;
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
        printf("%.2f \n", array[i]);
    }
}

void printElspotPricesArray(elspotPrices array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf("%s, ", array[i].date);
        printf("%.2f\n", array[i].price);
    }
}


