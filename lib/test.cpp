#include "includee/matrix.cpp"



int main(){

    Matrix X(4,4, 1.0f);

    Matrix Xa;
    Matrix Xb;

    X.splitColumn(Xa, Xb, 2);
    X.print();
    Xa.print();
    Xb.print();



    X.splitRow(Xa, Xb, 2);
    Xa.print();
    Xb.print();
}

