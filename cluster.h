#ifndef __cluster__
#define __cluster__

#include "layer.h"
#include <string>
#include <fstream>
#include "in_node.h"
#include <iostream>

//Layer cluster class
class Cluster
{
private:
	//Vector containing the layers in the cluster
	std::vector<Layer> theCluster;

	//The in node in the cluster
	in_node IntoNode;

public:
	//Function for loading the network
	void LoadNetwork(std::string&);

	//Function for getting the output of the network
	std::vector<double> GetOutput();

	//Function for saving the network
	void SaveNetwork(std::string&);

	//Function for setting the in node
	void in_set(std::vector<double>);

	//The packprobagation function fungerar bara för 3 lager
	void BackPropagation();

	//The output (this needs to be assigned before Backpropagation can be run)
	std::vector<double> theOutput;

	//Learning factor
	double alpha;

	//Desired output
	std::vector<double> t;

	//cin:a intens antalet svar
	void getDesired(int&);

	int insize();

	std::vector<double> getInto();
};
#endif