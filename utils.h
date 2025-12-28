//so header only included once
#ifndef UTILS_H
#define UTILS_H

/*print vector
Args:
    v1 (std::vector<double>): vector of doubles
*/
void printVector(std::vector<double> &v1);


class Accuracy
{
public:
    Accuracy(){}
    virtual double accuracy(std::vector<double> &v1, std::vector<double> &v2){return 0.0;};
};

class MeanAbsoluteDeviationAccuracy: public Accuracy
{
    /*
    class to compute mean absolute deviation for two vectors.
    */
public:
    MeanAbsoluteDeviationAccuracy() : Accuracy(){}
    double accuracy(std::vector<double> &v1, std::vector<double> &v2) override;
};


class MeanSquareErrorAccuracy: public Accuracy
{
    /*
    class to compute mse for two vectors.
    */
public:
    MeanSquareErrorAccuracy() : Accuracy(){}
    double accuracy(std::vector<double> &v1, std::vector<double> &v2) override;
};


#endif