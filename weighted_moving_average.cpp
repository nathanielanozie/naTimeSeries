/*simple moving average prediction model for single vector time series

//please modify/use at your own risk
*/

#include <iostream>
#include <vector>

#include <numeric>
#include <algorithm>

#include "weighted_moving_average.h"


/*compute weighted average of input vector. not equal weights
*/
double WeightedMovingAverage::_compute(std::vector<double> &vec)
{
	//assert input at least 1 element
	int n = vec.size();

    //get vector n to 1
    std::vector<double> weightNumerator(n); //resize to vector of n elements
    std::iota(weightNumerator.begin(), weightNumerator.end(), 1); //1,2, ...n
    std::reverse(weightNumerator.begin(), weightNumerator.end()); //n, n-1 ... 1

    //total the numerator so we can divide by it and have weights summing to 1
    double weightDenominator = std::accumulate(weightNumerator.begin(), weightNumerator.end(), 0); //0 is for start of sum

    double sum = 0.0;
    for(unsigned int i=0; i<n; i++)
    {
        sum += vec[i]*weightNumerator[i];
    }
    return sum/weightDenominator;

}

