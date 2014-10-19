nclude <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Neuron
{
	long double input;
	long double output;
	long double bias;
	//long double weights;
};

struct Layer
{
	long double numUnit;
	long double **weights;
	struct Neuron *neuron;
};


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
	 		l2->neuron[j].input += l1->neuron[i].output * l1->weights[i][j];
		}
		l2->neuron[j].output = sigmoid(l2->neuron[j].input);
	}
}

int main()
{
	printf("%Lf\n", sigmoid(4));
	return 0;
}

