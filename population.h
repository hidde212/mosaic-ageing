
#ifndef MOSAIC_AGEING_POPULATION_H
#define MOSAIC_AGEING_POPULATION_H

#include <vector>
#include "globals.h"
#include "individual.h"

class Population {
	std::vector<Individual> cohort;
public:
	Population() : cohort(popSize, Individual()) {};
	~Population() = default;



};

#endif //MOSAIC_AGEING_POPULATION_H