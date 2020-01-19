#ifndef UPDATE
#define UPDATE
#include <nlohmann/json.hpp>
#include <stock.h>

using namespace std;
bool haveThisStock(vector<stock>& myportfolio, string ticker);
void updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares ,string price, double dividendIncome, bool wait);
void updateStoAct(std::vector<stock>& mystocks, string dividend, string split, string stock, double& dividendIncome, bool wait);
void updateAll(std::vector<stock>& mystocks, vector<int>& actBuffer,vector<int>& stoActBuffer,const nlohmann::json & jsonAct,
const nlohmann::json & jsonStoAct, double & dividendIncome, string & bufferDate);

#endif