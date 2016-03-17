#ifndef __in_node__
#define __in_node__

#include <vector>

class in_node
{
private:
	//The values into the network
	std::vector<double> intoNetwork;
public:
	//Function for retreiving the vector
	std::vector<double> GetValues();

	//Function for setting the vector
	void SetValues(std::vector<double>&);

	int size();
};

#endif