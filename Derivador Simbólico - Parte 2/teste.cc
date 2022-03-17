#include <iostream>

#include "simbolico.cc"

using namespace std;

int main() {
  auto f = x->*3;
  //auto f = exp( x * log( x - 8.0 )  + 1.0 );

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}
