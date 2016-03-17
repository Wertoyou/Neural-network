#ifndef __layer__
#define __layer__

#include "node.h"
#include <fstream>

//Layer class
class Layer {
private:
	//Vector containing the nodes in the layer
	std::vector<Node> thisLayer;

public:
	//Constructor with size
	Layer(int&);

	//Constructor
	Layer();

	//Size function
	int size();

	//Size of previous layer
	int PreSize();

	//Calclayer
	void CalcLayer();

	//Function for getting the output
	std::vector<double> GetOutput();

	//Set the layer to a vector
	void SetLayer(std::vector<Node>&);

	//Function for setting the value of the input to the layer
	void SetVal(std::vector<double>&);

	//Function for printing the layer
	void printLayer(std::ofstream&);

	//Function for getting the weight of a node to another node
	double getWeight(int&,int&);

	//Function for setting a weight of a node to another node
	void setSingleWeight(int&,int&,const double&);

	std::vector<double> Output;
};
#endif