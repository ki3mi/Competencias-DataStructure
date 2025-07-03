#include <iostream>
using namespace std;

// --- Estructura del nodo ---
struct Nodo {
    int id;
    string nombre;
    string genero;
    Nodo* right;
    Nodo* left;
};

// --- Crear un nuevo nodo ---
Nodo* crearNodo(int id, string nombre, string genero) {
    return new Nodo{id, nombre, genero, NULL, NULL};
}

// --- Insertar hijo (izquierdo = madre, derecho = padre) ---
void insertarFamiliar(Nodo* nodo, string nombre, string genero) {
    int newId = nodo->id * 10;

    if (genero == "M" && nodo->right == NULL) {
        nodo->right = crearNodo(newId + 1, nombre, genero);
        cout << "Padre asignado correctamente a " << nodo->nombre << "\n";
    } else if (genero == "F" && nodo->left == NULL) {
        nodo->left = crearNodo(newId, nombre, genero);
        cout << "Madre asignada correctamente a " << nodo->nombre << "\n";
    } else {
        cout << "Error al insertar: ";
        if (genero != "M" && genero != "F")
            cout << "género inválido.\n";
        else
            cout << "ese familiar ya fue asignado.\n";
    }
}

// --- Buscar por nombre (recursivo preorden) ---
Nodo* buscarPorNombre(Nodo* nodo, string nombre) {
    if (!nodo) return NULL;
    if (nodo->nombre == nombre) return nodo;

    Nodo* izq = buscarPorNombre(nodo->left, nombre);
    if (izq) return izq;

    return buscarPorNombre(nodo->right, nombre);
}

// --- Buscar por ID (usa el patrón del ID como camino binario) ---
Nodo* buscarPorId(Nodo* nodo, int id) {
    if (!nodo || nodo->id == id) return nodo;

    int actual = nodo->id;
    string ruta = to_string(id).substr(to_string(actual).length());

    for (char paso : ruta) {
        if (!nodo) return NULL;
        nodo = (paso == '0') ? nodo->left : nodo->right;
    }
    return nodo;
}

// --- Eliminar por ID ---
bool eliminarPorId(Nodo* raiz, int id) {
    if (!raiz || id == 1) return false;

    Nodo* padre = buscarPorId(raiz, id / 10);
    if (!padre) return false;

    if (id % 10 == 0 && padre->left && padre->left->id == id) {
        delete padre->left;
        padre->left = NULL;
        return true;
    }
    if (id % 10 == 1 && padre->right && padre->right->id == id) {
        delete padre->right;
        padre->right = NULL;
        return true;
    }
    return false;
}

// --- Eliminar por nombre ---
bool eliminarPorNombre(Nodo* nodo, string nombre) {
    if (!nodo) return false;

    if (nodo->left && nodo->left->nombre == nombre) {
        delete nodo->left;
        nodo->left = NULL;
        return true;
    }
    if (nodo->right && nodo->right->nombre == nombre) {
        delete nodo->right;
        nodo->right = NULL;
        return true;
    }

    return eliminarPorNombre(nodo->left, nombre) || eliminarPorNombre(nodo->right, nombre);
}

// --- Recorridos del árbol ---
void mostrarPreorden(Nodo* nodo) {
    if (!nodo) return;
    cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Género: " << nodo->genero << "\n";
    mostrarPreorden(nodo->left);
    mostrarPreorden(nodo->right);
}

void mostrarInorden(Nodo* nodo) {
    if (!nodo) return;
    mostrarInorden(nodo->left);
    cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Género: " << nodo->genero << "\n";
    mostrarInorden(nodo->right);
}

void mostrarPostorden(Nodo* nodo) {
    if (!nodo) return;
    mostrarPostorden(nodo->left);
    mostrarPostorden(nodo->right);
    cout << "ID: " << nodo->id << ", Nombre: " << nodo->nombre << ", Género: " << nodo->genero << "\n";
}

// --- Menú principal ---
int main() {
    Nodo* raiz = crearNodo(1, "Persona Principal", "F");
    int opcion;

    do {
        cout << "\n--- MENU ARBOL GENEALOGICO ---\n";
        cout << "1. Insertar familiar\n";
        cout << "2. Buscar por nombre\n";
        cout << "3. Buscar por ID\n";
        cout << "4. Eliminar por nombre\n";
        cout << "5. Eliminar por ID\n";
        cout << "6. Mostrar Preorden\n";
        cout << "7. Mostrar Inorden\n";
        cout << "8. Mostrar Postorden\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombreReferencia;
                cout << "Ingrese nombre de la persona a quien agregar familiar: ";
                cin.ignore();
                getline(cin, nombreReferencia);
                Nodo* ref = buscarPorNombre(raiz, nombreReferencia);
                if (!ref) {
                    cout << "Persona no encontrada.\n";
                    break;
                }
                string nombreNuevo, genero;
                cout << "Ingrese nombre del familiar: ";
                getline(cin, nombreNuevo);
                cout << "Ingrese género (M/F): ";
                cin >> genero;
                insertarFamiliar(ref, nombreNuevo, genero);
                break;
            }

            case 2: {
                string nombre;
                cout << "Ingrese nombre a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                Nodo* encontrado = buscarPorNombre(raiz, nombre);
                if (encontrado)
                    cout << "ID: " << encontrado->id << ", Género: " << encontrado->genero << "\n";
                else
                    cout << "No encontrado.\n";
                break;
            }

            case 3: {
                int id;
                cout << "Ingrese ID a buscar: ";
                cin >> id;
                Nodo* encontrado = buscarPorId(raiz, id);
                if (encontrado)
                    cout << "Nombre: " << encontrado->nombre << ", Género: " << encontrado->genero << "\n";
                else
                    cout << "No encontrado.\n";
                break;
            }

            case 4: {
                string nombre;
                cout << "Ingrese nombre del nodo a eliminar: ";
                cin.ignore();
                getline(cin, nombre);
                if (!eliminarPorNombre(raiz, nombre))
                    cout << "No se encontró el nodo.\n";
                break;
            }

            case 5: {
                int id;
                cout << "Ingrese ID del nodo a eliminar: ";
                cin >> id;
                if (!eliminarPorId(raiz, id))
                    cout << "No se encontró el nodo.\n";
                break;
            }

            case 6:
                cout << "\n--- Recorrido Preorden ---\n";
                mostrarPreorden(raiz);
                break;

            case 7:
                cout << "\n--- Recorrido Inorden ---\n";
                mostrarInorden(raiz);
                break;

            case 8:
                cout << "\n--- Recorrido Postorden ---\n";
                mostrarPostorden(raiz);
                break;

            case 9:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opción inválida.\n";
        }

    } while(opcion != 9);

    return 0;
}
