#include "../headerss/neural_network.hpp"

static double power2(double val);
static double sigmoid(double val);
static double roundd(double val);
static double loga(double val);


neural_network::neural_network(Matrix X, Matrix Y, int layers, int nodes, int nClasses)
{
    this->X = X;
    this->Y = Y;
    inputs = X.ncolumns();
    m = X.nrows();
    ouputs = nClasses;
    for (size_t i = 0; i < layers; i++)
    {
        if(i == 0)
            theta.push_back(Matrix(inputs, X.ncolumns()+1);
        else if( i == (layers-1) )
            theta.push_back(Matrix(ouputs, theta[i-1].nrows()+1 ) );
        else
            theta.push_back(Matrix(theta[i-1].ncolumns), nodes+1);
    }
    

}




double neural_network::costJ(double lambda){


    Matrix hyp = hypotheses();

    //Y and hypotheses of size M x outputsize

    Matrix Yneg = Y*-1.0f;
    Matrix hypneg = hyp*-1.0f;

    double cost = (1.0f/(double)m)*( ( (Yneg).elementMulti(hyp.use(loga)) ) - ( (Yneg+1.0f).elementMulti( (hypneg+1.0f).use(loga) ) ) ).sum();
    return cost + regulCost(lambda);



}

double neural_network::regulCost(double lambda){
    double res = 0;

    for (size_t i = 0; i < theta.size(); i++)
    {
        // sum regularization for all thetas
        res += theta.use(power2).sum();

    }
    res *= lambda/(2*m)

}

Matrix neural_network::hypotheses(){
    //run through all matrices¨
    Matrix a = X;
    Matrix z;
    for (size_t i = 0; i < theta.size(); i++)
    {

        //add a0 column of ones
        Matrix ones(a.nrows(), 1, 1.0f);
        a = a.addToColumns(ones,0);
        z = a*theta[i].trans();
        a = z.use(sigmoid);
        
    }
    //final size of a = M x outputsize
    return a;
    
}


Matrix neural_network::gradient(double lambda){


}

void neural_network::train(double alpha, double lambda){


}
neural_network::~neural_network()
{
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
