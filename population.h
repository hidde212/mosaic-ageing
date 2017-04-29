
#ifndef MOSAIC_AGEING_POPULATION_H
#define MOSAIC_AGEING_POPULATION_H

#include <vector>
#include <array>
#include <fstream>
#include <stdexcept>
#include "globals.h"
#include "individual.h"


// Class containing vector of Individual class and functions acting on this
class Population {
	std::vector<Individual> cohort;
	std::array<double, dataMeansAmount> means;
	std::array<double, dataMeansAmount> stdDevs;

public:
	Population() : cohort(popSize, Individual()) {};
	~Population() = default;

	//Set functions
	void advance();					// Calculate fecundity and damage and increase the latter ((parallel))
									// Also kill, reproduce and mutate individuals
	void reproduceFromAll();		// Take new generation from all individuals (offspring before death)
	void reproduceFromAlive();		// Take new generation from alive individuals

	void calcMeanStdDev();									// Calculate statistics
	void writeMeanStdDev(std::ofstream &meandataofs);		// Write data
};


// Calculate fecundity and damage and increase the latter ((parallel))
// Also kill, reproduce and mutate individuals
inline void Population::advance() {
	for (auto &ind : cohort) {
		ind.calcResources();
		ind.kill();
	}

	reproduceFromAlive();
//	reproduceFromAll();

	for (auto ind : cohort) if (!ind.getAge()) ind.mutate();
//	for (auto ind : cohort) ind.mutate();


};


// Calculate means and stddev of genes, damage, age and LRS. <<WIP!!>>
inline void Population::calcMeanStdDev() {
	for (size_t i = 0; i < means.size(); ++i) means[i] = 0.0;
	std::vector<std::vector<double> > mValues;

	for (auto &ind : cohort) {
		std::vector<double> indData;
		for (size_t i = 0; i < genesAmount; ++i) indData.push_back(ind.getGenome()[i]);
		for (size_t i = 0; i < traitsAmount; ++i) indData.push_back(ind.getDamages()[i]);
		indData.push_back(ind.getAge());
		indData.push_back(ind.getLRS());
		mValues.push_back(indData);
	}

//	double g1_tot = g2_tot = g3_tot = g4_tot = d1_tot = d2_tot = age_tot = lrs_tot = 0.0;
#pragma omp parallel for
    for(size_t i = 0; i < mValues[0].size(); ++i) {
		double total = mean = varTotal = 0.0;
		for (auto& value : mValues[i]) total += value;
		mean = total / mValues[i].size();
		for (auto& value : mValues[i]) varTotal += pow((dev - mean), 2.0);
		stdDevs[i] = sqrt(varTotal / mValues[i].size());


	}


};

//Write means <<WIP>>
inline void Population::writeMeanStdDev(std::ofstream &meandataofs) {
	if (!meandataofs.is_open()) {
		throw std::runtime_error("Unable to open means datafile...");
	}
	meandataofs << "generation," << "gene1," << "gene2," << "gene3," << "gene4," << "dam1," << "dam2," << "age," << "lrs," << std::endl;

	meandataofs << 1;
	for (size_t i = 0; i < means.size(); ++i) meandataofs << "," << means[i];
	meandataofs << std::endl;
};





#endif //MOSAIC_AGEING_POPULATION_H

