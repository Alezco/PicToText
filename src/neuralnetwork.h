#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

long double sigmoid(long double x);
long double sigmoid_derivate(long double x);
void Initialize(int *layerSizes, int layerSizesLength); 
long double RandomVal(void); 
void Run(double *input, double *output);
double Train(double *input, double *desired,
						 double TrainingRate, double Momentum);
void Save();
void Load();
int main_neural(char a);

#endif
