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
    
    
    /*
    Bitset comparaison test:
    
    std::bitset<9> map;

    map.set(1);
    map.set(4);
    map.set(7);

    std::bitset<9> straightDownCheck;
    straightDownCheck.set(0);
    straightDownCheck.set(3);
    straightDownCheck.set(6);

    std::cout << map << std::endl;
    std::cout << straightDownCheck << std::endl;
    straightDownCheck <<= 1;
    std::cout << (map == straightDownCheck) << std::endl;
    std::cout << straightDownCheck << std::endl;*/
}

/*

_XXXX_
_XX_X_    _X_XX_
XXXX_     _XXXX      XXX_X    X_XXX     XX_XX
_XXX_     _X_XX      XX_X_



*/