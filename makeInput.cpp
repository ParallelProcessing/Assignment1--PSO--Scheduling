#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define MACHINE "machine"
#define TASK "task"
#define MAX_TIME 32

int CPU[] = {4, 8, 10, 12, 14, 16};
int RAM[] = {4, 8, 10, 12, 14, 16};

int NEEDCPU[] = {1, 2, 3, 4};
int NEEDRAM[] = {1, 2, 3, 4};

using namespace std;

int main(int argc, char **argv){
	srand(time(NULL));
	if (argc != 4)
		cout <<"Need 2 parameter: <type> <path_Of_Output> <number>"<<endl
		     <<"For exmaple: <machine> <input/machine1.txt> <10> " <<endl;
	else {
		string type = argv[1];
		string path = argv[2];
		int nObjects = stoi(argv[3]);
		
		ofstream outFile;
		outFile.open(path);

		if(type == MACHINE){
			for (int i = 0; i < nObjects; i++ ){
				outFile << to_string(CPU[rand() % 6]) << ","
					<< to_string(RAM[rand() % 6]) << "\n";
			}
			outFile.close();
		}
		
		else if (type == TASK){
			for (int i = 0 ; i < nObjects ;i++){
				outFile << to_string(NEEDCPU[rand() % 4]) << ","
					<< to_string(NEEDRAM[rand() % 4]) << ","
					<< to_string(rand() % (int)MAX_TIME + 1) << "\n"; 
			}
			outFile.close();
		}

		else 
			cout << "Type " << type <<" doesn't exist."<<endl;

		
	}

	return 0;
}










