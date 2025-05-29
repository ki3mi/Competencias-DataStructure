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

void showList(Nodo* inicio){
    Nodo* temp = inicio;
    while(temp != NULL){
        cout<<"ID: "<<temp->id<<"\n";
        cout<<"Proceso: "<<temp->proceso<<"\n";
        temp = temp->next;
    }
    cout<<endl;
}
void deleteToList(Nodo*& lista, int deleteId){
    if(lista == NULL){
        cout<<"La lista está vacia";
        return;
    }

    // Creamos los nodos temporal y anterior para reoganizar la lista
    Nodo* temp = lista;
    Nodo* anterior = NULL;

    // Caso en el que el primer nodo es el eliminado (no requiere de anterior)
    if(temp->id == deleteId){
        lista = temp->next;
        cout<<"Nodo eliminado \n";
        cout<<"ID: "<<temp->id<<"\n";
        cout<<"Proceso: "<<temp->proceso<<"\n";
        delete temp; // Liberando espacio de memoria
        return;
    }
    // Buscando nodo por ID y el nodo anterior a ese
    while(temp != NULL && temp->id != deleteId){
        anterior = temp;
        temp = temp->next;
    }
    
    if(temp == NULL){
        cout<<"Id no encontrado \n";
        return;
    }

    // Reenlazando el nodo y eliminando
    anterior->next = temp->next;
    cout<<"Nodo eliminado \n";
    cout<<"ID: "<<temp->id<<"\n";
    cout<<"Proceso: "<<temp->proceso<<"\n";
    delete temp;
}

void searchToList(Nodo* lista, int searchId){
    Nodo* temp = lista;

    if(temp == NULL){
        cout<<"La lista está vacia \n";
        return;
    }

    while(temp != NULL && temp->id != searchId){
        temp = temp->next;
    }

    if (temp == NULL){
        cout<<"ID no encontrado \n";
        return;
    }

    cout<<"ID: "<<temp->id<<"\n";
    cout<<"Proceso: "<<temp->proceso<<"\n";
}
int main(){

}