makeInput:
	g++ -std=c++11 makeInput.cpp -o makeInput.o
sequence:
	g++ -std=c++11 schedule.cpp sequence.cpp -o sequence.o -O3

parallel:
	mpic++ -std=c++11 schedule.cpp parallel.cpp -o parallel.o -O3 
       
clean:
	rm -rf *.o
