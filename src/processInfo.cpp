#include <iostream>
#include <iomanip>
#include <stockFunctions.h>
#include <update.h>
#include <boost/algorithm/string.hpp>
#include <nlohmann/json.hpp>
#include <string.h>
#include <cstring>
#include <debug.h>

using namespace std;

void process(vector<stock>& myportfolio, nlohmann::json& jsonAct, nlohmann::json& jsonStoAct, double dividendIncome);
nlohmann::json convertToJson(string str);
bool checkValidDate(string date);

//main control functio for processing the action and stock action strings
bool mainControl(vector<stock>& myportfolio, string jsonActStr, string jsonStoStr){
    double dividendIncome = 0.0;
    nlohmann::json jsonAct = convertToJson(jsonActStr);
    nlohmann::json jsonStoAct = convertToJson(jsonStoStr);
    process(myportfolio, jsonAct, jsonStoAct, dividendIncome);
    return true;
}

//convert into json file format and parse into json arrays
nlohmann::json convertToJson(string str){
    replace(str.begin(), str.end(), '\'', '\"');
	nlohmann::json jsonarr = nlohmann::json::parse(str);
	return jsonarr;
}

//check for the validity of the date
bool checkValidDate(string date){
    string year = date.substr(0,4);
    string month = date.substr(5,2);
    string day = date.substr(8,2);
    if(stoi(year) < 0001 || stoi(month) < 01 || stoi(month) > 12 || stoi(day) < 01 || stoi(day) > 31){
        cout << "Invalid date" << endl;
        return false;
    }else{
        return true;
    }
}

void process(vector<stock>& myportfolio, nlohmann::json& jsonAct, nlohmann::json& jsonStoAct, double dividendIncome){
    string actDate, stoActDate, currentStock;
    bool validDate = true;
    int i = 0, j = 0;
    int oldI = i, oldJ = j;
    int bufferType;
    bool actDateValid, stoActDateValid;
    string bufferDate = "0000/00/00";
    string currentDate;
    vector<int> actBuffer;
    vector<int> stoActBuffer;
    do{

        //get the current dates, and check validity within
        if(i < jsonAct.size()){
            actDateValid = checkValidDate(jsonAct[i]["date"]);
            if(actDateValid){
                actDate = jsonAct[i]["date"];
                actDate = actDate.substr(0,10);
            } 
        }
        
        if(j < jsonStoAct.size()){
            stoActDateValid = checkValidDate(jsonStoAct[j]["date"]);   
            if(stoActDateValid){
                stoActDate = jsonStoAct[j]["date"];
                stoActDate = stoActDate.substr(0,10);
            }
        }

        //for invalid dates: increment to the next action or stock action
        if(!actDateValid)i++;
        if(!stoActDateValid) j++;
        if(actDateValid && stoActDateValid){
            oldI = i;
            oldJ = j;
            if((strcmp(actDate.c_str(), stoActDate.c_str()) < 0)){
                i++;
                currentDate = actDate;
                bufferType = 1;
            }
            
            //if stock action has earlier date
            if(( strcmp(actDate.c_str(), stoActDate.c_str()) > 0)){
                j++;
                currentDate = stoActDate;
                bufferType = 2;
            }

            // both have the same date
            if((strcmp(actDate.c_str(), stoActDate.c_str()) == 0)){
                i++;
                j++;
                currentDate = actDate;
                bufferType = 3;
            }

            //update the buffer(update the porfolio and print transactions done within the same day)
            if((currentDate != bufferDate) || ((oldI == jsonAct.size()) && (oldJ == jsonStoAct.size()))){ 
                updateAll(myportfolio, actBuffer, stoActBuffer,jsonAct,jsonStoAct, dividendIncome, bufferDate);
            }
            bufferDate = currentDate;

            //put the index of the action or stock action into their respective buffers(previously determined)
            if(bufferType == 1) actBuffer.push_back(i-1);
            else if(bufferType == 2) stoActBuffer.push_back(j-1);
            else if(bufferType == 3){
                actBuffer.push_back(i-1);
                stoActBuffer.push_back(j-1);
            }

            //if finished processing the string, set it to a very large date such that it will not be the next action acessed
            if(i >= jsonAct.size())actDate = "9999/12/31";
            if(j >= jsonStoAct.size())stoActDate = "9999/12/31";
        }
    }while(i <= jsonAct.size() || j <= jsonStoAct.size());
    actBuffer.clear();
    stoActBuffer.clear();
}
