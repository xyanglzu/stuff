#include <iostream>
#include <fstream>	// file I/O
#include <cstdlib>	// rand
#include <ctime>	// time
#include <cmath>	// sqrt
#include <cstring>	// memcpy

#include "../lib/VRPlib.h"
#include "../lib/LSProgram.h"
#include "../lib/LSBase.h"

using namespace CBLS;
using namespace std;


char *program_name;
char *instance_file;
int nb_iter;


void usage() {
	cerr << "Usage is " << program_name << " nb_iter instance_file \n";
	cerr << "ex: ./testVRP 100000 ../data/cordeau/vrp/old/p02" << endl;
	exit (8);
}


int main(int argc, char *argv[]) {
	program_name = argv[0];
	if (argc < 3) usage();
	nb_iter = stoi(argv[1]);
	instance_file = argv[2];

	long t = time(NULL);
	srand(t);
	readInstanceFileCordeauLaporteVRPold(instance_file); 
	solutionVRP s;
	cout << "Generating initial VRP solution ..." << flush;
	s.generateInitialSolution();
	cout << "Done.\n" << flush; 
	cout << "Initial solution: " << endl << s.toString() << endl << flush;

	//LSProgramBasic<solutionVRP> p(&s, nb_iter, 3);
	LSProgramBasicDynamicWeights<solutionVRP> p(&s, nb_iter, 1, 0.01);
	cout << "Running LS program" << endl;
	p.run();
	cout << endl << "Terminated. Best solution found: \n" << s.toString() << endl;
	p.printWeights();	// remove if not DynamicWeights !!
}
