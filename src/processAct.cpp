#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateAct.h>
#include <processAct.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <printPortfolio.h>

using namespace std;

bool processAct(vector<stock>& myportfolio, string jsonstr, string delimiter, double dividendIncome){
    size_t position = 0;
    string date, action, price, ticker, shares;
    while (((position = jsonstr.find(delimiter)) != string::npos)) {
        string actionstring = jsonstr.substr(0, position);
        actionstring = actionstring + "}";
        jsonstr.erase(0, position + 1 + delimiter.length());
        boost::replace_all(actionstring, "\'", "\"");
        nlohmann::json inputaction = nlohmann::json::parse(actionstring);
        date = inputaction["date"];
        action = inputaction["action"];
        price = inputaction["price"];
        ticker = inputaction["ticker"];
        shares = inputaction["shares"];
        boost::replace_all(date, "/", "-");
        string printDate = date.substr(0,10);
        cout << "On " << printDate << ", you have:" << endl;
        bool update = updateAct(myportfolio, action, ticker, shares, price);
        printPorfolio(myportfolio, dividendIncome);
	}
   
   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
    return true;
}