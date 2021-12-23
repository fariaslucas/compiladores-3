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
            if (n < pilha.capacity())
                for (unsigned int i = pilha.size(); i > n; i--)
                    desempilha();

            pilha.resize(n);
            pilha.shrink_to_fit();
        }

        PilhaInt& operator = (const PilhaInt& p) {
            if (pilha.capacity() != p.pilha.capacity())
                redimensiona(p.pilha.capacity());

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
    PilhaInt a{7}, c{7};
    a << 8 << 3 << 1 << 4 << 5;
    c << 5 << 6 << 1;

    c.redimensiona(5);

    cout << c.capacidade() << endl;
    cout << a.capacidade() << endl;

    return 0;
}