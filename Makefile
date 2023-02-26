CC = gcc
CFLAGS =-std=c17 -pedantic -Wall
OBJ = ABR.o filtrage.o
EXE = filtrage
REG = src/


$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
filtrage.o: $(REG)filtrage.c $(REG)ABR.h
 

ABR.o : $(REG)ABR.c $(REG)ABR.h


%.o: $(REG)%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXE)
	rm -f *.pdf
	rm -f *.dot

install: $(EXE)
	mkdir bin
	mv $(EXE) bin/$(EXE)
	make mrproper

uninstall: mrproper
	rm -f bin/$(EXE)
	rm -rf bin
