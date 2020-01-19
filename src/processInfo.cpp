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
void process(vector<stock>&, nlohmann::json&, nlohmann::json&, double);
void processStoAct(vector<stock>&, nlohmann::json);

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
	return jsonarr;
}

void process(vector<stock>& myportfolio, nlohmann::json& jsonAct, nlohmann::json& jsonStoAct, double dividendIncome){
    string actDate, stoActDate, currentStock;
    bool printPortfolio = false;
    int i = 0, j = 0;
    int oldI = i, oldJ = j;
    int bufferType;
    string bufferDate = "0000/00/00";
    string currentDate;
    vector<int> actBuffer;
    vector<int> stoActBuffer;
    do{
        oldI = i;
        oldJ = j;
        if(i < jsonAct.size()){
            actDate = jsonAct[i]["date"];
            actDate = actDate.substr(0,10);
        }
        
        if(j < jsonStoAct.size()){
            stoActDate = jsonStoAct[j]["date"];
            stoActDate = stoActDate.substr(0,10);
        }

        // else has action and stock action strings: 
        // action has earlier date
        if(strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
            currentDate = actDate;
            bufferType = 1;
            i++;
        }
        
        //stock action has earlier date
        if( strcmp(actDate.c_str(), stoActDate.c_str()) > 0){
            currentDate = stoActDate;
            bufferType = 2;
            j++;
        }

        // both have the same date
        if(strcmp(actDate.c_str(), stoActDate.c_str()) == 0){
            currentDate = actDate;
            bufferType = 3;
            i++;
            j++;
        }

        if(i >= jsonAct.size())actDate = "9999/12/31";
        if(j >= jsonStoAct.size())stoActDate = "9999/12/31";

        if((currentDate != bufferDate) || ((oldI == jsonAct.size()) && (oldJ == jsonStoAct.size()))){ 
            updateAll(myportfolio, actBuffer,stoActBuffer,jsonAct,jsonStoAct, dividendIncome, bufferDate);
        }
        bufferDate = currentDate;
        if(bufferType == 1) actBuffer.push_back(i-1);
        else if(bufferType == 2) stoActBuffer.push_back(j-1);
        else if(bufferType == 3){
            actBuffer.push_back(i-1);
            stoActBuffer.push_back(j-1);
        }
        //cout << "\n\n*******" << endl << endl;
    }while(i <= jsonAct.size() || j <= jsonStoAct.size());
}

