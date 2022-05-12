#include <iostream>
// #include "Reader.hpp"

#include "Atmosphere.hpp"

#define NORMAL_MODE
#ifdef NORMAL_MODE
int main()
{
    // std::cout << "Hello World!";
    // int ind = 0;
    // std::cin >> ind;
    std::string filename;
    std::cin >> filename;
    Atmosphere Atm(filename);
    // Atm.simulate(weather);
    // Layer test('s',2.22);
    // Atm.addLayer(test,2);
    unsigned int it = 0;
    Atm.print(it);
    it++;
    while (Atm.allElementsExits())
    {
        Atm.simulate();
        Atm.print(it);
        it++;
    }
}

#else
#define ASSERT_CONFIG_MAIN
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

int main()
{
    std::string filename = "input1.txt";
    Atmosphere Atm(filename);
    assertm(Atm.getSize() == 1, "TEST 01");
    std::cout << "TEST 01 COMPLETED" << std::endl;

    Layer test('x', 2.15);
    Atm.createLayer(test, 0);
    assertm(Atm.getSize() == 1, "TEST 02");
    std::cout << "TEST 02 COMPLETED" << std::endl;

    assertm(Atm.getSize() == 1, "TEST 03");
    std::cout << "TEST 03 COMPLETED" << std::endl;

    assertm(Atm.getSize() == 1, "TEST 04");
    std::cout << "TEST 04 COMPLETED" << std::endl;

    assertm(Atm.getSize() == 1, "TEST 05");
    std::cout << "TEST 05 COMPLETED" << std::endl;

    assertm(Atm.getSize() == 1, "TEST 06");
    std::cout << "TEST 06 COMPLETED" << std::endl;
}

#endif