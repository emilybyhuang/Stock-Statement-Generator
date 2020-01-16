#include <iostream>
#include <iomanip>
#include <stock.h>
#include <update.h>
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
    //printPorfolio(myportfolio, dividendIncome);
   // cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
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
        //cout << actDate << actAction << actPrice << actTicker << actShares << endl;
        //cout << stoActDate << stoActDividend << stoActSplit << stoActStock << endl;
        //cout << "i: " << i << " j: " << j << endl;
        // cout << jsonAct[i] << endl;
        // cout << jsonStoAct[j] << endl;

        // no action, but stock_action:
        if( (i > jsonAct.size()) && ( j< jsonStoAct.size())) {
            stoActDate = stoActDate.substr(0,10);
            boost::replace_all(stoActDate, "/", "-");
	    if( stoActDate != date0) {
	        cout << "On " << stoActDate << ", you have:" << endl;
		    date0 = stoActDate;
	    }
            updateStoAct(myportfolio, stoActDividend, stoActSplit, stoActStock, dividendIncome);
            j++;
            continue;
        }

        // no stock_action but action
        if( (j>jsonStoAct.size()) && ( i < jsonAct.size()) ) {
//	    cout << DBG << " no more stock action record" << endl;
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
	    if( stoActDate != date0) {
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
