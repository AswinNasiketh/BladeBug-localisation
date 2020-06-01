IDIR =../inc
CC = gcc
CFLAGS=-I$(IDIR)

src = $(wildcard *.c)
obj = $(src:.c=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

main: $(obj)
	$(CC) -o $@ $^ $(CFLAGS)

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
#taken from http://nuclear.mutantstargoat.com/articles/make/
%.d: %.c
	@$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f *.o 

.PHONY: cleandep
cleandep:
	rm -f *.d