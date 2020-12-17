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

    double costJ(double lambda);
    double regulCost(double lambda);
    Matrix hypotheses();
    void backpropagation(double alpha, double lambda);
    void train(int iterations , double alpha, double lambda);


    Matrix predict(Matrix testEx);


    ~neural_network();
};

