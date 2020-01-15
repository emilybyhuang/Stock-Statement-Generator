#include <nlohmann/json.hpp>
#include <stock.h>
#include <boost/algorithm/string.hpp>
#include <typeinfo>
#include <updateAct.h>
#include <iomanip>


bool updateStoAct(std::vector<stock>& mystocks, string dividend, string split, string stock, double& dividendIncome){
    if(!split.empty()){
        for(int i = 0; i< mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                mystocks[i].shares = stoi(split) * mystocks[i].shares;
                mystocks[i].price = mystocks[i].price / stoi(split);
                cout <<'\t' << "- " << stock << " split " << split << " to 1, and you have " << mystocks[i].shares * stoi(split) << endl;
            }
        }   
    }else if(!dividend.empty()){
        for(int i = 0; i< mystocks.size(); i++){
            if(mystocks[i].ticker == stock){
                dividendIncome += mystocks[i].shares * stod(dividend);
                cout <<'\t' << "- " << stock << " paid out $" << fixed << setprecision(2) << stod(dividend) << 
                " per share, and you have " << mystocks[i].shares << " shares" << endl;
            }
        }
    }


    return true;

}