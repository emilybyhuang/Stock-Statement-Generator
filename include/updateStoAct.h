#include <nlohmann/json.hpp>
#include <stock.h>

using namespace std;

#ifndef UPDATESTOACT
#define UPDATESTOACT

bool updateStoAct(std::vector<stock>& mystocks, string dividend, string split, string stock, double& dividendIncome);
#endif