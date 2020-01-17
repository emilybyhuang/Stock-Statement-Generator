#include <iostream>
#include <iomanip>
#include <stock.h>
using namespace std;
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