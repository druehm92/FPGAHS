# Christian De Schryver 2014
# Markus Steffes 2015

CC=g++
CFLAGS=-Wall -std=c++0x
LDFLAGS=-I ./EasyBMP -L$(SYSTEMC_LIB_DIR) -lsystemc

all:
	$(CC) $(CFLAGS) $(LDFLAGS) -o main EasyBMP/EasyBMP.cpp memory.cpp median_module.cpp median_tb.cpp main.cpp

dbg:
	$(CC) -v -g $(CFLAGS) $(LDFLAGS)  -o main EasyBMP/EasyBMP.cpp memory.cpp median_module.cpp median_tb.cpp main.cpp

clean:	
	rm -f *.o main Output.bmp *.cpp.*

