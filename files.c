#include "spotPrices.h"
#include "electricVehicle.h"
#include "files.h"
#include "allError.h"

/*Funktionen readFile læser datafilen, og lægger det læste data ind i elPrArray*/
int readSpotPricesFile(spotPrices elPrArray[], int elPrArrayLen) {
    FILE *fpointer;
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    fpointer = fopen("output.csv", "r"); /*Åbner fil i readmode, derfor: "r"*/
    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, FILE_LINE_LENGTH, fpointer); /*Der læses én linje ad gangen*/
            numOfLineData = sscanf(singleline, "%[^;];%f", elPrArray[i].date, &elPrArray[i].price);
            
            if (numOfLineData != 2)
                printError(401, "output.csv");
            i++;
        }
    }
    else 
        printError(404, "output.csv");
    
    return fclose(fpointer);
}

/* Laver et array med options fra: "readOptionsFile".   */
int getOption(enum options option) {
    /* Laver statisk lagerallokering sådan arrayet ikke slettes hver gang funktionen kaldes. */
    static enum options optionsArray[OPTIONS_LENGTH]; 
    static int isFileRead;
    if (!isFileRead) {
        if(readOptionsFile(optionsArray)) 
            printError(409, "options.txt");
        isFileRead = 1;
    }    
    return optionsArray[option];
}

/* Læser data om elbiler fra EVdata.csv, og lægger dataen i et array*/
int readFileEV(electricVehicle array[], int arrayLen){
    FILE *fpointer = fopen("EVdata.csv", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    if (fpointer != NULL){
        while (!feof(fpointer)){
            fgets(singleline, FILE_LINE_LENGTH, fpointer);

            numOfLineData = sscanf(singleline, "%[^;]; %f; %f; %d; %f", 
                array[i].modelName, 
                &array[i].capacity, 
                &array[i].chargeRate, 
                &array[i].numOfEV, 
                &array[i].kmPrKwh);
            
            if (numOfLineData != 5)
                printError(401, "EVdata.csv");
            else if (array[i].numOfEV < 0)
                printError(402, "EVdata.csv - numOfEV");
            else if (array[i].capacity <= 0 || array[i].chargeRate <= 0 || array[i].kmPrKwh <= 0 )
                printError(403, "EVdata.csv - capacity or chargeRate or kmPrKwh");
            
        i++;
        }
    }
    else 
        printError(404, "EVdata.csv");

    return fclose(fpointer);
}

/*Læser tekstfilen med options, og lægger data derfra ind i et optionsArray*/
int readOptionsFile(enum options optionsArray[]) {
    FILE *fpointer = fopen("options.txt", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int numOfLineData = 0;
    int lineData = 0;
    int i;

    if (fpointer != NULL) {
        for (i = 0; i < OPTIONS_LENGTH; i++) {
            fgets(singleline, FILE_LINE_LENGTH, fpointer);
            numOfLineData = sscanf(singleline, "%*[^:]:%d", &lineData); 
            if (lineData < 0) 
                printError(402, "options.txt");
            optionsArray[i] = lineData;

            if (numOfLineData != 1)
                printError(401, "options.txt");
        }
    }
    else 
        printError(404, "options.txt");

    return fclose(fpointer);
}