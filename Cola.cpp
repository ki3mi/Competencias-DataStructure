#include<iostream>
using namespace std;

#define MAX 5
Nodo cola[MAX];

int frente = -1;
int final = -1;

struct Nodo{
    int id;
    string proceso;
    int priority;
};
bool estaVacia(){
    return frente == - 1;
}

bool estaLlena(){
    return final == MAX - 1;
}

void encolarCPU(Nodo proceso){
    if(estaLlena()){
        cout<<"La cola del CPU está llena \n";
    }else{
        if(frente == -1){
            frente = 0;
        }
        final++;
        cola[final] = proceso;
        cout<<"Proceso: "<<proceso.proceso<<" encolado."<<"\n"<<endl;
    }
}

void desencolarCPU(){
    if(estaVacia()){
        cout<<"La cola del CPU está vacía\n";
    }else{
        cout<<"Proceso: "<<cola[frente].proceso<<" desencolado."<<endl;
        frente++;
        if(frente > final){
            frente = final = -1;
        }
    }
}

int main(){
    // TAREAS PENDIENTES
    // HACER EL MENÚ Y UNIFICAR LOS CÓDIGOS
}