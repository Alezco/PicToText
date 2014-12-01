#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "neuralnetwork.h"

int layerCount; //nb couches 
int inputSize;  //nb n dans input
int *layerSize; //nb n par couche

double **layerOutput;
double **layerInput;
double **bias;
double **delta;
double **previousBiasDelta;

double ***weights;
double ***previousWeightDelta; 

long double sigmoid(long double x)
{
		return (1 /(1 + exp(-x)));
}

long double sigmoid_derivate(long double x)
{
		return sigmoid(x) * (1 - sigmoid(x));
}

void Initialize(int *layerSizes, int layerSizesLength)
{
		layerCount = layerSizesLength - 1;
		inputSize = layerSizes[0];
		layerSize = malloc(sizeof(int) * layerCount);

		for(int i = 0; i < layerCount; i++)
				layerSize[i] = layerSizes[i + 1];

		layerOutput = malloc(sizeof(double *) * layerCount);
		layerInput = malloc(sizeof(double *) * layerCount);
		bias = malloc(sizeof(double *) * layerCount);
		delta = malloc(sizeof(double *) * layerCount);
		previousBiasDelta = malloc(sizeof(double *) * layerCount);

		weights = malloc(sizeof(double **) * layerCount);
		previousWeightDelta = malloc(sizeof(double **) * layerCount);

		for(int l = 0; l < layerCount; l++)
		{
				layerOutput[l] = malloc(sizeof(double) * layerSize[l]);
				layerInput[l] = malloc(sizeof(double) * layerSize[l]);
				bias[l] = malloc(sizeof(double) * layerSize[l]);
				delta[l] = malloc(sizeof(double) * layerSize[l]);
				previousBiasDelta[l] = malloc(sizeof(double) * layerSize[l]);

				weights[l] = malloc(sizeof(double *) *
								(l == 0 ? inputSize : layerSize[l - 1]));
				previousWeightDelta[l] = malloc(sizeof(double *) *
								(l == 0 ? inputSize : layerSize[l - 1]));

				for(int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
				{
						weights[l][i] = malloc(sizeof(double) * layerSize[l]);
						previousWeightDelta[l][i] = malloc(sizeof(double) * layerSize[l]);
				}
		}

		for(int l = 0; l < layerCount; l++)
		{
				for(int j = 0; j < layerSize[l]; j++)
				{
						bias[l][j] = RandomVal();
						layerOutput[l][j] = 0.0;
						layerInput[l][j] = 0.0;
						delta[l][j] = 0.0;
						previousBiasDelta[l][j] = 0.0;
				}


				for(int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
				{
						for(int j = 0; j < layerSize[l]; j++)
						{
								weights[l][i][j] = RandomVal();
								previousWeightDelta[l][i][j] = 0.0;
						}
				}
		}
}

long double RandomVal(void)
{
		return ((double)rand() / (double)RAND_MAX);
}

void Run(double *input, double *output)
{
		for(int l = 0; l < layerCount; l++)
		{
				for(int j = 0; j < layerSize[l]; j++)
				{
						double sum = 0.0;

						for(int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
						{
								sum += weights[l][i][j] * 
											 (l == 0 ? input[i] : layerOutput[l - 1][i]);
						}

						sum += bias[l][j];
						layerInput[l][j] = sum;
						layerOutput[l][j] = sigmoid(sum);
				}
		}

		for(int i = 0; i < layerSize[layerCount - 1]; i++)
				output[i] = layerOutput[layerCount - 1][i];
}
double Train(double *input, double *desired, 
						 double TrainingRate, double Momentum)
{
		double error = 0.0;
		double sum = 0.0;
		double weightDelta = 0.0;
		double biasDelta = 0.0;

		double *output = malloc(sizeof(double) * layerSize[layerCount - 1]);

		Run(input, output);

		for(int l = layerCount - 1; l >= 0; l--)
		{
				if(l == layerCount - 1)
				{
						for(int k = 0; k < layerSize[l]; k++)
						{
								delta[l][k] = desired[k] - output[k];
								error += delta[l][k] * delta[l][k] * 0.5;
						}
				}
				else
				{
						for(int i = 0; i < layerSize[l]; i++)
						{
								sum = 0.0;
								for(int j = 0; j < layerSize[l + 1]; j++)
								{
										sum += weights[l + 1][i][j] * delta[l + 1][j];
								}
								delta[l][i] = sum;
						}
				}
		}

		for(int l = 0; l < layerCount; l++)
		{
				for(int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
				{
						for(int j = 0; j < layerSize[l]; j++)
						{
								weightDelta = TrainingRate * delta[l][j] *
															(l == 0 ? input[i] : layerOutput[l - 1][i]) *
															sigmoid_derivate(layerInput[l][j])
															+ Momentum * previousWeightDelta[l][i][j];
								weights[l][i][j] += weightDelta;
								previousWeightDelta[l][i][j] = weightDelta;
						}
				}
		}

		for(int l = 0; l < layerCount; l++)
		{
				for(int i = 0; i < layerSize[l]; i++)
				{
						biasDelta = TrainingRate * delta[l][i];
						bias[l][i] += biasDelta + Momentum * previousBiasDelta[l][i];
						previousBiasDelta[l][i] = biasDelta;
				}
		}

		return error;
}

int main_neural(void)
{		
		int layerSizes[3] = {1, 2, 1};
		Initialize(layerSizes, 3);
		double input[1] = {0.0};
		double desired[1] = {0.1};
		double output[1];
		double error = 0.0;

		for(int i = 0; i < 1000; i++)
		{
				error = Train(input, desired, 0.15, 0.1);
				Run(input, output);
				
				if(i % 100 == 0)
						printf("Iteration : %d\n Input : %f\n Output : %f\n Error : %f\n", 
						       i, input[0], output[0], error);
		}

		return 0;
}
