#pragma once
#include "Header.h"

template <typename T>
class Lista 
{
private:
    struct Nodo; 
    typedef function<int(T, T)> Comp;
    Nodo* ini;
    size_t lon;
    Comp comparar;

public:
    Lista() : ini(nullptr), lon(0), comparar([](T a, T b) {return a - b; }) {  }
    Lista(Comp comparar) : ini(nullptr), lon(0), comparar(comparar) {  }
    ~Lista();

    size_t longitud();
    bool esVacia();
    void push_Back_List(T dato);//ESTE NO MA ESTA QUE SE USA...:v...intente borrar lo demas pero me da error que raro...xd
    void agregaPos(T dato, size_t pos);
    void agregaFinal(T dato);
    void modificarInicial(T dato);
    void modificarPos(T dato, size_t pos);
    void modificarFinal(T dato);
    void eliminaInicial();
    void eliminaPos(size_t pos);
    void eliminaFinal();
    T obtenerInicial();
    T obtener_Pos(size_t pos);//USANDO XD
    T obtenerFinal();
    T buscar(T dato);
};

template <typename T>
struct Lista<T>::Nodo {
    T dato;
    Nodo* next;
    Nodo(T dato = 0, Nodo* next = nullptr) : dato(dato), next(next) {}
};

template <typename T>
Lista<T>::~Lista() {
    Nodo* aux = ini;
    while (aux != nullptr) {
        aux = ini;
        ini = ini->next;
        delete aux;
    }
}
template <typename T>
size_t Lista<T>::longitud() {
    return lon;
}

template <typename T>
bool Lista<T>::esVacia() {
    return lon == 0;
}

template <typename T>
void Lista<T>::push_Back_List(T dato) {
    Nodo* nuevo = new Nodo(dato, ini);
    if (nuevo != nullptr) {
        ini = nuevo;
        lon++;
    }
}

template <typename T>
T Lista<T>::buscar(T dato) {
    Nodo* aux = ini;
    while (aux != nullptr) {
        if (comparar(aux->dato, dato) == 0) {
            return aux->dato;
        }
        aux = aux->next;
    }
    return 0;
}

template <typename T>
void Lista<T>::eliminaInicial() {
    if (lon > 0) {
        Nodo* aux = ini;
        ini = ini->next;
        delete aux;
        lon--;
    }
}

template <typename T>
void Lista<T>::eliminaPos(size_t pos) {

}

template <typename T>
void Lista<T>::eliminaFinal() {

}

template <typename T>
void Lista<T>::agregaPos(T dato, size_t pos) {
    if (pos > lon) return;
    if (pos == 0) {
        push_Back_List(dato);
    }
    else {
        Nodo* aux = ini;
        for (int i = 1; i < pos; i++) {
            aux = aux->next;
        }
        Nodo* nuevo = new Nodo(dato, aux->next);
        if (nuevo != nullptr) {
            aux->next = nuevo;
            lon++;
        }
    }
}

template <typename T>
void Lista<T>::agregaFinal(T dato) {
    agregarPos(dato, lon); // ;)
}

template <typename T>
void Lista<T>::modificarInicial(T dato) {
    if (lon > 0) {
        ini->dato = dato;
    }
}

template <typename T>
void Lista<T>::modificarPos(T dato, size_t pos) {
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (size_t i = 0; i < pos; i++) {
            aux = aux->next;
        }
        aux->dato = dato;
    }
}

template <typename T>
void Lista<T>::modificarFinal(T dato) {
    modificar(dato, lon - 1);
}

template <typename T>
T Lista<T>::obtenerInicial() {
    return obtener_Pos(0);
}

template <typename T>
T Lista<T>::obtener_Pos(size_t pos) {
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (size_t i = 0; i < pos; i++) {
            aux = aux->next;
        }
        return aux->dato;
    }
    else {
        return 0;
    }
}

template <typename T>
T Lista<T>::obtenerFinal() {
    return (lon - 1);
}