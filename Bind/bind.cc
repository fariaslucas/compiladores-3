#include <type_traits>
#include <functional>

using namespace std;

template<typename Functor, typename FunctorBase, typename... Parametros>
class Bind {
    public:
        Bind(Functor func, FunctorBase funcBase, Parametros... param): func(func) {}

        template<typename... Argumentos>
        auto operator () (Argumentos... args) {
            if constexpr (is_invocable<FunctorBase, Parametros..., Argumentos...>::value)
                return invoke(func, args...);
            else   
                return [this, args...](auto... resto) { return invoke(func, args..., resto...); };
        }

        const Functor functor() {
            return func;
        }

    private:
        Functor func;
};

template<typename Functor, typename FunctorBase, typename... Parametros>
auto bind(Bind<Functor,FunctorBase> func, Parametros... param) {
    auto pegaFunc = func.functor();
    auto lambda = [func, param...](auto... resto) { return invoke(func.functor(), param..., resto...); };
    Bind f{lambda, func, param...};
    return f;
}

template<typename Functor, typename... Parametros>
auto bind(Functor func, Parametros... param) {
    if constexpr (is_class<Functor>::value) {
        auto lambda = [&func, param...](auto... resto) { return invoke(func, param..., resto...); };
        Bind f{lambda, func, param...};
        return f;
    } else {
        auto lambda = [func, param...](auto... resto) { return invoke(func, param..., resto...); };
        Bind f{lambda, func, param...};
        return f;
    }
}