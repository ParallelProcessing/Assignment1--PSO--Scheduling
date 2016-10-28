all:
	g++ -std=c++11 schedule.cpp sequence.cpp -o sequence.o -O2
       
clean:
	rm -rf *.o
