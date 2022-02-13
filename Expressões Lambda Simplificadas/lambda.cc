#include <math.h>
#include <type_traits>
#include <string>
#include <vector>

using namespace std;

class Variavel {
    public:
        auto operator () (auto valor) {
            return valor;
        }
};

template<typename C>
class Constante {
    public:
        Constante(const C& cte): cte(cte) {}

        auto operator () (auto valor) {
            return cte;
        }

    private:
        C cte;
};

template<typename F, typename G>
class Multiplica {
    public:
        Multiplica(F f, G g): f(f), g(g) {}

        auto operator () (auto valor) {
            return f(valor) * g(valor);
        }

    private:
        F f;
        G g;
};

template<typename F, typename G>
class Soma {
    public:
        Soma(F f, G g): f(f), g(g) {}

        auto operator () (auto valor) {
            return f(valor) + g(valor);
        }

    private:
        F f;
        G g;
};

template<typename F, typename G>
class Modulo {
    public:
        Modulo(F f, G g): f(f), g(g) {}

        template<typename T>
        T operator () (T valor) {
            return f(valor) % g(valor);
        } 

    private:
        F f;
        G g;
};

template<typename X1, typename X2>
auto operator * (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Multiplica<Constante<X1>, X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Multiplica<X1, Constante<X2>>(x1, x2);
    else
        return Multiplica<X1,X2>(x1, x2);
}

template<typename X1, typename X2>
auto operator + (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Soma<Constante<X1>,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Soma<X1,Constante<X2>>(x1, x2);
    else
        return Soma<X1,X2>(x1, x2);
}

template<typename X1, typename X2>
auto operator % (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Modulo<Constante<X1>,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Modulo<X1,Constante<X2>>(x1, x2);
    else
        return Modulo<X1,X2>(x1, x2);
} 

template<typename F, typename G>
class Igual {
    public:
        Igual(F f, G g): f(f), g(g) {}

        template<typename T>
        bool operator () (T valor) {
            return f(valor) == g(valor);
        } 

    private:
        F f;
        G g;
};

template<typename X1, typename X2>
auto operator == (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Igual<Constante<X1>,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Igual<X1,Constante<X2>>(x1, x2);
    else
        return Igual<X1,X2>(x1, x2);
} 

template<typename F, typename G>
class Imprime {
    public:
        Imprime(F& f, G g): f(f), g(g) {}

        template<typename T>
        void operator () (T valor) {
            f << g(valor) << fiml;
        }

        void adicionaFim(const char s) {
            fiml += s;
        }

    private:
        F& f;
        G g;
        string fiml = "";
};

template<typename X1, typename X2>
auto operator << (ostream& o, Multiplica<X1,X2> x) {
    return Imprime<ostream,Multiplica<X1,X2>>(o,x);
}

template<typename X1, typename X2>
auto operator << (ostream& o, Soma<X1,X2> x) {
    return Imprime<ostream,Soma<X1,X2>>(o,x);
}

auto operator << (ostream& o, Variavel x) {
    return Imprime<ostream,Variavel>(o, x);
}

template<typename X>
auto operator << (X x, const char c) {
    x.adicionaFim(c);
    return x;
}

template<typename tipoItr, typename tipoFunc>
auto operator | (const tipoItr &iteravel, tipoFunc funcao) {
    if constexpr (is_same<void, decltype(funcao(*begin(iteravel)))>::value) {
        for (auto elemento : iteravel) 
            funcao(elemento);

    } else if constexpr (is_same<bool, decltype(funcao(*begin(iteravel)))>::value) {
        auto itr = *begin(iteravel);

        vector<decltype(itr)> vetor;

        for (auto elemento : iteravel) 
            if (funcao(elemento)) 
                vetor.push_back(elemento);

        return vetor; 
    
    } else {
        vector<decltype(funcao(*begin(iteravel)))> vetor;

        for (auto elemento : iteravel) 
            vetor.push_back(funcao(elemento));

        return vetor;
    }
}

Variavel x;