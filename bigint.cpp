#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase) {
  if(setbase < 2 || setbase > 36){
      throw InvalidBaseException();
  }
  /************* You complete *************/
  base = setbase;
  isPositive = true;
  if (input == 0) {
    vec.push_back(0);
  }
  else {
    if (input < 0) {
      input *= -1;
      isPositive = false;
    }
    while (input > 0) {
      int hold = input % base;
      vec.push_back(hold);
      input /= base;
    }
  }
}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input strings will contain only
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=36]
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
  if(setbase < 2 || setbase > 36){
      throw InvalidBaseException();
  }
  /************* You complete *************/
  base = setbase;
  if (s[0] == '-') {
    isPositive = false;
  }
  else {
    isPositive = true;
  }
  
  int len = s.length();
  vec.push_back(0);
  
  for (int i = 0; i < len; i++)
  {
    int hold = (int) s[len - i - 1];
    int div = 1; //to see if we need to carry any over
    if (hold < 58 && hold >= 48) {
      hold -= 48;
      int stay = hold % base;
      int carry = hold / base;
      vec[i] += stay;
      if (i == (len-1) && carry != 0) {
        vec.push_back(carry);
        if (vec[i] > base) {
          div = vec[i]/base;
          vec[i] -= (div*base);
          vec[i+1] += div;
        }
      }
      else if (i < (len-1)) {
        vec.push_back(carry);
        if (vec[i] > base) {
          div = vec[i]/base;
          vec[i] -= (div*base);
          vec[i+1] += div;
        }
      }
    }
    else if ((hold <= 90 && hold >= 65) ||
            (hold <= 122 && hold >= 97))
    {
      if (hold <= 122 && hold >= 97) {
        hold -= 32;
      }
      hold -= 55;
      int stay = hold % base;
      int carry = hold / base;
      vec[i] += stay;
      if (i == (len-1) && carry != 0) {
        vec.push_back(carry);
        if (vec[i] > base) {
          div = vec[i]/base;
          vec[i] -= (div*base);
          vec[i+1] += div;
        }
      }
      else if (i < (len-1)) {
        vec.push_back(carry);
        if (vec[i] > base) {
          div = vec[i]/base;
          vec[i] -= (div*base);
          vec[i+1] += div;
        }
      }
    }
  }
  int newSize = this->vec.size() - 1;
  int index = newSize;
  
  while (this->vec[index] == 0) {
    this->vec.pop_back();
    index--;
    if (this->vec.size() == 0) {
      this->vec.push_back(0);
      break;
    }
  }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
  *this = b;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  Overriding a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/
  if (this == &b)
  {
    return *this;
  }
  this->vec.clear();
  
  isPositive = b.isPositive;
  base = b.base;
  int b_size = b.vec.size();
  for (int i = 0; i < b_size; i++)
  {
    this->vec.push_back(b.vec[i]);
  }

  return *this;
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/
  string str = "";
  
  if (!isPositive) {
    str += "-";
  }
  
	int len = vec.size();
  for (int i = len - 1; i >= 0; i--)
  {
    if (vec[i] >= 10) {
      str += ((char) ('A' + vec[i] - 10));
    }
    else {
      str += ((char) ('0' + vec[i]));
    }
  }
  return str;
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/
	long long len = vec.size();
  long long value = 0;
  long long factor = 1;

  if (isPositive) {
    for (unsigned int i = 0; i < len; i++) {
      value += (vec[i] * factor);
      if (value >= INT_MAX || factor >= INT_MAX) {
        return INT_MAX;
      }
      factor *= base;
    }
  }
  else if (!isPositive) {
    for (unsigned int i = 0; i < len; i++) {
      value -= (vec[i] * factor);
      if (value <= INT_MIN || factor >= INT_MAX) {
        return INT_MIN;
      }
      factor *= base;
    }
  }
  int var = (int) value;
  return var;
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?
  if (this->isPositive != b.isPositive)
  {
    if (this->isPositive) {
      return 1;
    }
    else if (b.isPositive) {
      return -1;
    }
  }
    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
  int vSize = this->vec.size();
  int bSize = b.vec.size();
  if (this->isPositive == b.isPositive && vSize != bSize) {
    if (this->isPositive) {
      if (vSize > bSize) {
        return 1;
      }
      else {
        return -1;
      }
    }
    else if (!this->isPositive) {
      if (vSize > bSize) {
        return -1;
      }
      else{
        return 1;
      }
    }
  }
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
  int indexed = vSize - 1;
  if (this->isPositive == b.isPositive 
      && vSize == bSize && this->isPositive) {
    for (int i = indexed; i >= 0; i--) {
      if (this->vec[i] > b.vec[i]) {
        return 1;
      }
      else if (this->vec[i] < b.vec[i]) {
        return -1;
      }
    }
  }
  else if (this->isPositive == b.isPositive 
      && vSize == bSize && !this->isPositive){
    for (int i = indexed; i >= 0; i--) {
      if (this->vec[i] < b.vec[i]) {
        return 1;
      }
      else if (this->vec[i] > b.vec[i]) {
        return -1;
      }
    }    
  }
    
  //If ALL digits are the same, then they MUST be equal!!
  return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if (a.compare(b) == 0) {
    return true;
  }
  else {
    return false;
  }
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if (a.compare(b) != 0) {
    return true;
  }
  else {
    return false;
  }
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  int result = a.compare(b);
  if (result != 1) {
    return true;
  }
  else {
    return false;
  }
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  int result = a.compare(b);
  if (result != -1) {
    return true;
  }
  else {
    return false;
  }
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if (a.compare(b) == 1) {
    return true;
  }
  else {
    return false;
  }
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  if (a.compare(b) == -1) {
    return true;
  }
  else {
    return false;
  }
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt c(a);
  c += b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
  if(base != b.base){
      throw DiffBaseException();
  }
  /************* You complete *************/
  int negs = 0;
  if (!this->isPositive) {
    negs++;
  }
  if (!b.isPositive) {
    negs++;
  }
  
  if (negs == 0 || negs == 2) {
    if (negs == 2) {
      BigInt temp = b;
      temp.isPositive = true;
      this->isPositive = true;
      *this += temp;
      this->isPositive = false;
    }
    else if (this->to_int() == 0) {
      *this = b;
    }
    else {
      int carry = 0;
      int counts = 0;
      for (unsigned int i = 0; i < max(this->vec.size(), b.vec.size()); i++) {
        int valA = 0;
        int valB = 0;
        if (i < min(this->vec.size(), b.vec.size())) {
          valA = this->vec[i];
          valB = b.vec[i];
        }
        else if (i >= min(this->vec.size(), b.vec.size())
                && min(this->vec.size(), b.vec.size()) == b.vec.size()) {
          valA = this->vec[i];
        }
        else if (i >= min(this->vec.size(), b.vec.size())
                && min(this->vec.size(), b.vec.size()) ==this->vec.size()) {
          valB = b.vec[i];
        }
        int hold = valA + valB;
        int num = hold % base;
        int stay = num + carry;
        counts = 0;
        
        if (stay >= base) {
          stay %= base;
          counts++;
        }
        
        if (i < this->vec.size()) {
          this->vec[i] = stay;
        }
        else {
          this->vec.push_back(stay);
        }
        carry = (hold / base) + counts;
      }
      if (carry > 0) {
        this->vec.push_back(carry);
      }
    }
  }
  else {
    if (!this->isPositive) {
      this->isPositive = true;
      if (*this >= b) {
        *this -= b;
        this->isPositive = false;
      }
      else {
        BigInt temp = *this;
        *this = b;
        *this -= temp;
        this->isPositive = true;
      }
    }
    else {
      BigInt temp = b;
      temp.isPositive = true;
      *this -= temp;
    }
  }
  
  int newSize = this->vec.size() - 1;
  int index = newSize;
  while (this->vec[index] == 0) {
    this->vec.pop_back();
    index--;
    if (this->vec.size() == 0) {
      this->vec.push_back(0);
      this->isPositive = true;
      break;
    }
  }
  newSize++;
  for (int i = 0; i < newSize; i++)
  {
    if (i > 0 && vec[i] > base) {
      int div = vec[i-1]/base;
      vec[i-1] -= (div*base);
      vec[i] += div;
    }
  }
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt c(a);
  c -= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
  int negs = 0;
  if (!this->isPositive) {
    negs++;
  }
  if (!b.isPositive) {
    negs++;
  }
  
  
  if (this->to_int() == 0) {
    *this = b;
    if (this->isPositive) {
      this->isPositive = false;
    }
    else {
      this->isPositive = true;
    }
  }
  else if (negs == 0 or negs == 2) {
    if (negs == 2) {
      BigInt temp = b;
      temp.isPositive = true;
      *this += temp;
    }
    else {
      BigInt temp = *this;
      if (*this < b) {
        *this = b;
        this->isPositive = false;
      }
      else if (*this > b) {
        temp = b;
      }
      for (unsigned int i = 0; 
           i < max(this->vec.size(), temp.vec.size()); i++) {
        int valA = 0;
        int valB = 0;
        if (i < min(this->vec.size(), temp.vec.size())) {
          valA = this->vec[i];
          valB = temp.vec[i];
        }
        else if (i >= min(this->vec.size(), temp.vec.size()) 
                 && max(this->vec.size(), temp.vec.size()) == this->vec.size()) {
          valA = this->vec[i];
        }
        else if (i >= min(this->vec.size(), temp.vec.size())
                && max(this->vec.size(), temp.vec.size()) == temp.vec.size()) {
          valB = temp.vec[i];
        }

        int hold = valA - valB;
        if (hold < 0) {
          int index = 1;
          while (this->vec[i + index] == 0) {
            index++;
          }
          while (index > 1) {
            this->vec[i + index]--;
            this->vec[i + index - 1] += base;
            index--;
          }
          this->vec[i + index]--;
          hold += base;
        }
        this->vec[i] = hold;
       }
    }
  }
  else {    
    if (!this->isPositive) {
      this->isPositive = true;
      *this += b;
      this->isPositive = false;
    }
    else if (!b.isPositive) {
      BigInt temp = b;
      temp.isPositive = true;
      *this += temp;
    }
  }
  
  int newSize = this->vec.size() - 1;
  int index = newSize;
  while (this->vec[index] == 0) {
    this->vec.pop_back();
    index--;
    if (this->vec.size() == 0) {
      this->vec.push_back(0);
      this->isPositive = true;
      break;
    }
  }
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt c(a);
  c *= b;
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
  
  int vSize = this->vec.size();
  int bSize = b.vec.size();
  int carry = 0;
  if (this->to_int() == 0) {
    return *this;
  }
  else if (b.to_int() == 0) {
    *this = b;
    return *this;
  }
  else {
    BigInt product(this->base);
    int totalSize = vSize + bSize;
    for (int i = 0; i < totalSize; i++) {
      product.vec.push_back(0);
    }
    for (int i = 0; i < bSize; i++) {
      BigInt temp(this->base);
      for (int j = 0; j < i; j++) {
        temp.vec.push_back(0);
      }
      for (int k = 0; k < vSize; k++) {
          int hold = this->vec[k] * b.vec[i];
          if (carry != 0) {
            hold += carry;
            carry = 0;
          }
          if (hold>=base){
            carry = hold / this->base;
            hold = hold % this->base;
          }
          temp.vec.push_back(hold);
      }
        
      if(carry !=0){
        temp.vec.push_back(carry);
        carry = 0;    
      }
      product += temp;
    }
    
    int negs = 0;
    if (!this->isPositive) {
      negs++;
    }
    if (!b.isPositive) {
      negs++;
      if (negs == 2) {
        product.isPositive = true;
      }
    }
    if (negs == 1) {
      product.isPositive = false;
    }
    *this = product;
    return *this;
  }
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt c(a);
  c /= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
  BigInt quotient(this->base);
  BigInt remainder(this->base);
  divisionMain(b, quotient, remainder);
  *this = quotient;
    int newSize = this->vec.size() - 1;
  int index = newSize;
  while (this->vec[index] == 0) {
    this->vec.pop_back();
    index--;
    if (this->vec.size() == 0) {
      this->vec.push_back(0);
      this->isPositive = true;
      break;
    }
  }
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt c(a);
  c %= b;
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/
  BigInt quotient(this->base);
  BigInt remainder(this->base);
  remainder.isPositive = this->isPositive;
  divisionMain(b, quotient, remainder);
  *this = remainder;
    int newSize = this->vec.size() - 1;
  int index = newSize;
  while (this->vec[index] == 0) {
    this->vec.pop_back();
    index--;
    if (this->vec.size() == 0) {
      this->vec.push_back(0);
      this->isPositive = true;
      break;
    }
  }
  return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
  BigInt divisor = b;
  const BigInt dividend = *this;
  // b and dividend are our const comparers
  int negs = 0;
  if (!this->isPositive) {
    negs++;
  }
  if (!divisor.isPositive) {
    negs++;
    if (negs == 2) {
      quotient.isPositive = true;
    }
  }
  if (negs == 1) {
    quotient.isPositive = false;
  }
  
  // to simplify operations
  divisor.isPositive = true;
  this->isPositive = true;
  
  //to make things easier on us
  BigInt zero(0, this->base);
  BigInt negOne(-1, this->base);
  BigInt one(1, this->base);
  
  if ((b > dividend && negs == 0) || (b < dividend && negs == 2)) {
    quotient = zero;
    remainder = dividend;
  }
  else if (*this == divisor && negs == 1) {
    quotient = negOne;
    remainder = zero;
  }
  else if (*this == divisor && (negs == 0 || negs == 2)) {
    quotient = one;
    remainder = zero;
  }
  else if (b == one) {
    if (negs == 1) {
      quotient = dividend;
    }
    else if (negs == 0) {
      quotient = dividend;
    }
    remainder = zero;
  }
//   else if (this->to_int() < divisor.to_int()) {
//     quotient = zero;
//     remainder = *this;
//     if (negs == 1) {
//       this->isPositive = false;
//     }
//   }
  else if (b == negOne) {
    if (negs == 1) {
      this->isPositive = false;
    }
    quotient = *this;
    remainder = zero;
  }
  else if (*this == zero) {
    quotient = zero;
    remainder = zero;
  }
  else {
    int pos = this->vec.size() - 1;
    BigInt divSeq(this->base);
    while(!this->vec.empty()) {
      while ((divSeq < divisor && !this->vec.empty())) {
        if(divSeq == zero) {
          divSeq.vec.pop_back();
        }
        divSeq.vec.insert(divSeq.vec.begin(), this->vec[pos]);
        pos--;
        this->vec.pop_back();
        if (divSeq < divisor && !this->vec.empty()) {
          quotient.vec.insert(quotient.vec.begin(), 0);
        }
      }
      int count = 0;
      while (divSeq >= divisor) {
        divSeq -= divisor;
        count++;
      }
      if (count < base) {
        quotient.vec.insert(quotient.vec.begin(), count);
      }
      else {
        quotient.vec.insert(quotient.vec.begin(), count%base);
        quotient.vec.insert(quotient.vec.begin(), count/base);
      }
    }
    remainder = divSeq;
    if (!dividend.isPositive) {
      remainder.isPositive = false;
    }
  }
}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  BigInt c(a);
  c.exponentiation(b);
  return c;
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
  BigInt exp = b;
  BigInt zero(0, this->base);
  BigInt one(1, this->base);
  BigInt two(2, this->base);
  BigInt factor = one;

  if (!this->isPositive && exp % two != zero) {
    this->isPositive = false;
  }
  else {
    this->isPositive = true;
  }
  
  while (true) {
    if (exp == zero) {
      *this = one;
      return *this;
    }
    else if (exp == one) {
      *this *= factor;
      return *this;
    }
    else if ((exp % two) != zero) {
      factor *= *this;
      *this *= *this;
      exp = ((exp - one)/two);
    }
    else if (exp % two == zero) {
      *this *= *this;
      exp /= two;
    }
  }
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
  
  BigInt c(a);
  c.modulusExp(b, m);
  return c;
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
  BigInt exp = b;
  BigInt zero(0, this->base);
  BigInt one(1, this->base);
  BigInt two(2, this->base);
  BigInt factor = one;
  
  while (true) {
    if (exp == zero) {
      *this = one;
      return *this;
    }
    else if (exp == one) {
      *this *= factor;
      *this %= m;
      return *this;
    }
    else if (exp % two != zero) {
      factor *= *this;
      factor %= m;
      *this *= *this;
      *this %= m;
      exp = ((exp - one)/two);
    }
    else if (exp % two == zero) {
      *this *= *this;
      *this %= m;
      exp /= two;
    }
  }
  
  return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

