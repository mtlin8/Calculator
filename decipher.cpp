#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/
  ifstream ifile (argv[1]);
  if (ifile.fail())
  {
    cout<< "Couldn't open file" <<endl;
    return 1;
  }
  
  int base;
  string d, n;
  ifile >> base >> d >> n;
  try {
    BigInt privateKey(d, base);
    BigInt mod(n, base);

    char line[100];
    ifile.getline(line, 100);
    while (!ifile.fail()) {
      BigInt secretCode(line, base);
      BigInt out(base);
      out = modPow(secretCode, privateKey, mod);
      cout << "" << (char)out.to_int();
      ifile.getline(line, 100);
    }
  }
  catch(const exception& e) {
    cout<<e.what()<<endl;//print the message of the exception defined in its "what" function.
    return -1;//end the program and return status != 0 to indicate that there is an error.
  }
    
  cout << endl;
  
  ifile.close();
	return 0;
}

