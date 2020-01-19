#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <update.h>
#include <iomanip>
#include <debug.h>
using namespace std;



double updateAct(std::vector<stock>& mystocks, nlohmann::json jsonAct, double& dividendIncome){
    string date = jsonAct["date"];
    //to do: check validity of date
    string action = jsonAct["action"];
    string ticker = jsonAct["ticker"];
    string price = jsonAct["price"];
    string shares = jsonAct["shares"];
    double profit;
    if(action == "BUY"){
        bool present = false;
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                present = true;
                mystocks[i].price = ((mystocks[i].price * mystocks[i].shares) + (stod(price) * stoi(shares)))
                / (mystocks[i].shares + stod(shares));
                mystocks[i].shares += stoi(shares);
                double worth = mystocks[i].shares * mystocks[i].price;
            }
        }
        if(present == false){
            stock *ns = new stock(ticker, stoi(shares),stod(price));
            mystocks.push_back(*ns);
        }
        return 0;
        //cout <<'\t' << "- You bought " << stoi(shares) << " of " << ticker << " at a price of $" << 
            //fixed << setprecision(2) << stod(price) << " per share" << endl;
    }else if (action == "SELL"){
        bool found = false;
        int original = 0;
        bool increment = true;
        for (auto it = mystocks.begin(); it != mystocks.end();){
            increment = true;
            if(ticker == it -> ticker){
                found = true;
                profit = stoi(shares) * stod(price);
                string word;
                if(profit > (stoi(shares) * (it->price))) word = "profit";
                else word = "loss";
                profit = (stoi(shares) * stod(price)) - (stoi(shares) * it -> price);
                
                original = it -> shares;
                it->shares = it->shares - stoi(shares);
                if(original != 0 && it->shares == 0){
                    increment = false;
                    it = mystocks.erase(it);
                }
                //cout <<'\t' << "- You sold " << stoi(shares) << " of " << ticker << " at a price of $" << 
                //fixed << setprecision(2) << stod(price) << " per share for a " << word << " of $" << 
                //worth - (stoi(shares) * (it->price)) << endl;
            }
            if(increment) it++;
        }
        if(!found) {
            cout << "Error: dont have stocks with this ticker" << endl;
            return 0;
        }
        return profit;
    }
}

double updateStoAct(std::vector<stock>& mystocks, nlohmann::json jsonStoAct, double& dividendIncome){
    cout << "&&&&&updating ok" << endl;
    //cout << "stock, wait: " << stock << wait << endl;
    string ticker = jsonStoAct["stock"];
    string split = jsonStoAct["split"];
    string dividend = jsonStoAct["dividend"];
    if(!haveThisStock(mystocks,ticker)) return 0;
    if(!split.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == ticker){
                mystocks[i].shares = stoi(split) * mystocks[i].shares;
                mystocks[i].price = mystocks[i].price / stoi(split);
                if(!wait){
                    cout << "updateStoAct split" << endl;
                    printPorfolio(mystocks, dividendIncome);
                    cout << "  Transactions:" << endl;
                }
                //cout <<'\t' << "- " << stock << " split " << split << " to 1, and you have " << mystocks[i].shares  << " shares" << endl;
		        break;
            }
        }   
    }
    if(!dividend.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == ticker){
                dividendIncome += mystocks[i].shares * stod(dividend);
                //cout <<'\t' << "- " << stock << " paid out $" << fixed << setprecision(2) << stod(dividend) << 
                //" per share, and you have " << mystocks[i].shares << " shares" << endl;
		        break;
            }
        }
    }
}

void updateAll(std::vector<stock>& mystocks, vector<int>& actBuffer,vector<int>& stoActBuffer,
const nlohmann::json & jsonAct, const nlohmann::json & jsonStoAct, double & dividendIncome, 
string & bufferDate){
    vector<double>profit;
    if(bufferDate == "0000/00/00") return;
    cout << DBG << endl;
    cout << actBuffer.size() << endl;
    cout << stoActBuffer.size() << endl;
    for(size_t i = 0; i < actBuffer.size(); i++){
        cout << "jsonAct[actBuffer[i]] " << jsonAct[actBuffer[i]] << endl;
        profit.push_back(updateAct(mystocks, jsonAct[actBuffer[i]], dividendIncome));
    }
    for(size_t j = 0; j < stoActBuffer.size(); j++){
        //if(!haveThisStock(mystocks, jsonStoAct[j]["ticker"])) break; 
        cout << "jsonStoAct[stoActBuffer[j]] " << jsonStoAct[stoActBuffer[j]] << endl;
        updateStoAct(mystocks, jsonStoAct[stoActBuffer[j]], dividendIncome);
    }
    printPorfolio(mystocks,dividendIncome);
    for(size_t i = 0; i < actBuffer.size(); i++){
        //cout << "print act trans" <<endl;
        printAct(mystocks, jsonAct[actBuffer[i]], profit[i]);
    }
    for(size_t j = 0; j < stoActBuffer.size(); j++){
        if(haveThisStock(mystocks,jsonStoAct[stoActBuffer[j]]["stock"])){
            //cout << "print sto act trans" <<endl;
            printStoAct(mystocks, jsonStoAct[stoActBuffer[j]], 0.0);
        }
    }
    
    actBuffer.clear();
    stoActBuffer.clear();
    bufferDate.clear();
}
