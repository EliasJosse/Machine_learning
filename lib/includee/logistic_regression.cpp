#include "../headerss/logistic_regression.hpp"

static double power2(double val);
static double sigmoid(double val);
static double roundd(double val);

logistic_regression::logistic_regression(Matrix Xx,Matrix Yy)
{
    X = Xx;            //examples mxn
    Y = Yy;            //classes mx1
    m = Xx.nrows();
    n = Xx.ncolumns();

    printf("constr \n");
    //add X0 term
    Matrix Xo(m,1, 1.0f);
    X = X.addToColumns(Xo,0);
    theta = Matrix(1,n+1,0.0f); //1xn
    printf("constr \n");


}



logistic_regression::~logistic_regression()
{

}


double logistic_regression::costJ(double lambda){

    Matrix hyp =X*(theta.trans()); //hyp = mx1
    hyp = hyp.use(sigmoid);
    Matrix Yneg = Y*-1.0f;
    Matrix hypneg = hyp*-1.0f;
    return (1.0f/m)*( ( (Yneg).elementMulti(hyp.use(log)) ) - ( (Yneg+1.0f).elementMulti( (hypneg+1.0f).use(log) ) ) ).sum(); // + lambda/(2.0f*m)*( (theta.use(power2).sum() ));

}


Matrix logistic_regression::gradients(double lambda){

    Matrix hyp = X*(theta.trans()); // Mx1
    hyp = hyp.use(sigmoid);
    Matrix eey(n+1);
    eey(0,0) = 0.0f;

    Matrix grad = ( (hyp-Y).trans() )*X; //+ (theta*(lambda/m))*eey;

    return grad;

}


void logistic_regression::updateTheta(Matrix gradients, double alpha){
    theta -= (gradients*alpha);
    gradients.print();
}

void logistic_regression::train(int iterations, double alpha, double lambda){
    printf("train \n");
    for (size_t i = 0; i < iterations; i++)
    {
        theta.print();
        //printf("Iteration: %d \n", i);
        double cost = costJ(lambda);
        printf("cost: %2.6f \n", cost);

        updateTheta(gradients(lambda), alpha);
        previosCost = cost;
        
    }
    printf("Training complete!");

}



Matrix logistic_regression::predict(Matrix test){

    Matrix testo(test.nrows(), 1, 1.0f);

    Matrix tes = test.addToColumns(testo,0);
    Matrix pred = tes * theta.trans();
    //pred.use(roundd);


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


static double roundd(double val){

    if(val > 0.5f) return 1;
    else return 0;
    
}