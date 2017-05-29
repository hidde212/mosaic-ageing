
#ifndef MOSAIC_AGEING_INDIVIDUAL_H
#define MOSAIC_AGEING_INDIVIDUAL_H

//#include <array>
//#include "globals.h"
#include "randomnumbers.h"

using genome = std::array<double, genesNo>;
using traits = std::array<double, traitsNo>;

// Individual class, including array of genes and array of traits 
class Individual {
	int age = 0;							// Current age of individual
	bool alive = true;						// Whether alive or not.
	int deathCause = 0;						// Indication of death by which trait (1, 2) or extr. factors (0)
	double lifetimeRS = 0.0;				// Lifetime Reproductive Success; measure for fitness.
	double fecundity = 0.0;					// (Relative) amount of offspring resources (max. = 1.0)
	genome genes;							// Array of genes
	traits damages = {{ 0.01, 0.01 }};		// Array of all traits' damage
	 

public:
	Individual() : genes(setGenes()) {}		// Default constructor setting genes from norm. dist.
	Individual(const genome &parentGenes) : genes(parentGenes) {} // Constructor with genes of parent
	~Individual() = default;				// Destructor

	// Update and set functions:
	void mutate();							// Mutate with parameters given
	bool kill();							// Determine if individual is killed and returns true if alive
	void calcResources();					// Calculate offspring(fecundity) and repair resources, add damage
	genome setGenes();						// Return array of genes with normal(geneMean, geneStdDev)

	// Get functions:
	genome getGenome() const { return genes; };			// Return values of genes 1/2/3/4
	traits getDamages() const { return damages; };		// Return trait damage values (array of two)
	int getAge() const { return age; };					// Return age
	double getFecundity() const { return fecundity; };	// Return fecundity
	double getLRS() const { return lifetimeRS; };		// Return lifetime reproductive success
	bool isAlive() const { return alive; };             // Check if alive
    int getDeathcause() const { return deathCause; };	// Return cause of death



};

//Return array of genes with normal(geneMean, geneStdDev)
inline genome Individual::setGenes() {
	genome genetemp;
	for (size_t i = 0; i < genetemp.size(); ++i) {
		genetemp[i] = normal(genesMean[i], genesStdDev[i]);
	}
	return genetemp;
};

//Mutate genes with norm(0, mutStdDev)
inline void Individual::mutate() {
	for (size_t i = 0; i < genes.size(); ++i) {
		if (ru() < mutRates[i]) {
			genes[i] += normal(0, mutStdDevs[i]);
		}
	}
}

//Kill individual when ru() < exp(-alpha*exp(-beta*damage)); when not killed age increased.
inline bool Individual::kill() {
	if (ru() < extDeathRate) {
		alive = false;
		deathCause = 0;
	}
	else if (ru() < exp(-alpha1 * exp(-beta1 * damages[0]))) {
		alive = false;
		deathCause = 1;
	}
    else if (ru() < exp(-alpha2 * exp(-beta2 * damages[1]))) {
		alive = false;
		deathCause = 2;
	}
	if (alive) ++age;
	return alive;
};

// Calculate offspring(fecundity) and repair resources, add damage
inline void Individual::calcResources() {
    double damTot = damages[0] + damages[1];
	//double offspringAlloc = 1 / (1 + exp(-genes[0] * beta * (1 - (damages[0] + damages[1])) + genes[1])); //OLD
    double offspringAlloc = 1 / (1 + exp(-genes[0] * (damTot - genes[1])));
    fecundity = 1 - exp(-f_c * offspringAlloc);							// Max fecundity not above 1.0
    lifetimeRS += fecundity;

	double repairTrait1 = 1 / (1 + exp(-genes[2] * ((damages[0] - damages[1]) / damTot) + genes[3]));
	damages[0] += baseDam + (gamma1 * offspringAlloc * (1.0 - repairTrait1));   // repair allocation = 1 - offspring; thus "damage allocation" = offspringAlloc
	damages[1] += baseDam + (gamma2 * offspringAlloc * repairTrait1);           // baseDam added
	for (auto& dam : damages) if (dam > 1.0) dam = 1.0;				// Make sure damage is not above 1.0
};



#endif //MOSAIC_AGEING_INDIVIDUAL_H