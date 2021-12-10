#include <iostream>

using namespace std;

class PilhaInt {
    public:
        PilhaInt(int tamanho = 10) {
            MAX_PILHA = tamanho;
            tab = (int *) malloc(MAX_PILHA * sizeof(int));

            for (int i = 0; i < MAX_PILHA; i++)
                tab[i] = 0;
            topo = 0;
        }

        PilhaInt(const PilhaInt& p) {
            MAX_PILHA = p.MAX_PILHA;

            tab = (int *) malloc(MAX_PILHA * sizeof(int));
            for (int i = 0; i < MAX_PILHA; i++) 
                tab[i] = p.tab[i];

            topo = p.topo;
        }

        ~PilhaInt() {
            free(tab);
        }

        int capacidade() {
            return MAX_PILHA;
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
        int MAX_PILHA;
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
    PilhaInt a( 7 );
    a << 3 << 5 << 13 << 19;
    PilhaInt b{ embaralha( a ) };
    a.print( cout ); cout << endl;
    b.print( cout ); cout << endl;

    return 0;
}