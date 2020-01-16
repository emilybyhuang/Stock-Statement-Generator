#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateAct.h>
#include <updateStoAct.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <printPortfolio.h>
#include <string.h>
#include <cstring>

using namespace std;

bool processInfo(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr, 
string delimiter, double dividendIncome){
    vector<json::action> actionArray;
    vector<json::
    string actDate, actAction, actPrice, actTicker, actShares, 
    stoActDate,stoActDividend, stoActSplit, stoActStock;
    bool actReady = true;
    bool stoActReady = true;

    size_t position1 = jsonActStr.find(delimiter);
    size_t position2 = jsonStoStr.find(delimiter);

    while(actReady||stoActReady){ 
        if(position1 != string ::npos && actReady){
            //cout << "Pos1 " << position1 << endl;
            string actionString = jsonActStr.substr(0, position1 + 1);
            //actionString = actionString + "}";
            
            boost::replace_all(actionString, "\'", "\"");
            
            //cout << "action string: " << actionString << endl;
            
            nlohmann::json inputAction = nlohmann::json::parse(actionString);
            
            //cout << "input action: " << inputAction << endl;
            
            actDate = inputAction["date"];
            actAction = inputAction["action"];
            actPrice = inputAction["price"];
            actTicker = inputAction["ticker"];
            actShares = inputAction["shares"];
            actReady = false;
        }
        
        if(position2 != string::npos && stoActReady){
            //cout << "Pos2 " << position2 << endl; 
            string stoActString = jsonStoStr.substr(0, position2 + 1);
            //stoActString = stoActString + "}";
            boost::replace_all(stoActString, "\'", "\"");
            
           //cout << "stock string: " << stoActString << endl;
            
            nlohmann::json inputStockAction = nlohmann::json::parse(stoActString);
            
            //cout << "input stock action: " << inputStockAction << endl;
           
            stoActDate = inputStockAction["date"];
            stoActDividend = inputStockAction["dividend"];
            stoActSplit = inputStockAction["split"];
            stoActStock = inputStockAction["stock"];
            stoActReady = false;
        }
        
        actDate = actDate.substr(0,10);
        stoActDate = stoActDate.substr(0,10);
        if((position1 != string::npos)&&(position2 != string::npos)){
            if(strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
                boost::replace_all(actDate, "/", "-");
                cout << "On " << actDate << ", you have:" << endl;
                bool update = updateAct(myportfolio, actAction, actTicker, actShares, actPrice);
                printPorfolio(myportfolio, dividendIncome);
                jsonActStr.erase(0, position1 + 1 + delimiter.length());
                actReady = true;
            }else if(strcmp(actDate.c_str(), stoActDate.c_str()) > 0){
                boost::replace_all(stoActDate, "/", "-");
                cout << "On " << stoActDate << ", you have:" << endl;
                bool update = updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
                printPorfolio(myportfolio, dividendIncome);
                jsonStoStr.erase(0, position2 + 1 + delimiter.length());
                stoActReady = true;
            }else{
                boost::replace_all(actDate, "/", "-");
                cout << "in same date" << endl;
                cout << "On " << actDate << ", you have:" << endl;
                bool update1 = updateAct(myportfolio, actAction, actTicker, actShares, actPrice);
                bool update2 = updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
                printPorfolio(myportfolio, dividendIncome);
                jsonActStr.erase(0, position1 + 1 + delimiter.length());
                jsonStoStr.erase(0, position2 + 1 + delimiter.length());
                actReady = true;
                stoActReady = true;
            }
        }else{
            if(position1 != string::npos && position2 == string::npos){
                boost::replace_all(actDate, "/", "-");
                string printDate = actDate.substr(0,10);
                cout << "On " << actDate << ", you have:" << endl;
                bool update = updateAct(myportfolio, actAction, actTicker, actShares, actPrice);
                printPorfolio(myportfolio, dividendIncome);
                jsonActStr.erase(0, position1 + 1 + delimiter.length());
                actReady = true;
            }else if(position1 == string::npos && position1 == string::npos){
                boost::replace_all(stoActDate, "/", "-");
                string printDate = stoActDate.substr(0,10);
                cout << "On " << stoActDate << ", you have:" << endl;
                bool update = updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
                printPorfolio(myportfolio, dividendIncome);
                jsonStoStr.erase(0, position2 + 1 + delimiter.length());
                stoActReady = true; 
            }
        }

        if(actReady){  
            if((position1 = jsonActStr.find(delimiter))!= string::npos){
                //do nothing
                //cout << jsonActStr.find(delimiter) << endl;
                actReady = true;
            }else if(jsonActStr.find(delimiter)== string::npos){
                actReady = false;
                //cout << "actReady false" << endl;
                if((position2 = jsonStoStr.find(delimiter))!= string::npos && stoActReady == false){
                    stoActReady = true;
                }
            }
        }
        if(stoActReady){
            if((position2 = jsonStoStr.find(delimiter))!= string::npos){
                //do nothing
                //cout << jsonStoStr.find(delimiter) << endl;
                stoActReady = true;
            }else if(jsonStoStr.find(delimiter) == string::npos){
                stoActReady = false;
                //cout << "stoActReady false" << endl;
                if((position1 = jsonActStr.find(delimiter))!= string::npos && actReady == false){
                    actReady = true;
                }
            }
        }
	}

   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
    return true;
}

