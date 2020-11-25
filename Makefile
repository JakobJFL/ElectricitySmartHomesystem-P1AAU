run.exe: main.c
	gcc -Wall -ansi -pedantic main.c \
		-o run.exe
		

clean:
	$(RM) *.o run.exe *~