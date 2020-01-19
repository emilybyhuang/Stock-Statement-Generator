#include <iostream>
#include <string>
#include <stdio.h>
#include <stock.h>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include <update.h>
#include <processinfo.h>

using namespace std;

//use the argument vectors as input(assume passing in input through command line)
int main(int argc, char *argv[]) {
	cout << "\"\"\"" << endl;
	vector<stock> mystocks;
	string actionstring, stockstring, actions, stockActions;

	//read from the input file
	fstream file(argv[1]);
	//check the input file
	if (!file.is_open()) cout << "Can not open file" << endl;
	
	//store the inputs as strings
	getline(file, actionstring);
	getline(file, stockstring);
	stringstream actStream(actionstring);
	stringstream stoActStream(stockstring);
	actStream >> actions;
	stoActStream >> stockActions;
	if(actions != "actions") cout << "Error: expecting actions" << endl;
	if(stockActions != "stock_actions") cout << "Error: expecting stock_actions" << endl;


	//get the action and stockaction string in a pseudo json form
	size_t foundLeft1 = actionstring.find('[');
	size_t foundRight1 = actionstring.find(']');
	size_t foundLeft2 = stockstring.find('[');
	size_t foundRight2 = stockstring.find(']');
	string jsonactstr = actionstring.substr(foundLeft1, foundRight1);
	string jsonstostr = stockstring.substr(foundLeft2, foundRight2);

	//update the user's stock porfolio, print stock statement
	mainControl(mystocks,jsonactstr,jsonstostr);

	//free dynamically allocated memory
	for(auto it = mystocks.begin(); it!= mystocks.end();){
		it = mystocks.erase(it);
	}
	cout << "\"\"\"" << endl;
	return 0;				
}