#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad5A
PROD = producent
KONS = konsument
PLIK_WE = produkty
PLIK_WY = konsumpcje
POTOK = FIFO
SCIEZKA = ./

#----------------------
EXEC1  = $(NAME1).x
EXECP  = $(PROD).x
EXECK  = $(KONS).x

OBJS1  = $(NAME1).o
OBJSP  = $(PROD).o
OBJSK  = $(KONS).o

#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXECP) $(EXECK)

$(EXEC1): $(OBJS1) $(LIBS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXECP): $(OBJSP) $(LIBSP)
	$(LD) -o $@ $(LFLAGS) $^

$(EXECK): $(OBJSK) $(LIBSK)
	$(LD) -o $@ $(LFLAGS) $^


#############################


.PHONY: runzad5B runzad5A clean tar
runzad5A: $(EXEC1) $(EXECP) $(EXECK)
	./$(EXEC1) $(EXECP) $(EXECK) $(PLIK_WE) $(PLIK_WY) $(POTOK)

runzad5B: $(EXECP) $(EXECK)
	mkfifo -m 0644 $(POTOK)
	xterm -hold -title $(PROD) -e $(SCIEZKA)$(EXECP) $(PLIK_WE) $(POTOK) & xterm -hold -title $(KONS) -e $(SCIEZKA)$(EXECK) $(PLIK_WY) $(POTOK)
	rm $(POTOK)
	
clean: 
	rm -f *.o *.x *~ $(EXECS) ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))


	
