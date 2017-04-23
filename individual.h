
#ifndef MOSAIC_AGEING_INDIVIDUAL_H
#define MOSAIC_AGEING_INDIVIDUAL_H

#include <array>
#include "globals.h"
#include "randomnumbers.h"

using genome = std::array<double, genesAmount>;
using traits = std::array<double, traitsAmount>;

// Individual class, including array of genes and array of traits 
class Individual {
	int age = 0;							// Current age of individual
	bool alive = true;						// Whether alive or not.
	int deathCause;							// Indication of death by which trait (1, 2) or extr. factors (0)
	double lifetimeRS = 0.0;				// Lifetime Reproductive Success; measure for fitness.
	//double repairRes;						// (Relative) amount of repair resources (max. = 1.0)
	genome genes;							// Array of genes
	traits traitDamages = { 0.01,0.01 };	// Array of all traits' damage

public:
	Individual() : genes(setGenes()) {}		// Default constructor setting genes from norm. dist.
	Individual(const genome &parentGenes) : genes(parentGenes) {} // Constructor with genes of parent
	~Individual() = default;				// Destructor

	// Update and set functions:
	void mutate();							// Mutate with parameters given
	bool kill();							// Determine if individual is killed and return this
	
	genome setGenes();						// 

	// Get functions:
	genome getGenome() const { return genes; };			// Return values of genes 1/2/3/4
	traits getDamages() const { return traitDamages; };	// Return trait damage values (array of two)
	int getAge() const { return age; };					// Return age
	double getLRS() const { return lifetimeRS; };		// Return lifetime reproductive success
	int getDeathcause() const { return deathCause; };	// Return cause of death



};

inline genome Individual::setGenes() {
	genome genetemp;
	for (size_t i = 0; i < genes.size(); ++i) {
		genetemp[i] = normal(genesMean[i], genesStdDev[i]);
	}
	return genetemp;
};

inline void Individual::mutate() {
	for (size_t i = 0; i < genes.size(); ++i) {
		if (ru() < mutRates[i]) {
			genes[i] += normal(0, mutStdDevs[i]);
		}
	}
}

//Kill individual when ru() < damage (thus when damage > 1 always dead)
inline bool Individual::kill() {
	if (ru() < extDeathRate) {
		alive = false;
		deathCause = 0;
	}
	else if (ru() < traitDamages[0]) {
		alive = false;
		deathCause = 1;
	}
	else if (ru() < traitDamages[1]) {
		alive = false;
		deathCause = 2;
	}
	return alive;
};



#endif //MOSAIC_AGEING_INDIVIDUAL_H