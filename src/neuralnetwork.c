#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "neuralnetwork.h"

#define numInputs  3
#define numPatterns  4
#define numHidden 2

const int iterations = 1000;
const double LR_IH = 0.7;
const double LR_HO = 0.07;

int patNum = 0;
double errThisPat = 0.0;
double outPred = 0.0;
double RMSerror = 0.0;

double hiddenVal[numHidden];

double weightsIH[numInputs][numHidden];
double weightsHO[numHidden];

int trainInputs[numPatterns][numInputs];
int trainOutput[numPatterns];

long double sigmoid(long double x)
{
	return (1 /(1 + exp(-x)));
}

void calcNet(void)
{
    int i = 0;
    int j = 0;

    for(i = 0;i < numHidden;i++)
    {
	hiddenVal[i] = 0.0;

        for(j = 0;j<numInputs;j++)
        {
	  hiddenVal[i]=hiddenVal[i]+(trainInputs[patNum][j] * weightsIH[j][i]);
        }

        hiddenVal[i] = sigmoid(hiddenVal[i]);
    }

    outPred = 0.0;

   for(i = 0;i<numHidden;i++)
   {
    outPred = outPred + hiddenVal[i] * weightsHO[i];
   }
    
    errThisPat = outPred - trainOutput[patNum];

}

void WeightChangesHO(void)
{
   for(int k = 0;k<numHidden;k++)
   {
	double weightChange = LR_HO * errThisPat * hiddenVal[k];
    	weightsHO[k] -= weightChange;

    	if (weightsHO[k] < -5)
    	{
     		weightsHO[k] = -5;
    	}
    	else if (weightsHO[k] > 5)
    	{
     	weightsHO[k] = 5;
    	}
   }

 }

void WeightChangesIH(void)
{
  for(int i = 0;i<numHidden;i++)
  {
   	for(int k = 0;k<numInputs;k++)
   	{
    		double x = 1 - (hiddenVal[i] * hiddenVal[i]);
    		x = x * weightsHO[i] * errThisPat * LR_IH;
    		x = x * trainInputs[patNum][k];
    		double weightChange = x;
    		weightsIH[k][i] = weightsIH[k][i] - weightChange;
   	}
  }

}

long double RandomVal(void)
{
 	return ((double)rand())/(double)RAND_MAX;
}

void initWeights(void)
{
 	for(int j = 0;j<numHidden;j++)
 	{
   		weightsHO[j] = (RandomVal() - 0.5)/2;
    		for(int i = 0;i<numInputs;i++)
    		{
     			weightsIH[i][j] = (RandomVal() - 0.5)/5;
     			printf("Weight = %f\n", weightsIH[i][j]);
    		}
  	}

}

void initData(void)
{
    trainInputs[0][0]  = 0;
    trainInputs[0][1]  = 0;
    trainInputs[0][2]  = 1;
    trainOutput[0] = 0;

    trainInputs[1][0]  = 0;
    trainInputs[1][1]  = 1;
    trainInputs[1][2]  = 1;
    trainOutput[1] = 1;

    trainInputs[2][0]  = 1;
    trainInputs[2][1]  = 0;
    trainInputs[2][2]  = 1;
    trainOutput[2] = 1;

    trainInputs[3][0]  = 1;
    trainInputs[3][1]  = 1;
    trainInputs[3][2]  = 1;
    trainOutput[3] = 0;

}

void displayResults(void)
{
 	for(int i = 0;i<numPatterns;i++)
 	{
  		patNum = i;
  		calcNet();
  		printf("pat = %d expected value = %d calculated value = %f\n",
  		patNum+1, trainOutput[patNum], outPred);
 	}
}

void calcOverallError(void)
{
     RMSerror = 0.0;
     for(int i = 0;i<numPatterns;i++)
        {
         patNum = i;
         calcNet();
         RMSerror = RMSerror + (errThisPat * errThisPat);
        }
     RMSerror = RMSerror/numPatterns;
     RMSerror = sqrt(RMSerror);
}

int main_neural(void)
{
 	srand ( time(NULL) );
 	initWeights();
	initData();

    	for(int j = 0;j <= iterations;j++)
    	{
        	for(int i = 0;i<numPatterns;i++)
        	{
          		patNum = rand()%numPatterns;
			calcNet();
			WeightChangesHO();
			WeightChangesIH();
        	}

        calcOverallError();
	printf("iteration = %d calculated value = %f\n",j,RMSerror);
    	}

	displayResults();
	return 0;
}
