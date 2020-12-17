#include "../includee/matrix.cpp"



class neural_network
{
private:
    Matrix X;
    Matrix Y;
    std::vector<Matrix> theta;
    std::vector<Matrix> a;
    std::vector<Matrix> z;
    int ouputs;
    int inputs;
    int m;
    int layers;
public:
    neural_network(Matrix X, Matrix Y, int layers,int nodes, int nClasses);


    train(int iterations , double alpha, double lambda);
    double costJ(double alpha, double lambda);
    Matrix gradient();
    void backpropagation(double alpha);
    Matrix hypotheses();
    double regulCost(double lambda);
    Matrix predict(const Matrix& testEx);

    
    ~neural_network();
};

