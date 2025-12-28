/*simple moving average prediction model for single vector time series

//please modify/use at your own risk
*/

#include <iostream>
#include <vector>

#include "simple_moving_average.h"


/*compute simple average of input vector. equal weights
*/
double SimpleMovingAverage::_compute(std::vector<double> &vec)
{
	//assert input at least 1 element
	int n = vec.size();
	double sum = 0.0;
	std::vector<double>::iterator vecIter;
	for(vecIter = vec.begin(); vecIter != vec.end(); ++vecIter)
		sum += *vecIter;

	return sum/n;
}

