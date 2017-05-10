#ifndef MOSAIC_AGEING_GLOBALS_H
#define MOSAIC_AGEING_GLOBALS_H

#include <array>
#include <ctime>
#include <iostream>

///Global variables
const unsigned popSize = 5000;			/// (Initial) generation size
const double intDeathRate = 0.5;	    /// Chance to die (lower is higher survivability); intrinsic death rate.
const double extDeathRate = 0.01;	    /// Fraction individuals who die each timestep, extrinsic death
const int maxGens = 50000;				/// Maximum amount of generation allowed per simulation
const int seed = 0;                     /// Seed.
const double f_c = 4.0;					/// Determining steepness of fecundity curve
const int skip = 250;                   /// To write output data at every $skip generations

const unsigned genesNo = 4;	            /// amount of genes
const unsigned traitsNo = 2;            /// amount of traits
const unsigned dataMeansNo = 8;	        /// amount of data of which the mean and stddev is collected (genes x4, damage x2, age, LRS)

///Parameters for mortality curves
const double alpha1 = 10.0;             /// Displacement of curve over x-axis; damage1
const double alpha2 = 10.0;             /// Displacement of curve over x-axis; damage2
const double beta1 = 4.0;              /// Steepness of curve; damage1
const double beta2 = 4.0;              /// Steepness of curve; damage2

///
///Parameters for setting Genes from normal distribution (genes vary from -inf to +inf)
///
const double gene1_Mean = 0.0;  		/// Mean of norm. dist. of gene 1
const double gene2_Mean	= 0.0;		    /// Mean of norm. dist. of gene 2
const double gene3_Mean	= 0.0;		    /// Mean of norm. dist. of gene 3
const double gene4_Mean	= 0.0;		    /// Mean of norm. dist. of gene 4

const double gene1_StdDev = 0.01;   	/// Standard Deviation of norm. dist. of gene 1 (higher than 0.0)
const double gene2_StdDev = 0.01;	    /// Standard Deviation of norm. dist. of gene 2 (higher than 0.0)
const double gene3_StdDev = 0.01;	    /// Standard Deviation of norm. dist. of gene 3 (higher than 0.0)
const double gene4_StdDev = 0.01;	    /// Standard Deviation of norm. dist. of gene 4 (higher than 0.0)

///
///Mutation paraers; (0.01 = 1% of population has chance on mutation)
///
const double mutationRate1 = 0.01;     /// Rate of mutation for gene 1
const double mutationRate2 = 0.01;     /// Rate of mutation for gene 2
const double mutationRate3 = 0.01;     /// Rate of mutation for gene 3
const double mutationRate4 = 0.01;     /// Rate of mutation for gene 4

const double mutationStddev1 = 0.5;    /// Standard deviation for mutation in gene 1
const double mutationStddev2 = 0.5;    /// Standard deviation for mutation in gene 2
const double mutationStddev3 = 0.5;    /// Standard deviation for mutation in gene 3
const double mutationStddev4 = 0.5;    /// Standard deviation for mutation in gene 4



const std::array<double, genesNo> genesMean = { { gene1_Mean, gene2_Mean, gene3_Mean, gene4_Mean } };
const std::array<double, genesNo> genesStdDev = { { gene1_StdDev, gene2_StdDev, gene3_StdDev, gene4_StdDev } };
const std::array<double, genesNo> mutRates = { { mutationRate1, mutationRate2, mutationRate3, mutationRate4 } };
const std::array<double, genesNo> mutStdDevs = { { mutationStddev1, mutationStddev2, mutationStddev3, mutationStddev4 } };

//void end_timer (long& startTime);
//inline void end_timer (long &startTime) { std::cout << "time: " << (clock()-startTime)/double(CLOCKS_PER_SEC)*1000 << std::endl; };

#endif //MOSAIC_AGEING_GLOBALS_H
