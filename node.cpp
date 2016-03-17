#include "node.h"

Node::Node(){
	result = 0;
}

void Node::CalcOutput(){
	result=0;
	for (unsigned long i = 0; i < inValue.size(); ++i) {
		result+=inValue[i]*inWeight[i];
	}
	result=(1.0/(1.0+exp(-(result))));
}

double Node::GetOutput(){
	return result;
}

void Node::SetWeight(std::vector<double>& a){
	inWeight=a;
}

void Node::SetValue(std::vector<double>& a){
	inValue=a;
}

int Node::size(){
	return inWeight.size();
}

void Node::printWeight(std::ofstream& fout){
	for (unsigned int i = 0; i < inWeight.size(); ++i) {
		fout << inWeight[i] << ' ';
	}
	fout << std::endl;
}

double Node::getWeight(int& a){
	return inWeight[a];
}

void Node::setSingleWeight(int& a,const double& b){
	inWeight[a]=b;
}