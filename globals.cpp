#include "globals.h"

//Global variables
unsigned popSize = 500;			/// (Initial) generation size
double intDeathRate = 0.5;		    /// Chance to die (lower is higher survivability); intrinsic death rate.
double extDeathRate = 0.01;		    /// Fraction individuals who die each timestep, extrinsic death
int maxGens = 1000;				/// Maximum amount of generation allowed per simulation
double maxOffspring = 3.0;          /// Max number of offspring allowed per individual
int seed = 0;                       /// Seed.
double alpha = 1.0;					/// variable determining how much impact the total state (damage) has on offspring/repair resources
double beta = 1.0;					/// variable determining how much impact the damage ratio has on repair allocation
double f_c = 4.0;					/// Determining steepness of fecundity curve
int skip = 50;                      /// To write output data at every $skip generations

std::array<double, genesAmount> genesMean;		/// Mean for constructing all genes from normal distribution
std::array<double, genesAmount> genesStdDev;	/// Standard deviation for constructing all genotypes from normal distribution
std::array<double, genesAmount> mutRates;		/// Rate of mutation (0.01 = 1% of population has chance on mutation)
std::array<double, genesAmount> mutStdDevs;		/// Rate of mutation (0.01 = 1% of population has chance on mutation)
