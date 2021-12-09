#include <iostream>

using namespace std;

#define MAX_PILHA 5

class PilhaInt {
    public:
        PilhaInt() {
            for (int i = 0; i < MAX_PILHA; i++)
                tab[i] = 0;
            topo = 0;
        }

        void empilha(int valor) {
            tab[topo++] = valor;
        }

        int desempilha() {
            return tab[--topo];
        }

        void print(ostream& o, const char *msg) {
            o << msg << endl;
        }

        const PilhaInt& operator = (const PilhaInt& p) {
            topo = p.topo;
            for (int i = 0; i < topo; i++) 
                tab[i] = p.tab[i];
            return *this;
        }
    
    private:
        int tab[MAX_PILHA];
        int topo;
};