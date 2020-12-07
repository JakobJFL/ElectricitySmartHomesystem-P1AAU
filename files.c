#include "spotPrices.h"
#include "electricVehicle.h"
#include "files.h"

int readFile(spotPrices elPrArray[], int elPrArrayLen) {
    FILE *fpointer;
    float price = 0;
    char date[DATE_MAX];
    char singleline[FILE_LINE_LENGTH];
    int i = 0;
    int numOfLineData = 0;

    fpointer = fopen("output.csv", "r"); /* For at fortælle at vi vil gerne læse fra den fil, vi bruger derfor "r" */
    if (fpointer != NULL) {
        while (!feof(fpointer)){
            fgets(singleline, FILE_LINE_LENGTH, fpointer); /* For at læse den linje pr. linje */
            numOfLineData = sscanf(singleline, "%[^;];%f", date, &price);
            elPrArray[i] = makeElspotPrice(date, price);
            
            if (numOfLineData != 2)
                printError(201);
            i++;
        }
    }
    else 
        printError(404);
    
    return fclose(fpointer);
}

int getOption(enum options option) {
    static enum options optionsArray[OPTIONS_LENGTH];
    if(readOptionsFile(optionsArray)) 
        printError(402);
    return optionsArray[option];
}

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
                printError(201);
        i++;
        }
    }
    else 
        printError(404);

    return fclose(fpointer);
}

int readOptionsFile(enum options optionsArray[]) {
    FILE *fpointer = fopen("options.txt", "r"); 
    char singleline[FILE_LINE_LENGTH];
    int numOfLineData = 0;
    int i = 0;
    char lineText[20];
    int lineData = 0;

    if (fpointer != NULL) {
        while (!feof(fpointer)) {
            fgets(singleline, FILE_LINE_LENGTH, fpointer);
            numOfLineData = sscanf(singleline, "%[^:]: %d", lineText, &lineData); 
            optionsArray[i] = lineData;
            if (numOfLineData != 2)
                printError(201);
            i++;
        }
    }
    else 
        printError(404);

    return fclose(fpointer);
}