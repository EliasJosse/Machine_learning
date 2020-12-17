// #include "includee/logistic_regression.cpp"
// #include "includee/matrix.cpp"
#include "includee/neural_network.cpp"

int main(){
    Matrix theta(1,4,0.0f);
    theta.randd(-1.0, 2.0);
    theta.print();
    printf(" %d ", rand());
}

