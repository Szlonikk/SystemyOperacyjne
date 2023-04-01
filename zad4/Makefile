#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad4
NAME2 = producent
NAME3 = konsument

#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o

#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = gcc
LD = $(CO)
#############################
%.o: %.c
	$(CO) $(COFLAGS) -c $<
#############################

$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^

#############################


.PHONY: runzad4 clean tar
runzad4: $(EXEC1)
	./$(EXEC1) $(NAME2) $(NAME3)

	
clean: 
	rm -f *.o *~ $(EXECS) ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))


	
