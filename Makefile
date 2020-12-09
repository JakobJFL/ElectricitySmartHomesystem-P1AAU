CFLAGS = -Wall -ansi -pedantic

run.exe: electricVehicle.o spotPrices.o files.o allError.o main.c
	gcc $(CFLAGS) electricVehicle.o spotPrices.o files.o allError.o main.c -o run.exe

electricVehicle.o: electricVehicle.c files.h electricVehicle.h spotPrices.h
	gcc $(CFLAGS) -c electricVehicle.c

spotPrices.o: spotPrices.c files.h spotPrices.h
	gcc $(CFLAGS) -c spotPrices.c

files.o: files.c files.h
	gcc $(CFLAGS) -c files.c

allError.o: allError.c allError.h
	gcc $(CFLAGS) -c allError.c

clean:
	$(RM) *.o run.exe *~