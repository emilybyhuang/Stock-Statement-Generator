#include <nlohmann/json.hpp>
#include <iostream>
using namespace std;

#ifndef TRANSACTION
#define TRANSACTION

void transaction(string action, string ticker, string shares ,string price);
#endif