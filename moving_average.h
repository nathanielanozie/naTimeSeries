
#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <map>
#include <vector>
#include "utils.h"

class MovingAverage
{
    /*class to help compute simple moving average for single vector time series.
    */
private:
    unsigned int mLag; //lag 1. says use previous data point to predict next data point.
                //lag 2. says use previous 2 data points to predict next data point.
    std::vector<double> mData;
    std::map<unsigned int, std::vector<double> > mPreviousDataMap;
public:
    MovingAverage(std::vector<double> &d, unsigned int lag=1, bool debug=true);
    virtual ~MovingAverage(){}

    //public methods
    /*compute prediction for given index of data. note some data points (those less than lag) will not have a prediction
    Args:
        dataIndex (int) data index
        result (double) result of prediction
    Returns:
        (bool) true if successfully made prediction. false otherwise
    */
    bool computePrediction(unsigned int dataIndex, double &result);

    /*compute all possible predicions. (depends on lag)
    */
    std::vector<double> computeAllPredictions();

    /*returns accuracy number after using this time series method. should support different accuracy methods
    Args:
        accObj (Accuracy): accuracy object to use for computing accuracy
    */
    double computeAccuracy(Accuracy &accObj);

    /*set lag before making another prediction.
    /*/
    void setLag(unsigned int lag);

    /*get lag for model
    */
    int getLag();

    /*to choose to use new data
    */
    void setData(std::vector<double> &d);

    /*print data. assumes data exists
    */
    void printData();
    //end public methods



    /*compute data map. index > previous data vector
    Args:
        debug (bool): true means to print debug values
    */
    bool _computeDataMap(bool debug=true);

    /*print previous data map
    */
    void printPreviousDataMap();

    void _assertLagIsValid(unsigned int lag);

    /*compute method for moving average. to be overriden by subclasses. ex. simple average of input vector with equal weights
    */
    virtual double _compute(std::vector<double> &vec);

};

#endif
