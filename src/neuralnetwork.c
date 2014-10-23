#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "neuralnetwork.h"

void initializeNeuron(struct Neuron *Neural, unsigned pNumberWeights)
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
		//struct Layer Hidden;
		struct Layer Output;

		initLay(&Input,2,1);
		//initLay(&Hidden,2,1);
		initLay(&Output,1,1);

		Input.neuron[0].weight[0] = 0.8;
		Input.neuron[0].weight[1] = 0.2;

		Input.neuron[1].weight[0] = 0.4;
		Input.neuron[1].weight[1] = 0.6;

		//Hidden.neuron[0].weight[0] = 0.7;
		//Hidden.neuron[1].weight[0] = 0.3;
	//	printf("%Lf\n", Output.neuron->output);
	//	printf("%Lf\n", sigmoid(4));
		ComputeSum(&Input, &Output);
		printf("%Lf\n", Output.neuron[0].output);
		return 0;
}

