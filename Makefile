# Makefile0.1

BDIR := ./lib

# define include diractery 
IDIR := ./include

# define obj diractery and obj file 
objf := ./word_an.o ./types_an.o ./identifier_an.o ./space.o ./constant_an.o ./separator_an.o ./string_an.o 

# define src diractery 
SDIR := ./src

# gcc link include
linklib := -I$(IDIR)

# get bin_fileuted file
bin_file := wordAna 

$(bin_file) : $(objf) 
	cc -o $(bin_file) $(objf) $(linklib) -g
	make clean_obj

word_an.o types_an.o : $(SDIR) $(IDIR) 
	cc -c $(SDIR)/types_an.c $(linklib) -g
	cc -c $(SDIR)/word_an.c $(linklib) -g
	cc -c $(SDIR)/identifier_an.c $(linklib) -g
	cc -c $(SDIR)/space.c $(linklib) -g
	cc -c $(SDIR)/constant_an.c $(linklib) -g
	cc -c $(SDIR)/separator_an.c $(linklib) -g
	cc -c $(SDIR)/string_an.c $(linklib) -g


.PHONY : clean_obj clean show 
clean_obj : 
	-rm $(objf) 

clean : 
	-rm $(bin_file) 
	-rm $(BDIR)/constant
	-rm $(BDIR)/identifier

show :
	@echo constant : 
	@cat  ./lib/constant
	@echo
	@echo identifier : 
	@cat  ./lib/identifier
	@echo
	@echo outfile : 
	@cat  ./outfile
	@echo
	@echo file :
	@cat ./file
