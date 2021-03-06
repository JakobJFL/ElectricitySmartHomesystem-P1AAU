#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SPOT_PRICES_LEN 36
#define DATE_MAX 15

typedef struct {
    char date[DATE_MAX];
    float price;
}spotPrices;

int compareSpotPrices(const void *ep1, const void *ep2);
void printspotPricesArray(spotPrices array[], int arrayLength);
int getArrayIndex(spotPrices array[], int arrayLen, struct tm tm);
void printCurrentPrice(spotPrices array[], int newArrayLen);