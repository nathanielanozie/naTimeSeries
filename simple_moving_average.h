
#ifndef SIMPLE_MOVING_AVERAGE_H
#define SIMPLE_MOVING_AVERAGE_H

#include <map>
#include "moving_average.h"

class SimpleMovingAverage : public MovingAverage
{
    /*class to help compute simple moving average for single vector time series.
    */
public:
    SimpleMovingAverage(std::vector<double> &d, unsigned int lag=1, bool debug=true) : MovingAverage(d, lag, debug){};

    /*compute simple average of input vector. equal weights
    */
    double _compute(std::vector<double> &vec) override;

};

#endif
