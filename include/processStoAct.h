#include <iostream>
#include <stock.h>
using namespace std;

#ifndef PROCESSSTOACT
#define PROCESSSTOACT

bool processStoAct(vector<stock>& myportfolio, string jsonstr, string delimiter, double& dividendIncome);

#endif