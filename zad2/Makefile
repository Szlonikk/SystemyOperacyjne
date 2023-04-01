Cflags = -O2
CO=gcc
DIR=$(notdir $(CURDIR))
b.x: b.c
	$(CO) $(Cflags) -o $@ $^
procesy.x: procesy.c
	$(CO) $(Cflags) -o $@ $^

.PHONY:  all runb procesy clean tar

runb: b.x
	./b.x $(argument)
procesy: procesy.x
	./procesy.x
	
clean: 
	rm -f *.o *~ *.a *.x a.out; rm -rf ${LIB_DIR}

tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz $(DIR))


	
