#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "neuralnetwork.h"

//NEW CODE FOR NEURAL NETWORK
//PREVIOUS VERSION DOWN 

/// Data dependent settings ////
#define numInputs  3
#define numPatterns  4
#define numHidden 2

//// User defineable settings ////
const int iterations = 1000;
const double LR_IH = 0.7;
const double LR_HO = 0.07;


//// functions ////
void initWeights();
void initData();
void calcNet();
void WeightChangesHO();
void WeightChangesIH();
void calcOverallError();
void displayResults();
double getRand();


//// variables ////
int patNum = 0;
double errThisPat = 0.0;
double outPred = 0.0;
double RMSerror = 0.0;

// the outputs of the hidden neurons
double hiddenVal[numHidden];

// the weights
double weightsIH[numInputs][numHidden];
double weightsHO[numHidden];

// the data
int trainInputs[numPatterns][numInputs];
int trainOutput[numPatterns];


//==============================================================
//************** function definitions **************************
//==============================================================

long double sigmoid(long double x)
{
	return (1 /(1 + exp(-x)));
}

//***********************************
// calculates the network output
void calcNet(void)
{
    //calculate the outputs of the hidden neurons
    int i = 0;
    int j = 0;

    for(i = 0;i<numHidden;i++)
    {
	  hiddenVal[i] = 0.0;

        for(j = 0;j<numInputs;j++)
        {
	   hiddenVal[i]=hiddenVal[i]+(trainInputs[patNum][j] * weightsIH[j][i]);
        }

        hiddenVal[i] = sigmoid(hiddenVal[i]);
    }

   //calculate the output of the network
   //the output neuron is linear
   outPred = 0.0;

   for(i = 0;i<numHidden;i++)
   {
    outPred = outPred + hiddenVal[i] * weightsHO[i];
   }
    //calculate the error
    errThisPat = outPred - trainOutput[patNum];

}


//************************************
//adjust the weights hidden-output
void WeightChangesHO(void)
{
   for(int k = 0;k<numHidden;k++)
   {
    double weightChange = LR_HO * errThisPat * hiddenVal[k];
    weightsHO[k] -= weightChange;

    //regularisation on the output weights
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


//************************************
// adjust the weights input-hidden
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


//************************************
// generates a random number
long double RandomVal(void)
{
 return ((double)rand())/(double)RAND_MAX;
}



//************************************
// set weights to random numbers 
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


//************************************
// read in the data
void initData(void)
{
    //printf("initialising data\n");

    // the data here is the XOR data
    // it has been rescaled to the range
    // [-1][1]
    // an extra input valued 1 is also added
    // to act as the bias
    // the output must lie in the range -1 to 1

    trainInputs[0][0]  = 0;
    trainInputs[0][1]  = 0;
    trainInputs[0][2]  = 1;    //bias
    trainOutput[0] = 0;

    trainInputs[1][0]  = 0;
    trainInputs[1][1]  = 1;
    trainInputs[1][2]  = 1;       //bias
    trainOutput[1] = 1;

    trainInputs[2][0]  = 1;
    trainInputs[2][1]  = 0;
    trainInputs[2][2]  = 1;        //bias
    trainOutput[2] = 1;

    trainInputs[3][0]  = 1;
    trainInputs[3][1]  = 1;
    trainInputs[3][2]  = 1;     //bias
    trainOutput[3] = 0;

}


//************************************
// display results
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


//************************************
// calculate the overall error
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

//==============================================================
//********** THIS IS THE MAIN PROGRAM **************************
//==============================================================


int main(void)
{
 // seed random number function
 srand ( time(NULL) );

 // initiate the weights
 initWeights();

 // load in the data
 initData();

 // train the network

    for(int j = 0;j <= iterations;j++)
    {
        for(int i = 0;i<numPatterns;i++)
        {
          //select a pattern at random
          patNum = rand()%numPatterns;

          //calculate the current network output
          //and error for this pattern
          calcNet();

          //change network weights
          WeightChangesHO();
          WeightChangesIH();
        }

        //display the overall network error
        //after each epoch
        calcOverallError();

        printf("iteration = %d calculated value = %f\n",j,RMSerror);
    }

 //training has finished
 //display the results
 displayResults();


 //system("PAUSE");
 return 0;
}

//PREVIOUS CODE FOR NEURAL NETWORK

/*void initializeNeuron(struct Neuron *Neural, unsigned pNumberWeights)
{
		unsigned w;
		Neural->output = 0;
		Neural->input = 0;
		Neural->numberWeights = pNumberWeights;
		
		Neural->weight = malloc(sizeof(long double) * pNumberWeights);

		for (w = 0; w < pNumberWeights; w++)
				Neural->weight[w] = 0;

}

void initLay(struct Layer *Layer,unsigned pnumUnit, unsigned pNumberWeights)
{
		struct Neuron neural;
		unsigned i;

		Layer->numUnit = pnumUnit;
		Layer->neuron = malloc(sizeof(neural) * pnumUnit);
		for(i = 0; i < pnumUnit; i++)
				initializeNeuron(&Layer->neuron[i],pNumberWeights);

}

long double sigmoid(long double x)
{
	return (1 /(1 + exp(-x)));
}

void ComputeSum(struct Layer *l1, struct Layer *l2)
{
	unsigned i, j;
	for(j = 0; j < l2->numUnit; j++)
	{
		for(i = 0; i < l1->numUnit; i++)
		{
	 		l2->neuron[j].input += l1->neuron[i].output *
								   (l1->neuron->weight[i] +
								   l1->neuron->weight[j]);
		}
		l2->neuron[j].output = sigmoid(l2->neuron[j].input);
	}
} 

int main_neural()
{
		struct Layer Input;
		struct Layer Hidden;
		struct Layer Output;

		initLay(&Input,2,1);
		initLay(&Hidden,2,1);
		initLay(&Output,1,1);

		Input.neuron[0].weight[0] = 0.8;
		Input.neuron[0].weight[1] = 0.2;

		Input.neuron[1].weight[0] = 0.4;
		Input.neuron[1].weight[1] = 0.6;

		Hidden.neuron[0].weight[0] = 0.7;
		Hidden.neuron[1].weight[0] = 0.3;
	//	printf("%Lf\n", Output.neuron->output);
	//	printf("%Lf\n", sigmoid(4));
		ComputeSum(&Input, &Hidden);
		printf("entrée du Hidden0: %Lf\n", Hidden.neuron[0].input);
		printf("poids du Hidden0: %Lf\n", Hidden.neuron[0].weight[0]);
		printf("sortie du Hidden0: %Lf\n\n", Hidden.neuron[0].output);

		printf("entrée du Hidden1: %Lf\n", Hidden.neuron[1].input);
		printf("poids du Hidden1: %Lf\n", Hidden.neuron[1].weight[0]);
		printf("sortie du Hidden1: %Lf\n\n", Hidden.neuron[1].output);

		printf("entrée du Input0: %Lf\n", Input.neuron[0].input);
		printf("les poids du Input0: %Lf\n et %Lf\n",
			   Input.neuron[0].weight[0], Input.neuron[0].weight[1]);
		printf(" Sortie du Input0: %Lf\n", Input.neuron[0].output);

		printf("sortie finale: %Lf\n\n", Output.neuron[0].output);
		return 0;
}*/

