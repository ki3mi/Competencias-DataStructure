#include<iostream>
using namespace std;


// Lista Enlazada
struct Nodo {
    int id;
    string proceso;
    int priority;
    Nodo* next;

    Nodo(int value, string name, int priori){
        id = value;
        proceso = name;
        priority = priori;
        next = NULL;
    }
};

void addToList(Nodo*& lista, int id, string name, int priori){
    Nodo* nuevoNodo = new Nodo(id, name, priori);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        Nodo* temp = lista;
        while (temp->next != NULL)
        {   
            temp = temp->next;
        }
        temp->next = nuevoNodo;
    }
}



int main(){

}