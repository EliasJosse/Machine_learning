#include "../includee/matrix.cpp"



class neural_network
{
private:
    Matrix X;
    Matrix Y;
    std::vector<Matrix> theta;
    int ouputs;
    int inputs;
    int m;
public:
    neural_network(Matrix X, Matrix Y, int layers,int nodes, int nClasses);
    train(double alpha, double lambda);
    double costJ(double alpha, double lambda);
    Matrix gradient();
    void backpropagation(double alpha);
    Matrix hypotheses();
    double regulCost(double lambda);

    ~neural_network();
};

