#ifndef MATRIX_C
#define MATRIX_C

#include "../headerss/matrix.hpp"
#include <iostream>
#include <cstdlib>

Matrix::Matrix(int row, int column){
    rows = row;
    columns = column;
    values = std::vector<double>();
    for (size_t i = 0; i < rows*columns; i++)
    {
        values.push_back(0.0f);
    }
}


Matrix::Matrix(int row, int column, double fillVal){
    rows = row;
    columns = column;
    values = std::vector<double>();
    for (size_t i = 0; i < rows*columns; i++)
    {
        values.push_back(fillVal);
    }
}

Matrix::Matrix(const Matrix& rhs){
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    this->values = rhs.values;
}

Matrix::Matrix(){

    
}

Matrix::Matrix(int n){
    rows = n;
    columns = n;
    values = std::vector<double>();
    for (size_t r = 0; r < rows; r++){
        for (size_t c = 0; c < columns; c++)
        {
            if(r == c)
                values.push_back(1.0f);
            else
                values.push_back(0.0f);
        }   
    }
}

Matrix& Matrix::operator=(const Matrix& rhs){
    if(&rhs == this)
        return *this;
    rows = rhs.rows;
    columns = rhs.columns;
    values = rhs.values;
    return *this;

}




Matrix::~Matrix(){
 
 
}

double& Matrix::operator()(int row,int column){
    return values[row * (this->columns) + column];
}

double Matrix::operator()(int row,int column) const {
    return values[row * (this->columns) + column];
}

Matrix& Matrix::operator+=(double val){
    for(auto& vals : values){
        vals += val;
    }

    return *this;
}

Matrix Matrix::operator+(double val) const{
    auto res = *this;
    return res += val;

}


Matrix& Matrix::operator-=(double val){
    for(auto& vals : values){
        vals -= val;
    }

    return *this;
}

Matrix Matrix::operator-(double val) const{
    auto res = *this;
    return res -= val;

}



Matrix& Matrix::operator*=(double val){
    for(auto& vals : values){
        vals *= val;
    }

    return *this;
}

Matrix Matrix::operator*(double val) const{
    auto res = *this;
    return res *= val;
}


Matrix& Matrix::operator+=(const Matrix& val){
    if(this->columns != val.columns || this->rows != val.rows) printf("ERROR IN OPERATOR+= \n");
    for (size_t i = 0; i < values.size(); i++)
    {
        values[i] += val.values[i];
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& val) const {

    auto res = *this;
    return res += val;

}


Matrix& Matrix::operator-=(const Matrix& val){
    if(this->columns != val.columns || this->rows != val.rows) printf("ERROR IN OPERATOR-= \n");
    for (size_t i = 0; i < values.size(); i++)
    {
        values[i] -= val.values[i];
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix& val) const {

    auto res = *this;
    return res -= val;
}


Matrix& Matrix::operator*=(const Matrix& val){
    if(this->columns != val.rows) printf("ERROR IN OPERATOR*= \n");

    Matrix res(this->rows,val.columns);
    double sum;

    for (size_t r = 0; r < res.rows; r++)
        for (size_t c = 0; c < res.columns; c++)
        {
   
            sum = 0;
            for (size_t i = 0; i < val.rows; i++)
            {
               sum += this->operator()(r,i) * val(i,c);
            }

            res(r,c) = sum;
     
        }        

    this->columns = res.columns;
    this->rows = res.rows;
    this->values = res.values;

    return *this;
}

Matrix Matrix::operator*(const Matrix& val) const{

    auto res = *this;
    return res *= val;



}


Matrix Matrix::elementMulti(const Matrix& val){
    if(this->columns != val.columns || this->rows != val.rows) printf("ERROR IN elementMulti \n");
    Matrix res(val.rows, val.columns);
    for (size_t r = 0; r < val.rows; r++)
    {
        for (size_t c = 0; c < val.columns; c++)
        {
            res(r,c) = this->operator()(r,c) * val(r,c);
        }
        
    }
    return res;
    
}


Matrix Matrix::eye(int n){
    Matrix res(n,n);
    for (size_t r = 0; r < res.rows; r++){
        for (size_t c = 0; c < res.columns; c++)
        {

            if(r == c)
                res(r,c) = 1.0f;
            else
                res(r,c) = 0.0f;
        }   
    }
    return res;
}


void Matrix::fill(double val){
    for (size_t r = 0; r < this->rows; r++)
        for (size_t c = 0; c < this->columns; c++)
        {
            this->operator()(r,c) = val;
        }
    
}


Matrix Matrix::trans(){
    Matrix res(this->columns, this->rows);

    for (size_t r = 0; r < this->rows; r++){
        for (size_t c = 0; c < this->columns; c++)
        {
            res(c,r) = this->operator()(r,c);
        }   
    }
    return res;

}

void Matrix::print(){
    printf("\n");
    for (size_t r = 0; r < this->rows; r++){
        printf(" [");
        for (size_t c = 0; c < this->columns; c++)
        {
            printf(" %2.2f ", this->operator()(r,c));
        }
        printf(" ]\n");   
    }
}

Matrix Matrix::use(double(*f)(double)){
    Matrix cp(*this);
    for(auto& vals : cp.values){
        vals = (*f)(vals);
    }

    return cp;

}


int Matrix::size(){

    return values.size();
}

int Matrix::ncolumns(){
    return columns;
}
int Matrix::nrows(){
    return rows;
}

double Matrix::sum(){
    double sum = 0;
    for (size_t r = 0; r < rows; r++)
        for (size_t c = 0; c < columns; c++)
        {
            sum += this->operator()(r,c);
        }
        
    return sum;
}



//end = 1 add to end / end = 0 add to beginning
Matrix Matrix::addToColumns(const Matrix& val, int end){
    if(this->rows != val.rows) printf("ERROR IN addToColumns \n");
    Matrix res(this->rows,this->columns + val.columns);


    //add to end 
    if(end){
        for (size_t r = 0; r < res.rows; r++){
            //copy from this
            for (size_t c = 0; c < this->columns; c++)
            {
                res(r,c) = this->operator()(r,c);
            }
            //copy from val
            for (size_t c = this->columns; c < res.columns; c++)
            {
                res(r,c) = val(r,c-(this->columns));
            }
        }
    }
    //add to beginning
    else
    {
        for (size_t r = 0; r < res.rows; r++){
            //copy from end
            for (size_t c = 0; c < val.columns; c++)
            {
                res(r,c) = val(r,c);
            }
            //copy from this
            for (size_t c = val.columns; c < res.columns; c++)
            {
                res(r,c) = this->operator()(r,c-(val.columns));
            }
        }        
    }
    

/*
    this->columns = res.columns;
    this->rows = res.rows;
    this->values = res.values;

*/
    return res;


}

//end = 1 add to end / end = 0 add to beginning
Matrix Matrix::addToRows(const Matrix& val, int end){
    if(this->columns != val.columns) printf("ERROR IN addToRows \n");

    Matrix res(this->rows + val.rows,this->columns);


    //add to end 
    if(end){
        //copy from this
        for (size_t r = 0; r < this->rows; r++){
            for (size_t c = 0; c < res.columns; c++)
            {
                res(r,c) = this->operator()(r,c);
            }
  
        }

        //copy from val
        for (size_t r = this->rows; r < res.rows; r++){
            for (size_t c = 0; c < res.columns; c++)
            {
                res(r,c) = val(r-(this->rows),c);
            }
        }


    }
    //add to beginning
    else
    {
        //copy from val
        for (size_t r = 0; r < val.rows; r++){
            for (size_t c = 0; c < res.columns; c++)
            {
                res(r,c) = val(r,c);
            }
        }

        for (size_t r = val.rows; r < res.rows; r++){
            //copy from this
            for (size_t c = 0; c < res.columns; c++)
            {
                res(r,c) = this->operator()(r-(val.rows),c);
            }
        }
    }


/*
    this->columns = res.columns;
    this->rows = res.rows;
    this->values = res.values;

*/
    return res;
}

//number of col columns will be put in leftres, remaining in rightres.
void Matrix::splitColumn(Matrix& leftRes,Matrix& rightRes,int col){

    Matrix left(this->rows, col);
    Matrix right(this->rows, (this->columns)-col);


    for (size_t r = 0; r < this->rows; r++)
    {
        for (size_t c = 0; c < col; c++)
        {
            left(r,c) = this->operator()(r,c);
        }
        for (size_t c = col; c < this->columns; c++)
        {
            right(r,c-(col) ) = this->operator()(r,c);
        }
    }
    


    leftRes.rows = left.rows;
    leftRes.columns = left.columns;
    leftRes.values = left.values;

    rightRes.rows = right.rows;
    rightRes.columns = right.columns;
    rightRes.values = right.values;


}
void Matrix::splitRow(Matrix& upperRes,Matrix& lowerRes,int rows){

    Matrix upper(rows, this->columns);
    Matrix lower((this->rows)-rows, (this->columns));


    for (size_t r = 0; r < rows; r++)
    {
        for (size_t c = 0; c < this->columns; c++)
        {
            upper(r,c) = this->operator()(r,c);
        }

    }

    for (size_t r = rows; r < this->rows; r++)
    {
        for (size_t c = 0; c < this->columns; c++)
        {
            lower(r-rows,c) = this->operator()(r,c);
        }
    }
    
    upperRes.rows = upper.rows;
    upperRes.columns = upper.columns;
    upperRes.values = upper.values;

    lowerRes.rows = lower.rows;
    lowerRes.columns = lower.columns;
    lowerRes.values = lower.values;

}


//compare simalairity between two matrices of same size
double Matrix::compare(const Matrix& val){
    if(this->columns != val.columns || this->rows != val.rows) printf("ERROR IN elementMulti \n");

    int simCount = 0;
    for (size_t r = 0; r < val.rows; r++)
    {
        for (size_t c = 0; c < val.columns; c++)
        {
            if(this->operator()(r,c) == val(r,c)) simCount++;
        }
    }
    
    return (1.0f*simCount/this->size()*1.0f);

}


void Matrix::randd(double lowerLim, double upperLim){

    for(auto& val : values){

        val = lowerLim + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(upperLim-lowerLim)));

    }
}

#endif