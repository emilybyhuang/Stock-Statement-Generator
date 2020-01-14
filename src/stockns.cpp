#include <nlohmann/json.hpp>
#include <iostream>
using nlohmann::json;

namespace stockns {
    // a simple struct to model an action
    struct action {
		std :: string date;
		// int year;
		// int month;
		// int day; 
		std :: string action;
		double price;
		std::string ticker;
        int shares;
    };
    void to_json(json& j, const action& currentaction) {
        j = json{{"date", currentaction.date}, {"action", currentaction.action}, {"price", currentaction.price}, 
        {"ticker", currentaction.ticker}, {"shares", currentaction.shares}};
    }

    void from_json(const json& j, action& currentaction) {
        j.at("date").get_to(currentaction.date);
        j.at("action").get_to(currentaction.action);
        j.at("price").get_to(currentaction.price);
        j.at("ticker").get_to(currentaction.ticker);
        j.at("shares").get_to(currentaction.shares);
    }
} // namespace ns