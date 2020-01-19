#include <iostream>
#include <iomanip>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>

using namespace std;

#ifndef STOCK
#define STOCK
ostream & operator <<(ostream & output, const stock & stk){
    output << '\t' << "- " << stk.shares << " shares of " << stk.ticker << " at $" << fixed << setprecision(2) << stk.price << " per share";
    return output;
} 

stock::stock (string ticker, int shares, double price){
    this -> ticker = ticker;
    this -> shares = shares;
    this -> price = price;
    //this -> value = this -> value + (shares*price);
}

void printPorfolio(vector<stock>& myportfolio, double dividendIncome){
    for(int i = 0; i < myportfolio.size(); i++){
        cout << myportfolio[i] << endl;
    }
    cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
}

void printAct(vector<stock>& mystocks, nlohmann::json jsonAct){
    bool increment = true;
    string action = jsonAct["action"];
    string shares = jsonAct["shares"];
    string ticker = jsonAct["ticker"];
    string price = jsonAct["price"];
    if(action == "BUY"){
        cout <<'\t' << "- You bought " << stoi(shares) << " of " << ticker << " at a price of $" << 
            fixed << setprecision(2) << stod(price) << " per share" << endl;
    }else if(action == "SELL"){
        string word;
        int original = 0;
        bool increment = true;
        for (auto it = mystocks.begin(); it != mystocks.end();){
            increment = true;
            if(ticker == it -> ticker){
                double worth = stoi(shares) * stod(price);
                if(worth > (stoi(shares) * (it->price))) word = "profit";
                else word = "loss";
                cout <<'\t' << "- You sold " << stoi(shares) << " of " << ticker << " at a price of $" << 
                fixed << setprecision(2) << stod(price) << " per share for a " << word << " of $" << 
                worth - (stoi(shares) * (it->price)) << endl;
            }
            if(increment) it++;
        }
    }  
}

void printStoAct(vector<stock>& mystocks, nlohmann::json jsonStoAct){
    string split = jsonStoAct["split"];
    string dividend = jsonStoAct["dividend"];
    string stock = jsonStoAct["stock"];
    if(!split.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                cout <<'\t' << "- " << stock << " split " << split << " to 1, and you have " << mystocks[i].shares  << " shares" << endl;
            }
        }
    }
    if(!dividend.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                cout <<'\t' << "- " << stock << " paid out $" << fixed << setprecision(2) << stod(dividend) << 
                " per share, and you have " << mystocks[i].shares << " shares" << endl;
                break;
            }
        }
    }
}
#endif