#include<iostream>
using namespace std;

int nElements = 0;
struct Nodo{
    int id;
    string proceso;
    Nodo* next;
    Nodo(){
        id = 0;
        proceso = "";
        next = NULL;
    }
    Nodo(int nID, string nProceso){
        id = nID;
        proceso = nProceso;
        next = NULL;
    }
};

void addToHist(Nodo*& lista, string proceso){
    nElements++;
    Nodo* nuevoNodo = new Nodo(nElements, proceso);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        Nodo* temp = lista;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nuevoNodo;
    }
}
void showHist(Nodo* lista){
    Nodo* temp = lista;
    while(temp != NULL){
        cout<<"*************\n";
        cout<<"ID: "<<temp->id<<"\n";
        cout<<"Proceso: "<<temp->proceso<<"\n";
        temp = temp->next;
    }
}
int main(){
    Nodo* lista = NULL;
    addToHist(lista, "Agregado");
    showHist(lista);
    system("pause");
}