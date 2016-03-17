#include "cluster.h"

void Cluster::LoadNetwork(std::string& in){
	int num_Layers;
	std::ifstream fin(in);
	if(!fin) std::cout << "error" << std::endl;

	fin >> num_Layers;
	std::vector<Layer> inCluster(num_Layers);

	Layer tmp_layer;

	int num_Nodes;
	int old_num_nodes = 1375; //Antalet indatanoder

	for (int i = 0; i < num_Layers; ++i) {
		fin >> num_Nodes;

		//ta hänsyn till bias
		++old_num_nodes;
		std::vector<Node> tmp_vectorNode(num_Nodes);
		std::vector<double> vftmp(old_num_nodes);
		for (int j = 0; j < num_Nodes; ++j) {
			for (int k = 0; k < old_num_nodes; ++k) {
				fin >> vftmp[k];
			}
			tmp_vectorNode[j].SetWeight(vftmp);
		}
		old_num_nodes=num_Nodes;

		inCluster[i].SetLayer(tmp_vectorNode);
	}

	theCluster=inCluster;
}

std::vector<double> Cluster::GetOutput(){
	std::vector<double> a;

	a=IntoNode.GetValues();

	for (unsigned int i = 0; i < theCluster.size(); ++i) {
		theCluster[i].SetVal(a);
		theCluster[i].CalcLayer();
		a = theCluster[i].GetOutput();
	}
	return a;
}

void Cluster::SaveNetwork(std::string& out){
	std::ofstream fout(out);
	fout << std::setprecision(70);
	fout << theCluster.size() << std::endl << std::endl;

	for (unsigned int i = 0; i < theCluster.size(); ++i) {
		fout << theCluster[i].size() << std::endl;
		theCluster[i].printLayer(fout);
		fout << std::endl;
	}
}

void Cluster::in_set(std::vector<double> a){
	IntoNode.SetValues(a);
}

void Cluster::BackPropagation(){
	//std::cout << "hi\n";
	std::vector<std::vector<double> > change(3);
	double tempChange;

	std::vector<double>& outOut=theCluster[2].Output;
	std::vector<double>& outHid2=theCluster[1].Output;
	std::vector<double>& outHid1=theCluster[0].Output;
	std::vector<double> outIn = IntoNode.GetValues();

	//Add bias in hidden output
	outHid1.push_back(1);
	outHid2.push_back(1);

	/*std::cout << "outIn: " << outIn.size() << std::endl;
	std::cout << "outHid: " << outHid.size() << std::endl;
	std::cout << "outOut: " << outOut.size() << std::endl << std::endl;*/
	// std::cout << "outOut: " << outOut.size() << std::endl << std::endl;
	// std::cout << "t.size(): " << t.size() << std::endl << std::endl;
	
	// Derivative for output layer
	for (int i = 0; i < theCluster[2].size(); ++i) {
		change[2].push_back((outOut[i]-t[i])*(outOut[i]*(1.0-outOut[i])));
	}
	// std::cout<<"BUGNOTFOUND1"<<std::endl;
	// Derivative for hidden layer no2
	for (int i = 0; i < theCluster[1].size(); ++i) {
		tempChange=0;
		for (int k = 0; k < theCluster[2].size(); ++k) {
			tempChange += (change[2][k] * theCluster[2].getWeight(i,k));
		}
		change[1].push_back((outHid2[i]*(1.0-outHid2[i]))*tempChange);
	}
	// std::cout<<"BUGNOTFOUND2"<<std::endl;
	// Derivative for hidden layer no1
	for (int i = 0; i < theCluster[0].size(); ++i) {
		tempChange=0;
		for (int k = 0; k < theCluster[1].size(); ++k) {
			tempChange += (change[1][k] * theCluster[1].getWeight(i,k));
		}
		change[0].push_back((outHid1[i]*(1.0-outHid1[i]))*tempChange);
	}
	// std::cout<<"BUGNOTFOUND3"<<std::endl;
	// Update Hid1
	for (int n = 0; n < theCluster[0].size(); ++n) {
		for (int m = 0; m < outIn.size(); ++m) {
			theCluster[0].setSingleWeight(m,n,(theCluster[0].getWeight(m,n)-((change[0][n])*outIn[m]*alpha)));
		}
	}
	// std::cout<<"BUGNOTFOUND4"<<std::endl;
	// Update Hid2
	for (int n = 0; n < theCluster[1].size(); ++n) {
		// std::cout<<"BUGNOTFOUNDN"<<n<<std::endl;
		for (int m = 0; m < outHid1.size(); ++m) {
			// std::cout<<"BUGNOTFOUNDM"<<m<<std::endl;
			theCluster[1].setSingleWeight(m,n,(theCluster[1].getWeight(m,n)-((change[1][n])*outHid1[m]*alpha)));
			// theCluster[1].setSingleWeight(m,n,(theCluster[1].getWeight(m,n)));
		}
	}

	// Update Out
	for (int n = 0; n < theCluster[2].size(); ++n) {
		for (int m = 0; m < outHid2.size(); ++m) {
			theCluster[2].setSingleWeight(m,n,(theCluster[2].getWeight(m,n)-((change[2][n])*outHid2[m]*alpha)));
		}
	}
}

int Cluster::insize() {return IntoNode.size();}

void Cluster::getDesired(int& a){
	t.resize(a);
	for (int i = 0; i < a; ++i) {
		std::cin >> t[i];
	}
}

/*void Cluster::BackPropagation(){
	for (int i = 0; i < theCluster[0].size(); ++i) {
		for (int j = 0; j < theCluster[1].size(); ++j) {
			int sum=0;
			for (int l = 0; l < theCluster[2].size(); ++l) {
				sum+=(theCluster[2].getWeight(j,l)*(theOutput[l]-t[l])*theOutput[l]*(1-theOutput[l]));
				//std::cout << "l\n";
			}
			//std::cout << "i: " << i << " outputSize0: " << theCluster[0].Output.size ( ) << " j: " << " outputSize1: " << theCluster[1].Output.size() << std::endl;
			theCluster[1].setSingleWeight(i,j,(theCluster[1].getWeight(i,j))-(alpha*theCluster[0].Output[i]*theCluster[1].Output[j]*(1-theCluster[1].Output[j])*sum));
			//std::cout << "j\n";
		}
		//std::cout << "i\n";
	}

	for (int j = 0; j < theCluster[1].size(); ++j) {
		for (int l = 0; l < theCluster[2].size(); ++l) {
			theCluster[2].setSingleWeight(j,l,(theCluster[2].getWeight(j,l)-alpha*theCluster[1].Output[j]*(theCluster[2].Output[l]-t[l])*theCluster[2].Output[l]*(1-theCluster[2].Output[l])));
		}
	}
}*/

/*void Cluster::BackPropagation(){
	double sum=0;

	std::vector<double>& outOut=theCluster[1].Output;
	std::vector<double>& outHid=theCluster[0].Output;
	std::vector<double> outIn = IntoNode.GetValues();
	double wij;

	for (int j = 0; j < theCluster[0].size(); ++j) {
		for (int i = 0; i < IntoNode.size(); ++i) {
			sum=0;

			for (int l = 0; l < theCluster[1].size(); ++l) {
				sum+=(theCluster[1].getWeight(j,l)*(outOut[l]-t[l])*(outOut[l]*(1-outOut[l])));
			}

			wij=theCluster[0].getWeight(i,j);
			theCluster[0].setSingleWeight(i,j,(wij-(alpha*outIn[i]*outHid[j]*(1-outHid[j])*sum)));
		}
	}

	double wjl;

	for (int l = 0; l < theCluster[1].size(); ++l) {
		for (int j = 0; j < theCluster[0].size()+1; ++j) {
			wjl=theCluster[1].getWeight(j,l);
			theCluster[1].setSingleWeight(j,l,(wjl-(alpha*outHid[j]*(outOut[l]-t[l])*outOut[l]*(1-outOut[l]))));
		}
	}
}*/