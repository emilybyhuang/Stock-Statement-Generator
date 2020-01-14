#include <iostream>
#include <string>
#include <stdio.h>
#include <stock.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>
#include <updateactions.h>
#include <transaction.h>
 
using namespace std;

//use the argument vectors as input(assume passing in input through command line)
int main(int argc, char *argv[]) {
	vector<nlohmann::json> profilevector;
	vector<stock> mystocks;
	double dividendIncome = 0.0;
	string actionstring, stockstring;
	string actiontoken, stocktoken, date, action, price, ticker, shares;
	string delimiter = "}";

	//read from the input file
	fstream file(argv[1]);
	//check the input file
	if (!file.is_open()) cout<< "Can not open file" << endl;
	
	//store the inputs as strings
	getline(file, actionstring);
	getline(file, stockstring);
	//cout << "Profile string = " << actionstring << endl;
	//cout << "Stock string = " << stockstring << endl;
	
	//get the action and stockaction string in a pseudo json form(omit action = [...] 
	//and stock_actions = [...]);
	size_t startindex = actionstring.find('[');
	string jsonactstr = actionstring.substr(startindex+1);
	string jsonstostr = stockstring.substr(startindex+1);
	jsonactstr.resize(jsonactstr.length()-1);
	jsonstostr.resize(jsonstostr.length()-1);

	size_t position1 = 0, position2 = 0;
	while (((position1 = jsonactstr.find(delimiter)) != string::npos)||
	((position2 = jsonactstr.find(delimiter)) != string::npos)){
		
		//for reading the actions one at a time and converting to standard json form
		actiontoken = jsonactstr.substr(0, position1);
		actiontoken = actiontoken + "}";
		jsonactstr.erase(0, position1 + 1 + delimiter.length());
		boost::replace_all(actiontoken, "\'", "\"");
		nlohmann::json inputaction = nlohmann::json::parse(actiontoken);
		
		//for reading the stock_actions one at a time and converting to standard json form
		stocktoken = jsonstostr.substr(0, position2);
		stocktoken = stocktoken + "}";
		jsonstostr.erase(0,position2 + 1 + delimiter.length());
		boost::replace_all(stocktoken, "\'", "\"");
		nlohmann::json inputstockaction = nlohmann::json::parse(stocktoken);
		
		date = inputaction["date"];
		action = inputaction["action"];
		price = inputaction["price"];
		ticker = inputaction["ticker"];
		shares = inputaction["shares"];
		boost::replace_all(date, "/", "-");
		date = date.substr(0,10);
		cout << "On " << date << ", you have:" << endl;
		bool addprofile = updateactions(mystocks, action, ticker, shares, price);
		cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
		transaction(action, ticker, shares, price);
	}
	return 0;				
}