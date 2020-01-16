#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateact.h>
#include <updatestoact.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <printportfolio.h>
#include <string.h>
#include <cstring>
#include <debug.h>

using namespace std;


nlohmann::json convertToJson(string);
nlohmann::json mergeTrans(nlohmann::json &);
void process(vector<stock>&, nlohmann::json, nlohmann::json, double);
void processStoAct(vector<stock>&, nlohmann::json);

bool mainControl(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr){
    double dividendIncome = 0.0;
    nlohmann::json jsonAct = convertToJson(jsonActStr);
    nlohmann::json jsonStoAct = convertToJson(jsonStoStr);
    // mergeTrans(jsonAct);
    // mergeTrans(jsonStoAct);
    process(myportfolio, jsonAct, jsonStoAct, dividendIncome);
    printPorfolio(myportfolio, dividendIncome);
   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
    return true;
}


nlohmann::json convertToJson(string str){
    replace(str.begin(), str.end(), '\'', '\"');
	nlohmann::json jsonarr = nlohmann::json::parse(str);
	cout << jsonarr << endl ;
	return jsonarr;
}

// nlohmann::json mergeTrans(nlohmann::json & jsonarr){
//     nlohmann::json * insertedJson = new nlohmann::json();
//     for(int i = 0; i < jsonarr.size(); i++){
//         for(int j = 0; j < insertedJson->size(); j++){
//             if((jsonarr[i]["date"]==(*insertedJson)[j]["date"]){
                
//             }
//         } 
//     }
//     return *insertedJson;
// }

void process(vector<stock>& myportfolio, nlohmann::json jsonAct, nlohmann::json jsonStoAct, double dividendIncome){
    string actDate, actAction, actPrice, actTicker, actShares;
    string stoActDate,stoActDividend, stoActSplit, stoActStock;
    //int count = jsonAct.size()+ jsonStoAct.size();
    int i = 0, j = 0;
    while(i < jsonAct.size() || j < jsonStoAct.size()){
        actDate = jsonAct[i]["date"];
        actAction = jsonAct[i]["action"];
        actPrice = jsonAct[i]["price"];
        actTicker = jsonAct[i]["ticker"];
        actShares = jsonAct[i]["shares"];
        stoActDate = jsonStoAct[j]["date"];
        stoActDividend = jsonStoAct[j]["dividend"];
        stoActSplit = jsonStoAct[j]["split"];
        stoActStock = jsonStoAct[j]["stock"];
        //cout << actDate << actAction << actPrice << actTicker << actShares << endl;
        //cout << stoActDate << stoActDividend << stoActSplit << stoActStock << endl;
        //cout << "i: " << i << " j: " << j << endl;
        // cout << jsonAct[i] << endl;
        // cout << jsonStoAct[j] << endl;
        if(j > jsonStoAct.size() || strcmp(actDate.c_str(), stoActDate.c_str()) < 0){
            cout << DBG << "1" << endl; 
            updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
            if(i!=0 && (actDate != jsonAct[i-1]["date"])){
                actDate = actDate.substr(0,10);
                boost::replace_all(actDate, "/", "-");
                cout << "On " << actDate << ", you have:" << endl;
            }
            i++;
        }else if(i > jsonAct.size() || strcmp(actDate.c_str(), stoActDate.c_str()) > 0){
            cout << "2" << endl;
            updateAct(myportfolio,actAction, actTicker, actShares, actPrice);
            if(j!=0 && (stoActDate != jsonStoAct[j-1]["date"])){
                stoActDate = stoActDate.substr(0,10);
                boost::replace_all(stoActDate, "/", "-");
                cout << "On " << stoActDate << ", you have:" << endl;
            }  
            j++;
        }else if(strcmp(actDate.c_str(), stoActDate.c_str()) == 0){
            cout << "3" << endl;
            updateAct(myportfolio,actAction, actTicker, actShares, actPrice);
            updateStoAct(myportfolio,stoActDividend, stoActSplit, stoActStock, dividendIncome);
            if(i!=0 && j!=0 && ((stoActDate != jsonStoAct[j-1]["date"])||(actDate != jsonAct[i-1]["date"]))){
                actDate = actDate.substr(0,10);
                boost::replace_all(actDate, "/", "-");
                cout << "On " << actDate << ", you have:" << endl;
            }
            i++;
            j++;
        }
    }
}
