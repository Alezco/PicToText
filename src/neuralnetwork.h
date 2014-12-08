#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

long double sigmoid(long double x);
long double sigmoid_derivate(long double x);
void Initialize(int *layerSizes, int layerSizesLength); 
long double RandomVal(void); 
void Run(double *input, double *output);
double Train(double *input, double *desired,
						 double TrainingRate, double Momentum);
void Save();
void Load();
void convert(int size, int input[size][256], double res[size][256]);

#endif
