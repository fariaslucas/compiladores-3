#include <iostream>

using namespace std;

class PilhaInt {
    public:
        PilhaInt(int tamanho = 10) {
            tam_pilha = tamanho;
            pilha = (int *) malloc(tam_pilha * sizeof(int));
            topo = 0;

            for (int i = 0; i < tam_pilha; i++)
                pilha[i] = 0;
        }

        PilhaInt(const PilhaInt& p) {
            tam_pilha = p.tam_pilha;
            pilha = (int *) malloc(tam_pilha * sizeof(int));
            topo = p.topo;

            for (int i = 0; i < topo; i++) 
                pilha[i] = p.pilha[i];
        }

        ~PilhaInt() {
            free(pilha);
        }

        void empilha(int valor) {
            if (topo > tam_pilha-1)
                redimensiona(2 * tam_pilha);

            pilha[topo++] = valor;
        }

        int desempilha() {
            return pilha[--topo];
        }

        int capacidade() {
            return tam_pilha;
        }

        const void print(ostream& o) {
            o << "[ ";
            for (int i = 0; i < topo-1; i++)
                o << pilha[i] << ", ";
            o << pilha[topo-1] << " ]";
        }

        void redimensiona(int n) {
            if (n < tam_pilha)
                for (int i = topo; i > n; i--)
                    desempilha();

            tam_pilha = n;
            pilha = (int *) realloc(pilha, tam_pilha * sizeof(int));
        }

        PilhaInt& operator = (const PilhaInt& p) {
            if (tam_pilha != p.tam_pilha)
                redimensiona(p.tam_pilha);

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
        int tam_pilha;
        int *pilha;
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