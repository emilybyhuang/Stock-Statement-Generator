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
    string actDate, stoActDate, currentStock;
    bool wait = false;
    int i = 0, j = 0;
    int bufferType;
    //string date0 = "0000/00-00";
    string bufferDate = "0000/00/00";
    string currentDate;
    vector<int> actBuffer;
    vector<int> stoActBuffer;
    while(i < jsonAct.size() || j < jsonStoAct.size()){
        //cout << "\n\n*******" << endl << endl;
        
       
        if(i < jsonAct.size()){
            actDate = jsonAct[i]["date"];
            cout << "ok1" << endl;
            actDate = actDate.substr(0,10);
        }
        
        if(j < jsonStoAct.size()){
            stoActDate = jsonStoAct[j]["date"];
            cout << "ok2" << endl;
            stoActDate = stoActDate.substr(0,10);
        }

        cout << "actDate: " <<  actDate << endl;
        cout << "stoActDate: " << stoActDate << endl;
        
        // action but no stock_action
        if((j>jsonStoAct.size()) && ( i < jsonAct.size()) ) {
            currentDate = actDate;
            bufferType = 1;
            i++;
        }

        //stock_action but no action
        if((i > jsonAct.size()) && ( j < jsonStoAct.size())) {
            currentDate = stoActDate;
            bufferType = 2;
            j++;
        }

        // else has action and stock action strings: 
        // action has earlier date
        if( strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
            currentDate = actDate;
            bufferType = 1;
            i++;
        }
        
        //stock action has earlier date
        if( strcmp(actDate.c_str(), stoActDate.c_str()) > 0){
            cout << DBG << "j++" << endl;
            currentDate = stoActDate;
            bufferType = 2;
            //updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome, wait);
            j++;
        }

        // both have the same date
        if(strcmp(actDate.c_str(), stoActDate.c_str()) == 0){
            //cout << "j== " << j << endl;
            currentDate = actDate;
            bufferType = 3;

            //updateAct(myportfolio,actAction, actTicker, actShares, actPrice, dividendIncome, wait);
            //updateStoAct(myportfolio,stoActDividend, stoActSplit, stoActStock, dividendIncome, wait);
            i++;
            j++;
        }

        if(i > jsonAct.size())actDate = "9999-12-31";
        if(j > jsonStoAct.size())stoActDate = "9999-12-31";


        cout << "\ncurrent date: " << currentDate << endl;
        cout << "bufferType" << bufferType << endl;
        cout << "i: " << i << " j: " << j << endl;
        cout << "bufferdate: " << bufferDate << endl << endl; 
        if(currentDate!=bufferDate){ 
            updateAll(myportfolio, actBuffer,stoActBuffer,jsonAct,jsonStoAct, dividendIncome, bufferDate);
        }
        bufferDate = currentDate;
        if(bufferType == 1) actBuffer.push_back(i-1);
        else if(bufferType == 2) stoActBuffer.push_back(j-1);
        else if(bufferType == 3){
            actBuffer.push_back(i-1);
            stoActBuffer.push_back(j-1);
        }

        cout << "\n\n*******" << endl << endl;
    }
}

bool haveThisStock(vector<stock>& myportfolio, string ticker){
    for(int i = 0; i < myportfolio.size(); i++){
        if(myportfolio[i].ticker == ticker) return true;
    }
    return false;
}