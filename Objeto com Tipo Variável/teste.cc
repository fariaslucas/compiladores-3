#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <type_traits>
#include <functional>

#include "var.cc"

using namespace std;

Var print( const Var& o ) {
  cout << "{ nome: " << o["nome"]
       << ", idade: " << o["idade"]( o )
       << ", nascimento: " << o["nascimento"]
       << ", print: " << o["print"] 
       << ", atr: " << o["atr"] 
       << " }" << endl;
       
  return Var();     
}

void imprime( Var v ) {
    v["print"]( v );
}

int main( int argc, char* argv[] ) {
  try {     

    Var a, b;
    a = 10.1;
    b = []( auto x ){ return x + x; };
    cout << b( a ) << " ";
    cout << b( "oba" ) << " ";
    cout << b( 'X' ) << " ";
    cout << b( true );

    return 0;
  
  } catch( Var::Erro e ) {
    cout << "Erro fatal: " << e() << endl;
  }
}