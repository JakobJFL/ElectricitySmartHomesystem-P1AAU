#include "spotPrices.h"
#include "electricVehicle.h"
#include "allError.h"
#include "files.h"

void printAndchargeEV(spotPrices elPrArray[]) {
    static electricVehicle fileEvArray[FILE_MAX_LINE];
    electricVehicle* evArray; 
    int evArrayLen;
    if (fileEvArray == NULL)
        printError(100);

    if (readFileEV(fileEvArray, FILE_MAX_LINE)) 
        printError(402);
    evArrayLen = getSumOfEvs(fileEvArray, FILE_MAX_LINE);

    evArray = (electricVehicle*)malloc(evArrayLen*sizeof(electricVehicle));
    if (evArray == NULL)
        printError(100);

    setEvArrayValues(fileEvArray, FILE_MAX_LINE, evArray, evArrayLen);
    setBatteryCharge(evArray, evArrayLen);
    /* printEV(evArray, evArrayLen); */
    chargeEV(evArray, evArrayLen, elPrArray);
    free(elPrArray);
}

int getSumOfEvs(electricVehicle array[], int arrayLen) {
    int i;
    int count = 0;
    for (i = 0; i < arrayLen; i++)
        count += array[i].numOfEV; 
        
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
    int minKm = getOption(minDistance);
    int maxKm = getOption(maxDistance);

    for (i = 0; i < evArrayLen; i++) {
        float km = (rand() % (maxKm - minKm + 1)) + minKm; /* Giver et gennemsnit på 46 km kørt pr. dag */
        evArray[i].charge = evArray[i].capacity - (km/evArray[i].kmPrKwh); 
        /*evArray[i].charge = (float)rand()/(float)(RAND_MAX)*evArray[i].capacity; helt tilfældig batteri niveau*/
    }
}

void printEV(electricVehicle array[], int arrayLength) { /* kan slettes når programmet er færdigt */
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf(" %.2f kWh/%f kWh, ", array[i].charge, array[i].capacity);
        printf("%s , %f \n", array[i].modelName, array[i].chargeRate);
    }
    printf("\n");
}

void chargeEV(electricVehicle evArray[], int evArrayLen, spotPrices elPrArray[]) {
    int numOfEvCharged = 2;
    int hourCount = 0;
    double evCharge = 0;
    double sumEvCharge = 0;
    int divideCh = getOption(divideCharging);
    int divideCharging = getOption(maxLoad);

    while (numOfEvCharged > 0) {
        evCharge = 0;
        numOfEvCharged = chargeEvOneHour(evArray, evArrayLen, evArrayLen/divideCh, divideCharging, &evCharge);
        sumEvCharge += evCharge;
        if (numOfEvCharged > 0) {
            hourCount++;
            printf("%d | Time: %s | Batteri opladet: %.3f MWh | Antal elbiler der oplader: %d | Elpris: %.2f EUR\n", 
            hourCount, 
            elPrArray[hourCount-1].date, 
            evCharge/1000, numOfEvCharged, 
            elPrArray[hourCount-1].price);
        }       
    }
    printf("Det tog: %d timer\n", hourCount);
    printf("Batteri opladet i alt: %.3f MWh", sumEvCharge/1000);
}

int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge, double maxLoad, double* evCharge) {
    int i;
    int numOfEvCharged = 0;
    double preEvCharge = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i].charge < evArray[i].capacity && numOfEvCharged < evToCharge && *evCharge < maxLoad) {
            preEvCharge = evArray[i].charge;
            evArray[i].charge += evArray[i].chargeRate;
            if (evArray[i].charge > evArray[i].capacity) 
                evArray[i].charge = evArray[i].capacity;
            *evCharge += evArray[i].charge - preEvCharge;
            numOfEvCharged++;
        }
    }
    return numOfEvCharged;
}
