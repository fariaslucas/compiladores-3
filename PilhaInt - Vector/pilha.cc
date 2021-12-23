#include <iostream>
#include <vector>

using namespace std;

class PilhaInt {
    public:
        PilhaInt(int tamanho = 10) {
            pilha.reserve(tamanho);
        }

        PilhaInt(const PilhaInt& p) {
            pilha = p.pilha;
        }

        void empilha(int valor) {
            pilha.push_back(valor);
        }

        int desempilha() {
            int topo = pilha.back();
            pilha.pop_back();
            return topo;
        }

        int capacidade() {
            return pilha.capacity();
        }

        const void print(ostream& o) {
            o << "[ ";
            for (unsigned int i = 0; i < pilha.size()-1; i++)
                o << pilha[i] << ", ";
            o << pilha.back() << " ]";
        }

        void redimensiona(unsigned int n) {
            if (n < pilha.size())
                for (unsigned int i = pilha.size(); i > n; i--)
                    desempilha();

            pilha.resize(n);
        }

        PilhaInt& operator = (const PilhaInt& p) {
            if (pilha.size() != p.pilha.size())
                redimensiona(p.pilha.size());

            pilha = p.pilha;
            return *this;
        }

        PilhaInt& operator << (int valor) {
            empilha(valor);
            return *this;
        }
    
    private:
        vector<int> pilha;
};

PilhaInt embaralha( PilhaInt q ) {
    int aux = q.desempilha();
    q << 32 << 9 << aux;
    
    return q;
}

// Apenas para teste
int main() {
    PilhaInt p;
    p.empilha( 1 );
    p << 3 << 9 << 13 << 89;
    cout << p.desempilha() << endl;
    cout << p.desempilha() << endl;
    p.print( cout );
    p << 19 << 18 << 17 << 30;

    return 0;
}