#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MODEL_NAME_LEN 25
#define MODEL_TYPE_LEN 4
#define FILE_MAX_LINE 100
#define FILE_LINE_LENGTH 40

typedef struct {
    float chargeRate;
    float capacity;
    float charge;
    char modelName[MODEL_NAME_LEN];
    int numOfEV;
}electricVehicle;

enum modelType {tesla, huyndai, renault, vw};

double sumOfbatCharged(electricVehicle evArray[], int evArrayLen);
void printAndchargeEV(spotPrices elPrArray[]);
int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge);
void setBatteryCharge(electricVehicle evArray[], int evArrayLen);
void printEV(electricVehicle array[], int arrayLength);
void chargeEV(electricVehicle evArray[], int evArrayLen, spotPrices elPrArray[]);
void readFileEV(electricVehicle array[], int arrayLen);
int getSumOfEvs(electricVehicle array[], int arrayLen);
void setEvArrayValues(electricVehicle arrayFile[], int arrayFileLen, electricVehicle evArray[], int evArrayLen);