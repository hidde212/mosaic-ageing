#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <limits>
#include "globals.h"
#include "randomnumbers.h"

using namespace std;

void readParameters(const std::string &parFilename = "nofile");

int main(int argc, char* argv[]){
    try {
        randomize();
        argc > 1 ? readParameters(argv[1]) : readParameters();
        cout << popSize << endl << intDeathRate << endl << extDeathRate << endl << endl << mutRate << endl
             << mutRateGen1
             << endl << mutRateGen2 << endl << endl << mutStdDev << endl << mutStdDevGen1 << mutStdDevGen2 << endl;
    }

    catch (std::exception &error) {
        std::cerr << error.what();
        exit(EXIT_FAILURE);
    }
};



void readParameters(const std::string &parFileName /*= "nofile"*/){

    std::ifstream ifs(parFileName.c_str());
    if(!ifs.is_open()){
        throw std::runtime_error("Unable to open parameter file...");
    }

    std::clog << "Reading parameters from " << parFileName << "\n";

    while(ifs.is_open()){
        std::string parId;
        ifs >> parId;
        if(ifs.good()) {
            if (parId == "Seed") {
                ifs >> seed;
            } else if (parId == "Population_Size") {
                ifs >> popSize;
            } else if (parId == "Intrinsic_Death_Rate") {
                ifs >> intDeathRate;
            } else if (parId == "Extrinsic_Death_Rate") {
                ifs >> extDeathRate;
            } else if (parId == "Maximum_Offspring") {
                ifs >> maxOffspring;
            } else if (parId == "Maximum_Generations") {
                ifs >> maxGens;
            } else if (parId == "Mutation_Rate") {
                ifs >> mutRate;
            } else if (parId == "Mutation_Rate1") {
                ifs >> mutRateGen1;
            } else if (parId == "Mutation_Rate2") {
                ifs >> mutRateGen2;
            } else if (parId == "Mutation_Rate3") {
                ifs >> mutRateGen3;
            } else if (parId == "Mutation_Rate4") {
                ifs >> mutRateGen4;
            } else if (parId == "Mutation_StdDev") {
                ifs >> mutStdDev;
            } else if (parId == "Mutation_StdDev") {
                ifs >> mutStdDevGen1;
            } else if (parId == "Mutation_StdDev") {
                ifs >> mutStdDevGen2;
            } else if (parId == "Mutation_StdDev") {
                ifs >> mutStdDevGen3;
            } else if (parId == "Mutation_StdDev") {
                ifs >> mutStdDevGen4;
            } else if (!parId.find("//")) {
                ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                throw std::logic_error("Unknown parameter in parameter file...");
            }
        }
        else break;
    }
};