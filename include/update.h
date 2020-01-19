#ifndef UPDATE
#define UPDATE
#include <nlohmann/json.hpp>
#include <stock.h>

using namespace std;
double updateAct(std::vector<stock>& mystocks, nlohmann::json jsonAct, double& dividendIncome);
double updateStoAct(std::vector<stock>& mystocks, nlohmann::json jsonStoAct, double& dividendIncome);
void updateAll(std::vector<stock>& mystocks, vector<int>& actBuffer,vector<int>& stoActBuffer,const nlohmann::json & jsonAct,
const nlohmann::json & jsonStoAct, double & dividendIncome, string & bufferDate);

#endif