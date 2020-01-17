#include <iostream>
#include <iomanip>
#include <stock.h>
#include <update.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <string.h>
#include <cstring>
#include <debug.h>

using namespace std;

nlohmann::json convertToJson(string);
nlohmann::json mergeTrans(nlohmann::json &);
void process(vector<stock>&, nlohmann::json, nlohmann::json, double);
void processStoAct(vector<stock>&, nlohmann::json);
bool haveThisStock(vector<stock>& myportfolio, string ticker);

bool mainControl(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr){
    double dividendIncome = 0.0;
    nlohmann::json jsonAct = convertToJson(jsonActStr);
    nlohmann::json jsonStoAct = convertToJson(jsonStoStr);
    process(myportfolio, jsonAct, jsonStoAct, dividendIncome);
    return true;
}


nlohmann::json convertToJson(string str){
    replace(str.begin(), str.end(), '\'', '\"');
	nlohmann::json jsonarr = nlohmann::json::parse(str);
	cout << jsonarr << endl ;
	return jsonarr;
}

void process(vector<stock>& myportfolio, nlohmann::json jsonAct, nlohmann::json jsonStoAct, double dividendIncome){
    string actDate, actAction, actPrice, actTicker, actShares;
    string stoActDate,stoActDividend, stoActSplit, stoActStock;
    //int count = jsonAct.size()+ jsonStoAct.size();
    
    int i = 0, j = 0;
    
    string date0{ "0000-00-00" };

    while(i < jsonAct.size() || j < jsonStoAct.size()){
        if( i < jsonAct.size()) {
            actDate = jsonAct[i]["date"];
            actAction = jsonAct[i]["action"];
            actPrice = jsonAct[i]["price"];
            actTicker = jsonAct[i]["ticker"];
            actShares = jsonAct[i]["shares"];
        }

        if( j < jsonStoAct.size()) {
            stoActDate = jsonStoAct[j]["date"];
            stoActDividend = jsonStoAct[j]["dividend"];
            stoActSplit = jsonStoAct[j]["split"];
            stoActStock = jsonStoAct[j]["stock"];
        }

        //stock_action but no action
        if((i > jsonAct.size()) && ( j< jsonStoAct.size())) {
            stoActDate = stoActDate.substr(0,10);
            boost::replace_all(stoActDate, "/", "-");
        if( stoActDate != date0 && haveThisStock(myportfolio, stoActStock) ) {
            cout << "On " << stoActDate << ", you have:" << endl;
            date0 = stoActDate;
        }
            updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
            j++;
            continue;
        }

        // no stock_action but action
        if((j>jsonStoAct.size()) && ( i < jsonAct.size()) ) {
            actDate = actDate.substr(0,10);
            boost::replace_all(actDate, "/", "-");
        if( date0 != actDate ) {
            cout << "On " << actDate << ", you have:" << endl;
            date0 = actDate;
        }
            updateAct(myportfolio,actAction, actTicker, actShares, actPrice, dividendIncome);
            i++;
            continue;
        }

        // else both: 
        // action has earlier date
        if( strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
            actDate = actDate.substr(0,10);
            boost::replace_all(actDate, "/", "-");
            if( date0 != actDate ) {
            cout << "On " << actDate << ", you have:" << endl;
            date0 = actDate;
        }
            updateAct(myportfolio,actAction, actTicker, actShares, actPrice, dividendIncome);
            i++;
            continue;
        }
        
        //stock action has earlier date
        if( strcmp(actDate.c_str(), stoActDate.c_str()) > 0){
            stoActDate = stoActDate.substr(0,10);
        if(stoActDate != date0 && haveThisStock(myportfolio, stoActStock)) {
            cout << "On " << stoActDate << ", you have:" << endl;
            date0 = stoActDate;
        }
            updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
            j++;
            continue;
        }

        // both have the same date
        if(strcmp(actDate.c_str(), stoActDate.c_str()) == 0){
            actDate = actDate.substr(0,10);
            boost::replace_all(actDate, "/", "-");
            if( date0 != actDate ) {
                cout << "On " << actDate << ", you have:" << endl;
                date0 = actDate;
            }
            updateAct(myportfolio,actAction, actTicker, actShares, actPrice, dividendIncome);
            updateStoAct(myportfolio,stoActDividend, stoActSplit, stoActStock, dividendIncome);
            i++;
            j++;
        }
    }
}

bool haveThisStock(vector<stock>& myportfolio, string ticker){
    for(int i = 0; i < myportfolio.size(); i++){
        if(myportfolio[i].ticker == ticker){
            return true;
        }
    }
    return false;
}

