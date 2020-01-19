#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <update.h>
#include <iomanip>
#include <debug.h>
using namespace std;

void updateAct(std::vector<stock>& mystocks, nlohmann::json jsonAct, double& dividendIncome){
            cout << "&&&&&updating ok" << endl;

    string date = jsonAct["date"];
    //to do: check validity of date
    string action = jsonAct["action"];
    string ticker = jsonAct["ticker"];
    string price = jsonAct["price"];
    string shares = jsonAct["shares"];
    if(action == "BUY"){
        bool present = false;
        for (int i = 0; i < mystocks.size(); i++){
            if(ticker == mystocks[i].ticker){
                present = true;
                mystocks[i].price = ((mystocks[i].price * mystocks[i].shares) + (stod(price) * stoi(shares)))
                / (mystocks[i].shares + stod(shares));
                mystocks[i].shares += stoi(shares);
            }
        }
        if(present == false){
            stock *ns = new stock(ticker, stoi(shares),stod(price));
            mystocks.push_back(*ns);
        }
        if(!wait){
            cout << "updateAct Buy" << endl;
            printPorfolio(mystocks, dividendIncome);
            cout << "  Transactions:" << endl;
        }
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
                if(!wait){
                    cout << "updateAct sell " << endl;
                    printPorfolio(mystocks, dividendIncome);
                    cout << "  Transactions:" << endl;
                }
                //cout <<'\t' << "- You sold " << stoi(shares) << " of " << ticker << " at a price of $" << 
                //fixed << setprecision(2) << stod(price) << " per share for a " << word << " of $" << 
                //worth - (stoi(shares) * (it->price)) << endl;
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

void updateStoAct(std::vector<stock>& mystocks, nlohmann::json jsonStoAct, double& dividendIncome){
            cout << "&&&&&updating ok" << endl;

    //cout << "stock, wait: " << stock << wait << endl;
    string stock = jsonStoAct["stock"];
    string split = jsonStoAct["split"];
    string dividend = jsonStoAct["dividend"];
    if(!split.empty()){
        for(int i = 0; i < mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
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
            if(mystocks[i].ticker == stock){
                dividendIncome += mystocks[i].shares * stod(dividend);
                if(!wait){
                    cout << "updateStoAct dividend" << endl;
                    printPorfolio(mystocks, dividendIncome);
                    cout << "  Transactions:" << endl;
                }
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
    if(bufferDate == "0000/00/00") return;
    cout << DBG << endl;
    cout << actBuffer.size() << endl;
    cout << stoActBuffer.size() << endl;
    for(size_t i = 0; i < actBuffer.size(); i++){
        updateAct(mystocks, jsonAct[actBuffer[i]], dividendIncome);
    }
    for(size_t j = 0; j < stoActBuffer.size(); j++){
        updateStoAct(mystocks, jsonStoAct[stoActBuffer[j]], dividendIncome);
    }
    printPorfolio(mystocks,dividendIncome);
    for(size_t i = 0; i < actBuffer.size(); i++){
        printAct(mystocks, jsonAct[actBuffer[i]]);
    }
    for(size_t j = 0; j < stoActBuffer.size(); j++){
        printStoAct(mystocks, jsonStoAct[stoActBuffer[j]]);
    }
    actBuffer.clear();
    stoActBuffer.clear();
    bufferDate.clear();
}
