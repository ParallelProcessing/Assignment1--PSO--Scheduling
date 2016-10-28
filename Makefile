all:
	g++ -std=c++11 schedule.cpp sequence.cpp -o sequence.o -O3
       
clean:
	rm -rf *.o
