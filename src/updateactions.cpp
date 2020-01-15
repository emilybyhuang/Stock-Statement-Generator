#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
bool updateactions(std::vector<stock>& mystocks, string action, string ticker, string shares, string price){
    //cout << "update size" << mystocks.size(); 
    if(action == "BUY"){
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                //cout << "buying shares" << endl;
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
                //cout << "selling shares" << endl;
                mystocks[i].shares -= stoi(shares);
            }
        }
        if(!found) cout << "Error: dont have this share" << endl;
    }
    
    return true;
}