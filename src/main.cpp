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
	
	size_t found = actionstring.find('[');
	//get the action and stockaction string in a pseudo json form(omit action = [...] and stock_actions = [...]);
	string jsonactstr = actionstring.substr(found+1);
	string jsonstostr = stockstring.substr(found+1);
	jsonactstr.resize(jsonactstr.length()-1);
	jsonstostr.resize(jsonstostr.length()-1);

	size_t position1 = 0, position2 = 0;
	cout << '\n' << endl;
	while (((position1 = jsonactstr.find(delimiter)) != string::npos)) {
		actiontoken = jsonactstr.substr(0, position1);
		actiontoken = actiontoken + "}";
		jsonactstr.erase(0, position1 + 1 + delimiter.length());
		boost::replace_all(actiontoken, "\'", "\"");
		nlohmann::json inputaction = nlohmann::json::parse(actiontoken);
		a_date = inputaction["date"];
		a_action = inputaction["action"];
		a_price = inputaction["price"];
		a_ticker = inputaction["ticker"];
		a_shares = inputaction["shares"];
		boost::replace_all(a_date, "/", "-");
		a_date = a_date.substr(0,10);
		cout << "On " << a_date << ", you have:" << endl;
		bool addinputaction = updateactions(mystocks, a_action, a_ticker, a_shares, a_price);
		cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
		//transaction(action, ticker, shares, price);
	}
	return 0;				
}