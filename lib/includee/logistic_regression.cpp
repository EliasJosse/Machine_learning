#include "../headerss/logistic_regression.hpp"

static double power2(double val);
static double sigmoid(double val);
static double roundd(double val);
static double loga(double val);
logistic_regression::logistic_regression(Matrix Xx,Matrix Yy)
{
    X = Xx;            //examples mxn
    Y = Yy;            //classes mx1
    m = Xx.nrows();
    n = Xx.ncolumns();

    //add X0 term
    Matrix Xo(m,1, 1.0f);
    X = X.addToColumns(Xo,0);
    theta = Matrix(1,n+1,0.0f); //1xn

}

logistic_regression::logistic_regression(Matrix Xx,Matrix Yy, double lower, double higher)
{
    X = Xx;            //examples mxn
    Y = Yy;            //classes mx1
    m = Xx.nrows();
    n = Xx.ncolumns();

    //add X0 term
    Matrix Xo(m,1, 1.0f);
    X = X.addToColumns(Xo,0);
    theta = Matrix(1,n+1,0.0f); //1xn
    theta.randd(lower,higher);

}




logistic_regression::~logistic_regression()
{

}


double logistic_regression::costJ(double lambda){

    Matrix hyp =X*(theta.trans()); //hyp = mx1
    hyp = hyp.use(sigmoid);
    Matrix Yneg = Y*-1.0f;
    Matrix hypneg = hyp*-1.0f;
    return (1.0f/(double)m)*( ( (Yneg).elementMulti(hyp.use(loga)) ) - ( (Yneg+1.0f).elementMulti( (hypneg+1.0f).use(loga) ) ) ).sum(); + lambda/(2.0f*m)*( (theta.use(power2).sum() ));

}


Matrix logistic_regression::gradients(double lambda){



    Matrix hyp = X*(theta.trans()); // Mx1

    hyp = hyp.use(sigmoid);
    Matrix eey(n+1);
    eey(0,0) = 0.0f;
    Matrix grad = ((hyp-Y).trans()*X)*(1.0f/m);
    Matrix reg = (theta*(lambda/(double)m));
    reg(0,0) = 0.0f;
    return (grad+reg);

}


void logistic_regression::updateTheta(Matrix gradients, double alpha){
    theta = theta - (gradients*alpha);
}

void logistic_regression::train(int iterations, double alpha, double lambda){
    printf("train \n");
    for (size_t i = 0; i < iterations; i++)
    {
        // if(i%(iterations/5) == 0){
        //     alpha *= 0.5;
        //     lambda *= 0.5;
        // }
        double cost = costJ(lambda);
        printf("cost: %2.6f \n", cost);
        updateTheta(gradients(lambda), alpha);
        previosCost = cost;
        
    }
    printf("Training complete!\n");
    printf("final cost: %2.6f \n", previosCost);
}



Matrix logistic_regression::predict(Matrix test){

    Matrix testo(test.nrows(), 1, 1.0f);

    Matrix tes = test.addToColumns(testo,0);
    Matrix pred = tes * theta.trans();


    pred = pred.use(sigmoid);
    pred = pred.use(roundd);


    return pred;

}



Matrix& logistic_regression::initTheta(){
}

static double sigmoid(double val){
    return 1.0f/(1.0f+exp(-val));
    // return sigmoid(-val);
}


static double power2(double val){
    return pow(val, 2.0f);
}


static double roundd(double val){

    if(val > 0.5f) return 1;
    else return 0;
    
}


static double loga(double val){

    if(val <= 0) return -20.0f;
    else
    {
        return log(val);
    }
    

}
