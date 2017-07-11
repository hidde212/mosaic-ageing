#include <string>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <boost/progress.hpp>
#include <iomanip>
#include "population.h"

using namespace std;

string getTimeDate();														/// Function to get time and date in string form
void writeOutput(ofstream &params, ofstream &means, ofstream &rparams);		/// Function writing output files

//
// Main program
//
int main(){
    try {
		long starttime = clock();
		long actualSeed = randomize(); //when seed = 0 (in globals.h), a new random seed is set.

        string timeNow = getTimeDate();		
		ofstream params("parameter" + timeNow + ".txt");
		ofstream means_data("means" + timeNow + ".csv");
        ofstream final("finalpop" + timeNow + ".csv");
        ofstream lastCohort("last_cohort"+ timeNow + ".csv");
		ofstream paramsR("parameter" + timeNow + ".R");
		params << "Parameters: " << endl << "Seed: " << actualSeed << endl << endl;
		means_data << "Seed: ," << actualSeed << endl;
		paramsR << "seed <- " << actualSeed << endl;
		
		writeOutput(params, means_data, paramsR);
		
		Population pop;
        int time = 0;
		//boost::progress_display show_progress(maxGens);
        pop.init();
        while (time < maxGens) {
            pop.advance();

            if(!(time % skip)) {
                pop.calcMeanStdDev();
                pop.writeMeanStdDev(means_data, time);
            }
            ++time;
			//++show_progress;
        }
        pop.writeFinalPop(final);
        pop.runFinalCohort(lastCohort);
		long hours, minutes, seconds, secondsTotal, timeElapsed = (clock() - starttime) / double(CLOCKS_PER_SEC) * 1000;
		secondsTotal = timeElapsed / 1000;
		minutes = secondsTotal / 60;
		seconds = secondsTotal % 60;
		hours = minutes / 60;
		minutes = minutes % 60;
		params << endl << "Simulation time: " << hours << "h" << minutes << "m" << seconds << "s" << endl;
    }	

    catch (exception &error) {
        cerr << error.what();
        cin.ignore(1024, '\n');
        cout << "Press enter to continue...";
        cin.get();
        exit(EXIT_FAILURE);
    }

    cin.ignore(1024, '\n');
    cout << "Press enter to continue...";
    cin.get();
	return 0;
};

string getTimeDate() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y%m%d_%H-%M-%S",timeinfo);
    string str(buffer);

    return ("_"+ str);
}

void writeOutput(ofstream &params, ofstream &means, ofstream &rparams) {
	const int width = 25;
	params << "Population size: " << popSize << setw(width) << "/// (Initial) generation size " << endl
		<< "Generations: " << maxGens << setw(width) << "/// Maximum amount of generation allowed per simulation" << endl
		<< "Extrinsic death rate: " << extDeathRate << setw(width) << "/// Fraction individuals who die each timestep, extrinsic death" << endl << endl
		<< "Skip: " << skip << setw(width) << "/// To write output data at every $skip generations" << endl
		<< "alpha1: " << alpha1 << setw(width) << "/// Displacement of curve over x-axis; damage trait 1" << endl
		<< "alpha2: " << alpha2 << setw(width) << "/// Displacement of curve over x-axis; damage trait 2" << endl
		<< "beta1: " << beta1 << setw(width) << "/// Steepness of curve; damage trait 1 " << endl
		<< "beta2: " << beta2 << setw(width) << "/// Steepness of curve; damage trait 2" << endl
           << "gamma1: " << gamma1 << setw(width) << "/// Damage prevention multiplier trait 1" << endl
           << "gamma2: " << gamma2 << setw(width) << "/// Damage prevention multiplier trait 2" << endl
           << "rho1: " << rho1 << setw(width) << "/// Parameter for efficiency of damage prevention to trait 1" << endl
           << "rho1: " << rho2 << setw(width) << "/// Parameter for efficiency of damage prevention to trait 2" << endl << endl;

	rparams << "popsize <- " << popSize << endl << "gens <- " << maxGens << endl << "extDeathRate <- " << extDeathRate << endl
            << "alpha1 <- " << alpha1 << endl << "alpha2 <- " << alpha2 << endl << "beta1 <- " << beta1 << endl << "beta2 <- "
            << beta2 << endl << "gamma1 <- " << gamma1 << endl << "gamma2 <- " << gamma2 << endl << "rho1 <- " << rho1
            << endl << "rho2 <- " << rho2 << endl;

	for (size_t i = 0; i < genesNo; ++i) {
		params << "Gene  " << i << ":" << endl << "Mean: " << genesMean[i] << endl << "Stddev: " << genesStdDev[i]
			<< endl << "Mutation rate: " << mutRates[i] << endl << "Mutation Stddev: " << mutStdDevs[i] << endl << endl;
		
		rparams << "gene" << i << "mean <- " << genesMean[i] << endl << "gene" << i << "stddev <- " << genesStdDev[i]
			<< endl << "gene" << i << "mutRate <- " << mutRates[i] << endl << "gene" << i << "mutStddev <- " << mutStdDevs[i] << endl;

	}
	
	means << "generation," << "g1mean," << "g1stddev," << "g2mean," << "g2stddev," << "g3mean," << "g3stddev,"
		<< "g4mean," << "g4stddev," << "d1mean," << "d1stddev," << "d2mean," << "d2stddev,"
		<< "agemean," << "agestddev," << "LRSmean," << "LRSstddev" << endl;

}