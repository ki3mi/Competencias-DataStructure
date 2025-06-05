#include <iostream>
using namespace std;
#define MAX 5

// =====================
// ESTRUCTURAS DE DATOS
// =====================

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

// Pila
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

// Cola
int frente = -1;
int final = -1;

struct Cola{
    int id;
    string proceso;
    int priority;
};
Cola cola[MAX];

// Historial
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

// =====================
// GESTOR DE PROCESOS
// =====================

// FUNCIONES

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
        cout<<"Prioridad: "<<temp->priority<<"\n";
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

void modifyList(Nodo*& lista, int modifyId, int newPriority){

    if(newPriority < 1 || newPriority > 10){
        cout<<"Prioridad no valida. Solo valores de 1 a 10 \n";
        return;
    }

    Nodo* temp = lista;

    while(temp != NULL && temp->id != modifyId){
        temp = temp->next;
    }

    if(temp == NULL){
        cout<<"ID no encontrado \n";
        return;
    }

    temp->priority = newPriority;

    cout<<"ID: "<<temp->id<<"\n";
    cout<<"Proceso: "<<temp->proceso<<"\n";
    cout<<"Nueva prioridad: "<<temp->priority<<"\n";
    
}

// =====================
//    GESTOR DE CPU
// =====================

// FUNCIONES
bool estaVacia(){
    return frente == - 1;
}

bool estaLlena(){
    return final == MAX - 1;
}

void encolarCPU(Cola proceso){
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

void showCola(){
    if(estaVacia()){
        cout<<"La cola del CPU está vacía. \n";
    }else{
        cout<<"Procesos en la cola del CPU. \n";
        for(int i = frente; i <= final; i++){
            cout<<"---------------------------------\n";
            cout<<"proceso: "<<cola[i].proceso<<"\n";
            cout<<"Prioridad: "<<cola[i].priority<<"\n";
        }
        cout<<endl;
    }
}

// =====================
//   GESTOR DE MEMORIA
// =====================

// FUNCIONES
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

// =====================
// HISTORIAL DE PROCESOS
// =====================

// FUNCIONES

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

// =====================
//          MENU
// =====================

void menu(){
    cout<<"******* GESTOR DE PROCESOS *******\n";
    cout<<"1: Agregar proceso a la cola de tareas\n";
    cout<<"2: Atender procesos pendientes (CPU y Memoria)\n";
    cout<<"3: Atender procesos en ejecucion\n";
    cout<<"-----------------------------------\n";
    cout<<"4: Mostrar procesos activos\n";
    cout<<"5: Mostrar cola de tareas\n";
    cout<<"6: Mostrar pila activa (memoria)\n";
    cout<<"7: Mostrar Historial\n";
    cout<<"0: Salir\n";
}
void menu2(){
    cout<<"******* PROCESOS PENDIENTES *******\n";
    cout<<"1: Asignar prioridad al siguiente proceso (Baja - Media - Alta)\n";
    cout<<"0: Volver\n";
}
void menu3(){
    cout<<"******* PROCESOS EN EJECUCION *******\n";
    cout<<"1: Finalizar proceso\n";
    cout<<"2: Buscar proceso\n";
    cout<<"3: Editar prioridad\n";
    cout<<"0: Volver\n";
}

// Lista principal de procesos activos
Nodo* listaActiva = NULL;
NodoH* historial = NULL;
int idGlobal = 1; // Para generar IDs únicos

int main() {
    int opcion;
    bool ejecutando = true;

    while (ejecutando) {
        menu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                // Agregar proceso a la cola
                string nombre;
                cout << "Nombre del proceso: ";
                cin.ignore(); getline(cin, nombre);
                Cola nuevo = {idGlobal++, nombre, 0};
                encolarCPU(nuevo);
                break;
            }
            case 2: {
                if (!estaVacia()) {
                    Cola proceso = cola[frente];
                    desencolarCPU();
                    addToPila(proceso.id, proceso.proceso);
                    addToList(listaActiva, proceso.id, proceso.proceso, proceso.priority);
                    cout << "Proceso " << proceso.proceso << " movido a ejecucion." << endl;
                }
                break;
            }
            case 3: {
                int sub;
                menu3();
                cout << "Seleccione una opcion: ";
                cin >> sub;
                switch(sub){
                    case 1: {
                        int id;
                        cout << "ID del proceso a finalizar: ";
                        cin >> id;
                        // Buscar el nombre para historial
                        Nodo* temp = listaActiva;
                        string nombre = "";
                        while (temp != NULL && temp->id != id) temp = temp->next;
                        if (temp != NULL) nombre = temp->proceso;
                        deleteToList(listaActiva, id);
                        removeFromPila();
                        addToHist(historial, nombre);
                        break;
                    }
                    case 2: {
                        int id;
                        cout << "ID a buscar: ";
                        cin >> id;
                        searchToList(listaActiva, id);
                        break;
                    }
                    case 3: {
                        int id, prioridad;
                        cout << "ID a modificar: "; cin >> id;
                        cout << "Nueva prioridad (1-10): "; cin >> prioridad;
                        modifyList(listaActiva, id, prioridad);
                        break;
                    }
                }
                break;
            }
            case 4:
                showList(listaActiva);
                break;
            case 5:
                showCola();
                break;
            case 6:
                for(int i = 0; i <= top; i++){
                    cout << "ID: " << memoria[i]->id << ", Proceso: " << memoria[i]->proceso << endl;
                }
                break;
            case 0:
                ejecutando = false;
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
        system("pause");
        system("cls");
    }
    return 0;
}