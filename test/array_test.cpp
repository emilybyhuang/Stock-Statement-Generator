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
		cout << jobjs << endl ;
		cout << "jobjs.size(): " <<jobjs.size() << endl;
	}

	return 0;
	
}
