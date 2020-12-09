#include <stdio.h>
#define FILE_MAX_LINE 100
#define FILE_LINE_LENGTH 40
#define OPTIONS_LENGTH 4

enum options {maxLoad, divideCharging, minDistance, maxDistance};

int readOptionsFile(enum options optionsArray[]);
int readFileEV(electricVehicle array[], int arrayLen);
int readSpotPricesFile(spotPrices elPrArray[], int elPrArraylen);
int getOption(enum options option);
