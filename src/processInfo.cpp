#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateAct.h>
#include <processAct.h>
#include <updateStoAct.h>
#include <processStoAct.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <printPortfolio.h>
#include <string.h>
#include <cstring>

using namespace std;

bool processInfo(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr, string delimiter, double dividendIncome){
    size_t position1 = 0, position2 = 0;
    string actDate, actAction, actPrice, actTicker, actShares, stoActDate,stoActDividend, stoActSplit, stoActStock;
    while (((position1 = jsonActStr.find(delimiter)) != string::npos) || 
    ((position2 = jsonStoStr.find(delimiter)) != string::npos)){
        
        string actionString = jsonActStr.substr(0, position1);
        actionString = actionString + "}";
        jsonActStr.erase(0, position1 + 1 + delimiter.length());
        boost::replace_all(actionString, "\'", "\"");
        cout << actionString << endl;
        nlohmann::json inputAction = nlohmann::json::parse(actionString);

        string stoActString = jsonStoStr.substr(0, position2);
        stoActString = stoActString + "}";
        jsonStoStr.erase(0, position2 + 1 + delimiter.length());
        boost::replace_all(stoActString, "\'", "\"");
        cout << stoActString << endl;
        nlohmann::json inputStockAction = nlohmann::json::parse(stoActString);
        
        actDate = inputAction["date"];
        actAction = inputAction["action"];
        actPrice = inputAction["price"];
        actTicker = inputAction["ticker"];
        actShares = inputAction["shares"];
        stoActDate = inputStockAction["date"];
        stoActDividend = inputStockAction["dividend"];
        stoActSplit = inputStockAction["split"];
        stoActStock = inputStockAction["stocks"];
        if(strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
            boost::replace_all(actDate, "/", "-");
            string printDate = actDate.substr(0,10);
            cout << "On " << actDate << ", you have:" << endl;
            bool update = updateAct(myportfolio, actAction, actTicker, actShares, actPrice);
            printPorfolio(myportfolio, dividendIncome);
        }else{
            boost::replace_all(stoActDate, "/", "-");
            string printDate = stoActDate.substr(0,10);
            cout << "On " << stoActDate << ", you have:" << endl;
            bool update = updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
            printPorfolio(myportfolio, dividendIncome);
        } 
	}
   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
    return true;
}