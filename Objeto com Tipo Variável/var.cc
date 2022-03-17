#include <variant>
#include <memory>
#include <string>
#include <map>
#include <type_traits>

using namespace std;

class Var {
  public:
    class Undefined {};

    class Object {
      public:
        virtual void imprime(ostream& o) const { o << "object"; }

        virtual Var funcao(const Var& var) const { throw Erro("Essa variável não pode ser usada como função"); }

        Var& lvalue(const string& st) { return obj[st]; }
        Var rvalue(const string& st) const {
          if (auto v = obj.find(st); v != obj.end()) return v->second;
          else return Var();
        }

      private:
        map<string,Var> obj;
    };

    template <typename F>
    class Function: public Object {
      public:
        Function(F func): func(func) {}

        virtual void imprime(ostream& o) const { o << "function"; }

        Var funcao(const Var& var) const { return invoke(func, var); }
      
      private:
        F func;
    };

    Var(): valor() {}
    Var(int n): valor(n) {}
    Var(double n): valor(n) {}
    Var(char c): valor(c) {}
    Var(string st): valor(st) {}
    Var(const char* st): valor(string(st)) {}
    Var(bool b): valor(b) {}
    Var(Object* obj): valor(shared_ptr<Object>(obj)) {}
    template<typename T>
    Var(T func): valor(shared_ptr<Object>(new Function(func))) {}

    Var& operator [] (const string& st) { 
      if (valor.index() != OBJECT) throw Erro("Essa variável não é um objeto");
      return get<OBJECT>(valor)->lvalue(st);
    }
    Var operator [] (const string& st) const {
      if (valor.index() != OBJECT) throw Erro("Essa variável não é um objeto");
      return get<OBJECT>(valor)->rvalue(st);
    }
    Var operator () (Var var) const { 
      if (valor.index() != OBJECT) throw Erro("Essa variável não pode ser usada como função");
      return get<OBJECT>(valor)->funcao(var);
    }

    class Erro {
      public:
        Erro(string msg): msg(msg) {}
        
        string operator() () const { return msg; }
        
      private:
        string msg;
    };

    void imprime(ostream& o) const {
      switch (valor.index()) {
        case UNDEFINED: 
          o << "undefined"; 
          break;
        case INT:
          o << get<INT>(valor);
          break;
        case DOUBLE:
          o << get<DOUBLE>(valor);
          break;
        case CHAR:
          o << get<CHAR>(valor);
          break;
        case STRING:
          o << get<STRING>(valor);
          break;
        case BOOL:
          o << (get<BOOL>(valor) ? "true" : "false");
          break;
        case OBJECT:
          get<OBJECT>(valor)->imprime(o);
          break;
      }
    }
  
    static constexpr int tipo_args(int arg1, int arg2) { return (arg1 << 4) | arg2; }

    static Var sel_adicao(const Var& arg1, const Var& arg2) {
      switch (tipo_args(arg1.valor.index(), arg2.valor.index())) {
        case tipo_args(INT, INT): return get<INT>(arg1.valor) + get<INT>(arg2.valor);
        case tipo_args(INT, DOUBLE): return get<INT>(arg1.valor) + get<DOUBLE>(arg2.valor);
        case tipo_args(INT, CHAR): return get<INT>(arg1.valor) + get<CHAR>(arg2.valor);

        case tipo_args(DOUBLE, DOUBLE): return get<DOUBLE>(arg1.valor) + get<DOUBLE>(arg2.valor);
        case tipo_args(DOUBLE, INT): return get<DOUBLE>(arg1.valor) + get<INT>(arg2.valor);

        case tipo_args(CHAR, CHAR): return string("") + get<CHAR>(arg1.valor) + get<CHAR>(arg2.valor);
        case tipo_args(CHAR, INT): return get<CHAR>(arg1.valor) + get<INT>(arg2.valor);
        case tipo_args(CHAR, STRING): return get<CHAR>(arg1.valor) + get<STRING>(arg2.valor);

        case tipo_args(STRING, STRING): return get<STRING>(arg1.valor) + get<STRING>(arg2.valor);
        case tipo_args(STRING, CHAR): return get<STRING>(arg1.valor) + get<CHAR>(arg2.valor);

        default: return Var();
      }
    }

    static Var sel_subtracao(const Var& arg1, const Var& arg2) {
      switch (tipo_args(arg1.valor.index(), arg2.valor.index())) {
        case tipo_args(INT, INT): return get<INT>(arg1.valor) - get<INT>(arg2.valor);
        case tipo_args(INT, DOUBLE): return get<INT>(arg1.valor) - get<DOUBLE>(arg2.valor);
        case tipo_args(INT, CHAR): return get<INT>(arg1.valor) - get<CHAR>(arg2.valor);

        case tipo_args(DOUBLE, DOUBLE): return get<DOUBLE>(arg1.valor) - get<DOUBLE>(arg2.valor);
        case tipo_args(DOUBLE, INT): return get<DOUBLE>(arg1.valor) - get<INT>(arg2.valor);

        case tipo_args(CHAR, CHAR): return get<CHAR>(arg1.valor) - get<CHAR>(arg2.valor);
        case tipo_args(CHAR, INT): return get<CHAR>(arg1.valor) - get<INT>(arg2.valor);
        
        default: return Var();
      }
    }

    static Var sel_multiplicacao(const Var& arg1, const Var& arg2) {
      switch (tipo_args(arg1.valor.index(), arg2.valor.index())) {
        case tipo_args(INT, INT): return get<INT>(arg1.valor) * get<INT>(arg2.valor);
        case tipo_args(INT, DOUBLE): return get<INT>(arg1.valor) * get<DOUBLE>(arg2.valor);

        case tipo_args(DOUBLE, DOUBLE): return get<DOUBLE>(arg1.valor) * get<DOUBLE>(arg2.valor);
        case tipo_args(DOUBLE, INT): return get<DOUBLE>(arg1.valor) * get<INT>(arg2.valor);

        default: return Var();
      }
    }

    static Var sel_divisao(const Var& arg1, const Var& arg2) {
      switch (tipo_args(arg1.valor.index(), arg2.valor.index())) {
        case tipo_args(INT, INT): return get<INT>(arg1.valor) / get<INT>(arg2.valor);
        case tipo_args(INT, DOUBLE): return get<INT>(arg1.valor) / get<DOUBLE>(arg2.valor);

        case tipo_args(DOUBLE, DOUBLE): return get<DOUBLE>(arg1.valor) / get<DOUBLE>(arg2.valor);
        case tipo_args(DOUBLE, INT): return get<DOUBLE>(arg1.valor) / get<INT>(arg2.valor);

        default: return Var();
      }
    }

    static Var sel_menor(const Var& arg1, const Var& arg2) {
      switch (tipo_args(arg1.valor.index(), arg2.valor.index())) {
        case tipo_args(INT, INT): return get<INT>(arg1.valor) < get<INT>(arg2.valor);
        case tipo_args(INT, DOUBLE): return get<INT>(arg1.valor) < get<DOUBLE>(arg2.valor);
        case tipo_args(INT, CHAR): return get<INT>(arg1.valor) < get<CHAR>(arg2.valor);

        case tipo_args(DOUBLE, DOUBLE): return get<DOUBLE>(arg1.valor) < get<DOUBLE>(arg2.valor);
        case tipo_args(DOUBLE, INT): return get<DOUBLE>(arg1.valor) < get<INT>(arg2.valor);

        case tipo_args(CHAR, CHAR): return get<CHAR>(arg1.valor) < get<CHAR>(arg2.valor);
        case tipo_args(CHAR, INT): return get<CHAR>(arg1.valor) < get<INT>(arg2.valor);
        case tipo_args(CHAR, STRING): return to_string(get<CHAR>(arg1.valor)) < get<STRING>(arg2.valor);

        case tipo_args(STRING, STRING): return get<STRING>(arg1.valor) < get<STRING>(arg2.valor);
        case tipo_args(STRING, CHAR): return get<STRING>(arg1.valor) < to_string(get<CHAR>(arg2.valor));

        case tipo_args(BOOL, BOOL): return get<BOOL>(arg1.valor) < get<BOOL>(arg2.valor);
        
        default: return Var();
      }
    }

    static Var sel_not(const Var& arg) {
      if (arg.valor.index() == BOOL) return !get<BOOL>(arg.valor);
      return Var();
    }

    static Var sel_and(const Var& arg1, const Var& arg2) {
      if (tipo_args(arg1.valor.index(), arg2.valor.index()) == tipo_args(BOOL, BOOL)) return get<BOOL>(arg1.valor) && get<BOOL>(arg2.valor);
      return Var();
    }

    static Var sel_or(const Var& arg1, const Var& arg2) {
      if (tipo_args(arg1.valor.index(), arg2.valor.index()) == tipo_args(BOOL, BOOL)) return get<BOOL>(arg1.valor) || get<BOOL>(arg2.valor);
      return Var();
    }

  private:
    enum {UNDEFINED, INT, DOUBLE, CHAR, STRING, BOOL, OBJECT};
    typedef variant<Undefined, int, double, char, string, bool, shared_ptr<Object>> Variavel;
    Variavel valor;
};

ostream& operator << (ostream& o, const Var& valor) {
  valor.imprime(o);
  return o;
}

Var::Object* newObject() { return new Var::Object(); }

inline Var operator + (const Var& arg1, const Var& arg2) { return Var::sel_adicao(arg1, arg2); }
inline Var operator - (const Var& arg1, const Var& arg2) { return Var::sel_subtracao(arg1, arg2); }
inline Var operator * (const Var& arg1, const Var& arg2) { return Var::sel_multiplicacao(arg1, arg2); }
inline Var operator / (const Var& arg1, const Var& arg2) { return Var::sel_divisao(arg1, arg2); }
inline Var operator < (const Var& arg1, const Var& arg2) { return Var::sel_menor(arg1, arg2); }
inline Var operator ! (const Var& arg) { return Var::sel_not(arg); }
inline Var operator && (const Var& arg1, const Var& arg2) { return Var::sel_and(arg1, arg2); }
inline Var operator || (const Var& arg1, const Var& arg2) { return Var::sel_or(arg1, arg2); }

inline Var operator > (const Var& arg1, const Var& arg2) { return arg2 < arg1; }
inline Var operator != (const Var& arg1, const Var& arg2) { return (arg1 < arg2) || (arg2 < arg1); }
inline Var operator == (const Var& arg1, const Var& arg2) { return !(arg1 != arg2); }
inline Var operator <= (const Var& arg1, const Var& arg2) { return !(arg2 < arg1); }
inline Var operator >= (const Var& arg1, const Var& arg2) { return !(arg1 < arg2); }