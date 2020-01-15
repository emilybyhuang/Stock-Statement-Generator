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

bool processInfo(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr, 
string delimiter, double dividendIncome){
    
    string actDate, actAction, actPrice, actTicker, actShares, 
    stoActDate,stoActDividend, stoActSplit, stoActStock;
    bool actReady = true;
    bool stoActReady = true;
    cout << "ACTSTRING: " << jsonActStr << endl << endl;
    cout << "STOACTSTRING: " << jsonStoStr << endl << endl;

    size_t position1 = jsonActStr.find(delimiter);
    size_t position2 = jsonStoStr.find(delimiter);

    //cout << jsonActStr.length() << endl;
    //cout << jsonStoStr.length() << endl;

    //&& ((position1 < jsonActStr.length())&&(position2 < jsonStoStr.length()))
    while(actReady||stoActReady){
    // cout << "this pos: " << pos2 << endl;
    // while ((!actReady && ((position1 = jsonActStr.find(delimiter,position1+1)) != string::npos)) || 
    // (!stoactReady && ((position2 = jsonStoStr.find(delimiter,position2+1)) != string::npos))){
        cout << "Pos1 " << position1 << endl;
        cout << "Pos2 " << position2 << endl; 
        if(position1 != string ::npos && actReady){
            string actionString = jsonActStr.substr(0, position1 + 1);
            //actionString = actionString + "}";
            
            boost::replace_all(actionString, "\'", "\"");
            
            cout << "action string: " << actionString << endl;
            
            nlohmann::json inputAction = nlohmann::json::parse(actionString);
            
            cout << "input action: " << inputAction << endl;
            
            actDate = inputAction["date"];
            actAction = inputAction["action"];
            actPrice = inputAction["price"];
            actTicker = inputAction["ticker"];
            actShares = inputAction["shares"];
            // cout << actTicker << endl;
            // cout << actDate << endl;
            // cout << actPrice << endl;
            // cout << actShares << endl;
            // cout << actAction << endl;
            actReady = false;
        }
        
        if(position2 != string::npos && stoActReady){
            string stoActString = jsonStoStr.substr(0, position2 + 1);
            //stoActString = stoActString + "}";
            boost::replace_all(stoActString, "\'", "\"");
            
            cout << "stock string: " << stoActString << endl;
            
            nlohmann::json inputStockAction = nlohmann::json::parse(stoActString);
            
            cout << "input stock action: " << inputStockAction << endl;
           
            stoActDate = inputStockAction["date"];
            stoActDividend = inputStockAction["dividend"];
            stoActSplit = inputStockAction["split"];
            stoActStock = inputStockAction["stock"];
            stoActReady = false;
        }
        
        if((position1 != string::npos)&&(position2 != string::npos)){
            if(strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
                //cout << "compare result: "  << strcmp(actDate.c_str(), stoActDate.c_str()) << endl;
                boost::replace_all(actDate, "/", "-");
                string printDate = actDate.substr(0,10);
                cout << "On " << actDate << ", you have:" << endl;
                bool update = updateAct(myportfolio, actAction, actTicker, actShares, actPrice);
                printPorfolio(myportfolio, dividendIncome);
                jsonActStr.erase(0, position1 + 1 + delimiter.length());
                actReady = true;
            }else{
                //cout << "compare result: "  << strcmp(actDate.c_str(), stoActDate.c_str()) << endl;
                boost::replace_all(stoActDate, "/", "-");
                string printDate = stoActDate.substr(0,10);
                cout << "On " << stoActDate << ", you have:" << endl;
                bool update = updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
                printPorfolio(myportfolio, dividendIncome);
                jsonStoStr.erase(0, position2 + 1 + delimiter.length());
                stoActReady = true;
            } 
        }else{
            if(position1 != string::npos && position2 == string::npos){
                boost::replace_all(actDate, "/", "-");
                string printDate = actDate.substr(0,10);
                cout << "On " << actDate << ", you have:" << endl;
                bool update = updateAct(myportfolio, actAction, actTicker, actShares, actPrice);
                printPorfolio(myportfolio, dividendIncome);
                actReady = true;
            }else if(position1 == string::npos && position1 == string::npos){
                boost::replace_all(stoActDate, "/", "-");
                string printDate = stoActDate.substr(0,10);
                cout << "On " << stoActDate << ", you have:" << endl;
                bool update = updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
                printPorfolio(myportfolio, dividendIncome);
                stoActReady = true; 
            }
        }
        if(actReady){  
            if((position1 = jsonActStr.find(delimiter))!= string::npos){
                cout << jsonActStr.find(delimiter) << endl;
                actReady = true;
            }else if(jsonActStr.find(delimiter)== string::npos){
                actReady = false;
                cout << "actReady false " << endl;
            }
        }else if(stoActReady){
            if((position2 = jsonStoStr.find(delimiter))!= string::npos){
                //do nothing
                cout << jsonStoStr.find(delimiter) << endl;
                stoActReady = true;
            }else if(jsonStoStr.find(delimiter)== string::npos){
                stoActReady = false;
                cout << "stoActReady false" << endl;
            }
        }
	}




   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
    return true;
}

