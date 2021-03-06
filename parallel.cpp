#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include "schedule.h"
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#define STEP 1000

using namespace std;

time_t time_ms(void) {
        timeval tp;
        gettimeofday(&tp, NULL);
        return (time_t)tp.tv_sec * 1000 + (time_t)tp.tv_usec / 1000;	
}

vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}



schedule* minOfVector(vector<schedule*> schedules){
	int min = (int)MAX_TIME  + 1;
	int minIndex = 0;
	for (int i = 0; i < schedules.size(); i++){
		if(schedules.at(i)->timeFinish < min){
			min = schedules.at(i)->timeFinish;
			minIndex = i;
		}
	}

	return schedules.at(minIndex);
}

int main(int argc, char **argv){
	int rank, size;
	int bestProcess;
	int *result;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	srand(time(NULL) + rank);

	if (rank == 0){
		result = new int [size];
	}

	vector<machine *>* machines = new vector<machine *>();
	vector<task *>* tasks = new vector<task *>();


	/* Generate machines and tasks from file*/
	string line;
	
	ifstream inputMachine (argv[1]);
	int id = 0;
	if (inputMachine.is_open()){
		while (getline (inputMachine,line) ){
			id++ ;
			vector<string> x = split(line,',');
			if(x.size() == 2)
				machines->push_back(new machine(id, resource(stoi(x.at(0)), stoi(x.at(1)))));
			x.clear();
	  }
		inputMachine.close();
	}
	else
		cout << "Unable to open file";

	ifstream inputTask (argv[2]);
	id = 0;
	if (inputTask.is_open()){
		while (getline (inputTask,line) ){
			id ++ ;
			vector<string> x = split(line,',');
			if(x.size() == 3)
				tasks->push_back(new task(id, resource(stoi(x.at(0)), stoi(x.at(1))), stoi(x.at(2))));
			x.clear();
	  }
		inputTask.close();
	}
	else
		cout << "Unable to open file";

	/* Each process do scheduling*/
	vector<schedule *> schedules;
	
	time_t begin = time_ms();
	for (int i = 0 ; i < (int)STEP / size; i++){
		schedule *scheduleObj;
		if (i % 5 == 0)
			 scheduleObj = new schedule(machines, tasks, true); //bestSeed
		else 
			scheduleObj = new schedule(machines, tasks, false); //randomSeed

		scheduleObj->scheduling();
		schedules.push_back(scheduleObj);
	}

	schedule *minSchedule = minOfVector(schedules);

	MPI_Gather(& minSchedule->timeFinish, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD );

	/* Check what process rerurn best result, then send a message to it for requiring drawing*/
	if(rank == 0){
		int min = 99999;
		int indexBestProcess = 0;

		/*Find process having best result*/
		for(int i = 0 ; i < size; i++){
			if (result[i] < min){
				min = result[i];
				indexBestProcess = i;
			}
		}

		/*Send message for requriring the best process draw*/
		bestProcess = indexBestProcess;
	}
	
	
	/* Send bestprocess to all process*/
	MPI_Bcast(&bestProcess, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == bestProcess){
		cout <<"Process "<< rank <<" releases the best result time: "<< minSchedule->timeFinish <<endl;
		cout <<"time schedule: "<< time_ms()- begin <<"(ms)"<<endl;
		cout <<"Do you want to simulate the progress ? (yes/no)" <<endl;
		string choice = "";
		cin >>choice ;
		if (choice == "yes")
			minSchedule->draw();
	}


	MPI_Finalize();
	return 0;
}
