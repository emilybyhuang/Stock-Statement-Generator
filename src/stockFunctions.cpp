#include <iostream>
#include <iomanip>
#include <stockFunctions.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
using namespace std;

ostream & operator <<(ostream & output, const stock & stk){
    output << "    - " << stk.shares << " shares of " << stk.ticker << " at $" << fixed << setprecision(2) << stk.price << " per share";
    return output;
} 

stock::stock (string ticker, int shares, double price){
    this -> ticker = ticker;
    this -> shares = shares;
    this -> price = price;
}

void printPorfolio(vector<stock>& myportfolio, double dividendIncome){
    for(int i = 0; i < myportfolio.size(); i++){
        cout << myportfolio[i] << endl;
    }
    if(dividendIncome == 0.0) cout << "    - $0" << " of dividend income" << endl;
    else cout << "    - $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
}

void printAct(vector<stock>& mystocks, nlohmann::json jsonAct, double profit){
    bool increment = true;
    string action = jsonAct["action"];
    string shares = jsonAct["shares"];
    string ticker = jsonAct["ticker"];
    string price = jsonAct["price"];
    if(action == "BUY"){
        cout <<"    - You bought " << stoi(shares) << " shares of " << ticker << " at a price of $" << 
            fixed << setprecision(2) << stod(price) << " per share" << endl;
    }else if(action == "SELL"){
        string word;
        if(profit > 0) word = "profit";
        else word = "loss";
        cout << "    - You sold " << stoi(shares) << " shares of " << ticker << " at a price of $" << 
        fixed << setprecision(2) << stod(price) << " per share for a " << word << " of $" << profit << endl;
    }  
}

void printStoAct(vector<stock>& mystocks, nlohmann::json jsonStoAct){
    string split = jsonStoAct["split"];
    string dividend = jsonStoAct["dividend"];
    string stock = jsonStoAct["stock"];
    if(!split.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                cout <<"    - " << stock << " split " << split << " to 1, and you have " << mystocks[i].shares  << " shares" << endl;
            }
        }
    }
    if(!dividend.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                cout <<"    - " << stock << " paid out $" << fixed << setprecision(2) << stod(dividend) << 
                " dividend per share, and you have " << mystocks[i].shares << " shares" << endl;
            }
        }
    }
}

//To check if a stock of the same ticker as the one passed in is present in the portfolio
bool haveThisStock(vector<stock>& myportfolio, string ticker){
    for(int i = 0; i < myportfolio.size(); i++){
        if(myportfolio[i].ticker == ticker) return true;
    }
    return false;
}
