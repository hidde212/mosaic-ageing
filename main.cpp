#include <string>
#include <stdexcept>
#include <iostream>
#include <boost/progress.hpp>
#include "population.h"

using namespace std;

//
// Main program
//
int main(){
    try {
        long actualSeed = randomize(); //when seed = 0 (in globals.h), a new random seed is set.

        std::ofstream params("pars.txt");

        params << "Parameters: " << endl << "Seed: " << actualSeed << endl << endl << "Population size: " << popSize << endl
               << "Intrinsic death rate: " << intDeathRate << "   (not used in 1.0)" <<  endl << "Extrinsic death rate: "
               << extDeathRate << endl << endl << "Maximum amount of generations: " << maxGens << endl << "Skip: "
               << skip << endl << endl;

        for (size_t i = 0; i < genesNo; ++i) {
            params << "Gene  "<< i << ":" << endl << "Mean: " << genesMean[i] << endl << "Stddev: " << genesStdDev[i]
                 << endl << "Mutation rate : " << mutRates[i] << endl << "Mutation Stddev :" << mutStdDevs[i] << endl << endl;
        }

		std::ofstream means_data("means.csv");
        means_data << "Seed: ," << actualSeed << endl;
        means_data << "generation,"  << "g1mean," << "g1stddev," << "g2mean," << "g2stddev," << "g3mean," << "g3stddev,"
                   << "g4mean," << "g4stddev," << "d1mean," << "d2stddev," << "d2mean," << "d2stddev,"
                   << "agemean," << "agestddev," << "LRSmean," << "LRSstddev" << endl;


		Population pop;
        int time = 0;
		boost::progress_display show_progress(maxGens);
        pop.init();
        while (time < maxGens) {
            pop.advance();

            if(!(time % skip)) {
                pop.calcMeanStdDev();
                pop.writeMeanStdDev(means_data, time);
            }
            ++time;
			++show_progress;
        }
    }	

    catch (exception &error) {
        cerr << error.what();
        std::cin.ignore(1024, '\n');
        std::cout << "Press enter to continue...";
        std::cin.get();
        exit(EXIT_FAILURE);
    }

    std::cin.ignore(1024, '\n');
    std::cout << "Press enter to continue...";
    std::cin.get();
	//system("pause");
	return 0;
};