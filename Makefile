CFLAGS = -Wall -ansi -pedantic

run.exe: electricVehicle.o spotPrices.o allErrorFile.o main.c
	gcc electricVehicle.o spotPrices.o allErrorFile.o main.c -o run.exe

electricVehicle.o: electricVehicle.c electricVehicle.h spotPrices.h
	gcc -c electricVehicle.c

spotPrices.o: spotPrices.c spotPrices.h
	gcc -c spotPrices.c

allErrorFile.o: allErrorFile.c allErrorFile.h
	gcc -c allErrorFile.c

clean:
	$(RM) *.o run.exe *~