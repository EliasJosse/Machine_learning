#include "../headerss/neural_network.hpp"

static double power2(double val);
static double sigmoid(double val);
static double sigmoidP(double val);
static double roundd(double val);
static double loga(double val);


neural_network::neural_network(Matrix X, Matrix Y, int layers, int nodes, int nClasses)
{
    this->X = X;
    this->Y = Y;
    inputs = X.ncolumns();
    m = X.nrows();

    if(ouputs > 2)
        ouputs = nClasses;
    else
        ouputs = 1;
    this->layers = layers;
    theta = std::vector<Matrix>();
    for (size_t i = 0; i < layers+1; i++)
    {
        if(i == 0)
            theta.push_back(Matrix(nodes, X.ncolumns()+1));
        else if( i == (layers) )
            theta.push_back(Matrix(ouputs, theta[i-1].ncolumns()+1 ) );
        else
            theta.push_back(Matrix(nodes+1, theta[i-1].ncolumns()+1));
    }

    a = std::vector<Matrix>(layers+2);
    z = std::vector<Matrix>(layers+1);

    
    Matrix ones(X.nrows(), 1, 1.0f);
    a[0] = X.addToColumns(ones,0);
    

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
        res += theta[i].use(power2).sum();

    }
    res *= lambda/(2.0f*m);
    return res;

}

Matrix neural_network::hypotheses(){
    //run through all matrices
    for (size_t i = 0; i < theta.size(); i++)
    {
        z[i] = a[i]*(theta[i].trans());
        a[i + 1] = z[i].use(sigmoid);
        //add a0 column of ones
        if(i < (theta.size()-1) ){    
            //add column of ones to new a matrix
            Matrix ones(a[i+1].nrows(), 1, 1.0f);
            a[i+1] = a[i+1].addToColumns(ones,0);
        }
        
    }
    //final size of a = M x outputsize
    return a[a.size()-1];
    
}


void neural_network::backpropagation(double alpha , double lambda){

    // first sigma

    Matrix yneg = Y*-1.0f;
    std::vector<Matrix> sigma(layers+1);
    sigma[layers] = a[a.size()-1]+yneg;
    for (signed int i = layers-1; i >= 0; i--)
    {
        sigma[i] = (sigma[i+1]*theta[layers-i]).elementMulti(z[i]);
        
    }

    //for all examples
    //calc hyp

    std::vector<Matrix> delta(layers+1);

    for (size_t i = 0; i < layers+1; i++)
    {
        delta[i] = (a[i]*sigma[i])*(1.0f/m);
        //reg

        Matrix reg = theta[i]*lambda;
        for (size_t r = 0; r < reg.nrows(); r++)
        {
            reg(0,r) = 0.0f;
        }
        
        delta[i] += reg;

        //update theta
        theta[i] -= (delta[i]*alpha);
    }
    

    

}

void neural_network::train(int iterations , double alpha, double lambda){


    for (size_t i = 0; i < iterations; i++)
    {
        printf("Iteration %d ", i);
        double cost = costJ(lambda);
        printf(" Cost: %2.4f", cost);
        backpropagation(alpha, lambda);

    }
    printf("Training done!");
    

}

Matrix neural_network::predict(Matrix testEx){
    //add zeroes
    Matrix ones(testEx.nrows(),1,1.0f);
    Matrix aa = testEx.addToColumns(ones,0);
    Matrix zz;
    for (size_t i = 0; i < theta.size(); i++)
    {
        zz = aa*(theta[i].trans());
        aa = zz.use(sigmoid);
        //add a0 column of ones
        if(i < (theta.size()-1) ){    
            Matrix ones(aa.nrows(), 1, 1.0f);
            aa = aa.addToColumns(ones,0);
        }
        
    }
    //final size of a = M x k
    return aa;


}
neural_network::~neural_network()
{
}
static double sigmoid(double val){
    return 1.0f/(1.0f+exp(-val));
    // return sigmoid(-val);
}

static double sigmoidP(double val){
    return sigmoid(val)*(1-sigmoid(val));
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
