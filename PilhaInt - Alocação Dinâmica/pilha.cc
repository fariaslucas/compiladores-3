#include <iostream>

using namespace std;

class PilhaInt {
    public:
        PilhaInt(int capacidade = 10) {
            tab = (int *) malloc(capacidade * sizeof(int));
            for (int i = 0; i < capacidade; i++)
                tab[i] = 0;
            topo = 0;
        }

        ~PilhaInt() {
            free(tab);
        }

        void empilha(int valor) {
            tab[topo++] = valor;
        }

        int desempilha() {
            return tab[--topo];
        }

        const void print(ostream& o) {
            o << "[ ";
            for (int i = 0; i < topo-1; i++)
                o << tab[i] << ", ";
            o << tab[topo-1] << " ]";
        }

        const PilhaInt& operator = (const PilhaInt& p) {
            topo = p.topo;
            for (int i = 0; i < topo; i++) 
                tab[i] = p.tab[i];
            return *this;
        }

        PilhaInt& operator << (int valor) {
            empilha(valor);
            return *this;
        }
    
    private:
        int *tab;
        int topo;
};

PilhaInt embaralha( PilhaInt q ) {
    int aux = q.desempilha();
    q << 32 << 9 << aux;
    
    return q;
}

// Apenas para teste
int main() {
    PilhaInt p;
    p << 19 << 18 << 17 << 30;

    p.print(cout);

    cout << endl;

    return 0;
}