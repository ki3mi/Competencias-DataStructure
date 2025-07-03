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
int main(){
    Nodo* lista = NULL;
    int opcion;

    do {
        cout << "\n--- MENU DE OPCIONES ---\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Mostrar procesos\n";
        cout << "3. Eliminar proceso\n";
        cout << "4. Buscar proceso\n";
        cout << "5. Modificar prioridad de proceso\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                int id, priority;
                string nombre;
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cout << "Ingrese nombre del proceso: ";
                cin.ignore(); // limpiar el buffer
                getline(cin, nombre);
                cout << "Ingrese prioridad (1 a 10): ";
                cin >> priority;
                if(priority >= 1 && priority <= 10){
                    addToList(lista, id, nombre, priority);
                    cout << "Proceso agregado.\n";
                } else {
                    cout << "Prioridad no válida. Debe ser entre 1 y 10.\n";
                }
                break;
            }

            case 2:
                showList(lista);
                break;

            case 3: {
                int id;
                cout << "Ingrese ID del proceso a eliminar: ";
                cin >> id;
                deleteToList(lista, id);
                break;
            }

            case 4: {
                int id;
                cout << "Ingrese ID del proceso a buscar: ";
                cin >> id;
                searchToList(lista, id);
                break;
            }

            case 5: {
                int id, newPriority;
                cout << "Ingrese ID del proceso a modificar: ";
                cin >> id;
                cout << "Ingrese nueva prioridad (1 a 10): ";
                cin >> newPriority;
                modifyList(lista, id, newPriority);
                break;
            }

            case 6:
                cout << "Saliendo del programa.\n";
                break;

            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while(opcion != 6);

    return 0;
}
