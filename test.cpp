#include <iostream>

int main()
{
    double tmp = 5;
    int i = 1;
    while (tmp > 0.5)
    {
        tmp -= tmp*0.05;
        std::cout << i << ". " << tmp << std::endl;
        i++;
    }
}