#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <updateAct.h>
bool updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares, string price){
    //cout << "update size" << mystocks.size(); 
    if(action == "BUY"){
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                mystocks[i].shares += stoi(shares);
            }
        }
        stock newstock(ticker, stoi(shares),stod(price));
        mystocks.push_back(newstock);
        cout <<"size:" << mystocks.size();
        for (int i = 0; i < mystocks.size(); i++){
            cout << mystocks[i] << endl;
        } 
    }else if (action == "SELL"){
        bool found = false;
        cout <<"size:" << mystocks.size();
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                found = true;
                mystocks[i].shares -= stoi(shares);
            }
        }
        if(!found) {
            cout << "Error: dont have stocks with this ticker" << endl;
            return false;
        }
    }
    
    return true;
}