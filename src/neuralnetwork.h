#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

typedef struct Neuron Neuron;
struct Neuron
{
	long double input;
	long double output;
	long double bias;
	unsigned numberWeights;
	long double *weight;
};

typedef struct Layer Layer;
struct Layer
{
	unsigned numUnit;
	unsigned numberUnits;
	struct Neuron *neuron;
};

//Here is declaration of functions

void initWeights();
void initData();
void calcNet();
void WeightChangesHO();
void WeightChangesIH();
void calcOverallError();
void displayResults();
double getRand();
void calcNet(void);
long double RandomVal(void);
int main_neural(void);

#endif
