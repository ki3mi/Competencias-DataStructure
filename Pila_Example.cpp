#include <iostream>
using namespace std;

#define MAX 5
int top = -1;

struct Pila {
    int id;
    string nombre;

    // Constructor por defecto
    Pila() {
        id = 0;
        nombre = "";
    }

    // Constructor parametrizado
    Pila(int nID, string nNombre) {
        id = nID;
        nombre = nNombre;
    }
};

Pila* memoria[MAX];

// --- Agregar elemento a la pila ---
void addToPila(int id, string nombre){
    if(top < MAX - 1){
        top++;
        memoria[top] = new Pila(id, nombre);
        cout << "Elemento agregado.\n";
    } else {
        cout << "La pila está llena.\n";
    }
}

// --- Eliminar el elemento del tope de la pila ---
void removeFromPila(){
    if(top == -1){
        cout << "La pila está vacía.\n";
    } else {
        cout << "Elemento retirado:\n";
        cout << "ID: " << memoria[top]->id << "\n";
        cout << "Nombre: " << memoria[top]->nombre << "\n";
        delete memoria[top];
        top--;
    }
}

// --- Mostrar pila de arriba hacia abajo ---
void showPila(){
    if(top == -1){
        cout << "La pila está vacía.\n";
        return;
    }
    cout << "\n--- Contenido de la pila ---\n";
    for(int i = top; i >= 0; i--){
        cout << "ID: " << memoria[i]->id << "\n";
        cout << "Nombre: " << memoria[i]->nombre << "\n\n";
    }
}

// --- Menú principal ---
int main(){
    int opcion;

    do {
        cout << "\n--- MENU PILA ---\n";
        cout << "1. Agregar elemento\n";
        cout << "2. Eliminar elemento\n";
        cout << "3. Mostrar pila\n";
        cout << "4. Salir\n";
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
                addToPila(id, nombre);
                break;
            }

            case 2:
                removeFromPila();
                break;

            case 3:
                showPila();
                break;

            case 4:
                cout << "Saliendo del programa.\n";
                break;

            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while(opcion != 4);

    // Liberar memoria restante antes de salir
    while(top != -1){
        delete memoria[top];
        top--;
    }

    return 0;
}
