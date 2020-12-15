#include "../lib/includee/logistic_regression.cpp"
#include <fstream>
#include <sstream>
#include <string>




int main(){

    //import data
    //768 examples
    //per row: 8 features 1 label, seperated by ","
    std::ifstream file("data/data.txt");
    std::string line;

    const int m = 768;

    Matrix X(768,8);
    Matrix Y(768,1);



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
            if(cc == 8) Y(rows,0) = val;
            else
            {
                X(rows, cc) = val;
            }
            cc++;
        }
        rows++;
    }
   


    
   //mean and std
    std::vector<double> mean = {0,0,0,0,0,0,0,0};
    std::vector<int> nonempty = {0,0,0,0,0,0,0,0};
   
    //mean
    for (size_t r = 0; r < X.nrows(); r++)
    {
        for (size_t c = 0; c < X.ncolumns(); c++)
        {
            double val = X(r,c);
            if( !(c != 0 && val == 0)){
                mean[c] += X(r,c);
                nonempty[c]++;
            }
        }
    }
    
    for (size_t i = 0; i < mean.size(); i++)
    {
        mean[i] = mean[i]/nonempty[i];
    }


    //standard deviation

    std::vector<double> std(8);
    for (size_t r = 0; r < X.nrows(); r++)
    {
        for (size_t c = 0; c < X.ncolumns(); c++)
        {
            double val = X(r,c);
            if( !(c != 0 && val == 0) ){
                std[c] += pow(X(r,c)-mean[c],2);
            }
        }
    }

    for (size_t i = 0; i < mean.size(); i++)
    {
        std[i] = sqrt(std[i]/nonempty[i]);
    }


    
    //new values
    for (size_t r = 0; r < X.nrows(); r++)
    {
        for (size_t c = 0; c < X.ncolumns(); c++)
        {

            if( !(c != 0 && X(r,c) == 0.0) ){
                X(r,c) = (X(r,c) - mean[c])/std[c];
            }
        }
    }



    for(auto val : mean) printf(" %2.2f",val);
    printf("\n");


    for(auto val : std) printf(" %2.2f",val);
    printf("\n");

    for(auto val : nonempty) printf(" %d",val);
    printf("\n");

    
    //test values;
    Matrix test;
    Matrix testlab;
    X.splitRow(X, test, 700);
    Y.splitRow(Y, testlab, 700);

    
 

    logistic_regression lga(X,Y);
    lga.train(100,3.0f,3.0f);

    logistic_regression lgb(X,Y,-10.f, 10.f);
    lgb.train(100,3.0f,3.0f);







  




    Matrix res = lga.predict(test);
    double d = res.compare(testlab);
    lga.theta.print();
    printf("accuracy %2.2f\n", d);


    res = lgb.predict(test);
    d = res.compare(testlab);
    lgb.theta.print();
    printf("accuracy %2.2f", d);

    
}



