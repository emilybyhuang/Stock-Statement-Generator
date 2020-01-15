#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updateStoAct.h>
#include <processStoAct.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <printPortfolio.h>

void printPorfolio(vector<stock>& myportfolio, double dividendIncome){
    for(int i = 0; i < myportfolio.size(); i++){
        cout << myportfolio[i] << endl;
    }
    cout << '\t' << "- $" << fixed << setprecision(2) << dividendIncome << " of dividend income" << endl;
}