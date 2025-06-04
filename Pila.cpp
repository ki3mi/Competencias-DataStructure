#include<iostream>
using namespace std;
#define MAX 5

int top = -1;

struct Pila{
    int id;
    string proceso;
    
    // Constructor por defecto
    Pila(){
        id = 0;
        proceso = "";
    }
    
    // Constructor parametrizado
    Pila(int nID, string nProceso){
        id = nID;
        proceso = nProceso;
    }
};

Pila* memoria[MAX];


void addToPila(int id, string proceso){
    Pila* element = new Pila(id, proceso);
    if(top < MAX - 1){
        top++;
        memoria[top] = element;
    }else{
        cout<<"La memoria esta llena \n";
    }
}

void removeFromPila(){
    if(top == -1){
        cout<<"No hay mas procesos en la memoria \n";
    }else{
        cout<<"Proceso retirado de la memoria: \n";
        cout<<"-> "<<memoria[top]->proceso<<"\n";
        delete memoria[top];
        top--;
    }
}
int main(){
    addToPila(1, "Proceso A");
    addToPila(2, "Proceso B");
    addToPila(3, "Proceso C");

    removeFromPila();
    removeFromPila();
    removeFromPila();
    removeFromPila(); // Probar pila vacía
    system("pause");
}