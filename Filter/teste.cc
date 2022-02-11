#include <iostream>

#include "filter.cc"

using namespace std;

int main( int argc, char* argv[]) {
  
    vector<string> v1 = { "janeiro", "fevereiro", "março", "abril", "maio" };
    v1 | &string::length | [] ( int x ) { cout << x << " "; };
  
    return 0;
}