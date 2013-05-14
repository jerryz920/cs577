
.PHONY: all clean

CXX=g++
LDFLAGS=-O0 -g 
CXXFLAGS=-Wno-write-strings -O0 -g 

all: driver

driver: driver.o dist.o
	$(CXX) $^ $(LDFLAGS) -o $@

%.o: %.cc
	$(CXX) $< $(CXXFLAGS) -o $@ -c

clean:
	rm -f *.o driver
