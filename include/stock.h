#ifndef STOCK_H
#define STOCK_H
#include <iostream>
#include <nlohmann/json.hpp>

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
void printAct(vector<stock>& mystocks, nlohmann::json jsonAct, double);
void printStoAct(vector<stock>& mystocks, nlohmann::json jsonStoAct, double);
bool haveThisStock(vector<stock>& myportfolio, string ticker);
#endif

