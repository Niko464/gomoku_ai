#include <cstdio>

#include <GoProgram.hpp>
#include <iostream>

//Ideas: try to take advantage of the BEGIN command, you basicaly have 5 seconds of free calculation to start thinking ahead

#include <bitset>

int main() {
    /*GoProgram GoProgram;

    GoProgram.startInputLoop();*/


    /*
    Bitset checks:
    
    std::bitset<9> player("011110000");
    std::bitset<9> ai("000000011");

    std::bitset<9> test("011110000");
    std::bitset<9> sec_test("0111101111");

    //0 & 1 = 1
    //1 & 1 = 1
    //1 & 0 = 0
    //0 & 0 = 0

    std::cout << (ai ^ sec_test) << std::endl;
    
    if ((player & test) == test && (ai ^ sec_test) == sec_test) {
        std::cout << "YES" << std::endl;
    }*/

    /*
    Time manipulation test:

    auto startingTime = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    auto endingTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed = endingTime - startingTime;

    std::cout << "MESSAGE " << "test " << elapsed.count() * 1000 << " time" << std::endl;*/
    
    
    
    //Bitset comparaison test:
    
    std::bitset<9> map;

    map.set(0);
    map.set(1);
    map.set(2);
    map.set(8);

    std::bitset<9> straightDownCheck;
    straightDownCheck.set(0);
    straightDownCheck.set(1);
    straightDownCheck.set(2);

    std::cout << ((map & straightDownCheck) == straightDownCheck) << std::endl;
}

/*

_XXXX_                                          1000
_XX_X_    _X_XX_                                700
XXXX_     _XXXX      XXX_X    X_XXX     XX_XX   500
_XXX_     _X_XX      XX_X_                      200



*/