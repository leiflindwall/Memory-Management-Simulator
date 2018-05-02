all: memory_simulator

memory_simulator: mm
	./mm

mm: mm.o
	g++ mm.o -o mm

mm.o: mm.cpp mm.h
	g++ -g -c mm.cpp

clean:
	rm -rf *.o mm
