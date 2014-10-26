#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

long double sigmoid(long double x);
void calcNet(void);
void WeightChangesHO(); 
void WeightChangesIH(); 
long double RandomVal(void); 
void initWeights(void);
void initData(void);
void displayResults(); 
void calcOverallError();
int main_neural(void);

#endif
