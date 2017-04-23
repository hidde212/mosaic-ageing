#ifndef MOSAIC_AGEING_GLOBALS_H
#define MOSAIC_AGEING_GLOBALS_H

#include <array>

//Global variables
extern unsigned popSize;	// (Initial) generation size
extern double intDeathRate;		// Chance to die (lower is higher survivability); intrinsic death rate.
extern double extDeathRate;		// Fraction individuals who die each timestep, extrinsic death
extern int maxGens;				// Maximum amount of generation allowed per simulation
extern double maxOffspring;		// Max nr. of offspring allowed per indvidual
extern int seed;				// Seed.
extern double alfa;				// variable determining how much impact the total state (damage) has on offspring/repair resources
extern double beta;				// variable determining how much impact the damage ratio has on repair allocation
const unsigned genesAmount = 4;	// amount of genes
const unsigned traitsAmount = 2;// amount of traits


extern std::array<double, genesAmount> genesMean;
extern std::array<double, genesAmount> genesStdDev;
extern std::array<double, genesAmount> mutRates;
extern std::array<double, genesAmount> mutStdDevs;


#endif //MOSAIC_AGEING_GLOBALS_H
