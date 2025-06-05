#include <iostream>
#include <limits>
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
#define MEM 51
int pila[MEM];

int top = -1;

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
    NodoH(){ id = 0; proceso = ""; next = NULL; }
    NodoH(int nID, string nProceso){ id = nID; proceso = nProceso; next = NULL; }
};

Nodo* lista = NULL;
NodoH* historial = NULL;
int globalID = 0;

// =====================
// FUNCIONES DE LISTA
// =====================

void addToList(Nodo*& lista, int id, string name, int priori){
    Nodo* nuevoNodo = new Nodo(id, name, priori);
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        Nodo* temp = lista;
        while (temp->next != NULL){ temp = temp->next; }
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
string getElement(Nodo*lista, int searchId){
    Nodo* temp = lista;
    while(temp != NULL && temp->id != searchId){
        temp = temp->next;
    }
    return temp->proceso;
}

int getPriority(Nodo*lista, int searchId){
    Nodo* temp = lista;
    while(temp != NULL && temp->id != searchId){
        temp = temp->next;
    }
    return temp->priority;
}

void deleteToList(Nodo*& lista, int deleteId){
    if(lista == NULL){ cout<<"La lista esta vacia\n"; return; }
    Nodo* temp = lista;
    Nodo* anterior = NULL;
    if(temp->id == deleteId){
        lista = temp->next;
        delete temp;
        return;
    }
    while(temp != NULL && temp->id != deleteId){ anterior = temp; temp = temp->next; }
    if(temp == NULL){ cout<<"Id no encontrado\n"; return; }
    anterior->next = temp->next;
    delete temp;
}

void searchToList(Nodo* lista, string name){
    Nodo* temp = lista;
    bool found = false;
    while(temp != NULL){
        if(temp->proceso == name){
            cout<<"ID: "<<temp->id<<"\nProceso: "<<temp->proceso<<"\nPrioridad: "<<temp->priority<<"\n";
            found = true;
        }
        temp = temp->next;
    }
    if(!found){ cout<<"Nombre de proceso no encontrado\n"; }
}
bool isExist(Nodo* lista, int searchId){
    Nodo* temp = lista;
    while(temp != NULL && temp->id != searchId){
        temp = temp->next;
    }
    if (temp == NULL){
        return false;
    }
    return true;
}

void modifyList(Nodo*& lista, int modifyId, int newPriority){
    if(newPriority < 1 || newPriority > 50){ cout<<"Prioridad no valida\n"; return; }
    Nodo* temp = lista;
    while(temp != NULL && temp->id != modifyId){ temp = temp->next; }
    if(temp == NULL){ cout<<"ID no encontrado\n"; return; }
    temp->priority = newPriority;
}

// =====================
// FUNCIONES DE COLA
// =====================

bool estaVacia(){ return frente == - 1; }
bool estaLlena(){ return final == MAX - 1; }

void encolarCPU(Cola proceso){
    if(estaLlena()){ cout<<"La cola del CPU esta llena\n"; }
    else{
        if(frente == -1) frente = 0;
        final++;
        cola[final] = proceso;
        cout<<"Proceso: "<<proceso.proceso<<" encolado.\n";
    }
}

void desencolarCPU(){
    if(estaVacia()){ cout<<"La cola del CPU esta vacía\n"; }
    else{
        cout<<"Proceso: "<<cola[frente].proceso<<" desencolado.\n";
        frente++;
        if(frente > final) frente = final = -1;
    }
}

void showCola(){
    if(estaVacia()){ cout<<"La cola del CPU está vacía.\n"; }
    else{
        for(int i = frente; i <= final; i++){
            cout<<"Proceso: "<<cola[i].proceso<<"\nPrioridad: "<<cola[i].priority<<"\n";
        }
    }
}

// =====================
// FUNCIONES DE PILA
// =====================

int getMemory(){
    return top+1/MEM;
}

bool isFull(int prioridad){
    if(top+prioridad < MEM - 1){
        return false;
    }
    else{
        return true;
    }
}

void addToPila(int prioridad){
    if(!isFull(prioridad)){
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

// =====================
// FUNCIONES DE HISTORIAL
// =====================

void addToHist(NodoH*& lista, string proceso){
    nElements++;
    NodoH* nuevoNodo = new NodoH(nElements, proceso);
    if(lista == NULL){ lista = nuevoNodo; }
    else{
        NodoH* temp = lista;
        while(temp->next != NULL){ temp = temp->next; }
        temp->next = nuevoNodo;
    }
}

void showHist(NodoH* lista){
    NodoH* temp = lista;
    while(temp != NULL){
        cout<<"*************\n";
        cout<<"ID: "<<temp->id<<"\nProceso: "<<temp->proceso<<"\n";
        temp = temp->next;
    }
}

// =====================
// MENÚS
// =====================

void menu(){
    cout<<"******* GESTOR DE PROCESOS *******\n";
    cout<<"1: Agregar proceso a la cola de tareas\n";
    cout<<"2: Atender procesos pendientes (CPU y Memoria)\n";
    cout<<"3: Atender procesos en ejecucion\n";
    cout<<"-----------------------------------\n";
    cout<<"4: Mostrar procesos activos\n";
    cout<<"5: Mostrar cola de tareas\n";
    cout<<"6: Mostrar historial\n";
    cout<<"0: Salir\n";
}

void limpiarEntrada(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menu2(){
    int opcion;
    do{
        system("cls");
        cout<<"******* PROCESOS PENDIENTES *******\n";
        cout<<"1: Asignar prioridad al siguiente proceso (1-50)\n";
        cout<<"0: Volver\n";
        cin>>opcion;
        if(cin.fail()){
            limpiarEntrada();
            cout<<"Entrada invalida. Intente de nuevo.\n";
            continue;
        }
        switch(opcion){
            case 1:
                if(!estaVacia()){
                    int prioridad;
                    cout<<"Ingrese prioridad para proceso: ";
                    cin>>prioridad;
                    if(cin.fail() || prioridad < 1 || prioridad > 50){
                        limpiarEntrada();
                        cout<<"Prioridad inválida. Debe estar entre 1 y 50.\n";
                        break;
                    }
                    if(isFull(prioridad)){
                       cout<<"Memoria insoficiente\n"; 
                    }else{
                        Cola proc = cola[frente];
                        proc.priority = prioridad;
                        addToList(lista, proc.id, proc.proceso, prioridad);
                        addToPila(prioridad);
                        desencolarCPU();
                    }
                }else{
                    cout<<"No hay procesos pendientes\n";
                }
                system("pause");
                break;
            case 0: break;
            default: cout<<"Opcion invalida\n";
        }
    }while(opcion != 0);
}

void menu3(){
    int opcion;
    do{
        system("cls");
        cout<<"******* PROCESOS EN EJECUCION *******\n";
        cout<<"1: Finalizar proceso\n";
        cout<<"2: Buscar proceso por nombre\n";
        cout<<"3: Editar prioridad\n";
        cout<<"0: Volver\n";
        cin>>opcion;
        if(cin.fail()){
            limpiarEntrada();
            cout<<"Entrada inválida. Intente de nuevo.\n";
            continue;
        }
        switch(opcion){
            case 1: {
                string name;
                int prioridad;
                int id;
                cout<<"Procesos:\n";
                showList(lista);
                cout<<"--------------\n";
                cout<<"Ingrese ID a finalizar: ";
                cin>>id;
                if(!isExist(lista, id)){
                    limpiarEntrada();
                    cout<<"ID invalido\n";
                    break;
                }
                name = getElement(lista, id);
                prioridad = getPriority(lista, id);
                deleteToList(lista, id);
                removeFromPila(prioridad); // Enviar la prioridad
                addToHist(historial, name);
                system("pause");
                break;
            }
            case 2: {
                string name;
                cout<<"Ingrese nombre del proceso: ";
                cin>>name;
                searchToList(lista, name);
                system("pause");
                break;
            }
            case 3: {
                int id, newPriority, priority, diferencia;
                cout<<"Procesos:\n";
                showList(lista);
                cout<<"--------------\n";
                cout<<"ID a modificar: "; cin>>id;
                priority = getPriority(lista, id);                
                cout<<"Nueva prioridad: "; cin>>newPriority;
                if(cin.fail() || newPriority < 1 || newPriority > 50){
                    limpiarEntrada();
                    cout<<"Prioridad invalida. Debe estar entre 1 y 50.\n";
                    break;
                }
                if(newPriority>priority){
                    diferencia = newPriority - priority;
                    if(isFull(diferencia)){
                        cout<<"Memoria insuficiente\n";
                    }
                }else{
                    diferencia = priority-newPriority;
                    removeFromPila(priority);
                    addToPila(newPriority);
                    modifyList(lista, id, newPriority);
                }
                system("pause");
                break;
            }
            case 0: break;
            default: cout<<"Opcion invalida\n";
        }
    }while(opcion != 0);
}

int main(){
    int opcion;
    do{
        menu();
        cin>>opcion;
        if(cin.fail()){
            limpiarEntrada();
            cout<<"Entrada invalida. Intente de nuevo.\n";
            continue;
        }
        switch(opcion){
            case 1: {
                globalID++;
                string name;
                cout<<"Ingrese nombre del proceso: ";
                cin>>name;
                Cola nuevo = {globalID, name, 0};
                encolarCPU(nuevo);
                break;
            }
            case 2: menu2(); break;
            case 3: menu3(); break;
            case 4: showList(lista); break;
            case 5: showCola(); break;
            case 6: showHist(historial); break;
            case 0: cout<<"Saliendo...\n"; break;
            default: cout<<"Opción invalida\n";
        }
        if(opcion!=0){
            system("pause");
        }
        system("cls");
    }while(opcion != 0);
    return 0;
}
