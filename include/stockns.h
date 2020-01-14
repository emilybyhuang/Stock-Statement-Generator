#include <nlohmann/json.hpp>
#include <iostream>
using nlohmann::json;

#ifndef STOCKNS
#define STOCKNS
namespace stockns {
    // a simple struct to model an action
    struct action {
		std :: string date;
		// int year;
		// int month;
		// int day; 
		std :: string action;
		double price;
		std :: string ticker;
        int shares;
    };
    void to_json(json& j, const action& currentaction); 

    void from_json(const json& j, action& currentaction);
} // namespace ns
#endif