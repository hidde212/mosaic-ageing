#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <limits>
#include "globals.h"
#include "randomnumbers.h"
#include "individual.h"

using namespace std;

//
// Function declarations
//
void readParameters(const std::string &parFilename = "nofile");
vector<individual> createCohort();
void checkCohort();
vector<individual> simulate(vector<individual> &vCohort);

//
// Main program
//

int main(int argc, char* argv[]){
    try {
        argc > 1 ? readParameters(argv[1]) : readParameters();
        randomize();
        cout << popSize << endl << intDeathRate << endl << extDeathRate << endl << endl << mutRate << endl
             << mutRateGene1 << endl << mutRateGene2 << endl << endl << mutStdDev << endl << mutStdDevGene1 << endl
             << mutStdDevGene2 << endl;

        checkCohort();
    }

    catch (std::exception &error) {
        std::cerr << error.what();
        exit(EXIT_FAILURE);
    }
};


//
// Function definitions
//
vector<individual> createCohort(){
    vector<individual> vCohort(popSize);
    for(size_t i = 0; i < vCohort.size(); ++i) {
        individual Individual;
        Individual.setGene1();
        Individual.setGene2();
        Individual.setGene3();
        Individual.setGene4();
        vCohort[i] = Individual;
    }
    return vCohort;
};

void checkCohort() {
    ofstream checkValues("data.csv");
    checkValues << "gene1," << "gene2," << "gene3," << "gene4" << endl;
    vector<individual> vCohort = createCohort();
    for(size_t i = 0; i < vCohort.size(); ++i){
        checkValues << vCohort[i].getGene1() << "," << vCohort[i].getGene2() << "," << vCohort[i].getGene3() << ","
                    << vCohort[i].getGene4() << "," << endl;
    }
};

void reproduce(vector<individual> &vGeneration, const double &alfa, const double &beta) {
	// Reproduce all individuals, then replace dead individuals with newborns

	vector<double> offspring(popSize);
	vector<int> deadIndividuals;

#pragma omp parallel for schedule(dynamic)
	for (size_t i = 0; i < vGeneration.size(); ++i) {	// Determine number of offspring for each individual
		double offspringResources = vGeneration[i].getOffspringResources();
		double dOffspring = (maxOffspring * tmp) / (alfa + tmp);
		if (dOffspring == 0)
			dOffspring = 0.0001;
		offspring[i] = dOffspring;
	}

	for (size_t i = 0; i < generation.size(); ++i) {	// Find dead sheep in generation, and store their position in the vector
		if (!generation[i].isAlive())
			deadSheep.push_back(i);
	}

	for (size_t j = 0; j < deadSheep.size(); ++j) {
		int parent = rindex(offspring);					// Pick parent using weighted lottery

		sheep Sheep;									// Create offspring, and give same gen1 and gen2 as parent..
		Sheep.setGen1(generation[parent].getGen1());
		Sheep.setGen2(generation[parent].getGen2());
		Sheep.setGen3(generation[parent].getGen3());
		Sheep.mutateGen1();							// .. and mutate possibly
		Sheep.mutateGen2();
		Sheep.mutateGen3();

		generation[deadSheep[j]] = Sheep;				// Replace dead sheep with their offspring
	}
}

vector<individual> simulate(vector<individual> &vCohort) {
	for (size_t i = 0; i < maxGens; ++i) {
#pragma omp parallel for ordered schedule(static,1)



	}

}; 





void readParameters(const std::string &parFileName /*= "nofile"*/){
    if (parFileName != "nofile") {
        std::ifstream ifs(parFileName.c_str());
        if (!ifs.is_open()) {
            throw std::runtime_error("Unable to open parameter file...");
        }

        std::clog << "Reading parameters from " << parFileName << "\n";

        while (ifs.is_open()) {
            std::string parId;
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
                } else if (parId == "Alfa") {
					ifs >> alfa;
				} else if (parId == "Gene_Mean") {
					ifs >> genMean;
				} else if (parId == "Gene1_Mean") {
					ifs >> gen1Mean;
				} else if (parId == "Gene2_Mean") {
					ifs >> gen2Mean;
				} else if (parId == "Gene3_Mean") {
					ifs >> gen3Mean;
				} else if (parId == "Gene4_Mean") {
					ifs >> gen4Mean;
				} else if (parId == "Gene_StdDev") {
					ifs >> genStdDev;
				} else if (parId == "Gene1_StdDev") {
					ifs >> gen1StdDev;
				} else if (parId == "Gene2_StdDev") {
					ifs >> gen2StdDev;
				} else if (parId == "Gene3_StdDev") {
					ifs >> gen3StdDev;
				} else if (parId == "Gene4_StdDev") {
					ifs >> gen4StdDev;
                } else if (parId == "Mutation_Rate") {
                    ifs >> mutRate;
                } else if (parId == "Mutation_Rate1") {
                    ifs >> mutRateGene1;
                } else if (parId == "Mutation_Rate2") {
                    ifs >> mutRateGene2;
                } else if (parId == "Mutation_Rate3") {
                    ifs >> mutRateGene3;
                } else if (parId == "Mutation_Rate4") {
                    ifs >> mutRateGene4;
                } else if (parId == "Mutation_StdDev") {
                    ifs >> mutStdDev;
                } else if (parId == "Mutation_StdDev") {
                    ifs >> mutStdDevGene1;
                } else if (parId == "Mutation_StdDev") {
                    ifs >> mutStdDevGene2;
                } else if (parId == "Mutation_StdDev") {
                    ifs >> mutStdDevGene3;
                } else if (parId == "Mutation_StdDev") {
                    ifs >> mutStdDevGene4;
                } else if (!parId.find("//")) {
                    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
					throw std::logic_error("Unknown parameter in parameter file...");
                }
            } else break;
        }
    }
	cout << "Parameters: " << endl << "Seed: " << seed << endl << endl << "Population size: " << popSize << endl
         << "Intrinsic death rate: " << intDeathRate << endl << "Extrinsic death rate: " << extDeathRate << endl
         << "Maximum offspring per ind.: " << maxOffspring << endl << "Maximum amount of generations: " << maxGens
         << endl << endl;
};