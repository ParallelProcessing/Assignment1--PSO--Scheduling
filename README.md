- Chay giai thuat tuan tu
	+ make sequence
	+ ./sequence.o input/machine<i>.txt input/task<i>.txt
- Chay giai thuat song song
	+ make parallel
	+ mpirun -n <num of process> ./parallel.o input/machine<i>.txt input/task<i>.txt


****NOTE***
Number of cores should be smaller or equal 32.
