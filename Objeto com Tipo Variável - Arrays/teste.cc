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
    a = newArray();
    a["sqr"] = []( Var n )->Var{ return n*n; };

    for( b = 0; (b < 10).asBool(); b = b + 1 )
      a[b] = a["sqr"]( b );

    auto pares = []( auto n ){ return n%2 == 0; };

    a.filter( pares ).forEach( []( Var n ){ cout << n << " "; } );
    cout << endl;

    return 0;
  
  } catch( Var::Erro e ) {
    cout << "Erro fatal: " << e() << endl;
  }
}