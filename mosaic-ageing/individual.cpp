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
