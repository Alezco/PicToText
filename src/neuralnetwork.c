#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "neuralnetwork.h"
#include "detect.h"


#define TAILLE_MAX 1000

int layerCount;
int inputSize;
int *layerSize;

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

void Save()
{
    FILE *file = NULL;

    file = fopen("save/weights.txt", "w+");

    if(file != NULL)
    {
        for(int l = 0; l < layerCount; l++)
            for(int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
                for(int j = 0; j < layerSize[l]; j++)
                    fprintf(file, "%f\n", weights[l][i][j]);
        fclose(file);
    }
    else
        printf("Impossible d'ouvrir weights.txt");

    file = fopen("save/bias.txt", "w+");

    if(file != NULL)
    {
        for(int l = 0; l < layerCount; l++)
            for(int i = 0; i < layerSize[l]; i++)
                fprintf(file, "%f\n", bias[l][i]);
        fclose(file);
    }
    else
        printf("Impossible d'ouvrir bias.txt");
}

void Load()
{
    FILE *file_weights = NULL;
    FILE *file_bias = NULL;

    file_weights = fopen("save/weights.txt", "r");
    file_bias = fopen("save/bias.txt", "r");

    char c[TAILLE_MAX] = "";

    if(file_weights != NULL && file_bias != NULL)
    {
        for(int l = 0; l < layerCount; l++)
            for(int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
                for(int j = 0; j < layerSize[l]; j++)
                {
                    fgets(c, TAILLE_MAX, file_weights);
                    weights[l][i][j] = atof(c);
                }

        fclose(file_weights);

        for(int l = 0; l < layerCount; l++)
            for(int i = 0; i < layerSize[l]; i++)
            {
                fgets(c, TAILLE_MAX, file_bias);
                bias[l][i] = atof(c);
            }

        fclose(file_bias);
    }
}

void convert(int size, int input[size][256], double res[size][256])
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            res[i][j] = (double)(input[i][j]);
        }
    }

}
