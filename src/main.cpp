#include <iostream>
#include <string>
#include <stdio.h>
#include <stock.h>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include <updateAct.h>
#include <updateStoAct.h>
#include <transaction.h>
#include <processAct.h>
#include <processStoAct.h>

using namespace std;

//use the argument vectors as input(assume passing in input through command line)
int main(int argc, char *argv[]) {
	vector<nlohmann::json> profilevector;
	vector<stock> mystocks;
	double dividendIncome = 0.0;
	string actionstring, stockstring;
	string actiontoken, a_date, a_action, a_price, a_ticker, a_shares;
	string delimiter = "}";

	//read from the input file
	fstream file(argv[1]);
	//check the input file
	if (!file.is_open()) cout<< "Can not open file" << endl;
	
	//store the inputs as strings
	getline(file, actionstring);
	getline(file, stockstring);
	//cout << "inputaction string = " << actionstring << endl;
	//cout << "Stock string = " << stockstring << endl;
	
	size_t found1 = actionstring.find('[');
	size_t found2 = stockstring.find('[');
	//get the action and stockaction string in a pseudo json form(omit action = [...] and stock_actions = [...]);
	string jsonactstr = actionstring.substr(found1+1);
	string jsonstostr = stockstring.substr(found2+1);
	jsonactstr.resize(jsonactstr.length()-1);
	jsonstostr.resize(jsonstostr.length()-1);
	
	cout << '\n' << endl;
	bool a_process = processAct(mystocks, jsonactstr, delimiter);
	bool s_process = processStoAct(mystocks, jsonstostr, delimiter, dividendIncome);
	return 0;				
}