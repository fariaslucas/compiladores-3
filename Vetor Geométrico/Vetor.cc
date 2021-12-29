#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template<int n, typename T>
class Vetor {
    public:
        class MeioDaAtribuicao {
            private:
                Vetor<n,T> *vetorAtr;
                MeioDaAtribuicao(Vetor<n,T> *v): vetorAtr(v) {}
                friend class Vetor;

            public:
                MeioDaAtribuicao operator , (T valor) {
                    *vetorAtr = valor;
                    return *this;
                }
        };

        MeioDaAtribuicao operator = (initializer_list<T> valores) {
            for (auto elemento : valores)
                vetor.push_back(elemento);

            return MeioDaAtribuicao(this);
        }

    private:
        vector<T> vetor;
};