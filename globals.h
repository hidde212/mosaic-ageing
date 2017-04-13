#ifndef MOSAIC_AGEING_GLOBALS_H
#define MOSAIC_AGEING_GLOBALS_H

//Global variables
extern unsigned long popSize;	// (Initial) generation size
extern double intDeathRate;		// Chance to die (lower is higher survivability); intrinsic death rate.
extern double extDeathRate;		// Fraction individuals who die each timestep, extrinsic death
extern int maxGens;				// Maximum amount of generation allowed per simulation
extern double maxOffspring;		// Max nr. of offspring allowed per indvidual
extern int seed;				// Seed.
extern double alfa;					// Dependency resources invested in offspring <-> actual offspring
//extern double beta1;				// Factor (steepness) in Gompertz's law of mortality for damage of trait 1
//extern double beta2;				// Factor (steepness) in Gompertz's law of mortality for damage of trait 2
//extern double rho1;                 // Factor (y-axis intersect) in Gompertz's law of mortality for damage of trait 1
//extern double rho2;                 // Factor (y-axis intersect) in Gompertz's law of mortality for damage of trait 2
//extern double phi;                  // Factor in linear mortality curve - not used
//extern double baseDamage;           // Standard amount of damage added per timestep before allocation of repair/offspring resources
//
//

extern double genMean;			// Mean for constructing all genes from normal distribution
extern double genStdDev;		// Standard deviation for constructing all genotypes from normal distribution

extern double gen1Mean;			// Mean for constructing genotype 1 from normal distribution
extern double gen1StdDev;		// Standard deviation for constructing genotype 1 from normal distribution
extern double gen2Mean;			// Mean for constructing genotype 2 from normal distribution
extern double gen2StdDev;		// Standard deviation for constructing genotype 2 from normal distribution
extern double gen3Mean;         // Mean for constructing genotype 3 from normal distribution
extern double gen3StdDev;       // Standard deviation for constructing genotype 3 from normal distribution
extern double gen4Mean;         // Mean for constructing genotype 4 from normal distribution
extern double gen4StdDev;       // Standard deviation for constructing genotype 4 from normal distribution

extern double mutRate;          // Rate of mutation (0.01 = 1% of population has chance on mutation)
extern double mutRateGen1;      // Rate of mutation for gen 1
extern double mutRateGen2;      // Rate of mutation for gen 2
extern double mutRateGen3;      // Rate of mutation for gen 3
extern double mutRateGen4;      // Rate of mutation for gen 4

extern double mutStdDev;        // Standard deviation for mutation
extern double mutStdDevGen1;    // Standard deviation for mutation in gen 1
extern double mutStdDevGen2;    // Standard deviation for mutation in gen 2
extern double mutStdDevGen3;    // Standard deviation for mutation in gen 3
extern double mutStdDevGen4;    // Standard deviation for mutation in gen 4

#endif //MOSAIC_AGEING_GLOBALS_H
