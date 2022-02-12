#include <iostream>

#include "derivador.cc"

using namespace std;

int main() {
  auto f = 3.0 * x * x;
  double v = 7;
  
  cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}
