#include <iostream>
#include <fstream> 
#include <ctime> 


using namespace std; 


int main(int argc, char** argv)
{
    string      line;
   ifstream inFile; 

   inFile.open("DO_NOT_OPEN.dat");

   getline(inFile, line);

   cout << line;


    return 0;
}