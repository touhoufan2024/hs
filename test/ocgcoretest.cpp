#include<bits/stdc++.h>

#include "ocgapi.h"
#include "duel.h"
#include "interpreter.h"


using namespace std;



int main() {

    duel* myduel = (duel*)create_duel(100);
    lua_State* L = myduel->lua->lua_state;

    auto version = lua_version(L);
    cout << "Lua version: " << version << endl;

    start_duel((intptr_t)myduel, 0x00010000); // Example options


    process((intptr_t)myduel);

    cout << " hello " << endl;
    return 0;
}
