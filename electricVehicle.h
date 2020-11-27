#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MODEL_NAME_LEN 25
#define MODEL_TYPE_LEN 4

#define PCT_TESLA 0.556
#define PCT_HYUNDAI 0.114
#define PCT_RENAULT 0.082

typedef struct {
    float chargeRate;
    float capacity;
    float charge;
    char modelName[MODEL_NAME_LEN];
}electricVehicle;

enum modelType {tesla, huyndai, renault, vw};

double sumOfbatCharged(electricVehicle evArray[], int evArrayLen);
void generateEvArray(electricVehicle evArray[], int evArrayLen);
void generateTeslaArray(electricVehicle evArray[], int evArrayStart, int evArrayEnd);
void generateHyundaiArray(electricVehicle evArray[], int evArrayStart, int evArrayEnd);
void generateRenaultArray(electricVehicle evArray[], int evArrayStart, int evArrayEnd);
void generateGolfArray(electricVehicle evArray[], int evArrayStart, int evArrayEnd);
int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge);
void generateKatArray(electricVehicle evArray[], int evArrayStart, int evArrayEnd, enum modelType mType);
electricVehicle makeEv(float capacity, float chargerate, float charge, char modelName[MODEL_NAME_LEN]);
void printEV(electricVehicle array[], int arrayLength);
void chargeEV(electricVehicle evArray[], int evArrayLen, spotPrices elPrArray[]);