#ifndef __node__
#define __node__

#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

//Node class
class Node{
private:
	//vector containing the weight in
	std::vector<double> inWeight;

	//vector containing the values in
	std::vector<double> inValue;

	//Result
	double result;

public:
	//Constructor
	Node();

	//Function for calculating the output
	void CalcOutput();

	//Function for Getting the output
	double GetOutput();

	//Get size of inWeight
	int size();

	//Function that takes a vector and sets the node's inWeight vector to the sent vector
	void SetWeight(std::vector<double>&);

	//Function that takes a vector and sets the node's inValue vector to the sent vector
	void SetValue(std::vector<double>&);

	//Function for printing weight vector
	void printWeight(std::ofstream&);

	//Function for getting the weight of a node
	double getWeight(int&);

	//Function for setting the weight of a single node
	void setSingleWeight(int&,const double&);
};
#endif