#include "globals.h"

//Global variables
unsigned long popSize = 15000;	    // (Initial) generation size
double intDeathRate = 0.5;		    // Chance to die (lower is higher survivability); intrinsic death rate.
double extDeathRate = 0.01;		    // Fraction individuals who die each timestep, extrinsic death
int maxGens = 5000;				    // Maximum amount of generation allowed per simulation
double maxOffspring = 3.0;          // Max number of offspring allowed per individual
int seed = 0;                       // Seed.
double alfa = 0.4;						// Conversion rate for dependency resources invested in offspring <-> actual offspring
//double beta1 = 2.0;			        	// Factor (steepness) in Gompertz's law of mortality for damage of trait 1
//double beta2 = 2.0;               		// Factor (steepness) in Gompertz's law of mortality for damage of trait 2
//double rho1 = 5.0;                      // Factor (y-axis intersect) in Gompertz's law of mortality for damage of trait 1
//double rho2 = 15.0;                     // Factor (y-axis intersect) in Gompertz's law of mortality for damage of trait 2
//double phi = 0.33;                      // Steepness of linear mortality curve
//double baseDamage = 0.1;                // Standard amount of damage added per timestep before allocation of repair/offspring resources
//
//double gen1Mean = 0.5;					// Mean for constructing gene 1 from normal distribution
//double gen1StdDev = 0.05;				// Standard deviation for constructing genotype 1 from normal distribution
//double gen2Mean = 0.0;					// Mean for constructing gene 2 from normal distribution
//double gen2StdDev = 0.1;				// Standard deviation for constructing genotype 2 from normal distribution
//double gen3Mean = 0.0;					// Mean for constructing gene 3 from normal distribution
//double gen3StdDev = 0.1;				// Standard deviation for constructing genotype 3 from normal distribution
//

double mutRate = 0.01;              // Rate of mutation (0.01 = 1% of population has chance on mutation)
double mutRateGen1 = mutRate;       // Rate of mutation for gen 1
double mutRateGen2 = mutRate;       // Rate of mutation for gen 2
double mutRateGen3 = mutRate;       // Rate of mutation for gen 3
double mutRateGen4 = mutRate;       // Rate of mutation for gen 4

double mutStdDev = 0.5;             // Standard deviation for mutation
double mutStdDevGen1 = mutStdDev;   // Standard deviation for mutation in gen 1
double mutStdDevGen2 = mutStdDev;   // Standard deviation for mutation in gen 2
double mutStdDevGen3 = mutStdDev;   // Standard deviation for mutation in gen 3
double mutStdDevGen4 = mutStdDev;   // Standard deviation for mutation in gen 4