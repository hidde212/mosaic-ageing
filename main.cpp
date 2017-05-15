#include <string>
#include <stdexcept>
#include <iostream>
#include <ctime>
//#include <boost/progress.hpp>
#include <iomanip>
#include <thread>
#include "population.h"

using namespace std;

string getTimeDate(); /// Function to get time and date in string form
void thread_simulation(size_t i, unsigned int rand);

//
// Main program
//
int main(){
    try {
		unsigned int n_threads = thread::hardware_concurrency();
		cout << "available threads: " << n_threads << endl;
		if (n_threads == 0) n_threads = 2;

		unsigned int rand;
		if (seed == 0) {
			static random_device rd{};
			rand = rd();
		} else {
			n_threads = 2;
			rand = seed;
		}
		
		vector<thread> workers;

		for (size_t i = 1; i < n_threads; ++i) {
			workers.push_back(thread(thread_simulation, i, rand));
		}
		
		for (auto&& t : workers) {
			t.join();
		}


    }	

    catch (exception &error) {
        cerr << error.what();
        std::cin.ignore(1024, '\n');
        std::cout << "Press enter to continue...";
        std::cin.get();
        exit(EXIT_FAILURE);
    }

//    std::cin.ignore(1024, '\n');
//    std::cout << "Press enter to continue...";
//    std::cin.get();
	return 0;
};

string getTimeDate() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d_%H-%M",timeinfo);
    std::string str(buffer);

    return ("_"+ str);
}

void thread_simulation(size_t t_no, unsigned int rand) {
	string timeNow = getTimeDate();
	unsigned int seeder = t_no * rand;

	std::ofstream params("parameter" + timeNow + "_" + to_string(t_no) + ".txt");
	std::ofstream means_data("means" + timeNow + "_" + to_string(t_no) + ".csv");


	long starttime = clock();
	randomize(seeder); 

	const int width = 15;
	params << "Parameters: " << endl << "Seed: " << seeder << endl << endl
		<< "Population size: " << popSize << setw(width) << "/// (Initial) generation size " << endl
		<< "Generations: " << maxGens << setw(width) << "/// Maximum amount of generation allowed per simulation" << endl
		<< "Extrinsic death rate: " << extDeathRate << setw(width) << "/// Fraction individuals who die each timestep, extrinsic death" << endl << endl
		<< "Skip: " << skip << setw(width) << "/// To write output data at every $skip generations" << endl
		<< "alpha1: " << alpha1 << setw(width) << "/// Displacement of curve over x-axis; damage1" << endl
		<< "alpha2: " << alpha2 << setw(width) << "/// Displacement of curve over x-axis; damage1" << endl
		<< "beta1: " << beta1 << setw(width) << "/// Steepness of curve; damage1" << endl
		<< "beta2: " << beta2 << setw(width) << "/// Steepness of curve; damage1" << endl << endl;

	for (size_t i = 0; i < genesNo; ++i) {
		params << "Gene  " << i << ":" << endl << "Mean: " << genesMean[i] << endl << "Stddev: " << genesStdDev[i]
			<< endl << "Mutation rate: " << mutRates[i] << endl << "Mutation Stddev: " << mutStdDevs[i] << endl << endl;
	}

	means_data << "Seed: ," << seeder << endl;
	means_data << "generation," << "g1mean," << "g1stddev," << "g2mean," << "g2stddev," << "g3mean," << "g3stddev,"
		<< "g4mean," << "g4stddev," << "d1mean," << "d1stddev," << "d2mean," << "d2stddev,"
		<< "agemean," << "agestddev," << "LRSmean," << "LRSstddev" << endl;


	Population pop;
	int time = 0;
	//boost::progress_display show_progress(maxGens);
	pop.init();
	while (time < maxGens) {
		pop.advance();

		if (!(time % skip)) {
			pop.calcMeanStdDev();
			pop.writeMeanStdDev(means_data, time);
		}
		++time;
		//++show_progress;
	}
	long hours, minutes, seconds, secondsTotal, timeElapsed = (clock() - starttime) / double(CLOCKS_PER_SEC) * 1000;
	secondsTotal = timeElapsed / 1000;
	minutes = secondsTotal / 60;
	seconds = secondsTotal % 60;
	hours = minutes / 60;
	minutes = minutes % 60;
	params << endl << "Simulation time: " << hours << "h" << minutes << "m" << seconds << "s" << endl;
}