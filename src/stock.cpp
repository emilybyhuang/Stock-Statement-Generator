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

#endif