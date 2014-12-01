#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

long double sigmoid(long double x);
long double sigmoid_derivate(long double x);
void Initialize(int *layerSizes); 
long double RandomVal(void); 
void Run(double *input, double *output);
double Train(double *input, double *desired,
						 double TrainingRate, double Momentum);
int main_neural(void);

#endif
