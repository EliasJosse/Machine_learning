
#ifndef LOGISTIC_REGRESSION_H
#define LOGISTIC_REGRESSION_H

#include "../includee/matrix.cpp"
class logistic_regression
{
private:

public:
    //mxn
    Matrix X;
    //1xn
    Matrix theta;
    //mx1
    Matrix Y;
    int m, n;
    double previosCost;
    logistic_regression(Matrix Xx, Matrix Yy);

    ~logistic_regression();
    double costJ(double lambda);
    Matrix gradients(double lambda);
    Matrix& initTheta();
    void updateTheta(Matrix gradients, double alpha);
    void train(int iterations, double alpha, double lambda);
    Matrix predict(Matrix test);
};

#endif

