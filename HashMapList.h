#ifndef U05_HASH_HASHMAP_HASHMAPLIST_H_
#define U05_HASH_HASHMAP_HASHMAPLIST_H_

#include "HashEntry.h"
#include "Lista.h"
#include <iostream>
#include <type_traits>  // ← necesario para if constexpr con std::is_same
#include <utility>      // para std::pair
#include "utilidades.h"
using namespace std;  



template <class K, class T>
class HashMapList {
private:
    Lista<HashEntry<K, T>>** tabla;
    unsigned int tamanio;
    static unsigned int hashFunc(K clave);
    unsigned int (*hashFuncP)(K clave);

public:
    HashMapList(unsigned int k);
    HashMapList(unsigned int k, unsigned int (*fp)(K clave));
    ~HashMapList();

    void put(K clave, T valor);
    void remove(K clave);
    T get(K clave);

    bool esVacio() const;
    void print() const;
    void getList(K clave)const;  // ya está, pero confirmá que esté en la sección pública


    Lista<HashEntry<K, T>>* getListaEnPos(int pos) const;
};

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>>*[tamanio];
    for (unsigned int i = 0; i < tamanio; i++) {
        tabla[i] = nullptr;
    }
    hashFuncP = hashFunc;
}

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k, unsigned int (*fp)(K clave)) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>>*[tamanio];
    for (unsigned int i = 0; i < tamanio; i++) {
        tabla[i] = nullptr;
    }
    hashFuncP = fp;
}

template <class K, class T>
HashMapList<K, T>::~HashMapList() {
    for (unsigned int i = 0; i < tamanio; i++) {
        if (tabla[i] != nullptr) {
            delete tabla[i];
        }
    }
    delete[] tabla;
}

template <class K, class T>
void HashMapList<K, T>::put(K clave, T valor) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == nullptr) {
        tabla[pos] = new Lista<HashEntry<K, T>>();
    }

    tabla[pos]->insertarUltimo(HashEntry<K, T>(clave, valor));
}

template <class K, class T>
void HashMapList<K, T>::remove(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] != nullptr) {
        Nodo<HashEntry<K, T>>* actual = tabla[pos]->getInicio();
        int index = 0;
        while (actual != nullptr) {
            if (actual->getDato().getClave() == clave) {
                tabla[pos]->remover(index);
                return;
            }
            actual = actual->getSiguiente();
            index++;
        }
        throw 404;
    } else {
        throw 409;
    }
}

template <class K, class T>
T HashMapList<K, T>::get(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == nullptr) {
        throw 404;
    }

    Nodo<HashEntry<K, T>>* nodo = tabla[pos]->getInicio();
    while (nodo != nullptr) {
        if (nodo->getDato().getClave() == clave) {
            return nodo->getDato().getValor();
        }
        nodo = nodo->getSiguiente();
    }
    throw 404;
}

template <class K, class T>
bool HashMapList<K, T>::esVacio() const {
    for (unsigned int i = 0; i < tamanio; i++) {
        if (tabla[i] != nullptr) {
            return false;
        }
    }
    return true;
}

template <class K, class T>
void HashMapList<K, T>::print() const {
    for (unsigned int i = 0; i < tamanio; i++) {
        if (tabla[i] != nullptr) {
            Nodo<HashEntry<K, T>>* aux = tabla[i]->getInicio();
            while (aux != nullptr) {
                cout << "(" << aux->getDato().getClave()
                     << ", " << aux->getDato().getValor()
                     << ")" << endl;
                aux = aux->getSiguiente();
            }
        }
    }
}


template <class K>
void printPair(const HashMapList<K, pair<double, int>>& map) {
    for (int i = 0; i < 200; i++) {
        Lista<HashEntry<K, pair<double, int>>>* lista = map.getListaEnPos(i);
        if (lista != nullptr) {
            for (int j = 0; j < lista->getTamanio(); j++) {
                auto dato = lista->getDato(j);
                auto valor = dato.getValor();
                cout << "(" << dato.getClave()
                     << ", promedio: " << valor.first
                     << ", cantidad: " << valor.second << ")" << endl;
            }
        }
    }
}



template <class K, class T>
Lista<HashEntry<K, T>>* HashMapList<K, T>::getListaEnPos(int pos) const {
    if (pos < 0 || static_cast<unsigned int>(pos) >= tamanio) return nullptr;
    return tabla[pos];
}

template <class K, class T>
unsigned int HashMapList<K, T>::hashFunc(K clave) {
    unsigned int hash = 0;
    for (char c : clave) {
        hash = hash * 31 + c;
    }
    return hash;
}

template <class K, class T>
void HashMapList<K, T>::getList(K clave) const {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == nullptr) {
        throw 404;
    }

    Nodo<HashEntry<K, T>>* aux = tabla[pos]->getInicio();

    while (aux != nullptr) {
        const auto& dato = aux->getDato();
        cout << "Clave: " << dato.getClave() << " | Valor: ";
        mostrarValor(dato.getValor());  // función auxiliar genérica
        cout << endl;
        aux = aux->getSiguiente();
    }
}



#endif // U05_HASH_HASHMAP_HASHMAPLIST_H_
