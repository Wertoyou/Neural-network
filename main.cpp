#include "cluster.h"
#include <iostream>
#include <string>
#include <algorithm>

// 12out4LRFRANCK

std::string intToString(int n, int base){
	std::string result;
	while(n!=0){
		if (n%base<10) {
			result.push_back((n%base)+'0');
		}
		if (n%base>=10) {
			result.push_back((n%base)+'A');
		}
		n/=base;
	}
	std::reverse(result.begin(),result.end());
	return result;
}

/*int main(){
	std::string in;
	std::string out;
	std::cout << "What file do you want to load the network from? (Don't forget file extention): \n";
	std::cin >> in;
	std::cout << "What file do you want to save the network to? (Don't forget file extention): \n";
	std::cin >> out;

	Cluster Network;
	Network.LoadNetwork(in);

	Network.alpha = 1;

	std::ifstream kin("in2.txt");

	double tmp;

	for (int i = 0; i < 1000; ++i) {
		std::vector<double> iner(4);
		kin >> iner[0] >> iner[1] >> iner[2] >> iner[3];
		Network.in_set(iner);
		kin >> tmp;	
		Network.t.push_back(tmp);

		Network.theOutput = Network.GetOutput();

		std::cout << "Tru_Answer: " << Network.t[0] << std::endl;
		std::cout << "Net_Answer: " << Network.theOutput[0] << std::endl << std::endl;

		Network.BackPropagation();
		std::cout << "EoL" << std::endl;
		Network.t.pop_back();
		//Network.alpha-=0.001;
	}

	Network.SaveNetwork(out);

	return 0;
}*/

/*int main(){
	std::string in;
	std::string out;
	std::cin >> in >> out;

	Cluster Network;
	Network.LoadNetwork(in);

	Network.alpha=0.1;

	//Network.t.push_back(1);

	std::vector<double> iner(4);
	std::cin >> iner[0] >> iner[1] >> iner[2] >> iner[3];
	Network.in_set(iner);

	Network.theOutput = Network.GetOutput();

	std::cout << "Tru_Answer: " << Network.t[0] << std::endl;
	std::cout << "Net_Answer: " << Network.theOutput[0] << std::endl << std::endl;

	Network.BackPropagation();
	std::cout << "EoL\n";

	Network.SaveNetwork(out);

	return 0;
}*/

/*int main(){

	return 0;
}*/

int main() {
	std::string s;
	std::cout << "Is this training or running?" << std::endl;
	std::cin >> s;

	Cluster Network;

	if (s[0]=='t' || s[0]=='T') {
		std::string in;
		std::string out;
		std::cout << "What file do you want to load the network from? (Don't forget file extention and absolute path): \n";
		std::cin >> in;
		std::cout << "What file do you want to save the network to? (Don't forget file extention and absolute path): \n";
		std::cin >> out;

		Network.LoadNetwork(in);

		std::cout << "What learning alpha do you want?" << std::endl;
		std::cin >> Network.alpha;

		std::string data;
		std::cout << "What file do you want to load input and output from? (Don't forget file extention)" << std::endl;
		std::cin >> data;
		
		std::ifstream myList;
		std::ifstream inList;
		std::ifstream reList;
		// Skriv ut till fil spara värden för träning
		std::ofstream Resout ("RESULTAT_12out4L1.txt");

		myList.open(data);
		if(!myList) std::cout << "ErrorData" << std::endl;
	
		unsigned long long int numData;
		numData=100000;
		
		for (unsigned long long int i = 0; i < numData; ++i) {
			std::string Note,Case;
			myList >> Note >> Case;
			std::string inPath = "Notes/" + Note + '/' + Case + ".txt";
			std::string rePath = "Notes/" + Note + '/' + "Res3.txt";
			inList.open(inPath);
			reList.open(rePath);

			if(!inList) std::cout << "ErrorIn" << std::endl << inPath << std::endl;
			if(!reList) std::cout << "ErrorRe" << std::endl;

			unsigned long long int numInput, numOutput;
			numInput=1375;
			numOutput=12;
			std::vector<double> inVector(numInput);

			for (unsigned long long int j = 0; j < numInput; ++j) {
				inList >> inVector[j];
			}

			Network.t.resize(numOutput);

			for (unsigned long long int j = 0; j < numOutput; ++j) {
				reList >> Network.t[j];
			}

			Network.in_set(inVector);

			Network.theOutput = Network.GetOutput();

			if(!(i%500)) {
				int tt=std::find(Network.t.begin(),Network.t.end(),1)-Network.t.begin();
				if(tt!=87){
					if(!(i%500)){
						std::cout << tt << std::endl;
						std::cout << "Diff: " << double(1.0l - double(Network.theOutput[tt])) << std::endl << std::endl;
					}
					Resout << tt << std::endl;
					Resout << "Diff: " << double(1.0l - double(Network.theOutput[tt])) << std::endl << std::endl;
				}
				// Network.SaveNetwork(out);
			}

			Network.BackPropagation();

			inList.close();
			reList.close();
		}

		Network.SaveNetwork(out);
		return 0;
	}
	
	std::string in;
	std::cout << "What file do you want to load the network from? (Don't forget file extention): \n";
	std::cin >> in;

	Network.LoadNetwork(in);

	std::string data;

	std::cout << "What file do you want to load the input from? (Don't forget file extention): \n";
	std::cin >> data;

	int numdata=12;

	std::ofstream Resout ("TEST_RESULTAT_12out4L0R.txt");
	std::ifstream inList(data);
	for(int k=0; k<numdata; ++k){
		std::string note;

			inList>>note;
			
		
		for(int k2=1; k2<33; ++k2){
			

			std::string noterep="/Users/Victors/Documents/NETWORKTEST/Notes/"+note+"/R"+std::to_string(k2)+".txt";

			std::ifstream kin(noterep);

			unsigned long long int numInput;
			numInput=1375;
			std::vector<double> inVector(numInput);

			for (unsigned long long int j = 0; j < numInput; ++j) {
				kin >> inVector[j];
			}

			Network.in_set(inVector);

			Network.theOutput = Network.GetOutput();

			// std::cout << Network.theOutput[k] << std::endl;
			Resout <<note<<' '<< Network.theOutput[k] << std::endl;

			for (unsigned int i = 0; i < Network.theOutput.size(); ++i) {
				// std::cout << Network.theOutput[i] << ' ';
				Resout << Network.theOutput[i] << ' ';
			}
			// std::cout<<std::endl<<std::endl;
			Resout<<std::endl<<std::endl;

			// Network.theOutput = Network.GetOutput();

			// for (unsigned int i = 0; i < Network.theOutput.size(); ++i) {
			// 	std::cout << Network.theOutput[i] << ' ';
			// }
		}
	}
	return 0;
}


