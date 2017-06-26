#ifndef MOSAIC_AGEING_GLOBALS_H
#define MOSAIC_AGEING_GLOBALS_H

#include <array>
#include <ctime>
#include <iostream>

///Global variables
const unsigned popSize = 5000;			/// (Initial) generation size
const double extDeathRate = 0.1;	    /// Fraction individuals who die each timestep, extrinsic death
const int maxGens = 75000;				/// Maximum amount of generation allowed per simulation
const int seed = 0;                     /// Seed. When 0, random seed is created.
const double f_c = 2.0;					/// Determining steepness of fecundity curve
const int skip = 250;                   /// To write output data at every $skip generations
///const double baseDam = 0.02;            /// Standard damage per timestep

const unsigned genesNo = 4;	            /// amount of genes
const unsigned traitsNo = 2;            /// amount of traits
const unsigned dataMeansNo = 8;	        /// amount of data of which the mean and stddev is collected (genes x4, damage x2, age, LRS)

///Parameters for mortality curves
const double alpha1 = 4.0;             /// Displacement of curve over x-axis; damage1
const double alpha2 = 4.0;             /// Displacement of curve over x-axis; damage2
const double beta1 = 4.0;               /// Steepness of curve; damage1
const double beta2 = 4.0;               /// Steepness of curve; damage2
const double gamma1 = 0.2;              /// 'Multiplier' of the amount of damage added
const double gamma2 = 0.2;              /// 'Multiplier' of the amount of damage added
const double rho1 = 0.5;                /// Parameter for efficiency of damage prevention to trait 1
const double rho2 = 0.5;                /// Parameter for efficiency of damage prevention to trait 2

///
///Parameters for setting Genes from normal distribution (genes vary from -inf to +inf)
///
const double gene1_Mean = 0.0;  		/// Mean of norm. dist. of gene 1
const double gene2_Mean	= 0.0;		    /// Mean of norm. dist. of gene 2
const double gene3_Mean	= 0.0;		    /// Mean of norm. dist. of gene 3
const double gene4_Mean	= 0.0;		    /// Mean of norm. dist. of gene 4

const double gene1_StdDev = 1.00;   	/// Standard Deviation of norm. dist. of gene 1 (higher than 0.0)
const double gene2_StdDev = 1.00;	    /// Standard Deviation of norm. dist. of gene 2 (higher than 0.0)
const double gene3_StdDev = 1.00;	    /// Standard Deviation of norm. dist. of gene 3 (higher than 0.0)
const double gene4_StdDev = 1.00;	    /// Standard Deviation of norm. dist. of gene 4 (higher than 0.0)

///
///Mutation paraers; (0.01 = 1% of population has chance on mutation)
///
const double mutationRate1 = 0.01;     /// Rate of mutation for gene 1
const double mutationRate2 = 0.01;     /// Rate of mutation for gene 2
const double mutationRate3 = 0.01;     /// Rate of mutation for gene 3
const double mutationRate4 = 0.01;     /// Rate of mutation for gene 4

const double mutationStddev1 = 0.1;    /// Standard deviation for mutation in gene 1
const double mutationStddev2 = 0.1;    /// Standard deviation for mutation in gene 2
const double mutationStddev3 = 0.1;    /// Standard deviation for mutation in gene 3
const double mutationStddev4 = 0.1;    /// Standard deviation for mutation in gene 4

const std::array<double, genesNo> genesMean = { { gene1_Mean, gene2_Mean, gene3_Mean, gene4_Mean } };
const std::array<double, genesNo> genesStdDev = { { gene1_StdDev, gene2_StdDev, gene3_StdDev, gene4_StdDev } };
const std::array<double, genesNo> mutRates = { { mutationRate1, mutationRate2, mutationRate3, mutationRate4 } };
const std::array<double, genesNo> mutStdDevs = { { mutationStddev1, mutationStddev2, mutationStddev3, mutationStddev4 } };

//inline void end_timer (long &startTime, std::ofstream &data) { data << std::endl << "Simulation time: " << (clock()-starttime)/double(CLOCKS_PER_SEC)*1000 << std::endl; };

#endif //MOSAIC_AGEING_GLOBALS_H
