#include <nlohmann/json.hpp>
#include <stock.h>

using namespace std;

#ifndef UPDATE
#define UPDATE
void updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares ,string price, double dividendIncome);
void updateStoAct(std::vector<stock>& mystocks, string dividend, string split, string stock, double& dividendIncome);
#endif