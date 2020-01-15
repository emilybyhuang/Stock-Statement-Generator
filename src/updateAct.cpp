#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <updateAct.h>
#include <iomanip>

bool updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares, string price){
    //cout << "update size" << mystocks.size(); 
    if(action == "BUY"){
        bool present = false;
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                present = true;
                mystocks[i].shares += stoi(shares);
            }
        }
        if(present == false){
            stock newstock(ticker, stoi(shares),stod(price));
            mystocks.push_back(newstock);
        }
        cout <<'\t' << "- You bought " << stoi(shares) << " of " << ticker << " at a price of $" << fixed << setprecision(2) << stod(price) << "per share" << endl;
    }else if (action == "SELL"){
        bool found = false;
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