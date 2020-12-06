#include "spotPrices.h"
#include "electricVehicle.h"
#include "allErrorFile.h"

void printAndchargeEV(spotPrices elPrArray[]) {
    static electricVehicle fileEvArray[FILE_MAX_LINE];
    if (fileEvArray == NULL) {
        printError(100);
    }
    readFileEV(fileEvArray, FILE_MAX_LINE);

    int evArrayLen = getSumOfEvs(fileEvArray, FILE_MAX_LINE);

    electricVehicle* evArray = (electricVehicle*)malloc(evArrayLen*sizeof(electricVehicle)); 
    if (evArray == NULL) {
        printError(100);
    }
    setEvArrayValues(fileEvArray, FILE_MAX_LINE, evArray, evArrayLen);
    setBatteryCharge(evArray, evArrayLen);
    //printEV(evArray, evArrayLen);
    chargeEV(evArray, evArrayLen, elPrArray);
    free(elPrArray);
}

void readFileEV(electricVehicle array[], int arrayLen){
    FILE *EVdata = fopen("EVdata2.csv", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    if (EVdata != NULL){
        while (!feof(EVdata)){
            fgets(singleline, FILE_LINE_LENGTH, EVdata);

            numOfLineData = sscanf(singleline, "%[^;]; %f; %f; %d; %f", array[i].modelName, &array[i].capacity, &array[i].chargeRate, &array[i].numOfEV, &array[i].kmPrKwh);

            //printf("%s %.1f %f %d \n", array[i].modelName, array[i].capacity, array[i].chargeRate, array[i].numOfEV); //den her skal slettes senere :) 
            
            if (numOfLineData != 5) {
                printError(201);
            }
        i++;
        }
    }
}

int getSumOfEvs(electricVehicle array[], int arrayLen) {
    int i;
    int count = 0;
    for (i = 0; i < arrayLen; i++)
    {
        count += array[i].numOfEV; 
    }
    return count;
}

void setEvArrayValues(electricVehicle arrayFile[], int arrayFileLen, electricVehicle evArray[], int evArrayLen) {
    int i, j;
    int newIndex = 0;
    for (i = 0; i < arrayFileLen; i++) {
        for(j = newIndex; j < arrayFile[i].numOfEV+newIndex; j++) {
            strcpy(evArray[j].modelName, arrayFile[i].modelName);
            evArray[j].capacity = arrayFile[i].capacity;
            evArray[j].chargeRate = arrayFile[i].chargeRate;
            evArray[j].kmPrKwh = arrayFile[i].kmPrKwh;
        }
        newIndex = arrayFile[i].numOfEV+newIndex;
    }
}

void setBatteryCharge(electricVehicle evArray[], int evArrayLen){
    int i;
    int minKm = 20;
    int maxKm = 70;
    for (i = 0; i < evArrayLen; i++) {
        float km = (rand() % (maxKm - minKm + 1)) + minKm;
        evArray[i].charge = evArray[i].capacity - (km/evArray[i].kmPrKwh);
        //(float)rand()/(float)(RAND_MAX)*evArray[i].capacity;
        printf("charge: %f, km: %d", evArray[i].charge, km);
       
    }
}

void printEV(electricVehicle array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf(" %.2f kWh/%f kWh, ", array[i].charge, array[i].capacity);
        printf("%s , %f \n", array[i].modelName, array[i].chargeRate);
    }
    printf("\n");
}

void chargeEV(electricVehicle evArray[], int evArrayLen, spotPrices elPrArray[]) {
    double sum1 = sumOfbatCharged(evArray, evArrayLen);

    int numOfEvCharged = 1;
    int hourCount = 0;
    int evToChargeThreshold = evArrayLen/2;
    float batCharged = 0;
    float preBatCharged = 0;

    //printEV(evArray, evArrayLen);
    while (numOfEvCharged > 0) {
        hourCount++;
        float evCharge = 0;
        numOfEvCharged = chargeEvOneHour(evArray, evArrayLen, evArrayLen/2, &evCharge);
        batCharged = sumOfbatCharged(evArray, evArrayLen)-preBatCharged;
        printf("%d | Time: %s | batCharged: %.3f MWh | eVCharging %d | Pris: %.2f\n", hourCount, elPrArray[hourCount-1].date, evCharge/1000, numOfEvCharged, elPrArray[hourCount-1].price);
        preBatCharged = sumOfbatCharged(evArray, evArrayLen);
    }
    printf("After EvArray:\n");
    printf("Det tog: %d timer\n", hourCount);
    double sum2 = sumOfbatCharged(evArray, evArrayLen);
    printf("BatCharged: %.3f MWh", (sum2-sum1)/1000);
}

double sumOfbatCharged(electricVehicle evArray[], int evArrayLen) {
    int i;
    double sum = 0;
    for(i = 0; i < evArrayLen; i++) {
        sum += evArray[i].charge;
    }
    return sum;
}

int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge, float* evCharge) {
    int i;
    int numOfEvCharged = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i].charge < evArray[i].capacity && numOfEvCharged < evToCharge) {
            evArray[i].charge += evArray[i].chargeRate;
            if (evArray[i].charge > evArray[i].capacity) {
                evArray[i].charge = evArray[i].capacity;
            }
            *evCharge += evArray[i].chargeRate;
            numOfEvCharged++;
        }
    }
    return numOfEvCharged;
}
