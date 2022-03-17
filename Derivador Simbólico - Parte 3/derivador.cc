#include <math.h>
#include <type_traits>
#include <string>
#include <sstream>

using namespace std;

class Variavel {
    public:
        double e(double valor) const { return valor; }

        double dx(double valor) const { return 1; }

        string operador() const { return op; }

        string str() const { return "x"; }

        string dx_str() const { return "1"; }

    private:
        string op;
};

class Constante {
    public:
        Constante(double cte): cte(cte) { op = ""; }

        double e(double valor) const { return cte; }

        double dx(double valor) const { return 0; }

        string operador() const { return op; }

        string str() const { 
            stringstream s;
            s << cte;
            return s.str();
        }

        string dx_str() const { return "0"; }

    private:
        double cte;
        string op;
};

template<typename F, typename G>
class Multiplica {
    public:
        Multiplica(F f, G g): f(f), g(g) { op = "*"; }

        double e(double valor) const { return f.e(valor) * g.e(valor); }

        double dx(double valor) const { return f.dx(valor) * g.e(valor) + f.e(valor) * g.dx(valor); }

        string operador() const { return op; }

        string str() const { 
            if ((f.operador() == "+" || f.operador() == "-" ) && 
                (g.operador() == "+" || g.operador() == "-"))
                return "(" + f.str() + ")*(" + g.str() + ")";

            if (f.operador() == "+" || f.operador() == "-")
                return "(" + f.str() + ")*" + g.str();

            if (g.operador() == "+" || g.operador() == "-")
                return f.str() + "*(" + g.str() + ")";

            return f.str() + "*" + g.str();
        }

        string dx_str() const { 
            if (f.dx_str() == "1") {
                if (g.dx_str() == "1")
                    return  g.str() + "+" + f.str();
                if (g.dx_str() != "0")
                    return g.str() + "+" + f.str() + "*" + g.dx_str();
            }

            if (f.dx_str() != "0") {
                if (g.dx_str() == "1")
                    return f.dx_str() + "*" + g.str() + "+" + f.str();
                if (g.dx_str() != "0")
                    return f.dx_str() + "*" + g.str() + "+" + f.str() + "*" + g.dx_str(); 
            }

            return f.str();
        }

    private:
        F f;
        G g;
        string op;
};

template<typename F, typename G>
class Soma {
    public:
        Soma(F f, G g): f(f), g(g) { op = "+"; }

        double e(double valor) const { return f.e(valor) + g.e(valor); }

        double dx(double valor) const { return f.dx(valor) + g.dx(valor); }

        string operador() const { return op; }

        string str() const { return f.str() + "+" + g.str(); }

        string dx_str() const { 
            if (f.dx_str() != "0" && g.dx_str() != "0")
                 return f.dx_str() + "+" + g.dx_str();

            if (f.dx_str() == "0")
                return g.dx_str();

            if (g.dx_str() == "0")
                return f.dx_str();

            return ""; 
        }

    private:
        F f;
        G g;
        string op;
};

template<typename F, typename G>
class Subtrai {
    public:
        Subtrai(F f, G g): f(f), g(g) { op = "-"; }

        double e(double valor) const { return f.e(valor) - g.e(valor); }

        double dx(double valor) const { return f.dx(valor) - g.dx(valor); }

        string operador() const { return op; }

        string str() const {
            if ((f.operador() == "+" || f.operador() == "-" ) && 
                (g.operador() == "+" || g.operador() == "-"))
                return "(" + f.str() + ")-(" + g.str() + ")";

            if (f.operador() == "+" || f.operador() == "-")
                return "(" + f.str() + ")-" + g.str();

            if (g.operador() == "+" || g.operador() == "-")
                return f.str() + "-(" + g.str() + ")";

            return f.str() + "-" + g.str();
        }

        string dx_str() const { 
            if (f.dx_str() != "0" && g.dx_str() != "0")
                 return f.dx_str() + "-" + g.dx_str();

            if (f.dx_str() == "0")
                return g.dx_str();

            if (g.dx_str() == "0")
                return f.dx_str();

            return ""; 
        }

    private:
        F f;
        G g;
        string op;
};

template<typename F, typename G>
class Divide {
    public:
        Divide(F f, G g): f(f), g(g) { op = "/"; }

        double e(double valor) const { return f.e(valor) / g.e(valor); }

        double dx(double valor) const {
            return (f.dx(valor) * g.e(valor) + f.e(valor) * g.dx(valor)) 
                / (g.e(valor) * g.e(valor));
        }

        string operador() const { return op; }

        string str() const { 
            return f.str() + "/" + g.str();
        }

        string dx_str() const { 
            if (f.dx_str() == "1") {
                if (g.dx_str() == "1") {
                    if (g.operador() == "+" || g.operador() == "-" || g.operador() == "*" ||
                        g.operador() == "/" || g.operador() == "^")
                        return g.str() + "-(" + f.str() + ")/(" + g.str() + ")^2"; 
                    return g.str() + "-" + f.str() + "/" + g.str() + "^2";
                }

                if (g.dx_str() != "0") {
                    if (g.operador() == "+" || g.operador() == "-" || g.operador() == "*" ||
                        g.operador() == "/" || g.operador() == "^")
                        return g.str() + "-(" + f.str() + "*" + g.dx_str() + ")/(" + g.str() + ")^2";
                    return g.str() + "-" + f.str() + "*" + g.dx_str() + "/" + g.str() + "^2";
                }

                if (f.operador() == "+" || f.operador() == "-" || f.operador() == "*" || f.operador() == "/")
                    return "(" + g.str() + ")/" + g.str() + "^2";
                
                return g.str() + "/" + g.str() + "^2";
            }

            if (f.dx_str() != "0") {
                if (g.dx_str() == "1") {
                    if (g.operador() == "+" || g.operador() == "-" || g.operador() == "*" ||
                        g.operador() == "/" || g.operador() == "^")
                        return f.dx_str() + "*" + g.str() + "-(" + f.str() + ")/(" + g.str() + ")^2";
                    return f.dx_str() + "*" + g.str() + "-" + f.str() + "/" + g.str() + "^2";
                }

                if (g.dx_str() != "0") {
                    if (g.operador() == "+" || g.operador() == "-" || g.operador() == "*" ||
                        g.operador() == "/" || g.operador() == "^")
                        return f.dx_str() + "*" + g.str() + "-(" + f.str() + "*" + g.dx_str() + ")/(" + g.str() + ")^2";
                    return f.dx_str() + "*" + g.str() + "-" + f.str() + "*" + g.dx_str() + "/" + g.str() + "^2"; 
                }

                if (f.operador() == "+" || f.operador() == "-" || f.operador() == "*" || f.operador() == "/")
                    return "(" + f.dx_str() + "*" + g.str() + ")/" + g.str() + "^2";
                
                return "(" + f.dx_str() + "*" + g.str() + ")/" + g.str() + "^2";
            }           
            
            return "";
        }

    private:
        F f;
        G g;
        string op;
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
        Seno(F f): f(f) { op = "sin"; }

        double e(double valor) const { return sin(f.e(valor)); }

        double dx(double valor) const { return cos(f.e(valor)) * f.dx(valor); }

        string operador() const { return op; }

        string str() const { return "sin(" + f.str() + ")"; }

        string dx_str() const { 
            if (f.dx_str() == "1")
                return "cos(" + f.str() + ")";
            else  
                return "cos(" + f.str() + ")*" + f.dx_str();
        }

    private:
        F f;
        string op;
};

template<typename F>
class Cosseno {
    public:
        Cosseno(F f): f(f) { op = "cos"; }

        double e(double valor) const { return cos(f.e(valor)); }

        double dx(double valor) const { return -sin(f.e(valor)) * f.dx(valor); }

        string operador() const { return op; }

        string str() const { return "cos(" + f.str() + ")"; }

        string dx_str() const { 
            if (f.dx_str() == "1")
                return "-sin(" + f.str() + ")";
            else  
                return "-sin(" + f.str() + ")*" + f.dx_str();
        }

    private:
        F f;
        string op;
};

template<typename X>
Seno<X> sin(X x) { return Seno<X>(x); }

template<typename X>
Cosseno<X> cos(X x) { return Cosseno<X>(x); }

template<typename F>
class Exponencial {
    public:
        Exponencial(F f): f(f) { op = "exp"; }

        double e(double valor) const { return exp(f.e(valor)); }

        double dx(double valor) const { return exp(f.e(valor)) * f.dx(valor); }

        string operador() const { return op; }

        string str() const { return "exp(" + f.str() + ")"; }

        string dx_str() const { 
            if (f.operador() == "+" || f.operador() == "-" || 
                f.operador() == "*" || f.operador() == "/")
                return "exp(" + f.str() + ")*(" + f.dx_str() + ")";
            return "exp(" + f.str() + ")*" + f.dx_str();
        }

    private:
        F f;
        string op;
};

template<typename F>
class Logaritmo {
    public:
        Logaritmo(F f): f(f) { op = "log"; } 

        double e(double valor) const { return log(f.e(valor)); }

        double dx(double valor) const { return f.dx(valor)/f.e(valor); }

        string operador() const { return op; }

        string str() const { return "log(" + f.str() + ")"; }

        string dx_str() const { 
            if (f.dx_str() == "1")
                return "1/(" + f.str() + ")";
            return "1/(" + f.str() + ")*" + f.dx_str();
        }

    private:
        F f;
        string op;
};

template<typename X>
Exponencial<X> exp(X x) { return Exponencial<X>(x); }

template<typename X>
Logaritmo<X> log(X x) { return Logaritmo<X>(x); }

template<typename F, typename G>
class Potencia {
    public:
        Potencia(F f, G g): f(f), g(g) { op = "^"; }

        double e(double valor) const { return pow(f.e(valor), g.e(valor)); }

        double dx(double valor) const { return g.e(valor) * pow(f.e(valor), g.e(valor)-1) * f.dx(valor); }

        string operador() const { return op; }

        string str() const { 
            if (f.operador() == "+" || f.operador() == "-" ||
                f.operador() == "*" || f.operador() == "/")
                return "(" + f.str() + ")^" + g.str();
            return f.str() + "^" + g.str(); 
        }

        string dx_str() const { 
            stringstream s;
            if (f.dx_str() != "1") {
                if (f.operador() == "+" || f.operador() == "-" || f.operador() == "*"
                    || f.operador() == "/" || f.operador() == "^")
                    s <<  g.str() << "*" << f.dx_str() << "*(" << f.str() << ")";
                else
                    s <<  g.str() << "*" << f.dx_str() << "*" << f.str();
            }
            else 
                s << g.str() << "*" << f.str();
            
            if (g.str() > "2")
                s << "^" << g.e(0)-1;

            return s.str();
        }

    private:
        F f;
        G g;
        string op;
};

template<typename X1, typename X2>
Potencia<X1, Constante> operator ->* (X1 x1, X2 x2) {
    static_assert(is_same_v<int, X2>, "Operador de potenciação definido apenas para inteiros");
    return Potencia<X1, Constante>(x1, x2);
}

Variavel x;