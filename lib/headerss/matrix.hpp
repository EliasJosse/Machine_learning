
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <math.h>
class Matrix
{
private:
    std::vector<double> values;
    int rows, columns;
public:
    Matrix(int rows, int columns); // constr
    Matrix(int row, int column, double fillVal);
    Matrix(const Matrix& rhs);
    Matrix(int n); //indentity nxn
    Matrix(); //indentity nxn

    ~Matrix(); // destr
    Matrix& operator=(const Matrix& rhs);
    double& operator()(int row,int column);
    double operator()(int row,int column) const;

    //skalar operators
    Matrix& operator+=(double val);
    Matrix operator+(double val) const;
    Matrix& operator-=(double val);
    Matrix operator-(double val) const;
    Matrix& operator*=(double val);
    Matrix operator*(double val) const;
    
    //matrix operators
    Matrix& operator+=(const Matrix& val);
    Matrix operator+(const Matrix& val) const;
    Matrix& operator-=(const Matrix& val);
    Matrix operator-(const Matrix& val) const;
    Matrix& operator*=(const Matrix& val);
    Matrix operator*(const Matrix& val) const;
    
    Matrix eye(int n); //identity
    Matrix trans();
    Matrix& use(double(*f)(double));

    void fill(double val);
    void print();
    int size();
    int nrows();
    int ncolumns();

    double sum();

};
#endif