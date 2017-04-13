
#ifndef MOSAIC_AGEING_INDIVIDUAL_H
#define MOSAIC_AGEING_INDIVIDUAL_H

class individual {
public:
	individual();			// Constructor

	// Set functions:
	void setGene1(const double &setManual = 0.0);	// Set genes 1/2/3. If argument is given, gene value equals this argument.
	void setGene2(const double &setManual = 0.0);	// Else without argument, pulled from normal distribution with mean/stddev defined in globals.cpp
	void setGene3(const double &setManual = 0.0);
	void setGene4(const double &setManual = 0.0);
	void mutateGene1();							// Add mutations to traits
	void mutateGene2();
	void mutateGene3();
	void mutateGene4();
	


private:
	int age;					// Current age of individual
	double damageTrait1;		// Damage in component 1 an individual has accumulated over lifetime
	double damageTrait2;		// Damage in component 2 an inidivual has accumulated over lifetime
	bool alive;					// Whether alive, or not. TRUE or FALSE value
	int deathCause;

	double gene1;				// Curve of function determining resources towards offspring
	double gene2;				// Shift of function determining resources towards offspring
	double gene3;				// Curve of function determining repair resources towards trait 1
	double gene4;				// Shift of function determining repair resources towards trait 1

	double repairResources;		// Fraction of resources being appointed to repair
	double offspringResources;	// Fraction of resources used for reproduction
};

#endif //MOSAIC_AGEING_INDIVIDUAL_H