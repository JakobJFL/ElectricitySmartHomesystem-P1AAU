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
    FILE *EVdata = fopen("EVdata.csv", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    if (EVdata != NULL){
        while (!feof(EVdata)){
            fgets(singleline, FILE_LINE_LENGTH, EVdata);

            numOfLineData = sscanf(singleline, "%[^;]; %f; %f; %d", array[i].modelName, &array[i].capacity, &array[i].chargeRate, &array[i].numOfEV);

            //printf("%s %.1f %f %d \n", array[i].modelName, array[i].capacity, array[i].chargeRate, array[i].numOfEV); //den her skal slettes senere :) 
            
            if (numOfLineData != 4) {
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
        }
        newIndex = arrayFile[i].numOfEV+newIndex;
    }
}

void setBatteryCharge(electricVehicle evArray[], int evArrayLen){
    int i;
    for (i = 0; i < evArrayLen; i++) {
<<<<<<< Updated upstream
        evArray[i].charge = (float)rand()/(float)(RAND_MAX)*evArray[i].capacity;
=======
        float km = (rand() % (maxKm - minKm + 1)) + minKm; /* Giver et gennemsnit på 46 km kørt pr. dag */
        evArray[i].charge = evArray[i].capacity - (km/evArray[i].kmPrKwh); 
        //evArray[i].charge = 0;
        /*evArray[i].charge = (float)rand()/(float)(RAND_MAX)*evArray[i].capacity; helt tilfældig batteri niveau*/
>>>>>>> Stashed changes
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
    int numOfEvCharged = 2;
    int hourCount = 0;
    double evCharge = 0;
    double sumEvCharge = 0;
    float preBatCharged = 0;

    while (numOfEvCharged > 0) {
        evCharge = 0;
        numOfEvCharged = chargeEvOneHour(evArray, evArrayLen, evArrayLen/2, &evCharge);
        sumEvCharge += evCharge;
        if (numOfEvCharged > 0) {
            hourCount++;
            printf("%d | Time: %s | batCharged: %.3f MWh | eVCharging %d | Pris: %.2f\n", hourCount, 
            elPrArray[hourCount-1].date, 
            evCharge/1000, numOfEvCharged, 
            elPrArray[hourCount-1].price);
        }       
    }
    printf("After EvArray:\n");
    printf("Det tog: %d timer\n", hourCount);
    printf("BatCharged: %.3f MWh", sumEvCharge/1000);
}

double sumOfbatCharged(electricVehicle evArray[], int evArrayLen) {
    int i;
    double sum = 0;
    for(i = 0; i < evArrayLen; i++) {
        sum += evArray[i].charge;
    }
    return sum;
}

int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge, double* evCharge) {
    int i;
    int numOfEvCharged = 0;
    double preEvCharge = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i].charge < evArray[i].capacity && numOfEvCharged < evToCharge) {
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
