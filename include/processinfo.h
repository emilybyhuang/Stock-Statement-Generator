#ifndef PROCESSINFO_H
#define PROCESSINFO_H
#include <iostream>
using namespace std;
nlohmann::json convertToJson(string);
void process(vector<stock>&, nlohmann::json&, nlohmann::json&, double);
bool checkValidDate(string date);
bool mainControl(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr);
#endif