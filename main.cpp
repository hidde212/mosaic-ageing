#include <string>
//#include <fstream>
#include <stdexcept>
#include <iostream>
//#include <limits>
//#include <ctime>
//#include <array>
#include <boost/progress.hpp>
#include "globals.h"
#include "randomnumbers.h"
//#include "individual.h"
#include "population.h"

using namespace std;


// Function to read from parameter file.
void readParameters(const std::string &parFilename = "nofile");

//
// Main program
//
int main(int argc, char* argv[]){
    try {
        argc > 1 ? readParameters(argv[1]) : readParameters();
        randomize(); // To be called AFTER reading parameters; when seed = 0 (default), a new random seed is set.

		std::ofstream means_data("means.csv");
        means_data << "generation,"  << "g1mean," << "g1stddev," << "g2mean," << "g2stddev," << "g3mean," << "g3stddev,"
                   << "g4mean," << "g4stddev," << "d1mean," << "d2stddev," << "d2mean," << "d2stddev,"
                   << "agemean," << "agestddev," << "LRSmean," << "LRSstddev" << endl;


		Population pop;
        int time = 0;
		boost::progress_display show_progress(maxGens);
        pop.init();
        while (time < maxGens) {
            pop.advance();
            pop.calcMeanStdDev();

            if(!(time % skip)) {
                pop.writeMeanStdDev(means_data, time);
            }
            ++time;
			++show_progress;
        }
    }	

    catch (exception &error) {
        cerr << error.what();
        exit(EXIT_FAILURE);
    }

	//system("pause");
	return 0;
};


//
// Function definitions
//

void readParameters(const std::string &parFileName /*= "nofile"*/){
    if (parFileName != "nofile") {
        ifstream ifs(parFileName.c_str());
        if (!ifs.is_open()) {
            throw runtime_error("Unable to open parameter file...");
        }

        clog << "Reading parameters from " << parFileName << "\n";

        while (ifs.is_open()) {
            string parId;
            ifs >> parId;
            if (ifs.good()) {
                if (parId == "Seed") {
                    ifs >> seed;
                } else if (parId == "Population_Size") {
                    ifs >> popSize;
                } else if (parId == "Intrinsic_Death_Rate") {
                    ifs >> intDeathRate;
                } else if (parId == "Extrinsic_Death_Rate") {
                    ifs >> extDeathRate;
                } else if (parId == "Maximum_Offspring") {
                    ifs >> maxOffspring;
                } else if (parId == "Maximum_Generations") {
                    ifs >> maxGens;
				} else if (parId == "Seed") {
					ifs >> seed;
				} else if (parId == "Alpha") {
					ifs >> alpha;
				} else if (parId == "Beta") {
					ifs >> beta;
				} else if (parId == "Fec_Steepness") {
					ifs >> f_c;
                } else if (parId == "Skip") {
                    ifs >> skip;
				} else if (parId == "Gene1_Mean") {
					ifs >> genesMean[0];
				} else if (parId == "Gene2_Mean") {
					ifs >> genesMean[1];
				} else if (parId == "Gene3_Mean") {
					ifs >> genesMean[2];
				} else if (parId == "Gene4_Mean") {
					ifs >> genesMean[3];
				} else if (parId == "Gene1_StdDev") {
					ifs >> genesStdDev[0];
				} else if (parId == "Gene2_StdDev") {
					ifs >> genesStdDev[1];
				} else if (parId == "Gene3_StdDev") {
					ifs >> genesStdDev[2];
				} else if (parId == "Gene4_StdDev") {
					ifs >> genesStdDev[3];
                } else if (parId == "Mutation_Rate1") {
                    ifs >> mutRates[0];
                } else if (parId == "Mutation_Rate2") {
                    ifs >> mutRates[1];
                } else if (parId == "Mutation_Rate3") {
                    ifs >> mutRates[2];
                } else if (parId == "Mutation_Rate4") {
                    ifs >> mutRates[3];
                } else if (parId == "Mutation_StdDev1") {
                    ifs >> mutStdDevs[0];
                } else if (parId == "Mutation_StdDev2") {
                    ifs >> mutStdDevs[1];
                } else if (parId == "Mutation_StdDev3") {
                    ifs >> mutStdDevs[2];
                } else if (parId == "Mutation_StdDev4") {
                    ifs >> mutStdDevs[3];
                } else if (!parId.find("//")) {
                    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
					throw logic_error("Unknown parameter in parameter file...");
                }
            } else break;
        }
		for (size_t i = 0; i < genesStdDev.size(); ++i) {
			if (genesStdDev[i] == 0.0) throw logic_error("Genes standard deviation parameter cannot be 0.0 ...");
			if (mutStdDevs[i] == 0.0) throw logic_error("Mutation standard deviation parameter cannot be 0.0 ...");
		}
    } else {
        for (size_t i = 0; i < mutRates.size(); ++i) {
			genesStdDev[i] = 0.0001;
            mutRates[i] = 0.01;
            mutStdDevs[i] = 0.5;
        }
    }
	cout << "Parameters: " << endl << "Seed: " << seed << endl << endl << "Population size: " << popSize << endl
         << "Intrinsic death rate: " << intDeathRate << "   (not used in 1.0)" <<  endl << "Extrinsic death rate: " << extDeathRate << endl
         << "Maximum offspring per ind.: " << maxOffspring << endl << "Maximum amount of generations: " << maxGens
         << endl << "Skip: " << skip << endl << endl;

    for (size_t i = 0; i < genesAmount; ++i) {
        cout << "Gene  "<< i << ":" << endl << "Mean: " << genesMean[i] << endl << "Stddev: " << genesStdDev[i]
             << endl << "Mutation rate : " << mutRates[i] << endl << "Mutation Stddev :" << mutStdDevs[i] << endl << endl;
    }
};