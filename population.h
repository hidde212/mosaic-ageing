
#ifndef MOSAIC_AGEING_POPULATION_H
#define MOSAIC_AGEING_POPULATION_H

#include <vector>
#include <fstream>
#include <stdexcept>
#include "individual.h"


// Class containing vector of Individual class and functions acting on this
class Population {
	std::vector<Individual> cohort;             // Vector of individuals
	std::array<double, dataMeansNo> means;  // Array of means as calculated from all individuals
	std::array<double, dataMeansNo> stdDevs;// Array of standard deviations as calculated from all individuals

public:
	//Set functions
    void init();
	void advance();					// Calculate fecundity and damage and increase the latter ((parallel))
									// Also kill, reproduce and mutate individuals
	void reproduceFromAll();		// Take new generation from all individuals (offspring before death)
	void reproduceFromAlive();		// Take new generation from alive individuals

	void calcMeanStdDev();			// Calculate means and stddev of genes, damage, age and LRS.
	void writeMeanStdDev(std::ofstream &data, int &generation);		// Write data
    void writeFinalPop(std::ofstream &data);
    void runFinalCohort(std::ofstream &data);
};

// Initialise population with Individuals
inline void Population::init() {
    for (size_t i = 0; i < popSize; ++i) {
        Individual ind;
        cohort.push_back(ind);
    }
}


// Calculate fecundity and damage and increase the latter ((parallel))
// Also kill, reproduce and mutate individuals
inline void Population::advance() {
	for (auto &ind : cohort) {
		ind.calcResources();
		ind.kill();
	}

	reproduceFromAlive();
//	reproduceFromAll();

//	for (auto& ind : cohort) if (ind.getAge() == 0) ind.mutate();
//	    for (auto& ind : cohort) ind.mutate();


};

#endif //MOSAIC_AGEING_POPULATION_H

