#include <iostream>
#include <string>
#include <stdio.h>
#include <stock.h>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include <update.h>
#include <transaction.h>
#include <processinfo.h>

using namespace std;

//use the argument vectors as input(assume passing in input through command line)
int main(int argc, char *argv[]) {
	vector<nlohmann::json> profilevector;
	vector<stock> mystocks;
	string actionstring, stockstring;

	//read from the input file
	fstream file(argv[1]);
	//check the input file
	if (!file.is_open()) cout << "Can not open file" << endl;
	
	//store the inputs as strings
	getline(file, actionstring);
	getline(file, stockstring);
	
	size_t foundLeft1 = actionstring.find('[');
	size_t foundRight1 = actionstring.find(']');
	size_t foundLeft2 = stockstring.find('[');
	size_t foundRight2 = stockstring.find(']');
	//get the action and stockaction string in a pseudo json form
	string jsonactstr = actionstring.substr(foundLeft1, foundRight1);
	string jsonstostr = stockstring.substr(foundLeft2, foundRight2);
	
	//bool a_process = processAct(mystocks, jsonactstr, delimiter, dividendIncome);
	//bool s_process = processStoAct(mystocks, jsonstostr, delimiter, dividendIncome);
	mainControl(mystocks,jsonactstr,jsonstostr);
	// int a;
	// cin >> a;
	return 0;				
}