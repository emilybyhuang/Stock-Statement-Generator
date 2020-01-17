#include <iostream>

using namespace std;
#ifndef SHARE
#define SHARE
class stock{
    public:
    string ticker;
    int shares;
    double price;
    // double value;
    stock (string ticker, int shares, double price);
    friend ostream &operator <<(ostream & output, const stock & stk);
};

#endif