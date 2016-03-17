#include "layer.h"

Layer::Layer(int& a){
	thisLayer.resize(a);
}

Layer::Layer(){
}

void Layer::CalcLayer(){
	for(unsigned long i = 0; i < thisLayer.size(); ++i){
		thisLayer[i].CalcOutput();
	}
	Output=GetOutput();
	//Output.push_back(1);
}

void Layer::SetLayer(std::vector<Node>& a){
	thisLayer=a;
}

void Layer::SetVal(std::vector<double>& a){
	a.push_back(1);
	for (unsigned int i = 0; i < thisLayer.size(); ++i) {
		thisLayer[i].SetValue(a);
	}
}

std::vector<double> Layer::GetOutput() {
	std::vector<double> a(thisLayer.size());
	for (unsigned int i = 0; i < thisLayer.size(); ++i) {
		a[i]=thisLayer[i].GetOutput();
	}
	return a;
}

int Layer::size(){
	return thisLayer.size();
}

int Layer::PreSize(){
	return thisLayer[0].size();
}

void Layer::printLayer(std::ofstream& fout){
	for (unsigned int i = 0; i < thisLayer.size(); ++i) {
		thisLayer[i].printWeight(fout);
	}
}

double Layer::getWeight(int& a,int& b){
	return thisLayer[b].getWeight(a);
}

void Layer::setSingleWeight(int& a,int& b, const double& c){
	thisLayer[b].setSingleWeight(a,c);
}