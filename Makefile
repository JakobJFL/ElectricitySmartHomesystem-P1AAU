CFLAGS = -Wall -ansi -pedantic

run.exe: electricVehicle.o spotPrices.o main.c
	gcc electricVehicle.o spotPrices.o main.c -o run.exe

electricVehicle.o: electricVehicle.c electricVehicle.h
	gcc -c electricVehicle.c

spotPrices.o: spotPrices.c spotPrices.h
	gcc -c spotPrices.c

clean:
	$(RM) *.o run.exe *~