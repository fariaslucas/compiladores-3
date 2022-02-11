#include <type_traits>
#include <initializer_list>
#include <vector>

using namespace std;

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