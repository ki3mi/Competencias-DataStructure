#include <iostream>
using namespace std;

#define MAX 100

int lista[MAX];
int tam = 0;

// --- Agregar elemento al final ---
void insertarElemento(int valor) {
    if (tam < MAX) {
        lista[tam++] = valor;
        cout << "Elemento insertado.\n";
    } else {
        cout << "La lista está llena.\n";
    }
}

// --- Eliminar primer elemento igual a 'valor' ---
void eliminarElemento(int valor) {
    int pos = -1;
    for (int i = 0; i < tam; i++) {
        if (lista[i] == valor) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        cout << "Elemento no encontrado.\n";
        return;
    }
    for (int i = pos; i < tam - 1; i++) {
        lista[i] = lista[i + 1];
    }
    tam--;
    cout << "Elemento eliminado.\n";
}

// --- Búsqueda secuencial ---
int busquedaSecuencial(int valor) {
    for (int i = 0; i < tam; i++) {
        if (lista[i] == valor)
            return i;
    }
    return -1;
}

// --- Búsqueda binaria (requiere lista ordenada) ---
int busquedaBinaria(int valor) {
    int ini = 0, fin = tam - 1;
    while (ini <= fin) {
        int mid = (ini + fin) / 2;
        if (lista[mid] == valor)
            return mid;
        else if (lista[mid] < valor)
            ini = mid + 1;
        else
            fin = mid - 1;
    }
    return -1;
}

// --- Ordenamiento burbuja ---
void ordenarBurbuja() {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                int temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    cout << "Lista ordenada (burbuja).\n";
}

// --- Ordenamiento selección ---
void ordenarSeleccion() {
    for (int i = 0; i < tam - 1; i++) {
        int min = i;
        for (int j = i + 1; j < tam; j++) {
            if (lista[j] < lista[min])
                min = j;
        }
        if (min != i) {
            int temp = lista[i];
            lista[i] = lista[min];
            lista[min] = temp;
        }
    }
    cout << "Lista ordenada (selección).\n";
}

// --- Ordenamiento inserción ---
void ordenarInsercion() {
    for (int i = 1; i < tam; i++) {
        int actual = lista[i];
        int j = i - 1;
        while (j >= 0 && lista[j] > actual) {
            lista[j + 1] = lista[j];
            j--;
        }
        lista[j + 1] = actual;
    }
    cout << "Lista ordenada (inserción).\n";
}

// --- Mostrar lista ---
void mostrarLista() {
    if (tam == 0) {
        cout << "Lista vacía.\n";
        return;
    }
    cout << "Lista: ";
    for (int i = 0; i < tam; i++)
        cout << lista[i] << " ";
    cout << "\n";
}

// --- Menú principal ---
int main() {
    int opcion;
    do {
        cout << "\n--- MENU DE OPERACIONES DE LISTA ---\n";
        cout << "1. Insertar elemento\n";
        cout << "2. Eliminar elemento\n";
        cout << "3. Buscar (secuencial)\n";
        cout << "4. Buscar (binaria)\n";
        cout << "5. Ordenar (burbuja)\n";
        cout << "6. Ordenar (selección)\n";
        cout << "7. Ordenar (inserción)\n";
        cout << "8. Mostrar lista\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int valor;
                cout << "Ingrese valor a insertar: ";
                cin >> valor;
                insertarElemento(valor);
                break;
            }
            case 2: {
                int valor;
                cout << "Ingrese valor a eliminar: ";
                cin >> valor;
                eliminarElemento(valor);
                break;
            }
            case 3: {
                int valor;
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                int pos = busquedaSecuencial(valor);
                if (pos != -1)
                    cout << "Encontrado en posición " << pos << ".\n";
                else
                    cout << "No encontrado.\n";
                break;
            }
            case 4: {
                int valor;
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                int pos = busquedaBinaria(valor);
                if (pos != -1)
                    cout << "Encontrado en posición " << pos << ".\n";
                else
                    cout << "No encontrado o lista no ordenada.\n";
                break;
            }
            case 5:
                ordenarBurbuja();
                break;
            case 6:
                ordenarSeleccion();
                break;
            case 7:
                ordenarInsercion();
                break;
            case 8:
                mostrarLista();
                break;
            case 9:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 9);

    return 0;
}
