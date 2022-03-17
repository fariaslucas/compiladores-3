#include <iostream>

#include "derivador.cc"

using namespace std;

int main() {
 // auto f = 3.0 + x + x;
  //auto f = x*x;
  //auto f = x - (x - 5.0);
  auto f = (x+7.0)*(x-7.0);
  //auto f = x->*3;
  //auto f = (7.0*x+5.0)->*3;
  //auto f = sin( x + 5 );
  //auto f = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4;
  //auto f = exp( x * log( x - 8.0 ) + 1.0 );
  //auto f = exp( (x + 1.0)*(x - 1.0) )->*2;
  //auto f = log( x->* 4 + 8.0 ) * sin( cos( x / 3.14 ) );
  //auto f = log( (8.1/(x+1.0)->*3 - 9.2 ) * (x + 3) * sin( cos( x / 3.14 ) + x ));

  //auto f = sin(x)->*2;

  cout << "f(x) = " << f.str() << ", f'(x) = " << f.dx_str() << endl;
}
