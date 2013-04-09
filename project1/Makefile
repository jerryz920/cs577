
.PHONY: all clean

CXX=g++
LDFLAGS=-O0 -g -std=c++11
CXXFLAGS=-Wno-write-strings -O0 -g -std=c++11

all: splay opt

splay: splay.o
	$(CXX) $< $(LDFLAGS) -o $@ 

opt: opt.o
	$(CXX) $< $(LDFLAGS) -o $@ 

%.o: %.c
	$(CXX) $< $(CXXFLAGS) -o $@ -c

clean:
	rm -f *.o splay opt
