#include <iostream>
using namespace std;

// --- Estructura del nodo ---
struct Nodo {
    int id;
    string nombre;
    Nodo* next;

    Nodo(int value, string name){
        id = value;
        nombre = name;
        next = NULL;
    }
};

// --- Agregar al final de la lista ---
void addToList(Nodo*& lista, int id, string name){
    Nodo* nuevoNodo = new Nodo(id, name);
    if(lista == NULL){
        lista = nuevoNodo;
    } else {
        Nodo* temp = lista;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nuevoNodo;
    }
}

// --- Mostrar toda la lista ---
void showList(Nodo* inicio){
    Nodo* temp = inicio;
    if (temp == NULL) {
        cout << "La lista está vacía.\n";
        return;
    }
    while(temp != NULL){
        cout << "ID: " << temp->id << "\n";
        cout << "Nombre: " << temp->nombre << "\n\n";
        temp = temp->next;
    }
}

// --- Eliminar un nodo por ID ---
void deleteToList(Nodo*& lista, int deleteId){
    if(lista == NULL){
        cout << "La lista está vacía.\n";
        return;
    }

    Nodo* temp = lista;
    Nodo* anterior = NULL;

    if(temp->id == deleteId){
        lista = temp->next;
        cout << "Nodo eliminado:\n";
        cout << "ID: " << temp->id << "\n";
        cout << "Nombre: " << temp->nombre << "\n";
        delete temp;
        return;
    }

    while(temp != NULL && temp->id != deleteId){
        anterior = temp;
        temp = temp->next;
    }

    if(temp == NULL){
        cout << "ID no encontrado.\n";
        return;
    }

    anterior->next = temp->next;
    cout << "Nodo eliminado:\n";
    cout << "ID: " << temp->id << "\n";
    cout << "Nombre: " << temp->nombre << "\n";
    delete temp;
}

// --- Buscar un nodo por ID ---
void searchToList(Nodo* lista, int searchId){
    Nodo* temp = lista;

    if(temp == NULL){
        cout << "La lista está vacía.\n";
        return;
    }

    while(temp != NULL && temp->id != searchId){
        temp = temp->next;
    }

    if(temp == NULL){
        cout << "ID no encontrado.\n";
        return;
    }

    cout << "ID: " << temp->id << "\n";
    cout << "Nombre: " << temp->nombre << "\n";
}

// --- Modificar nombre por ID ---
void modifyList(Nodo*& lista, int modifyId, string nuevoNombre){
    Nodo* temp = lista;

    while(temp != NULL && temp->id != modifyId){
        temp = temp->next;
    }

    if(temp == NULL){
        cout << "ID no encontrado.\n";
        return;
    }

    temp->nombre = nuevoNombre;

    cout << "Nodo actualizado:\n";
    cout << "ID: " << temp->id << "\n";
    cout << "Nuevo nombre: " << temp->nombre << "\n";
}

// --- Menú principal ---
int main(){
    Nodo* lista = NULL;
    int opcion;

    do {
        cout << "\n--- MENU DE OPCIONES ---\n";
        cout << "1. Agregar nodo\n";
        cout << "2. Mostrar lista\n";
        cout << "3. Eliminar nodo\n";
        cout << "4. Buscar nodo\n";
        cout << "5. Modificar nombre\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                int id;
                string nombre;
                cout << "Ingrese ID: ";
                cin >> id;
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nombre);
                addToList(lista, id, nombre);
                cout << "Nodo agregado.\n";
                break;
            }

            case 2:
                showList(lista);
                break;

            case 3: {
                int id;
                cout << "Ingrese ID a eliminar: ";
                cin >> id;
                deleteToList(lista, id);
                break;
            }

            case 4: {
                int id;
                cout << "Ingrese ID a buscar: ";
                cin >> id;
                searchToList(lista, id);
                break;
            }

            case 5: {
                int id;
                string nuevoNombre;
                cout << "Ingrese ID a modificar: ";
                cin >> id;
                cout << "Ingrese nuevo nombre: ";
                cin.ignore();
                getline(cin, nuevoNombre);
                modifyList(lista, id, nuevoNombre);
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
