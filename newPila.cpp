#include<iostream>
using namespace std;
#define MEM 50
int top = -1;
int pila[MEM];

int getMemory(){
    return top+1/MEM;
}
void addToPila(int prioridad){
    if(top+prioridad < MEM - 1){
        for(int i = 0; i<=prioridad; i++){
            top++;
            pila[top] = 1;
        }
    }else{
        cout<<"Memoria insuficiente\n";
    }
}

void removeFromPila(int prioridad){
    if(top == -1){
        cout<<"Memoria Vacia\n";
    }else{
        cout<<"Liberando Memoria\n";
        for(int i = 0; i<=prioridad; i++){
            pila[top] = 0;
            top--;
        }
    }
}