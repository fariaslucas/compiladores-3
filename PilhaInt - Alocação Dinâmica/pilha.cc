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

            topo = p.topo;
            for (int i = 0; i < topo; i++) 
                tab[i] = p.tab[i];
        }

        ~PilhaInt() {
            free(tab);
        }

        int capacidade() {
            return MAX_PILHA;
        }

        void empilha(int valor) {
            if (topo > MAX_PILHA-1) {
                redimensiona(2 * MAX_PILHA);
            }
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

        PilhaInt& operator = (const PilhaInt& p) {
            if (MAX_PILHA != p.MAX_PILHA)
                redimensiona(p.MAX_PILHA);

            topo = p.topo;
            for (int i = 0; i < topo; i++) 
                tab[i] = p.tab[i];

            return *this;
        }

        PilhaInt& operator << (int valor) {
            empilha(valor);
            return *this;
        }

        void redimensiona(int n) {
            if (n < MAX_PILHA) {
                for (int i = topo; i > n; i--)
                    desempilha();
            }

            MAX_PILHA = n;
            tab = (int *) realloc(tab, MAX_PILHA * sizeof(int));
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
    PilhaInt a{3};
    for( int i = 0; i < 20; i++ ) {
        a << i;
        cout << a.capacidade() << " ";
    }
    cout << endl;
    a.print( cout ); cout << endl;

    return 0;
}