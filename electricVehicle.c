/* ElectricVehicle.c*/
#include "spotPrices.h"
#include "electricVehicle.h"

void chargeEV(electricVehicle evArray[], int evArrayLen, spotPrices elPrArray[]) {
    double sum1 = sumOfbatCharged(evArray, evArrayLen);

    int numOfEvCharged = 1;
    int hourCount = 0;
    int evToChargeThreshold = evArrayLen/3;

    //printEV(evArray, evArrayLen);
    while (numOfEvCharged > 0) {
        hourCount++;
        numOfEvCharged = chargeEvOneHour(evArray, evArrayLen, evToChargeThreshold*hourCount);
        float batCharged = sumOfbatCharged(evArray, evArrayLen)-sum1;
        printf("%d | Time: %s | batCharged: %.2f | eVCharging %d | Pris: %.2f\n", hourCount, elPrArray[hourCount-1].date, batCharged, numOfEvCharged, elPrArray[hourCount-1].price);
    }
    printf("After EvArray:\n");
    printf("Det tog: %d timer\n", hourCount);
    double sum2 = sumOfbatCharged(evArray, evArrayLen);
    printf("BatCharged: %.2f", sum2-sum1);
}

double sumOfbatCharged(electricVehicle evArray[], int evArrayLen) {
    int i;
    double sum = 0;
    for(i = 0; i < evArrayLen; i++) {
        sum += evArray[i].charge;
    }
    return sum;
}

void generateEvArray(electricVehicle evArray[], int evArrayLen) {
    int evArrayStart = 0;
    int evArrayEnd = evArrayLen*PCT_TESLA;
    generateKatArray(evArray, evArrayStart, evArrayEnd, tesla);
    evArrayStart += evArrayLen*PCT_TESLA;
    evArrayEnd += evArrayLen*PCT_HYUNDAI;
    generateKatArray(evArray, evArrayStart, evArrayEnd, huyndai);
    evArrayStart += evArrayLen*PCT_HYUNDAI;
    evArrayEnd += evArrayLen*PCT_RENAULT;
    generateKatArray(evArray, evArrayStart, evArrayEnd, renault);
    evArrayStart += evArrayLen*PCT_RENAULT;
    evArrayEnd = evArrayLen;
    generateKatArray(evArray, evArrayStart, evArrayEnd, vw);
}

void generateKatArray(electricVehicle evArray[], int evArrayStart, int evArrayEnd, enum modelType mType) {
    float capacity[] = {65, 64, 52, 35.8};
    float chargeRate[] = {11, 10.5, 11, 7.2};
    char modelName[MODEL_TYPE_LEN][MODEL_NAME_LEN] = {"Tesla Model 3", "Huyndai Kona", "Renault Zoe", "VW e-Golf"};
    float charge = 0;

    int i;
    for (i = evArrayStart; i < evArrayEnd; i++) {
        charge = (float)rand()/(float)(RAND_MAX)*capacity[mType];
        evArray[i] = makeEv(capacity[mType], chargeRate[mType], charge, modelName[mType]);
    }
}

electricVehicle makeEv(float capacity, float chargeRate, float charge, char modelName[MODEL_NAME_LEN]){
    electricVehicle ev;
    ev.capacity = capacity;
    ev.chargeRate = chargeRate;
    ev.charge = charge;
    strcpy(ev.modelName, modelName);
    
    return ev;
}

int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge) {
    int i;
    int numOfEvCharged = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i].charge < evArray[i].capacity && i <= evToCharge) {
            evArray[i].charge += evArray[i].chargeRate;
            if (evArray[i].charge > evArray[i].capacity) {
                evArray[i].charge = evArray[i].capacity;
            }
            numOfEvCharged++;
        }
    }
    return numOfEvCharged;
}

void printEV(electricVehicle array[], int arrayLength) {
    int i;
    for(i = 0; i < arrayLength; i++) {
        printf(" %.2f kWh/%f kWh, ", array[i].charge, array[i].capacity);
        printf("%s , %f \n", array[i].modelName, array[i].chargeRate);
    }
    printf("\n");
}
