/* #include<nlohmann/json.hpp> */
#include "json.hpp"
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

int main() {
	const string inFile{"action.txt"};
	string l;

	ifstream infile(inFile);
	while(getline(infile, l)) {
		replace(l.begin(), l.end(), '\'', '\"');
		cout << "original json string:" << endl;
		cout << l << endl;

		nlohmann::json jobjs = nlohmann::json::parse(l);
		
//		jobjs.erase(2);

		for(int i=0; i< jobjs.size(); i ++) {

			cout <<  jobjs[i]["date"] << endl;
		}
	}




	int bufferIndex=0;  // buffer index

	for(int i=1; i < jobjs.size(); ) {
		//this element is the same as bufferred
		if(jobjs[i]["date"] == jobjs[bufferIndex]["date"] ){


			//merfe jobjs[i] to jobjs[bufferIndex];
			//
			//jobjs.erace(i);

		} else {

			buffer = jobjs[i];
			bufferIndex = i;
			
		}
	}


	return 0;
	
}
