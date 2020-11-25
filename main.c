#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DATE_MAX_LENGTH 15
#define SPOT_PRICES_LEN 31

typedef struct {
    char date[DATE_MAX_LENGTH];
    float price;
}spotPrices;

typedef struct {
    /* Tesla Model 3, Renault Zoe og Hyundai Kona */
    float chargeRate;
    float capacity;
}eVdata;

int readFile(spotPrices elPrArray[], int elPrArraylen);
void generateEvArray(float evArray[], int evArrayLen, int batCapacity);
eVdata eVSpecs (float chargeRate, float capacity);
spotPrices makeElspotPrice(char date[DATE_MAX_LENGTH], float price);
double sumOfbatCharged(float evArray[], int evArrayLen);
int comparespotPrices(const void *ep1, const void *ep2);
int chargeEvOneHour(float evArray[], int evArrayLen, float batThreshold, float batChargeSpeed, int evToCharge, float batCapacity);
void printspotPricesArray(spotPrices array[], int arrayLength);
void printFloatArray(float array[], int arrayLength);
void chargeEV(float evArray[], int evArrayLen);
void askForNewData(void);

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
    float* evArray = (float*)malloc(evArrayLen*sizeof(float)); 

    generateEvArray(evArray, evArrayLen, 65);

    printf("EvArray:\n");
    //printFloatArray(evArray, evArrayLen);
    chargeEV(evArray, evArrayLen);

    free(elPrArray);

    return(0);
}

eVdata eVSpecs (float chargeRate, float capacity) {
    eVdata tesla;
    eVdata hyundai;
    eVdata renault;
    /* ChargeRate = kW */
    /* Capacity = kWh */
    tesla.chargeRate = 11;
    tesla.capacity = 50;

    hyundai.chargeRate = 10.5;
    hyundai.capacity = 67.5;
    
    renault.chargeRate = 11;
    renault.capacity = 52;
    printf("hej");
    printf("chargerate: %f, cap: %f", tesla.chargeRate, tesla.capacity);

    return tesla, hyundai, renault;
}

void askForNewData(void) {
    char yn;
    printf("Do you want to get data? Type \"y\" for yes and \"n\" for no: ");
    scanf(" %c", &yn);
    if (yn == 'y') {
        system("APIGetspotPrices\\spotPrices.exe");
    }
}

int readFile(spotPrices elPrArray[], int elPrArrayLen) {
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
    else return 1;
    
    return fclose(fpointer);
}

/* spotPrices.c */

spotPrices makeElspotPrice(char date[DATE_MAX_LENGTH], float price) {
    spotPrices spotPr;
    strcpy(spotPr.date, date);
    spotPr.price = price;
    return spotPr;
}

int comparespotPrices(const void *p1, const void *p2) {
    const spotPrices *elem1 = p1;    
    const spotPrices *elem2 = p2;

    if (elem1->price < elem2->price)
            return -1;
        else if (elem1->price > elem2->price)
            return 1;
        else
            return 0; 
}

void printspotPricesArray(spotPrices array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf("%s, ", array[i].date);
        printf("%.2f\n", array[i].price);
    }
}

/* ElectricVehicle.c */
void chargeEV(float evArray[], int evArrayLen) {
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

void printFloatArray(float array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf(" %.2f, ", array[i]);
    }
    printf("\n");
}