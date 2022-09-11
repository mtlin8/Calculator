#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {
  
  

  
  
//   BigInt thistest("10000000000000000", 16);
//   cout<<thistest.to_int()<<endl;
    
//   BigInt x(2, 10);
//   BigInt y(72, 2);
//   x *= y;
//   //cout << x.to_string() << endl;
//   cout << x.to_int() << endl;
  
//   BigInt a("2", 10);
//   BigInt b("72", 10);
//   BigInt exp = pow(a, b);
//   cout << exp.to_int() << endl;
  
//   BigInt a("-3", 10);
//   BigInt b(2, 10);
//   a %= b;
//   cout << a.to_string() << endl;
  
  BigInt x("978804645501", 10);
  BigInt y("838281360509", 10);
  BigInt z("1006072556617", 10);
  modPow(x, y, z);
  cout << (char)x.to_int() << endl;
  // outputs weird char when it should output O

  BigInt var1(496,10);
  BigInt var2(249,10);
  BigInt var3(1189,10);
  BigInt var4 = modPow(var1,var2,var3);
  cout<<var4.to_int()<<endl;//should print 72
  cout<<(char)var4.to_int()<<endl;//should print "H"
  
  return 0;
}
