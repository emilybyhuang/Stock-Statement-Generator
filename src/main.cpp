#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stock.h>
#include <keyWordsList.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//assume all inputs are in the forms of strings
//use the argument vectors as input(assume passing in input through command line)
int main(int argc, char *argv[]) {
	vector<stock> profile;
	double dividendIncome;
	string profilestring, stockstring;
	string command, line, date, keyword, token;
	string osbracket, csbracket, equalsign;
	size_t pos = 0;
	bool action;//true = buy, false = sell
	
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
	//cout << "> ";
	//getline(cin, line);

	
	
	// while ((file.peek()!='\n')){
	// 	file >> profilestring;	
	// }
	// getline(file, profilestring);
	// getline(file, stockstring);
	// while ((file.peek()!='\n')){
	// 	file >> stockstring;
	// }
	// cout << "Profile string = " << profilestring << endl;
	// cout << "Stock string = " << stockstring << endl;

	while(!file.eof()){
		file >> ws;
		file >> command;
		cout << "command: " << command << endl;
			if(command == "actions"){
				file >> ws;
				file >> equalsign;
				if(equalsign != "=") return 0;
				file >> ws;
				cout << file.peek() << endl;
				while(!file.eof() && file.peek()!= 93){
					getline(file, profilestring);	
					cout << "in profile get line" << endl;		
				}
				cout << "Profile string = " << profilestring << endl;
			}else if(command == "stock_actions"){
				file >> ws;
				file >> equalsign;
				cout << "equalsign" <<  equalsign << endl;
				if(equalsign != "=") return 0;
				file >> ws;
				while(file.peek()!= 93){
					getline(file, stockstring);			
				}
				cout << "Stock string = " << stockstring << endl;
			}else{
				break;
			}
		}
	
	//
		


	
	//string delimiter5 = "[";
	//string delimiter6 = "]";

	// size_t pos = 0;
	// string token;
	// while ((pos = s.find(delimiter1)) != string :: npos) {
	// 	token = s.substr(0, pos);
	// 	cout << token << endl;
	// 	s.erase(0, pos + delimiter1.length());
	// }
	return 0;
	//cout << s << endl;
	while(!file.eof()){
		cout << "in while" << endl;
		file >> command;
		cout << "command" << endl;
		if(command == "actions"){
			file >> ws;
			//go until it hits [
			file.ignore(256,'[');
			//getline(file, token, delimeter1)) {
			
			//ascii 93 is ]

			while(!file.eof() && file.peek()!= 93){
				//get and store new info: date, action, ticker, price, shares
				while ((pos = profilestring.find(apo)) != string::npos) {
					token = profilestring.substr(0, pos);
					cout << token << endl;
					profilestring.erase(0, pos + delimiter1.length());
				}
				file >> date;
				cout << "date is" << date << endl;
				char a;
				a = getchar();
			}
			// linestream >> keyword;
			// cout << "read in" << keyword << endl;
			// if(keyword.compare(wordsList[2]) == 0){

			// }
			 
		}else if(command == "stock_actions"){
		}
	}					
}