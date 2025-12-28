/*simple moving average prediction model for single vector time series

//please modify/use at your own risk
*/

#include <iostream>
#include <vector>
#include <map>
#include <stdexcept> //for throwing errors
#include <cmath>

#include "utils.h"
#include "moving_average.h"


MovingAverage::MovingAverage(std::vector<double> &d, unsigned int lag, bool debug){ 
	mData = d;
	_assertLagIsValid(lag);
	mLag = lag;
	//printf("initialized variables\n");
	_computeDataMap(/*debug*/ debug);
}

//public methods
/*compute prediction for given index of data. note some data points (those less than lag) will not have a prediction
Args:
	dataIndex (int) data index
	result (double) result of prediction
Returns:
	(bool) true if successfully made prediction. false otherwise
*/
bool MovingAverage::computePrediction(unsigned int dataIndex, double &result)
{
	//recompute previous map first. as artist may have changed lag and or data
	_computeDataMap(/*debug*/ false);

	//assert index is smaller than lag.
	if(mPreviousDataMap.count(dataIndex) != 1)
	{
		printf("not enough data to make prediction for index %d. try an index bigger than lag %d\n", dataIndex, mLag);
		return false;
	}

	result = _compute(mPreviousDataMap[dataIndex]); //21;//compute correct value here

	return true; //success
}

/*compute all possible predicions. (depends on lag)
*/
std::vector<double> MovingAverage::computeAllPredictions()
{
	std::vector<double> result;

	//recompute previous map first. as artist may have changed lag and or data
	_computeDataMap(/*debug*/ false);

	//assert lag is >= 1
	for(unsigned int i=mLag; i<mData.size(); i++)
	{
		double prediction = _compute(mPreviousDataMap[i]);
		result.push_back(prediction);
	}

	return result;
}

/*returns accuracy number after using this time series method. should support different accuracy methods
Args:
	accObj (Accuracy): accuracy object to use for computing accuracy
*/
double MovingAverage::computeAccuracy(Accuracy &accObj)
{
	//assert lag >= 1
	//assert length of data > lag
	double result;

	std::vector<double> predictions;
	std::vector<double> data;

	predictions = computeAllPredictions();
	//only look at subset of data. depends on lag
	for(unsigned int i=mLag; i<mData.size(); i++)
		data.push_back(mData[i]);

	printf("pred\n");
	printVector(predictions);
	printf("data subset\n");
	printVector(data);

	printf("calling accuracy method\n");
	result = accObj.accuracy(predictions, data);
	return result;
}

/*set lag before making another prediction.
/*/
void MovingAverage::setLag(unsigned int lag)
{
	_assertLagIsValid(lag);
	mLag = lag; //set lag private variable
}

/*get lag for model
*/
int MovingAverage::getLag()
{
	return mLag;
}

/*to choose to use new data
*/
void MovingAverage::setData(std::vector<double> &d)
{
	//could possibly check if data has no elements.
	mData = d;
}

/*print data. assumes data exists
*/
void MovingAverage::printData()
{
	for(unsigned int i=0; i<mData.size(); i++)
	{
		printf("%f\n", mData[i]);
	}
}
//end public methods



/*compute data map. index > previous data vector
Args:
	debug (bool): true means to print debug values
*/
bool MovingAverage::_computeDataMap(bool debug)
{

	std::vector<double> previousData;
	if(debug)
		printf("lag: %d\n", mLag);
	//start from lag
	for(unsigned int i=mLag; i<mData.size(); i++)
	{
		previousData.clear(); //clear previous vector for this element of data
		
		for(unsigned int j=0; j<mLag; j++)
		{
			//printf("j: %d", j);
			previousData.push_back(mData[i-(j+1)]);
		}
		mPreviousDataMap[i] = previousData; //get previous elements
		
	}
	//printf("computed previous data map\n");
	

	if(debug)
		printPreviousDataMap();

	return true;		
}

/*print previous data map
*/
void MovingAverage::printPreviousDataMap()
{
	printf("printing previous data map:\n");
	std::vector<double> previousData;
	std::map<unsigned int, std::vector<double> >::iterator prevDataIter;
	for(prevDataIter = mPreviousDataMap.begin(); prevDataIter != mPreviousDataMap.end(); ++prevDataIter)
	{
		unsigned int i = prevDataIter->first;
		previousData = {};
		previousData = prevDataIter->second;
		printf("i: %d\n", i);
		printf("prev: ");
		for(unsigned int j=0; j<previousData.size(); j++)
		{
			double prevElement = previousData[j]; 
			printf("%f ", prevElement);
		}
		printf("\n");
	}		
}

/*to be overriden by subclass. compute on input vector.
*/
double MovingAverage::_compute(std::vector<double> &vec)
{
	printf("to be implemented in subclasses\n");
	/*
	//assert input at least 1 element
	int n = vec.size();
	double sum = 0.0;
	std::vector<double>::iterator vecIter;
	for(vecIter = vec.begin(); vecIter != vec.end(); ++vecIter)
		sum += *vecIter;
	
	return sum/n;
	*/
	return 0.0;
}

void MovingAverage::_assertLagIsValid(unsigned int lag)
{
	//assert lag is greater than 0. and less than number of data points
	if((lag < 1) || (lag >= mData.size()))
	{
		throw std::runtime_error("Expecting lag is greater than 0. and less than number of data points");
	}
}


