#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <update.h>
#include <iomanip>

void updateAct(std::vector<stock>& mystocks, string action, string ticker, string shares, string price, double dividendIncome){
    //cout << "update size" << mystocks.size(); 
    if(action == "BUY"){
        bool present = false;
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                present = true;
                mystocks[i].price = ((mystocks[i].price * mystocks[i].shares) + (stod(price) * stoi(shares)))
                / (mystocks[i].shares + stod(shares));
                mystocks[i].shares += stoi(shares);
                //cout << "current price/stock: " << mystocks[i].price <<endl;
                //cout << "current shares: " << mystocks[i].shares << endl;
            }
        }
        if(present == false){
            stock *ns = new stock(ticker, stoi(shares),stod(price));
            mystocks.push_back(*ns);
        }
        printPorfolio(mystocks, dividendIncome);
        cout << "  Transactions:" << endl;
        cout <<'\t' << "- You bought " << stoi(shares) << " of " << ticker << " at a price of $" << 
        fixed << setprecision(2) << stod(price) << " per share" << endl;
    }else if (action == "SELL"){
        bool found = false;
        int original = 0;
        bool increment = true;
        for (auto it = mystocks.begin(); it != mystocks.end();){
            increment = true;
            if(ticker == it -> ticker){
                found = true;
                double worth = stoi(shares) * stod(price);
                string word;
                if(worth > (stoi(shares) * (it->price))) word = "profit";
                else word = "loss";
                original = it -> shares;
                it->shares = it->shares - stoi(shares);
                if(original != 0 && it->shares == 0){
                    increment = false;
                    it = mystocks.erase(it);
                }
                printPorfolio(mystocks, dividendIncome);
                cout << "  Transactions:" << endl;
                cout <<'\t' << "- You sold " << stoi(shares) << " of " << ticker << " at a price of $" << 
                fixed << setprecision(2) << stod(price) << " per share for a " << word << " of $" << 
                worth - (stoi(shares) * (it->price)) << endl;
            }
            if(increment) it++;
        }
        if(!found) {
            cout << "Error: dont have stocks with this ticker" << endl;
            return;
        }
    }
    return;
}

void updateStoAct(std::vector<stock>& mystocks, string dividend, string split, string stock, double& dividendIncome){
    if(!split.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                mystocks[i].shares = stoi(split) * mystocks[i].shares;
                mystocks[i].price = mystocks[i].price / stoi(split);
                printPorfolio(mystocks, dividendIncome);
                cout << "  Transactions:" << endl;
                cout <<'\t' << "- " << stock << " split " << split << " to 1, and you have " << mystocks[i].shares  << " shares" << endl;
		        break;
            }
        }   
    }
    if(!dividend.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                dividendIncome += mystocks[i].shares * stod(dividend);
                printPorfolio(mystocks, dividendIncome);
                cout << "  Transactions:" << endl;
                cout <<'\t' << "- " << stock << " paid out $" << fixed << setprecision(2) << stod(dividend) << 
                " per share, and you have " << mystocks[i].shares << " shares" << endl;
		        break;
            }
        }
    }

}
