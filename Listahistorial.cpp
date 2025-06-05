#include<iostream>
using namespace std;

int nElements = 0;
struct NodoH{
    int id;
    string proceso;
    NodoH* next;
    NodoH(){
        id = 0;
        proceso = "";
        next = NULL;
    }
    NodoH(int nID, string nProceso){
        id = nID;
        proceso = nProceso;
        next = NULL;
    }
};

void addToHist(NodoH*& lista, string proceso){
    nElements++;
    NodoH* nuevoNodo = new NodoH(nElements, proceso);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        NodoH* temp = lista;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nuevoNodo;
    }
}
void showHist(NodoH* lista){
    NodoH* temp = lista;
    while(temp != NULL){
        cout<<"*************\n";
        cout<<"ID: "<<temp->id<<"\n";
        cout<<"Proceso: "<<temp->proceso<<"\n";
        temp = temp->next;
    }
}
int main(){
    NodoH* lista = NULL;
    addToHist(lista, "Agregado");
    showHist(lista);
    system("pause");
}