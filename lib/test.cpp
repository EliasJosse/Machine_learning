#include "includee/matrix.cpp"



int main(){

    Matrix X(2,2, 1.0f);
    Matrix Y(2,2, 2.0f);


    X.print();
    Y.print();

    Matrix res = X.addToColumns(Y,1);

    res.print();


    Matrix n = res.addToRows(res,1);
    n.print();
}

