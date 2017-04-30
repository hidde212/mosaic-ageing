#include "population.h"


void Population::calcMeanStdDev() {
//	for (auto& value : means) value = 0.0;
    std::vector<std::vector<double> > mValues;

    for (auto &ind : cohort) {
        std::vector<double> indData;
        for (size_t i = 0; i < genesAmount; ++i) indData.push_back(ind.getGenome()[i]);
        for (size_t i = 0; i < traitsAmount; ++i) indData.push_back(ind.getDamages()[i]);
        indData.push_back(ind.getAge());
        indData.push_back(ind.getLRS());
        mValues.push_back(indData);
    }

//#pragma omp parallel for schedule(dynamic)
    for(int i = 0; i < mValues[0].size(); ++i) {
        double total = 0.0, varTotal = 0.0;
        for (auto &value : mValues) total += value[i];
        means[i] = total / mValues.size();
        for (auto &dev : mValues) varTotal += pow((dev[i] - means[i]), 2.0);
        stdDevs[i] = sqrt(varTotal / mValues.size());
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


void Population::reproduceFromAlive(){
    std::vector<double> vFec, vIndex;
    for (size_t i = 0; i < cohort.size(); ++i) {
        if (cohort[i].isAlive()) {
            vFec.push_back(cohort[i].getFecundity());
            vIndex.push_back(i);
        }
    }

    for (size_t i = 0; i < cohort.size(); ++i) {
        if (!cohort[i].isAlive()) {
            Individual indNew(cohort[vIndex[rindex(vFec)]].getGenome());// Get genome of rand. parent by pulling from vector
            cohort[i] = indNew;                                         // with offspring resources of alive individuals
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