#ifndef STOCK_H
#define STOCK_H
#include <iostream>

using namespace std;
class stock{
    public:
    string ticker;
    int shares;
    double price;
    // double value;
    stock (string ticker, int shares, double price);
    friend ostream &operator <<(ostream & output, const stock & stk);
};
void printPorfolio(vector<stock>& myportfolio, double dividendIncome);
#endif
