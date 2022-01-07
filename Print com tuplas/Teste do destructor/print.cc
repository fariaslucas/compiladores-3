#include <iostream>
#include <initializer_list>
#include <memory>

using namespace std;

class AbstractPair {
    public:
        virtual ~AbstractPair() {}
        virtual void imprime(ostream& o) = 0;
};

template<typename A, typename B>
class PairImpl: public AbstractPair {
    public:
        PairImpl(A& valor1, B& valor2): primeiro(valor1), segundo(valor2) {}

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
        Pair(A primeiro, B segundo): p(shared_ptr<AbstractPair>{new PairImpl<A,B>(primeiro,segundo)}) {}

        void imprime(ostream& o) {
            p->imprime(o);
        }

    private:
        shared_ptr<AbstractPair> p;
};

void print(ostream& o, initializer_list<Pair> lista) {
    for (Pair elemento : lista) {
        elemento.imprime(o);
    }
}