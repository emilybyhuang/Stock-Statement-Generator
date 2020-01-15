#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateactions.h>
#include <processactions.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>

using namespace std;

bool processactions(vector<stock>& myportfolio, string jsonstr, string delimiter){
    size_t position = 0;
    string date, action, price, ticker, shares;
    while (((position = jsonstr.find(delimiter)) != string::npos)) {
        string actiontoken = jsonstr.substr(0, position);
        actiontoken = actiontoken + "}";
        jsonstr.erase(0, position + 1 + delimiter.length());
        boost::replace_all(actiontoken, "\'", "\"");
        nlohmann::json inputaction = nlohmann::json::parse(actiontoken);
        date = inputaction["date"];
        action = inputaction["action"];
        price = inputaction["price"];
        ticker = inputaction["ticker"];
        shares = inputaction["shares"];
        boost::replace_all(date, "/", "-");
        date = date.substr(0,10);
	}
    cout << "On " << date << ", you have:" << endl;
    bool addinputaction = updateactions(myportfolio, action, ticker, shares, price);
   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
    return true;
}