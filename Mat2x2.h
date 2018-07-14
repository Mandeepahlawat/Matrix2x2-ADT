//-----------------------------------------------
/**
* The is the header file for Mat2x2 class. This file describes
* all the methods which can be called on the Mat2x2 object and
* what parameters are required for those functions to operate
* in a correct way

* Constructor of this class takes 4 input values to
* initialize the matrix. The order of input variables is from
* a, b, c and d, where a, b, c, d are following elements in the matrix
*
* |a  b|
* |    |
* |c  d|

* If no variables are provided then it initializes the values to
* zeros

*
* @author  Mandeep Ahlawat
* @version 1.0
* @since   2018-07-12 
*/
//-----------------------------------------------
#ifndef MAT2X2_H
#define MAT2X2_H
#include <iostream>
#include <vector>
class Mat2x2{
  private:
    double a, b, c, d;
    int maxLeftMemLength() const; // returns the maximum length from a and c
    int maxRightMemLength() const; // returns the maximum length from a and c
    void removeNegativeZeros();
  public:
    Mat2x2(double a = 0, double b = 0, double c = 0, double d = 0); // ctor
    ~Mat2x2()=default; // dtor
    Mat2x2(const Mat2x2 &mat)=default; // default copy constructor
    Mat2x2 &operator=(const Mat2x2 &mat)=default; // default copy assignment
    
    // compound assignments
    Mat2x2 &operator+=(const Mat2x2 &mat);
    Mat2x2 &operator-=(const Mat2x2 &mat);
    Mat2x2 &operator*=(const Mat2x2 &mat);
    Mat2x2 &operator/=(const Mat2x2 &mat);
    Mat2x2 &operator+=(double x);
    Mat2x2 &operator-=(double x);
    Mat2x2 &operator*=(double x);
    Mat2x2 &operator/=(double x);

    // matrix related operations
    Mat2x2 inverse() const;
    Mat2x2 transpose() const;
    int determinant() const;
    int trace() const;
    bool isSymmetric() const;
    bool isSimilar(const Mat2x2 &mat) const;

    // subscript operator
    const double &operator[](const int) const;
    double &operator[](const int);

    // function objects
    std::vector<double> operator()(int);
    int operator()();

    // equality and inequality operator
    friend bool operator==(const Mat2x2 &matLhs, const Mat2x2 &matRhs);
    friend bool operator!=(const Mat2x2 &matLhs, const Mat2x2 &matRhs);

    //basic airthmetic operators
    friend Mat2x2 operator+(const Mat2x2 &matLhs, const Mat2x2 &matRhs);
    friend Mat2x2 operator-(const Mat2x2 &matLhs, const Mat2x2 &matRhs);
    friend Mat2x2 operator*(const Mat2x2 &matLhs, const Mat2x2 &matRhs);
    friend Mat2x2 operator/(const Mat2x2 &matLhs, const Mat2x2 &matRhs);

    // left side operator being a mat and right an integer, i.e mat + 1
    friend Mat2x2 operator+(const Mat2x2 &mat, double x);
    friend Mat2x2 operator-(const Mat2x2 &mat, double x);
    friend Mat2x2 operator*(const Mat2x2 &mat, double x);
    friend Mat2x2 operator/(const Mat2x2 &mat, double x);

    // left side operator being an integer and right a mat, i.e 1 + mat
    friend Mat2x2 operator+(double x, const Mat2x2 &mat);
    friend Mat2x2 operator-(double x, const Mat2x2 &mat);
    friend Mat2x2 operator*(double x, const Mat2x2 &mat);
    friend Mat2x2 operator/(double x, const Mat2x2 &mat);

    // pre and post incremenet and decrement operators
    Mat2x2 &operator++();
    Mat2x2 &operator--();
    Mat2x2 operator++(int);
    Mat2x2 operator--(int);

    // change signs
    Mat2x2 operator+();
    Mat2x2 operator-();

    // overloaded output and input operators
    friend std::ostream &operator<<(std::ostream &cout, const Mat2x2 &mat);
    friend std::istream &operator>>(std::istream &in, Mat2x2 &mat);
};
#endif
