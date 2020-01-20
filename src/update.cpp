#include <nlohmann/json.hpp>
#include <stockFunctions.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <update.h>
#include <iomanip>
#include <debug.h>
using namespace std;



double updateAct(std::vector<stock>& mystocks, nlohmann::json jsonAct, double& dividendIncome){
    string date = jsonAct["date"];
    //to do: check validity of date
    string action = jsonAct["action"];
    string ticker = jsonAct["ticker"];
    string price = jsonAct["price"];
    string shares = jsonAct["shares"];
    double profit;
    vector<stock>::iterator it = mystocks.begin();
    bool found = false;
    //check if the stock of the same ticker exists
    for (it = mystocks.begin(); it != mystocks.end();it++){
        if(ticker == it -> ticker){
            found = true;
            break;
        }
    }
    //1. Not found -> buy: add stock to portfolio
    //             -> sell: error message
    if(!found){
        if(action == "BUY"){
            stock *ns = new stock(ticker, stoi(shares),stod(price));
            mystocks.push_back(*ns);
        }else if(action == "SELL"){
            cout << "Error: stock with ticker " << ticker << " was not found." << endl;
        }else{  
            cout << "Error: the action " << action << " does not exist." << endl;
        }
        return 0;
    }
    //2. Found: update accordingly
    if(action == "BUY"){
        it -> price = ((it->price * it->shares) + (stod(price) * stoi(shares)))/(it->shares + stod(shares));
        it->shares += stoi(shares);
        return 0;
    }else if(action == "SELL"){
        int originalShares = 0;
        profit = stoi(shares) * stod(price) - (stoi(shares) * (it->price));
        originalShares = it->shares;
        it->shares = it->shares - stoi(shares);
        if(originalShares != 0 && it->shares == 0){
            it=mystocks.erase(it);
        }
        return profit;
    }
}

double updateStoAct(std::vector<stock>& mystocks, nlohmann::json jsonStoAct, double& dividendIncome){
    string ticker = jsonStoAct["stock"];
    string split = jsonStoAct["split"];
    string dividend = jsonStoAct["dividend"];
    if(!haveThisStock(mystocks,ticker)) return 0;
    if(!split.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == ticker){
                mystocks[i].shares = stoi(split) * mystocks[i].shares;
                mystocks[i].price = mystocks[i].price / stoi(split);
            }
        }   
    }
    if(!dividend.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == ticker){
                dividendIncome += mystocks[i].shares * stod(dividend);
            }
        }
    }
}

void updateAll(std::vector<stock>& mystocks, vector<int>& actBuffer,vector<int>& stoActBuffer,
const nlohmann::json & jsonAct, const nlohmann::json & jsonStoAct, double & dividendIncome, 
string & bufferDate){
    vector<double>profit;
    bool updated = false;
    //ignore the initialized bufferDate
    if(bufferDate == "0000/00/00") return;

    //update portfolio
    for(size_t i = 0; i < actBuffer.size(); i++){
        profit.push_back(updateAct(mystocks, jsonAct[actBuffer[i]], dividendIncome));
    }
    for(size_t j = 0; j < stoActBuffer.size(); j++){
        if(haveThisStock(mystocks,jsonStoAct[stoActBuffer[j]]["stock"])){
            updateStoAct(mystocks, jsonStoAct[stoActBuffer[j]], dividendIncome);
            updated = true;
        }
    }

    //print the updated portfolio
    if(profit.size()!= 0 || updated){
        boost::replace_all(bufferDate, "/", "-");
        cout << "On " << bufferDate << ", you have:" << endl;
        printPorfolio(mystocks,dividendIncome);
        cout << "  Transactions:" << endl;
    }
    
    //print the transactions
    for(size_t i = 0; i < actBuffer.size(); i++){
        printAct(mystocks, jsonAct[actBuffer[i]], profit[i]);
    }
    for(size_t j = 0; j < stoActBuffer.size(); j++){
        if(haveThisStock(mystocks,jsonStoAct[stoActBuffer[j]]["stock"])){
            printStoAct(mystocks, jsonStoAct[stoActBuffer[j]]);
        }
    }

    actBuffer.clear();
    stoActBuffer.clear();
    bufferDate.clear();
    profit.clear();
}