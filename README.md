- Chay giai thuat tuan tu
	+ make
	+ ./sequence.o input/machine<i>.txt input/task<i>.txt
- Chay giai thuat song song
	+ mpic++ -std=c++11 schedule.cpp parallel.cpp -o parallel.o
	+ mpirun -n <num of process> ./parallel.o input/machine<i>.txt input/task<i>.txt
