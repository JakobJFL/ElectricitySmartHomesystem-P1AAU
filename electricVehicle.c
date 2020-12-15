#include "spotPrices.h"
#include "electricVehicle.h"
#include "allError.h"
#include "files.h"

/* Oplader elbilerne ved at advokerer plads til et array, læse data fra en fil, 
og køre de forskellige nedenstående funktioner hvor man til sidst ender med et array med alt data som printes.  */
void chargeEV(spotPrices priceArray[]) {
    static electricVehicle fileEvArray[FILE_MAX_LINE];
    electricVehicle* evArray; 
    int evArrayLen;

    if (readFileEV(fileEvArray, FILE_MAX_LINE)) 
        printError(409, "EVdata.csv");
    evArrayLen = getSumOfEvs(fileEvArray, FILE_MAX_LINE);

    evArray = (electricVehicle*)malloc(evArrayLen*sizeof(electricVehicle));
    if (evArray == NULL)
        printError(100, "evArray");

    setEvArrayValues(fileEvArray, FILE_MAX_LINE, evArray, evArrayLen);
    setBatteryCharge(evArray, evArrayLen);
    chargeAndPrintEV(evArray, evArrayLen, priceArray);
    free(priceArray);
}

/* Returnerer en sum af hvor mange elbiler der er af hver slags. */
int getSumOfEvs(electricVehicle array[], int arrayLen) {
    int i;
    int count = 0;
    for (i = 0; i < arrayLen; i++)
        count += array[i].numOfEV; 
        
    return count;
}

/* Udfylder: "evArray" med alle elementer fra: "arrayFile" og indsætter kopier efter hvor mange der skal være af hver. */
void setEvArrayValues(electricVehicle arrayFile[], int arrayFileLen, electricVehicle evArray[], int evArrayLen) {
    int i, j;
    int newIndex = 0;
    for (i = 0; i < arrayFileLen; i++) {
        for(j = newIndex; j < arrayFile[i].numOfEV+newIndex; j++) {
            strcpy(evArray[j].modelName, arrayFile[i].modelName);
            evArray[j].capacity = arrayFile[i].capacity;
            evArray[j].chargeRate = arrayFile[i].chargeRate;
            evArray[j].kmPrKwh = arrayFile[i].kmPrKwh;
        }
        newIndex = arrayFile[i].numOfEV+newIndex;
    }
}

/* Sætter et tilfældigt batteriniveau(Charge) i: "evArray" mellem værdierne: "minKm", "maxKm". */
void setBatteryCharge(electricVehicle evArray[], int evArrayLen){
    int i;
    int minKm = getOption(minDistance);
    int maxKm = getOption(maxDistance);

    for (i = 0; i < evArrayLen; i++) {
        float km = (rand() % (maxKm - minKm + 1)) + minKm; /* Output: et tilfældigt tal mellem minKM og maxKM */
        evArray[i].charge = evArray[i].capacity - (km/evArray[i].kmPrKwh); 
    }
}

/* Oplader alle elbilerne i: "evArray". Den sådan "Charge" er lig med "capacity" for alle elbiler. Herefter printes hver opladning. */
void chargeAndPrintEV(electricVehicle evArray[], int evArrayLen, spotPrices priceArray[]) {
    int numOfEvCharging = 2;
    int hourCount = 0;
    double evCharge = 0;
    double sumEvCharge = 0;
    int divideCh = getOption(divideCharging);
    int loadMax = getOption(maxLoad);

    if (!divideCh) 
        printError(403, "options.txt - divideCharging");

    /* Kører så længe at "chargeEvOneHour" ikke returnerer 0 altså at 0 elbiler blev opladet i den time 
    fordi der ikke er flere der skal oplades. */
    while (numOfEvCharging != 0) { 
        evCharge = 0;
        numOfEvCharging = chargeEvOneHour(evArray, evArrayLen, evArrayLen/divideCh, loadMax, &evCharge);
        sumEvCharge += evCharge;
        if (numOfEvCharging != 0) {
            hourCount++;
            printf("%d | Date: %s | Batteries charged: %.3f MWh | Electric cars charging: %d | Electricity price: %.2f EUR\n", 
                hourCount, 
                priceArray[hourCount-1].date, 
                evCharge/1000, numOfEvCharging, 
                priceArray[hourCount-1].price);
        }
    }
    printf("It took %d hours\n", hourCount);
    printf("Power used: %.3f MWh", sumEvCharge/1000);
}

/* Oplader elbilerne for en time ved at ligge "chargeRate" til "charge" på hver elbil i "evArray" 
så længe antal elbiler der ikke lader ikke overskrider det der må lades ("maxLoad", "evToCharge"). */
int chargeEvOneHour(electricVehicle evArray[], int evArrayLen, int evToCharge, double maxLoad, double* evCharge) {
    int i;
    int numOfEvCharging = 0;
    double preEvCharge = 0;
    for(i = 0; i < evArrayLen; i++) {
        if (evArray[i].charge < evArray[i].capacity && numOfEvCharging < evToCharge && *evCharge < maxLoad) {
            preEvCharge = evArray[i].charge;
            evArray[i].charge += evArray[i].chargeRate;
            if (evArray[i].charge > evArray[i].capacity) 
                evArray[i].charge = evArray[i].capacity;
            *evCharge += evArray[i].charge - preEvCharge;
            numOfEvCharging++;
        }
    }
    return numOfEvCharging;
}
