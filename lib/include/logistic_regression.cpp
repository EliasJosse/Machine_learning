#include "../headers/logistic_regression.hpp"

static double power2(double val);
static double sigmoid(double val);

logistic_regression::logistic_regression(Matrix Xx,Matrix Yy)
{
    X = Xx;            //examples mxn
    theta = Matrix(n,1,0.0f); //1xn
    Y = Yy;            //classes mx1
    m = Xx.nrows();
    n = Xx.ncolumns();
}



logistic_regression::~logistic_regression()
{

}


double logistic_regression::costJ(double lambda){

    Matrix hyp = theta.trans()*X;
    hyp = hyp.use(sigmoid);
    Matrix Yneg = Y*-1.0f;
    Matrix hypneg = hyp*-1.0f;
    return (1.0f/m)*( ((Yneg)*(hyp.use(log))) - (Yneg+1.0f)*(hypneg+1.0f).use(log) ).sum()  + lambda/(2.0f*m)*( (theta.use(power2).sum() ));

}


Matrix logistic_regression::gradients(double lambda){

    Matrix hyp = theta.trans()*X;
    hyp = hyp.use(sigmoid);
    Matrix eey(m);
    eey(0,0) = 0.0f;

    Matrix grad = ( (hyp-Y)*(X.trans()) ) + (theta*(lambda/m))*eey;

    return grad;

}


void logistic_regression::updateTheta(Matrix gradients, double alpha){
    theta -= (gradients*alpha);
}

void logistic_regression::train(int iterations, double alpha, double lambda){
    
    for (size_t i = 0; i < iterations; i++)
    {
        printf("Iteration: ", i);
        double cost = costJ(lambda);
        updateTheta(gradients(lambda), alpha);
        previosCost = cost;
        
    }
    printf("Training complete");

}



Matrix logistic_regression::predict(Matrix test){
    Matrix pred = theta.trans()*test;
    return pred;

}



Matrix& logistic_regression::initTheta(){
}

static double sigmoid(double val){
    return 1.0f/(1.0f+exp(-val));
}


static double power2(double val){
    return pow(val, 2.0f);
}


