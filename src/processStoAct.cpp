#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateStoAct.h>
#include <processStoAct.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
using namespace std;

bool processStoAct(vector<stock>& myportfolio, string jsonstr, string delimiter, double& dividendIncome){
    size_t position = 0;
    string date, dividend, split, stock;
    while (((position = jsonstr.find(delimiter)) != string::npos)) {
        string stockstring = jsonstr.substr(0, position);
        stockstring = stockstring + "}";
        jsonstr.erase(0, position + 1 + delimiter.length());
        boost::replace_all(stockstring, "\'", "\"");
        nlohmann::json stockaction = nlohmann::json::parse(stockstring);
        date = stockaction["date"];
        dividend = stockaction["dividend"];
        split = stockaction["split"];
        stock = stockaction["stock"];
        boost::replace_all(date, "/", "-");
        date = date.substr(0,10);
        cout << "On " << date << ", you have:" << endl;
        bool update = updateStoAct(myportfolio, dividend, split, stock, dividendIncome);
    }
    return true;
}