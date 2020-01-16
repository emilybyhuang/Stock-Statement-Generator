#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <updateact.h>
#include <iomanip>

void updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares, string price){
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
            stock *ns = new stock(ticker, stoi(shares),stod(price));
            mystocks.push_back(*ns);
        }
        cout <<'\t' << "- You bought " << stoi(shares) << " of " << ticker << " at a price of $" << 
        fixed << setprecision(2) << stod(price) << " per share" << endl;
    }else if (action == "SELL"){
        bool found = false;
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                found = true;
                double worth = stoi(shares) * stod(price);
                string word;
                if(worth > (stoi(shares) * (mystocks[i].price))) word = "profit";
                else word = "loss";
                mystocks[i].shares = mystocks[i].shares - stoi(shares);
                cout <<'\t' << "- You sold " << stoi(shares) << " of " << ticker << " at a price of $" << 
                fixed << setprecision(2) << stod(price) << " per share for a " << word << " of $" << 
                worth - (stoi(shares) * (mystocks[i].price)) << endl;
            }
        }
        if(!found) {
            cout << "Error: dont have stocks with this ticker" << endl;
            return;
        }
    }
    return;
}