#include <nlohmann/json.hpp>
#include <stock.h>
#ifndef UPDATESTOACT
#define UPDATESTOACT

bool updateStoAct(std::vector<stock>& mystocks, string dividend, string split, string stock);

#endif