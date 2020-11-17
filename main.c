#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char* getCurrentTime(void);
int readFile(void);

int main (void)
{
    system("APIGetData\\GetElectricityProductionAPI.exe");
    
    if (readFile()) {
        printf("NEJ\n");
    }
    return(0);
}

int readFile(void) {
    FILE *fpointer;
    double price;
    char date[20];
    char singleline[20];
    fpointer = fopen("output.txt", "r"); /* For at fortælle at vi vil gerne læse fra det fil, vi bruger derfor "r" */
    
    if (fpointer != NULL) {
        int i = 0;
        while (!feof(fpointer)){
            for(int x = 0; x < 2; x++) {
                fgets(singleline, 20, fpointer); /* For at læse den linje pr. linje */
                if (x % 2 == 0) 
                    memcpy(date, strtok(singleline, "\n"), sizeof singleline);
                else 
                    price = atof(singleline); /* Konverterer til en double */
            } 
            i++;
        }
    }
    else 
        return 1;
    return fclose(fpointer);
}
