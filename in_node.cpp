#include "in_node.h"

std::vector<double> in_node::GetValues(){
	return intoNetwork;
}

void in_node::SetValues(std::vector<double>& a){
	a.push_back(1);
	intoNetwork = a;
}

int in_node::size(){return intoNetwork.size();}