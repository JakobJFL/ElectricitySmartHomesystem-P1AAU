/* spotPrices.c */
#include <string.h>
#include "spotPrices.h"

spotPrices makeElspotPrice(char date[DATE_MAX_CHARS], float price) {

    
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

/*void findRelevantspotprices(spotPrices array[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //printf("\n\n\n%d\n\n\n", tm.tm_hour);

    int arrayLen;
    switch (tm.tm_hour) {
    case 15:
        arrayLen = 32; break;
    case 16:
        arrayLen = 31; break;
    case 17:
        arrayLen = 30; break;
    case 18:
        arrayLen = 29; break;
    case 19:
        arrayLen = 28; break;
    case 20:
        arrayLen = 27; break;
    case 21:
        arrayLen = 26; break;
    case 22:
        arrayLen = 25; break;
    case 23:
        arrayLen = 24; break;
    case 00:
        arrayLen = 23; break;
    case 01:
        arrayLen = 22; break;
    case 02:
        arrayLen = 21; break;
    case 03:
        arrayLen = 20; break;
    case 04:
        arrayLen = 19; break;
    case 05:
        arrayLen = 18; break;
    case 06:
        arrayLen = 17; break;
    default: printf(" No is not workin'"); break;
    }

    printspotPricesArray(tempArray, arrayLen);


}*/