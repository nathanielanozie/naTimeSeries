
#include "testing.h"

int main()
{
    sma_test();
    wma_test();
    return 0;
}

//g++ -std=c++11 utils.cpp testing.cpp main.cpp moving_average.cpp simple_moving_average.cpp weighted_moving_average.cpp -o prog
