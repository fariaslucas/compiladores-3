#include <iostream>

using namespace std;

class PilhaInt {
    public:
        PilhaInt() {
            topo = 0;
            for (int i = 0; i < capacidade; i++)
                pilha[i] = 0;
        }

        void empilha(int valor) {
            pilha[topo++] = valor;
        }

        int desempilha() {
            return pilha[--topo];
        }

        const void print(ostream& o) {
            o << "[ ";
            for (int i = 0; i < topo-1; i++)
                o << pilha[i] << ", ";
            o << pilha[topo-1] << " ]";
        }

        const PilhaInt& operator = (const PilhaInt& p) {
            topo = p.topo;
            for (int i = 0; i < topo; i++) 
                pilha[i] = p.pilha[i];
            return *this;
        }

        PilhaInt& operator << (int valor) {
            empilha(valor);
            return *this;
        }
    
    private:
        static const int capacidade = 5;
        int pilha[capacidade];
        int topo;
};

// Apenas para teste
int main() {
    PilhaInt p;
    p << 19 << 18 << 17 << 30;

    p.print(cout);

    cout << endl;

    return 0;
}