#ifndef MOSAIC_AGEING_GLOBALS_H
#define MOSAIC_AGEING_GLOBALS_H

#include <array>
#include <ctime>
#include <iostream>


//Global variables
extern unsigned popSize;		/// (Initial) generation size
extern double intDeathRate;		/// Chance to die (lower is higher survivability); intrinsic death rate.
extern double extDeathRate;		/// Fraction individuals who die each timestep, extrinsic death
extern int maxGens;				/// Maximum amount of generation allowed per simulation
extern double maxOffspring;		/// Max nr. of offspring allowed per indvidual
extern int seed;				/// Seed.
extern double alpha;			/// variable determining how much impact the total state (damage) has on offspring/repair resources
extern double beta;				/// variable determining how much impact the damage ratio has on repair allocation
extern double f_c;				/// Determining steepness of fecundity curve
extern int skip;                /// To write output data at every $skip generations

const unsigned genesAmount = 4;	/// amount of genes
const unsigned traitsAmount = 2;/// amount of traits
const unsigned dataMeansAmount = 8;	/// amount of data of which the mean and stddev is collected (genes x4, damage x2, age, LRS)


extern std::array<double, genesAmount> genesMean;
extern std::array<double, genesAmount> genesStdDev;
extern std::array<double, genesAmount> mutRates;
extern std::array<double, genesAmount> mutStdDevs;

//void end_timer (long& startTime);
inline void end_timer (long &startTime) { std::cout << "time: " << (clock()-startTime)/double(CLOCKS_PER_SEC)*1000 << std::endl; };

#endif //MOSAIC_AGEING_GLOBALS_H
