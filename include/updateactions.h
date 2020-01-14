#include <nlohmann/json.hpp>
#include <stock.h>
#ifndef UPDATEACTIONS
#define UPDATEACTIONS

bool updateactions(std::vector<stock>& mystocks, string action, string ticker, string shares ,string price);

#endif