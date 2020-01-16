#include <nlohmann/json.hpp>
#include <stock.h>
#ifndef UPDATEACT
#define UPDATEACT

void updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares ,string price);

#endif