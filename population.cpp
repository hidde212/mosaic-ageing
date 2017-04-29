#include "population.h"

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