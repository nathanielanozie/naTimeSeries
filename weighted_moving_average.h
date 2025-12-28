
#ifndef WEIGHTED_MOVING_AVERAGE_H
#define WEIGHTED_MOVING_AVERAGE_H

#include <map>
#include "moving_average.h"

class WeightedMovingAverage : public MovingAverage
{
    /*class to help compute weighted moving average for single vector time series.
    */
public:
    WeightedMovingAverage(std::vector<double> &d, unsigned int lag=1, bool debug=true) : MovingAverage(d, lag, debug){};

    /*compute weighted average of input vector. weights higher closer to forecast
    */
    double _compute(std::vector<double> &vec) override;

};

#endif
