//Here is the definition of our Neural and Layer
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

void computedSum(Layer *layer1, Layer *layer2);
long double sigmoid(long double x);
void initLay(Layer *layer, unsigned pnumUnit, unsigned pNumberWeights);
void data(Layer *Input, Layer *Hidden, Layer *Output);
