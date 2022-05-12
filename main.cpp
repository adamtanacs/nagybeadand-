#include <iostream>
// #include "Reader.hpp"

#include "Atmosphere.hpp"

// #define NORMAL_MODE
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

int cycle(Atmosphere &Atm)
{
    unsigned it = 0;
    Atm.print(it);
    it++;
    while (Atm.allElementsExits())
    {
        Atm.simulate();
        // Atm.print(it);
        it++;
    }
    std::cout << "END:" << std::endl;
    it--;
    Atm.print(it);
    return it;
}

int main()
{
    // TEST 1
    #define EPSILON 1000
    std::string filename = "input1.txt";
    Atmosphere Atm(filename);
    int iter = cycle(Atm);
    assertm(round(Atm.getLayer(0).getSize()*EPSILON)/EPSILON == 1.5550, "TEST 01");
    assertm(iter == 0, "TEST 01 ITERATIONS");
    std::cout << std::endl << "TEST 01 COMPLETED" << std::endl << std::endl;

    // TEST 2

    filename = "input2.txt";
    Atmosphere Atm2(filename);
    cycle(Atm2);
    assertm(round(Atm2.getLayer(0).getSize()*EPSILON)/EPSILON == 1.5550, "TEST 02A");
    assertm(round(Atm2.getLayer(1).getSize()*EPSILON)/EPSILON == 3.1200, "TEST 02B");
    assertm(iter == 0, "TEST 02 ITERATIONS");
    std::cout << std::endl << "TEST 02 COMPLETED" << std::endl << std::endl;

    // TEST 3

    filename = "input3.txt";
    Atmosphere Atm3(filename);
    cycle(Atm3);
    assertm(round(Atm3.getLayer(0).getSize()*EPSILON)/EPSILON == 2.33 && 
             Atm3.getLayer(0).getName() == oxigen, "TEST 03A");
    assertm(round(Atm3.getLayer(1).getSize()*EPSILON)/EPSILON == 3.1200 &&
             Atm3.getLayer(1).getName() == ozon, "TEST 03B");
    assertm(round(Atm3.getLayer(2).getSize()*EPSILON)/EPSILON == 1.78 &&
             Atm3.getLayer(2).getName() == oxigen, "TEST 03C");
    assertm(iter == 0, "TEST 03 ITERATIONS");
    std::cout << std::endl << "TEST 03 COMPLETED" << std::endl << std::endl;

    filename = "input4.txt";
    Atmosphere Atm4(filename);
    iter = cycle(Atm4);
    assertm(round(Atm4.getLayer(0).getSize()*EPSILON)/EPSILON == 1.675 && 
            Atm4.getLayer(0).getName() == oxigen, "TEST 04A");
    assertm(Atm4.getLayer(1).getSize() == 5 &&
             Atm4.getLayer(1).getName() == ozon, "TEST 04B");
    assertm(iter == 45, "TEST 04 ITERATIONS");
    std::cout << std::endl << "TEST 04 COMPLETED" << std::endl << std::endl;

    // TEST 5

    filename = "input5.txt";
    Atmosphere Atm5(filename);
    iter = cycle(Atm5);
    assertm(round(Atm5.getLayer(0).getSize()*EPSILON)/EPSILON == 9.006 && 
            Atm5.getLayer(0).getName() == dioxid, "TEST 05A");
    assertm(Atm5.getLayer(1).getSize() == 5 &&
             Atm5.getLayer(1).getName() == dioxid, "TEST 05B");
    assertm(iter == 45, "TEST 05 ITERATIONS");
    std::cout << std::endl << "TEST 05 COMPLETED" << std::endl << std::endl;

    // TEST 6

    filename = "input6.txt";
    Atmosphere Atm6(filename);
    iter = cycle(Atm6);
    assertm(round(Atm6.getLayer(0).getSize()*EPSILON)/EPSILON == 4.688 && 
            Atm6.getLayer(0).getName() == ozon, "TEST 06A");
    assertm(round(Atm6.getLayer(1).getSize()*EPSILON)/EPSILON == 5 &&
             Atm6.getLayer(1).getName() == ozon, "TEST 06B");
    assertm(round(Atm6.getLayer(2).getSize()*EPSILON)/EPSILON &&
             Atm6.getLayer(2).getName() == dioxid, "TEST 06C");
    assertm(iter == 4, "TEST 06 ITERATIONS");
    std::cout << std::endl << "TEST 06 COMPLETED" << std::endl << std::endl;

    // TEST 7

    filename = "input7.txt";
    Atmosphere Atm7(filename);
    iter = cycle(Atm7);
    assertm(round(Atm7.getLayer(0).getSize()*EPSILON)/EPSILON == 7.828 && 
            Atm7.getLayer(0).getName() == ozon, "TEST 07A");
    assertm(round(Atm7.getLayer(1).getSize()*EPSILON)/EPSILON == 1.675 &&
             Atm7.getLayer(1).getName() == oxigen, "TEST 07B");
    assertm(round(Atm7.getLayer(2).getSize()*EPSILON)/EPSILON == 5 &&
             Atm7.getLayer(2).getName() == ozon, "TEST 07C");
    assertm(iter == 15, "TEST 07 ITERATIONS");
    std::cout << std::endl << "TEST 07 COMPLETED" << std::endl << std::endl;

    // TEST 08

    filename = "input8.txt";
    Atmosphere Atm8(filename);
    iter = cycle(Atm8);
    assertm(round(Atm8.getLayer(0).getSize()*EPSILON)/EPSILON == 9.006 && 
            Atm8.getLayer(0).getName() == dioxid, "TEST 08A");
    assertm(round(Atm8.getLayer(1).getSize()*EPSILON)/EPSILON == 5 &&
             Atm8.getLayer(1).getName() == dioxid, "TEST 08B");
    assertm(iter == 15, "TEST 08 ITERATIONS");
    std::cout << std::endl << "TEST 08 COMPLETED" << std::endl << std::endl;
}

#endif