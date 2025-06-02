#ifndef LISTA_H
#define LISTA_H

#include <iostream>

template <typename T>
struct Nodo {
    T dato;
    Nodo* siguiente = nullptr;
};

template <typename T>
class Lista {
private:
    Nodo<T>* inicio;

public:
    Lista() : inicio(nullptr) {}
    ~Lista() { vaciar(); }

    void insertarUltimo(T dato) {
        Nodo<T>* nuevo = new Nodo<T>{dato};
        if (!inicio) {
            inicio = nuevo;
        } else {
            Nodo<T>* aux = inicio;
            while (aux->siguiente)
                aux = aux->siguiente;
            aux->siguiente = nuevo;
        }
    }

    T getDato(int pos) const {
        Nodo<T>* aux = inicio;
        for (int i = 0; i < pos && aux; i++) {
            aux = aux->siguiente;
        }
        if (!aux) throw 404;
        return aux->dato;
    }

    int getTamanio() const {
        Nodo<T>* aux = inicio;
        int tam = 0;
        while (aux) {
            tam++;
            aux = aux->siguiente;
        }
        return tam;
    }

    void vaciar() {
        while (inicio) {
            Nodo<T>* borrar = inicio;
            inicio = inicio->siguiente;
            delete borrar;
        }
    }
};

#endif
