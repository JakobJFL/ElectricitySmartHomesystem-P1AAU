CFLAGS = -Wall -ansi -pedantic

run.exe: electricVehicle.o spotPrices.o files.o allError.o main.c
	gcc electricVehicle.o spotPrices.o files.o allError.o main.c -o run.exe

electricVehicle.o: electricVehicle.c files.h electricVehicle.h spotPrices.h
	gcc -c electricVehicle.c

spotPrices.o: spotPrices.c files.h spotPrices.h
	gcc -c spotPrices.c

files.o: files.c files.h
	gcc -c files.c

allError.o: allError.c allError.h
	gcc -c allError.c

clean:
	$(RM) *.o run.exe *~