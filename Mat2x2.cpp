//-----------------------------------------------
/**
* The is the implementation file for Mat2x2 class which takes 4 input values to
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

#include <iostream>
#include <cassert>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include "Mat2x2.h"

using namespace std;


//-----------------------------------------------
/*
* Constructor for the class which takes 4 input values,
* if no variables are passed then it assigns a default 
* value of 0 to all 4 member variables.
*/
//-----------------------------------------------
Mat2x2::Mat2x2(double a1, double b1, double c1, double d1) : a(a1), b(b1), c(c1), d(d1) {};

// matrix specific functions

//-----------------------------------------------
/*
* This function finds the inverse of the matrix, where inverse of
* a matrix is defined as 
*
* (1/ad-bc) * (d, -b)
*             (-c, a)
*
* if the denominator part, i.e ((a*d) - (b*c)) is zero
* then it throws overflow error
*/
//-----------------------------------------------
Mat2x2 Mat2x2::inverse() const{
  Mat2x2 temp(d, - b, - c, a);
  double denominator = ((a * d) - (b * c));
  if(denominator <= exp(-6)){
    throw std::overflow_error("Inverse undefined");
  }
  temp /= denominator;
  return temp;
}

//-----------------------------------------------
/*
* This finds the transpose of the matrix without
* modyfying the actually object
*
* transpose of a matrix is a mirror immage along its diagonals
* for a 2x2 matrix it just interchange b and c elements
*/
//-----------------------------------------------
Mat2x2 Mat2x2::transpose() const{
  Mat2x2 temp(a, c, b, d);
  return temp;
}

//-----------------------------------------------
/*
* This finds the transpose of the matrix without
* modyfying the actually object
*
* transpose of a matrix is a mirror immage along its diagonals
* for a 2x2 matrix it just interchange b and c elements
*/
//-----------------------------------------------
int Mat2x2::determinant() const{
  return (int) ((a*d) - (b*c));
}

//-----------------------------------------------
/*
* This function returns the trance, where trace is
* defined as the summation of a and d elements
* 
*/
//-----------------------------------------------
int Mat2x2::trace() const{
  return (int) (a + d);
}

//-----------------------------------------------
/*
* This function checks if a matrix is symmetric or
* not and returns the boolean value accordingly
* A matrix is called symmetric if its diagonal
* elemts are equal
* 
*/
//-----------------------------------------------
bool Mat2x2::isSymmetric() const{
  if(b == c){
      return true;
  }
  return false;
}

//-----------------------------------------------
/*
* This function checks if a matrix is similar to
* the matrix passed in as the arguments or
* not and returns the boolean value accordingly
* 
* A matrix is called similar if both the determinant and
* trace of the matrices is same.
* 
*/
//-----------------------------------------------
bool Mat2x2::isSimilar(const Mat2x2 &mat) const{
  return (this->determinant() == mat.determinant() && this->trace() == mat.trace());
}


//-----------------------------------------------
/*
* Following functions are all the compound operators
* which are overloaded for this class so that 
* a Mat2x2 object can behave correctly for a
* airthmetic operator. 
*
* Each of the following functions
* accepts a double scalar value in the argument
* and perform that airthmetic operation the
* Mat2x2 object
* 
*/
//-----------------------------------------------
Mat2x2 &Mat2x2::operator+=(double x){
  a += x;
  b += x;
  c += x;
  d += x;
  removeNegativeZeros();
  return *this;
}

Mat2x2 &Mat2x2::operator-=(double x){
  a -= x;
  b -= x;
  c -= x;
  d -= x;
  removeNegativeZeros();
  return *this;
}

Mat2x2 &Mat2x2::operator*=(double x){
  a *= x;
  b *= x;
  c *= x;
  d *= x;
  removeNegativeZeros();
  return *this;
}

Mat2x2 &Mat2x2::operator/=(double x){
  if(x == 0){
    throw std::overflow_error("Division by zero"); // throw overflow error if divide by 0
  }
  assert (x!=0);
  a /= x;
  b /= x;
  c /= x;
  d /= x;
  return *this;
}

//-----------------------------------------------
/*
* Following functions are all the compound operators
* which are overloaded for this class so that 
* a Mat2x2 object can behave correctly for a
* airthmetic operator.
*
* Each of the following functions
* accepts another Mat2x2 object in the argument
* and perform that airthmetic operation
* 
*/
//-----------------------------------------------
Mat2x2 &Mat2x2::operator+=(const Mat2x2 &mat){
  a += mat.a;
  b += mat.b;
  c += mat.c;
  d += mat.d;
  return *this;
}

Mat2x2 &Mat2x2::operator-=(const Mat2x2 &mat){
  a -= mat.a;
  b -= mat.b;
  c -= mat.c;
  d -= mat.d;
  return *this;
}

Mat2x2 &Mat2x2::operator*=(const Mat2x2 &mat){
  double a1, a2, a3, a4;
  a1 = (a * mat.a) + (b * mat.c);
  a2 = (a * mat.b) + (b * mat.d);
  a3 = (c * mat.a) + (d * mat.c);
  a4 = (c * mat.b) + (d * mat.d);
  
  a = a1;
  b = a2;
  c = a3;
  d = a4;
  return *this;
}

Mat2x2 &Mat2x2::operator/=(const Mat2x2 &mat){
  Mat2x2 temp = mat.inverse();
  *this *= temp;
  return *this;
}

//-----------------------------------------------
/*
* This function checks for the equality of two
* Mat2x2 objects. if they are equal it returns true
* otherwise it returns false.
*
* Two Mat2x2 objects are equal if the absolute difference of
* each corresponding attribute in matrices is less than
* 1.e-6.
* 
*/
//-----------------------------------------------
bool operator==(const Mat2x2 &matLhs, const Mat2x2 &matRhs){
  if((fabs(matLhs.a - matRhs.a) < exp(-6)) && fabs(matLhs.b - matRhs.b) < exp(-6) && fabs(matLhs.c - matRhs.c) < exp(-6) && fabs(matLhs.d - matRhs.d) < exp(-6)){
      return true;
  }
  return false;
}

//-----------------------------------------------
/*
* This function checks for the inequality of two
* Mat2x2 objects. if they are not equal it returns true
* otherwise it returns false.
* 
*/
//-----------------------------------------------
bool operator!=(const Mat2x2 &matLhs, const Mat2x2 &matRhs){
  return !(matLhs == matRhs);
}

// airthmetic operators
//-----------------------------------------------
/*
* Following 3 functions defines the overloaded
* '*' airthmatic operator for this class so that 
* a Mat2x2 object can behave correctly when a
* multiplication is performed. 
*
* Each of the following functions either
* accepts two Mat2x2 objects, or one scalar and one
* Mat2x2 object in the arguments list. The scalar
* value can also appears on either side of operator
* so we need 2 different functions to perform
* airthematic operations with scalar values.
* 
* Following 3 functions use their corresponding *= compound
* operator internally for their operations.
* 
*/
//-----------------------------------------------
Mat2x2 operator*(const Mat2x2 &matLhs, const Mat2x2 &matRhs){
  Mat2x2 temp = matLhs;
  temp *= matRhs;
  return temp;
}

Mat2x2 operator*(double x, const Mat2x2 &matRhs){
  Mat2x2 temp;
  temp = matRhs;
  temp *= x;
  return temp;
}

Mat2x2 operator*(const Mat2x2 &matRhs, double x){
  return (x * matRhs);
}

//-----------------------------------------------
/*
* Following 3 functions defines the overloaded
* '/' airthmatic operator for this class so that 
* a Mat2x2 object can behave correctly when a
* division is performed. 
*
* Each of the following functions either
* accepts two Mat2x2 objects, or one scalar and one
* Mat2x2 object in the arguments list. The scalar
* value can also appears on either side of operator
* so we need 2 different functions to perform
* airthematic operations with scalar values.
* 
* Following 3 functions use their corresponding /= compound
* operator internally for their operations.
* 
*/
//-----------------------------------------------
Mat2x2 operator/(const Mat2x2 &matLhs, const Mat2x2 &matRhs){
  Mat2x2 temp = matLhs;
  temp /= matRhs;
  return temp;
}

Mat2x2 operator/(double x, const Mat2x2 &mat){
  Mat2x2 temp = mat.inverse();
  temp *= x;
  return temp;
}

Mat2x2 operator/(const Mat2x2 &mat, double x){
  Mat2x2 temp = mat;
  temp /= x;
  return temp;
}

//-----------------------------------------------
/*
* Following 3 functions defines the overloaded
* '+' airthmatic operator for this class so that 
* a Mat2x2 object can behave correctly when an
* addition is performed. 
*
* Each of the following functions either
* accepts two Mat2x2 objects, or one scalar and one
* Mat2x2 object in the arguments list. The scalar
* value can also appears on either side of operator
* so we need 2 different functions to perform
* airthematic operations with scalar values.
* 
* Following 3 functions use their corresponding += compound
* operator internally for their operations.
* 
*/
//-----------------------------------------------
Mat2x2 operator+(const Mat2x2 &matLhs, const Mat2x2 &matRhs){
  Mat2x2 temp = matLhs;
  temp += matRhs;
  return temp;
}

Mat2x2 operator+(double x, const Mat2x2 &mat){
  Mat2x2 temp = mat;
  temp += x;
  return temp;
}

Mat2x2 operator+(const Mat2x2 &mat, double x){
  return (x + mat);
}

//-----------------------------------------------
/*
* Following 3 functions defines the overloaded
* '-' airthmatic operator for this class so that 
* a Mat2x2 object can behave correctly when a
* subtraction is performed. 
*
* Each of the following functions either
* accepts two Mat2x2 objects, or one scalar and one
* Mat2x2 object in the arguments list. The scalar
* value can also appears on either side of operator
* so we need 2 different functions to perform
* airthematic operations with scalar values.
* 
* Following 3 functions use their corresponding -= compound
* operator internally for their operations.
* 
*/
//-----------------------------------------------
Mat2x2 operator-(const Mat2x2 &matLhs, const Mat2x2 &matRhs){
  Mat2x2 temp = matLhs;
  temp -= matRhs;
  return temp;
}

Mat2x2 operator-(const Mat2x2 &mat, double x){
  Mat2x2 temp = mat;
  temp -= x;
  return temp;
}

Mat2x2 operator-(double x, const Mat2x2 &mat){
  return -(mat - x);
}

//-----------------------------------------------
/*
* Following function returns the constant
* version of the subscript operator. Since a
* Mat2x2 class is a 2x2 matrix so valid options
* are 0,1,2,3 for any other values, it throws a
* invalid_argument exception.
* 
*/
//-----------------------------------------------
const double &Mat2x2::operator[](const int x) const {
  switch (x) {
    case 0:
      return a;
      break;
    case 1:
      return b;
      break;
    case 2:
      return c;
      break;
    case 3:
      return d;
      break;
    default:
      throw invalid_argument( "invalid argument" );
      break;
  }
}

//-----------------------------------------------
/*
* Following function returns the non constant
* version of the subscript operator, so it can
* update the value of the Mat2x2 object. 
* 
* Since a Mat2x2 class is a 2x2 matrix so valid options
* are 0,1,2,3 for any other values, it throws a
* invalid_argument exception.
* 
*/
//-----------------------------------------------
double &Mat2x2::operator[](const int x){
  switch (x) {
    case 0:
      return a;
      break;
    case 1:
      return b;
      break;
    case 2:
      return c;
      break;
    case 3:
      return d;
      break;
    default:
      throw std::invalid_argument( "invalid argument" );
      break;
  }
}

//-----------------------------------------------
/*
* Following 4 function overloads the post-increment,
* post-decrement, pre-increment and pre-decrement
* opertors for the Mat2x2 class.
*
* All of these functions uses the compund operators
* "+=" or "-=" for their operations internally.
* 
*/
//-----------------------------------------------
Mat2x2& Mat2x2::operator++(){
  *this += 1;
  return *this;
}

Mat2x2 Mat2x2::operator++(int x){
  Mat2x2 temp = *this;
  *this += 1;
  return temp;
}

Mat2x2& Mat2x2::operator--(){
  *this -= 1;
  return *this;
}

Mat2x2 Mat2x2::operator--(int x){
  Mat2x2 temp = *this;
  *this -= 1;
  return temp;
}


// change signs
//-----------------------------------------------
/*
* Following 2 function overloads the sign operators
* for the Mat2x2 class, where the "+" sign just returns
* the original matrix the "-" sign multiples the
* Mat2x2 object by -1 and returns the result
*
* Both of these functions doesn't update the original
* Mat2x2 object and returns a copy of it.
* 
*/
//-----------------------------------------------
Mat2x2 Mat2x2::operator+(){
  Mat2x2 temp = *this;
  return temp;
}

Mat2x2 Mat2x2::operator-(){
  Mat2x2 temp = *this;
  temp = -1 * temp;
  return temp;
}

// function objects
//-----------------------------------------------
/*
* Following function overloads the function call operator, "()"
* for Mat2x2 class, in the argument, this function accepts an
* integer value, where valid values are 1 and 2, if any other
* integer value is passed then it throws a invalid_argument
* error.
*
* This function basically returns a vector containing the
* eigen values for the Mat2x2 object, where eiger values are defined
* as:
*
* eigen1, eigen2 = tr(M)/2 (+)(-) sqrt(pow(trace(M), 2) - 4 * (determinant(M)))/2
* since sqrt(pow(trace(M), 2) - 4 * (determinant(M))) can be either positive
* or negative so this function either contains vector of size 1 or size 2
* for positive and negative values of the sqrt part.
*/
//-----------------------------------------------
vector<double> Mat2x2::operator()(int x){
  bool complex = false;
  vector<double> temp;
  double sqrtPart = (pow(trace(), 2) - 4 * (determinant()));
  if(sqrtPart >= 0){
      sqrtPart = sqrt(sqrtPart)/2;
  }
  else{
      complex = true;
      sqrtPart = sqrt(-sqrtPart)/2;
  }
  double realPart = trace()/2;
  if(x == 1){
      if(!complex){
          temp.push_back(realPart + sqrtPart);
      }
      else{
          temp.push_back(realPart);
          temp.push_back(sqrtPart);
      }
      return temp;
  }
  else if(x == 2){
      if(!complex){
          temp.push_back(realPart - sqrtPart);
      }
      else{
          temp.push_back(realPart);
          temp.push_back(-sqrtPart);
      }
      return temp;
  }
  else{
      throw invalid_argument( "invalid argument" );
  }
}

//-----------------------------------------------
/*
* Following function alo overloads the function call operator, "()"
* for Mat2x2 class, in this case there are no values are passed in
* the argument.
*
* This function simply returns the determinat of the Mat2x2 object
*/
//-----------------------------------------------
int Mat2x2::operator()(){
  return (determinant());
}

//-----------------------------------------------
/*
* Overloaded output operator to print the Mat2x2
* object in a specific way, it accepts a ostream and Mat2x2
* objects and returns the reference ostream object so it can
* be chained.
*
* This function doesn't updates the input Mat2x2 object.
*/
//-----------------------------------------------
ostream &operator<<(ostream &cout, const Mat2x2 &mat){
  int leftWidthLength = mat.maxLeftMemLength(); // get max width of the left side members, i.e a and c
  int rightWidthLength = mat.maxRightMemLength(); // get max width of the right side members, i.e b and d
  cout << fixed << setprecision(2);
  cout << "|" << setw(leftWidthLength) << mat.a << " " << setw(rightWidthLength) << mat.b << "|" << endl;
  cout << "|" << setw(leftWidthLength + rightWidthLength + 2) << "|" << endl;
  cout << "|" << setw(leftWidthLength) << mat.c << " " << setw(rightWidthLength) << mat.d << "|" << endl;
  return cout;
}

//-----------------------------------------------
/*
* Overloaded input operator to fill the value of Mat2x2
* object, it accepts a istream and Mat2x2
* objects and returns the reference ostream object so it can
* be chained.
*
* This function updates the input Mat2x2 object.
*/
//-----------------------------------------------
istream &operator>>(istream &in, Mat2x2 &mat){
  double a1, a2, a3, a4;
  cout << "To create the following 2*2 matrix:" << endl;
  cout << "|a  b|" << endl;
  cout << "|    |" << endl;
  cout << "|c  d|" << endl;
  cout << "enter four numbers a, b, c, d, in that order" << endl;
  in >> a1 >> a2 >> a3 >> a4;
  Mat2x2 temp(a1, a2, a3, a4);
  mat = temp;
  return in;
}

//-----------------------------------------------
/*
* This is a helper method to find the maximum length
* of the right side members in the matrix, i.e a and c
* so the Mat2x2 object could be ouput with correct formatting
*/
//-----------------------------------------------
int Mat2x2::maxLeftMemLength() const {
  stringstream ssa, ssc;
  ssa << fixed << setprecision(2);
  ssa << a;
  
  ssc << fixed << setprecision(2);
  ssc << c;
  
  int aLength = (int) ssa.str().size();
  int cLength = (int) ssc.str().size();
  
  int max = aLength >= cLength ? aLength : cLength;
  return max;
}

//-----------------------------------------------
/*
* This is a helper method to find the maximum length
* of the right side members in the matrix, i.e a and c
* so the Mat2x2 object could be ouput with correct formatting
*/
//-----------------------------------------------
int Mat2x2::maxRightMemLength() const {
  stringstream ssb, ssd;
  ssb << fixed << setprecision(2);
  ssb << b;
  
  ssd << fixed << setprecision(2);
  ssd << d;
  
  int bLength = (int) ssb.str().size();
  int dLength = (int) ssd.str().size();
  
  int max = bLength >= dLength ? bLength : dLength;
  return max;
}

//-----------------------------------------------
/*
* This is a helper method is used in airthmetic
* compound operators because when we multiply
* a 0 with -1 then the complier returns a -0, since
* a -0 doesn't exists so it just adds a 0.0 to the original
* values to change a negative zero to a positive zero
*/
//-----------------------------------------------
void Mat2x2::removeNegativeZeros(){
  a = a + 0.0;
  b = b + 0.0;
  c = c + 0.0;
  d = d + 0.0;
}
