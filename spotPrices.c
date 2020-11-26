/* spotPrices.c */
#include "spotPrices.h"

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
