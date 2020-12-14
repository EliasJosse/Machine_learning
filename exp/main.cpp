#include "../lib/includee/logistic_regression.cpp"
#include <fstream>
#include <sstream>
#include <string>

int main(){

    std::ifstream file("data/data.txt");
    std::string line;

    //const int m = 768;

    Matrix X(100,2);
    Matrix Y(100,1);



    int count = 0;
    int rows = 0;
    while(file.good()){
        std::getline(file,line);
        std::stringstream ss(line);
        int cc = 0;
        while(ss.good()){
            std::string substr;
            std::getline(ss,substr, ',');
            double val = std::stod(substr);
            if(cc == 2) Y(rows,0) = val;
            else
            {
                X(rows, cc) = val;
            }
            cc++;
        }
        rows++;
    }




    Matrix test;
    Matrix testlab;
    X.splitRow(test,X, 10);
    Y.splitRow(testlab,Y, 10);
    //put first 10 in traning 



    logistic_regression lg(X,Y);
    lg.train(1000, 3.0f,0.3f);

    Matrix pred = lg.predict(test);
    double ress = pred.compare(testlab);
    printf("res %2.2f", ress);


    //compare pred and Y

}