#include "individual.h"
#include "globals.h"
#include "randomnumbers.h"


individual::individual() {
	age = 0;
}

void individual::setGene1(const double &setManual /* = 0 */) {	// If default argument is given (setManual), gene value equals this argument. Else, value taken from normal distribution
	setManual ? gene1 = setManual : gene1 = normal(gen1Mean, gen1StdDev);
}

void individual::setGene2(const double &setManual /* = 0 */) {	// If default argument is given (setManual), gene value equals this argument. Else, value taken from normal distribution
	setManual ? gene2 = setManual : gene2 = normal(gen2Mean, gen2StdDev);
}

void individual::setGene3(const double &setManual /* = 0 */) {	// If default argument is given (setManual), gene value equals this argument. Else, value taken from normal distribution
	setManual ? gene3 = setManual : gene3 = normal(gen3Mean, gen3StdDev);
}

void individual::setGene4(const double &setManual /* = 0 */) {	// If default argument is given (setManual), gene value equals this argument. Else, value taken from normal distribution
	setManual ? gene4 = setManual : gene4 = normal(gen4Mean, gen4StdDev);
}


void individual::mutateGene1() { // Add mutation to gen 2. No restriction to gene value
	if (ru() < mutRateGene1) {
		double mutation = normal(0, mutStdDevGene1);
		gene1 += mutation;
	}
}
void individual::mutateGene2() { // Add mutation to gen 2. No restriction to gene value
	if (ru() < mutRateGene2) {
		double mutation = normal(0, mutStdDevGene2);
		gene2 += mutation;
	}
}
void individual::mutateGene3() { // Add mutation to gen 2. No restriction to gene value
	if (ru() < mutRateGene3) {
		double mutation = normal(0, mutStdDevGene3);
		gene3 += mutation;
	}
}
void individual::mutateGene4() { // Add mutation to gen 2. No restriction to gene value
	if (ru() < mutRateGene4) {
		double mutation = normal(0, mutStdDevGene4);
		gene4 += mutation;
	}
}