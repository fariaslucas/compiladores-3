#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

template<typename tipoItr, typename tipoFunc>
auto apply(const tipoItr& iteravel, tipoFunc funcao) {
    auto itr = begin(iteravel);

    vector<decltype(funcao(*itr))> vetor;

    for (auto elemento : iteravel)
        vetor.push_back(funcao(elemento));
    
    return vetor;
}

template<typename tipoItr, typename tipoFunc>
auto apply(const initializer_list<tipoItr>& iteravel, tipoFunc funcao) {
    auto itr = iteravel.begin();

    vector<decltype(funcao(*itr))> vetor;

    for (auto elemento : iteravel)
        vetor.push_back(funcao(elemento));
    
    return vetor;
}
