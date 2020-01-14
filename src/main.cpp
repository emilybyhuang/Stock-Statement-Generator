#include <iostream>
#include <string>
#include <stdio.h>
#include <stock.h>
#include <keyWordsList.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <stockns.h>
using namespace std;

//use the argument vectors as input(assume passing in input through command line)
int main(int argc, char *argv[]) {
	vector<stock> profile;
	double dividendIncome;
	string profilestring, stockstring;
	string command, line, date, keyword, token;
	string osbracket, csbracket, equalsign;
	size_t pos = 0;

	string delimiter1 = ": ";
	string delimiter2 = ", ";
	string ocbracket = "{";
	string ccbracket = "}";
	string delimiter5 = "/";
	string apo = "'";

	//read from the input file
	fstream file(argv[1]);
	//check the input file
	if (!file.is_open()) cout<< "Could not open file\n";
	else cout << "opened file" << endl;
	
	getline(file, profilestring);
	getline(file, stockstring);
	cout << "Profile string = " << profilestring << endl;
	cout << "Stock string = " << stockstring << endl;
	
	// nlohmann:: json j;
	// file >> j;
	// cout << "j is" << j << endl;

	// json js = profilestring;
	// auto s2 = js.get<std::string>();
	// cout << "s2:" << s2 << endl;
	
	size_t found1 = profilestring.find('[');
	size_t found2 = profilestring.find(']');
	string forjsonprofilestr = profilestring.substr(found1+1);
	forjsonprofilestr.resize(forjsonprofilestr.length()-1);
	forjsonprofilestr = '{' + forjsonprofilestr + '}';
	cout << '\n' << "FOR:" << forjsonprofilestr << endl ;
	stockns::action profilejson = nlohmann::json::parse(forjsonprofilestr);
	cout << profilejson << endl;
	// auto j3 = nlohmann::json::parse(forjsonprofilestr);
	// cout << j3 << endl;
	// nlohmann:: json j;
	// forjsonprofilesubstr >> j;
	// cout << "j is" << j << endl;



	//cout << "here: " << profilejson.is_array() << endl;
	// json j;
	// file >> j;
	// cout << j << endl;

	// size_t pos = 0;
	// string token;
	// while ((pos = s.find(delimiter1)) != string :: npos) {
	// 	token = s.substr(0, pos);
	// 	cout << token << endl;
	// 	s.erase(0, pos + delimiter1.length());
	// }

	return 0;
	//cout << s << endl;
	// while(!file.eof()){
	// 	cout << "in while" << endl;
	// 	file >> command;
	// 	cout << "command" << endl;
	// 	if(command == "actions"){
	// 		file >> ws;
	// 		//go until it hits [
	// 		file.ignore(256,'[');
	// 		//getline(file, token, delimeter1)) {
			
	// 		//ascii 93 is ]

	// 		while(!file.eof() && file.peek()!= 93){
	// 			//get and store new info: date, action, ticker, price, shares
	// 			while ((pos = profilestring.find(apo)) != string::npos) {
	// 				token = profilestring.substr(0, pos);
	// 				cout << token << endl;
	// 				profilestring.erase(0, pos + delimiter1.length());
	// 			}
	// 			file >> date;
	// 			cout << "date is" << date << endl;
	// 			char a;
	// 			a = getchar();
	// 		}
	// 	}else if(command == "stock_actions"){
	// 	}
	// }					
}