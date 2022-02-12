#include <math.h>
#include <type_traits>

using namespace std;

class Variavel {
    public:
        double e(double valor) {
            return valor;
        }

        double dx(double valor) {
            return 1;
        }
};

class Constante {
    public:
        Constante(double cte): cte(cte) {}

        double e(double valor) {
            return cte;
        }

        double dx(double valor) {
            return 0;
        }

    private:
        double cte;
};

template<typename F, typename G>
class Multiplica {
    public:
        Multiplica(F f, G g): f(f), g(g) {}

        double e(double valor) {
            return f.e(valor) * g.e(valor);
        }

        double dx(double valor) {
            return f.dx(valor) * g.e(valor) + f.e(valor) * g.dx(valor);
        }

    private:
        F f;
        G g;
};

template<typename F, typename G>
class Soma {
    public:
        Soma(F f, G g): f(f), g(g) {}

        double e(double valor) {
            return f.e(valor) + g.e(valor);
        }

        double dx(double valor) {
            return f.dx(valor) + g.dx(valor);
        }

    private:
        F f;
        G g;
};

template<typename F, typename G>
class Subtrai {
    public:
        Subtrai(F f, G g): f(f), g(g) {}

        double e(double valor) {
            return f.e(valor) - g.e(valor);
        }

        double dx(double valor) {
            return f.dx(valor) - g.dx(valor);
        }

    private:
        F f;
        G g;
};

template<typename F, typename G>
class Divide {
    public:
        Divide(F f, G g): f(f), g(g) {}

        double e(double valor) {
            return f.e(valor) / g.e(valor);
        }

        double dx(double valor) {
            return (f.dx(valor) * g.e(valor) + f.e(valor) * g.dx(valor)) 
                / (g.e(valor) * g.e(valor));
        }

    private:
        F f;
        G g;
};

template<typename X1, typename X2>
auto operator * (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Multiplica<Constante,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Multiplica<X1,Constante>(x1, x2);
    else
        return Multiplica<X1,X2>(x1, x2);
}

template<typename X1, typename X2>
auto operator + (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Soma<Constante,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Soma<X1,Constante>(x1, x2);
    else
        return Soma<X1,X2>(x1, x2);
}

template<typename X1, typename X2>
auto operator - (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Subtrai<Constante,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Subtrai<X1,Constante>(x1, x2);
    else
        return Subtrai<X1,X2>(x1, x2);
}

template<typename X1, typename X2>
auto operator / (X1 x1, X2 x2) {
    if constexpr (is_same_v<int, X1> || is_same_v<double, X1>) 
        return Divide<Constante,X2>(x1, x2);
    else if constexpr (is_same_v<int, X2> || is_same_v<double, X2>)
        return Divide<X1,Constante>(x1, x2);
    else
        return Divide<X1,X2>(x1, x2);
}

template<typename F>
class Seno {
    public:
        Seno(F f): f(f) {}

        double e(double valor) {
            return sin(f.e(valor));
        }

        double dx(double valor) {
            return cos(f.e(valor)) * f.dx(valor);
        }

    private:
        F f;
};

template<typename F>
class Cosseno {
    public:
        Cosseno(F f): f(f) {}

        double e(double valor) {
            return cos(f.e(valor));
        }

        double dx(double valor) {
            return -sin(f.e(valor)) * f.dx(valor);
        }

    private:
        F f;
};

template<typename X>
Seno<X> sin(X x) {
    return Seno<X>(x);
}

template<typename X>
Cosseno<X> cos(X x) {
    return Cosseno<X>(x);
}

template<typename F>
class Exponencial {
    public:
        Exponencial(F f): f(f) {}

        double e(double valor) {
            return exp(f.e(valor));
        }

        double dx(double valor) {
            return exp(f.e(valor)) * f.dx(valor);
        }

    private:
        F f;
};

template<typename F>
class Logaritmo {
    public:
        Logaritmo(F f): f(f) {}

        double e(double valor) {
            return log(f.e(valor));
        }

        double dx(double valor) {
            return f.dx(valor)/f.e(valor);
        }

    private:
        F f;
};

template<typename X>
Exponencial<X> exp(X x) {
    return Exponencial<X>(x);
}

template<typename X>
Logaritmo<X> log(X x) {
    return Logaritmo<X>(x);
}

template<typename F, typename G>
class Potencia {
    public:
        Potencia(F f, G g): f(f), g(g) {}

        double e(double valor) {
            return pow(f.e(valor), g.e(valor));
        }

        double dx(double valor) {
            return g.e(valor) * pow(f.e(valor), g.e(valor)-1) * f.dx(valor);
        }

    private:
        F f;
        G g;
};

template<typename X1, typename X2>
Potencia<X1, Constante> operator ->* (X1 x1, X2 x2) {
    static_assert(is_same_v<int, X2>, "Operador de potenciação definido apenas para inteiros");
    return Potencia<X1, Constante>(x1, x2);
}

Variavel x;