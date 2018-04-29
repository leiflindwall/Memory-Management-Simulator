all: mm

mm: mm.o
	g++ mm.o -o mm

mm.o: mm.cpp
	g++ -g -c mm.cpp

clean:
	rm -rf *.o mm
