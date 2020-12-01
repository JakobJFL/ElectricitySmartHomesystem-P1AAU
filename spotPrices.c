/* spotPrices.c */
#include "spotPrices.h"
#include "allErrorFile.h"

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

int getArrayIndexForPricesNow(spotPrices array[], int arrayLen) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char timeDate[DATE_MAX_CHARS];
    
    sprintf(timeDate, "%d-%02d-%02d %02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour);
    int i;
    for (i = 0; i < arrayLen; i++) {
        if (strcmp(array[i].date, timeDate) == 0) {
            return i+1;
        }
    }
    printError(202);
    return 0; 
}