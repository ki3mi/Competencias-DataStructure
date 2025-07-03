#include <iostream>
using namespace std;

#define MAX 5

int frente = -1;
int final = -1;

struct Cola {
    int id;
    string nombre;
};

Cola cola[MAX];

// --- Verifica si la cola está vacía ---
bool colaEstaVacia(){
    return frente == -1;
}

// --- Verifica si la cola está llena ---
bool colaEstaLlena(){
    return final == MAX - 1;
}

// --- Agrega un elemento al final de la cola ---
void agregarElementoACola(Cola proceso){
    if(colaEstaLlena()){
        cout << "La cola está llena.\n";
    } else {
        if(frente == -1) frente = 0;
        final++;
        cola[final] = proceso;
        cout << "Elemento encolado: " << proceso.nombre << "\n";
    }
}

// --- Elimina el elemento del frente de la cola ---
void quitarElementoDeCola(){
    if(colaEstaVacia()){
        cout << "La cola está vacía.\n";
    } else {
        cout << "Elemento desencolado:\n";
        cout << "ID: " << cola[frente].id << "\n";
        cout << "Nombre: " << cola[frente].nombre << "\n";
        frente++;
        if(frente > final){
            frente = final = -1; // Reiniciar cola vacía
        }
    }
}

// --- Muestra todos los elementos en la cola ---
void mostrarCola(){
    if(colaEstaVacia()){
        cout << "La cola está vacía.\n";
    } else {
        cout << "\n--- Contenido de la cola ---\n";
        for(int i = frente; i <= final; i++){
            cout << "ID: " << cola[i].id << "\n";
            cout << "Nombre: " << cola[i].nombre << "\n\n";
        }
    }
}

// --- Menú principal para interacción del usuario ---
int main(){
    int opcion;

    do {
        cout << "\n--- MENU DE COLA ---\n";
        cout << "1. Encolar elemento\n";
        cout << "2. Desencolar elemento\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion){
            case 1: {
                Cola nuevo;
                cout << "Ingrese ID: ";
                cin >> nuevo.id;
                cout << "Ingrese nombre: ";
                cin.ignore();
                getline(cin, nuevo.nombre);
                agregarElementoACola(nuevo);
                break;
            }

            case 2:
                quitarElementoDeCola();
                break;

            case 3:
                mostrarCola();
                break;

            case 4:
                cout << "Saliendo del programa.\n";
                break;

            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }

    } while(opcion != 4);

    return 0;
}
