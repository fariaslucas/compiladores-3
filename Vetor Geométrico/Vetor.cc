#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template<int n, typename T>
class Vetor {
    public:
        class MeioDasOperacoes {
            private:
                Vetor<n,T> *vetorOp;
                MeioDasOperacoes(Vetor<n,T> *v): vetorOp(v) {}
                friend class Vetor;

            public:
                MeioDasOperacoes operator , (T valor) {
                    *vetorOp = valor;
                    return *this;
                }
        };

        void insere(T valor) {
            vetor.push_back(valor);
        }

        MeioDasOperacoes operator = (initializer_list<T> valores) {
            for (T valor : valores)
                insere(valor);

            return MeioDasOperacoes(this);
        }

        const void print(ostream& o) {
            for (T valor : vetor)
                o << valor << " ";
        }

        Vetor<n,T> operator + (const Vetor<n,T>& v) {
            Vetor<n,T> soma;
            for (unsigned int i = 0; i < n; i++)
                soma.insere(vetor[i] + v.vetor[i]);
            
            return soma;
        }

        Vetor<n,T> operator - (const Vetor<n,T>& v) {
            Vetor<n,T> resto;
            for (unsigned int i = 0; i < n; i++)
                resto.insere(vetor[i] - v.vetor[i]);
            
            return resto;
        }

        T operator * (const Vetor<n,T>& v) {
            T produto = 0;
            for (unsigned int i = 0; i < n; i++)
                produto += vetor[i] * v.vetor[i];

            return produto;
        }

        Vetor<n,T> operator * (T escalar) {
            Vetor<n,T> produto;
            for (unsigned int i = 0; i < n; i++)
                produto.insere(vetor[i] * escalar);

            return produto;
        }

        Vetor<n,T> operator / (T escalar) {
            Vetor<n,T> quociente;
            for (unsigned int i = 0; i < n; i++)
                quociente.insere(vetor[i] / escalar);

            return quociente;
        }

        MeioDasOperacoes operator * () {
            return MeioDasOperacoes(this);
        }

        Vetor<n,T> operator * (const MeioDasOperacoes& meio) {
            Vetor<n,T> produto;

            if (n == 2) {
                produto.insere(0);
                produto.insere(0);
            }
            else if (n == 3) {
                produto.insere(vetor[1] * (meio.vetorOp)->vetor[2] - vetor[2] * (meio.vetorOp)->vetor[1]);
                produto.insere(vetor[2] * (meio.vetorOp)->vetor[0] - vetor[0] * (meio.vetorOp)->vetor[2]);
            }
            produto.insere(vetor[0] * (meio.vetorOp)->vetor[1] - vetor[1] * (meio.vetorOp)->vetor[0]);

            return produto;
        }

    private:
        vector<T> vetor;
};

template<int n, typename T>
Vetor<n,T> operator * (T escalar, Vetor<n,T> vetor) {
    return vetor * escalar;
}

template<int n, typename T>
ostream& operator << (ostream& o, Vetor<n,T> vetor) {
    vetor.print(o);
    return o;
}