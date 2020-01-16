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

	return 0;
	
}
