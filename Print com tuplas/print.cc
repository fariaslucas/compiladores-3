#include <initializer_list>
#include <iostream>

using namespace std;

class AbstractPair {
    public:
        virtual void imprime(ostream& o) = 0;
};

template<typename A, typename B>
class PairImpl: public AbstractPair {
    public:
        PairImpl(A valor1, B valor2): primeiro(valor1), segundo(valor2) {}

        void imprime(ostream& o) {
            o << primeiro << " = " << segundo << endl;
        }
    
    private:
        A primeiro;
        B segundo;
};

class Pair {
    public:
        template <typename A, typename B>
        Pair(A primeiro, B segundo) {
            p = new PairImpl<A,B>(primeiro,segundo);
        }

        void imprime(ostream& o) {
            p->imprime(o);
        }

    private:
        AbstractPair *p;
};

void print(ostream& o, initializer_list<Pair> lista) {
    for (Pair elemento : lista) {
        elemento.imprime(o);
    }
}

int main() {
    Pair p( "1", 2 );
  
    print(cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } });

    return 0;  
}