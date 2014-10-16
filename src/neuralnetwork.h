//Here is the definition of our Neural and Layer
typedef struct Neural Neural;
struct Neural
{
	long double computedVal;
	long double sumVal;
	long double bias;
};

typedef struct Layer Layer;
struct Layer
{
	unsigned numberLinks;
	long double **weights;
	unsigned numberUnits;
	Neural *Units;
};

//Here is declaration of functions

void computedSum(Layer *layer1, Layer *layer2);
long double sigmoid(long double x);
void initializeLayer(Layer *layer);
void data(Layer *Input, Layer *Hidden, Layer *Output);
