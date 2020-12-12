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
    int count = 0;
    int rows = 0;

    Matrix X(768,8);
    Matrix Y(768,1);

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
   

   //features scaling: standardization

   //mean and std
    std::vector<double> mean(8);
    std::vector<int> nonempty(8);
   
    //mean
    for (size_t r = 0; r < X.nrows(); r++)
    {
        for (size_t c = 0; c < X.ncolumns(); c++)
        {
            double val = X(r,c);
            if(c != 0 && val == 0){

            }
            else
            {
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
            if(c != 0 && val == 0){

            }
            else
            {
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

            if( !(c != 0 && X(r,c) == 0) ){
                X(r,c) = (X(r,c) - mean[c])/std[c];
            }
        }
    }


    X.print(); 



}



