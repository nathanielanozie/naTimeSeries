

#include <iostream>
#include <vector>

#include "testing.h"
#include "utils.h"

//moving average methods
#include "simple_moving_average.h"
#include "weighted_moving_average.h"


void sma_test_example()
{
    printf("\n");
    printf("model example with accuracy\n");
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    unsigned int lag = 2;
    double accuracy;
    std::vector<double> actual;
    std::vector<double> predicted;
    SimpleMovingAverage smaModelExample(/*data*/ data, /*lag*/ lag, /*debug*/ false);
    bool status;
    for(unsigned int j=0; j<data.size(); j++)
    {
        if(j < lag)
            continue; //skip elements smaller than lag

        double pred;
        status = smaModelExample.computePrediction(/*index*/ j, /*result*/ pred);
        if(status) //if was successful prediction
        {
            actual.push_back(data[j]);
            predicted.push_back(pred);
        }
    }
    printf("actual: predicted \n");
    for(unsigned int i=0; i<actual.size(); i++)
    {
        printf("%f: %f\n", actual[i], predicted[i]);
    }
    printf("computed mean absolute deviation accuracy: \n");
    MeanAbsoluteDeviationAccuracy accObj;
    accuracy = accObj.accuracy(actual, predicted);
    printf("%f\n", accuracy);
    printf("expected: %f\n", 1.5);

}

void sma_test_accuracy_example()
{

    //compute accuracy example
    std::vector<double> dat = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    printf("about to run model\n");
    SimpleMovingAverage smaModel(/*data*/ dat, /*lag*/ 2, /*debug*/ false);

    printf("lag: %d\n", smaModel.getLag());

    //status = smaModel.computePrediction(/*index of data*/ 2, /*result*/ result);
    printf("data:\n");
    smaModel.printData();

    std::vector<double> predictions = smaModel.computeAllPredictions();
    printf("predictions:\n");
    printVector(predictions);

    MeanAbsoluteDeviationAccuracy madAcc;
    double acc = smaModel.computeAccuracy(madAcc); //excepts any subclass of Accuracy
    printf("mad accuracy: %f\n", acc);

    MeanSquareErrorAccuracy mseAcc;
    acc = smaModel.computeAccuracy(mseAcc); //excepts any subclass of Accuracy
    printf("mse accuracy: %f\n", acc);  
    //

}


void sma_test()
{   
    std::vector<double> dat = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    printf("about to run model\n");
    SimpleMovingAverage smaModel(/*data*/ dat, /*lag*/ 2, /*debug*/ false);
    double result;
    int status;

    status = smaModel.computePrediction(/*index of data*/ 2, /*result*/ result);
    printf("data:\n");
    smaModel.printData();
    if(status){
        printf("prediction index: %d\n", 2);
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result);
        printf("expected: %f\n", 1.5); //3/2
    }

    status = smaModel.computePrediction(/*index of data*/ 3, /*result*/ result);
    if(status){
        printf("prediction index: %d\n", 3);
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result);
        printf("expected: %f\n", 2.5); // 5/2
    }
    status = smaModel.computePrediction(/*index of data*/ 4, /*result*/ result);
    if(status){
        printf("prediction index: %d\n", 4);    
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result);
        printf("expected: %f\n", 3.5); // 7/2
    }
    ///using different lag
    //change lag
    smaModel.setLag(/*lag*/ 1);
    status = smaModel.computePrediction(/*index*/ 2, /*result*/ result);
    printf("data:\n");
    smaModel.printData();
    if(status){
        printf("prediction index: %d\n", 2);
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result);
        printf("expected: %f\n", 2.0);  //2/1   
    }
    status = smaModel.computePrediction(/*index*/ 3, /*result*/ result);
    if(status){
        printf("prediction index: %d\n", 3);
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result);
        printf("expected: %f\n", 3.0);  //3/1
    }   
    ///

    printf("using new data\n");
    std::vector<double> newDat = {21.0, 44.0, 49.0};
    smaModel.setData(/*data*/ newDat);
    smaModel.setLag(/*lag*/ 2);
    printf("data:\n");
    smaModel.printData();
    printf("prediction index: %d\n", 2);        
    status = smaModel.computePrediction(/*index*/ 2, /*result*/ result);
    if(status){
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result);
        printf("expected: %f\n", 32.5); //65/2 = 32.5
    }
    smaModel.setLag(/*lag*/ 1);
    status = smaModel.computePrediction(/*index*/ 1, /*result*/ result);
    if(status==0){
        printf("data:\n");
        smaModel.printData();
        printf("lag: %d\n", smaModel.getLag());
        printf("result: %f\n", result); 
        printf("expected: %f\n", 21.0); //21/1
    }

    printf("\n");
    printf("accuracy example:\n");
    double acc;
    std::vector<double> v1 = {1, 2, 3};
    std::vector<double> v2 = {4, 5, 6};
    MeanAbsoluteDeviationAccuracy accObj; 
    acc = accObj.accuracy(v1, v2);
    printf("accuracy: %f\n", acc);
    printf("expected: %f\n", 3.0); //1/3 *( abs(1-4) + abs(2-5) + abs(3-6) ) = 1/3 *( 3 + 3 + 3 ) = 1/3 * 9 = 3


    sma_test_example();


    sma_test_accuracy_example();
}



void wma_test_accuracy_example()
{
    printf("wma_test_accuracy_example ---- \n\n\n");

    //compute accuracy example
    std::vector<double> dat = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    printf("about to run model\n");
    WeightedMovingAverage wmaModel(/*data*/ dat, /*lag*/ 2, /*debug*/ false);

    printf("lag: %d\n", wmaModel.getLag());

    printf("data:\n");
    wmaModel.printData();

    std::vector<double> predictions = wmaModel.computeAllPredictions();
    printf("predictions:\n");
    printVector(predictions);

    MeanAbsoluteDeviationAccuracy madAcc;
    double acc = wmaModel.computeAccuracy(madAcc); //excepts any subclass of Accuracy
    printf("mad accuracy: %f\n", acc);

    MeanSquareErrorAccuracy mseAcc;
    acc = wmaModel.computeAccuracy(mseAcc); //excepts any subclass of Accuracy
    printf("mse accuracy: %f\n", acc);  
    //

}

void wma_test()
{   
    wma_test_accuracy_example();
}
