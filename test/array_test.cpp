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




	nlohmann::json buffer=jobjs[0];
	int bufferIndex=0;

	for(int i=1; i < jobjs.size(); ) {
		//this element is the same as bufferred
		if(jobjs[i]["date"] == temp["date"] ){
			//add jobjs[i] to temp;
			//jobjs.erace(i);
			//
		} else {
			buffer = jobjs[i];
			bufferIndex = i;
			
			}
	}


	return 0;
	
}
