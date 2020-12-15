/* spotPrices.c */
#include "spotPrices.h"
#include "allError.h"

/*Funktionen compareSpotPrices sammenligner elpriser, der anvendes af qsort-funktionen*/
int compareSpotPrices(const void *p1, const void *p2) {
    const spotPrices *elem1 = p1;    
    const spotPrices *elem2 = p2;

    if (elem1->price < elem2->price)
            return -1;
        else if (elem1->price > elem2->price)
            return 1;
        else
            return 0; 
}

/*  */
int getArrayIndexForPricesNow(spotPrices array[], int arrayLen, struct tm tm) {
    int i;
    char timeDate[DATE_MAX];
    sprintf(timeDate, "%d-%02d-%02d %02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour);
    for (i = 0; i < arrayLen; i++) {
        if (strcmp(array[i].date, timeDate) == 0) { /*Tjekker om der er ens dato og tid, med den hentede data fra C#-programmet*/
            return i+1;
        }
    }
    printError(202, "output.csv"); /*Printer fejlkode hvis der ikke findes nogen ens dato og tid*/
    return 0; 
}