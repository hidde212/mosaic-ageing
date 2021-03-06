#include "population.h"

// Calculate means and stddev of genes, damage, age and LRS.
void Population::calcMeanStdDev() {
	for (size_t i = 0; i < dataMeansNo; ++i) {
		double ss = 0.0, sum = 0.0;
		if (i < genesNo) {
			for (auto& ind : cohort) {
				double geneval = ind.getGenome()[i];
				sum += geneval;
				ss += geneval * geneval;
			}
		} else if (i < genesNo + traitsNo) {
			for (auto& ind : cohort) {
				double damval = ind.getDamages()[i - genesNo];
				sum += damval;
				ss += damval * damval;
			}
		} else if (i < 7) {
			for (auto& ind : cohort) {
				double age = ind.getAge();
				sum += age;
				ss += age * age;
			}
		} else if (i < dataMeansNo) {
			for (auto& ind : cohort) {
				double lrs = ind.getLRS();
				sum += lrs;
				ss += lrs * lrs;
			}
		}
		double mean = sum / cohort.size();
		double stddev = (ss / cohort.size()) - (mean * mean);
		means[i] = mean;
		stdDevs[i] = stddev;
	}
};


void Population::writeMeanStdDev(std::ofstream &data, int &generation) {
    if (!data.is_open()) {
        throw std::runtime_error("Unable to open means datafile...");
    }

//    means_data << "generation,"  << "g1mean," << "g1stddev," << "g2mean," << "g2stddev," << "g3mean," << "g3stddev,"
//               << "g4mean," << "g4stddev," << "d1mean," << "d2stddev," << "d2mean," << "d2stddev,"
//               << "agemean," << "agestddev," << "LRSmean," << "LRSstddev" << endl;
    data << generation;
    for (size_t i = 0; i < means.size(); ++i) data << "," << means[i] << "," << stdDevs[i];
    data << std::endl;
};

void Population::writeFinalPop(std::ofstream &data) {
    if (!data.is_open()) {
        throw std::runtime_error("Unable to open means datafile...");
    }

    data << "gene1,"  << "gene2," << "gene3," << "gene4," << "dam1," << "dam2," << "age," << "LRS," << "deathcause," << std::endl;

    for (auto& ind : cohort) {
        for (size_t i = 0; i < genesNo; ++i) {
            data << ind.getGenome()[i] << ",";
        }
        data << ind.getDamages()[0] << "," << ind.getDamages()[1] << "," << ind.getAge() << "," << ind.getLRS()
             << ", " << ind.getDeathcause() << std::endl;
    }
}


void Population::reproduceFromAlive(){
    std::vector<double> vFec;
    std::vector<int> vIndex;
    for (int i = 0; i < cohort.size(); ++i) {
        if (cohort[i].isAlive()) {
            vFec.push_back(cohort[i].getFecundity());
            vIndex.push_back(i);
        }
    }

    for (size_t i = 0; i < cohort.size(); ++i) {
        if (!cohort[i].isAlive()) {
            Individual indNew(cohort[vIndex[rindex(vFec)]].getGenome());    // Get genome of rand. parent by pulling from vector
            indNew.mutate();                                                // with offspring resources of alive individuals
            cohort[i] = indNew;
        }
    }
};

void Population::reproduceFromAll(){
    std::vector<double> vFec(popSize);
    for (size_t i = 0; i < cohort.size(); ++i) {
        vFec.push_back(cohort[i].getFecundity());
    }

    for (size_t i = 0; i < cohort.size(); ++i) {
        if (!cohort[i].isAlive()) {
            Individual indNew(cohort[rindex(vFec)].getGenome());    // Get genome of rand. parent by pulling from vector
            cohort[i] = indNew;                                     // with offspring resources of all individuals
        }
    }
};

void Population::runFinalCohort(std::ofstream &data) {
    data << "individual," << "deathcause," << "gene1," << "gene2," << "gene3," << "gene4," << "damage1," << "damage2,"
         << "age," << "LRS" << std::endl;
    int aliveTotal;
    do {
        aliveTotal = 0;

        for (size_t i = 0; i < cohort.size(); ++i) {
            cohort[i].calcResources();
            if(!cohort[i].kill()) {
                data << i << "," << cohort[i].getDeathcause() << ",";
                for(size_t j = 0; j < genesNo; ++j) data << cohort[i].getGenome()[j] << ",";
                data << cohort[i].getDamages()[0] << "," << cohort[i].getDamages()[1] << "," << cohort[i].getAge()
                     << "," << cohort[i].getLRS() << std::endl;
            }

            aliveTotal += cohort[i].isAlive();
        }
    } while (aliveTotal);
}