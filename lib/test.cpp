#include "includee/logistic_regression.cpp"



int main(){

    int m = 700;
    Matrix a(4,1, 1.0f);
    Matrix b(4,1, 0.0f);

    a = a.addToRows(b,1);

    Matrix aneg = a*-1.0f;

    Matrix res = aneg.elementMulti(aneg);



    a = a.use(loga);
    a.print();
    
    Matrix first = ( (aneg).elementMulti(a.use(loga)) );
    Matrix second =  ( (aneg+1.0f).elementMulti( (aneg+1.0f).use(loga) ) );
    first.print();
    second.print();
    Matrix resul = first - second;
    resul.print();
    double r = resul.sum();

                //(1.0f/(double)m)*( ( (Yneg).elementMulti(hyp.use(log)) ) - ( (Yneg+1.0f).elementMulti( (hypneg+1.0f).use(log) ) ) ).sum()
    printf("%6.6f", r);
    
}

