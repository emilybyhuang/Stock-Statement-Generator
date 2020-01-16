#include <iostream>
#include <iomanip>
#include <stock.h>
#include <updatestoact.h>
#include <updateact.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>

#ifndef PRINTPORTFOLIO
#define PRINTPORTFOLIO

void printPorfolio(vector<stock>& myportfolio, double dividendIncome);

#endif