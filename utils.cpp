
#include <iostream>
#include <vector>
#include <cmath>

#include "utils.h"

void printVector(std::vector<double> &v1)
{
    for(unsigned int i=0; i<v1.size(); i++)
    {
        printf("%f\n", v1[i]);
    }
}

double MeanAbsoluteDeviationAccuracy::accuracy(std::vector<double> &v1, std::vector<double> &v2)
{
    if(v1.size() != v2.size())
        throw std::runtime_error("requires equal length input");

    double sum = 0.0;
    for(unsigned int i=0; i<v1.size(); i++)
    {
        //printf("%f - %f\n", v1[i], v2[i]);
        sum += std::abs(v1[i] - v2[i]);
    }

    //printf("sum>>>>:%f\n", sum);
    return float(sum/v1.size());
}


double MeanSquareErrorAccuracy::accuracy(std::vector<double> &v1, std::vector<double> &v2)
{
    if(v1.size() != v2.size())
        throw std::runtime_error("requires equal length input");

    double sum = 0.0;
    for(unsigned int i=0; i<v1.size(); i++)
    {
        //printf("%f - %f\n", v1[i], v2[i]);
        sum += (v1[i] - v2[i])*(v1[i] - v2[i]);
    }

    //printf("sum>>>>:%f\n", sum);
    return float(sum/v1.size());
}

