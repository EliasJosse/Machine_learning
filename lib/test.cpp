#include "includee/logistic_regression.cpp"



int main(){

    Matrix X(1,2, 1.0f);
    Matrix Y(1,2, 1.0f);


    logistic_regression lg(X,Y);
}

