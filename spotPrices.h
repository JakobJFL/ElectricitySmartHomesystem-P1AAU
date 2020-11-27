#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define SPOT_PRICES_LEN 37
#define DATE_MAX_CHARS 15

typedef struct {
    char date[DATE_MAX_CHARS];
    float price;
}spotPrices;

spotPrices makeElspotPrice(char date[DATE_MAX_CHARS], float price);
int comparespotPrices(const void *ep1, const void *ep2);
void printspotPricesArray(spotPrices array[], int arrayLength);
int getArrayLenPricesNow(spotPrices array[], int arrayLen);