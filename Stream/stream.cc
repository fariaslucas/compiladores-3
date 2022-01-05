#include <iostream>

using namespace std;

template<typename tipoItr, typename tipoFunc>
void operator | (const tipoItr& iteravel, tipoFunc funcao) {
    for (auto elemento : iteravel)
        funcao(elemento);
}
