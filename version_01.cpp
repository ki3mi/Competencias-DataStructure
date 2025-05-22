#include <iostream>
using namespace std;

// =====================
// ESTRUCTURAS DE DATOS
// =====================

struct Proceso {
    int ID;
    string Nombre;
    int Prioridad;
    Proceso* siguiente;
};

struct NodoCola {
    Proceso* proceso;
    NodoCola* siguiente;
};

struct NodoMemoria {
    int ProcesoID;
    int Tamano;
    NodoMemoria* siguiente;
};

struct RegistroHistorial {
    int ID;
    string Nombre;
    int TiempoEjecucion;
    RegistroHistorial* siguiente;
};

// =====================
// GESTOR DE PROCESOS
// =====================

Proceso* InsertarProceso(Proceso* lista, Proceso* nuevo) {
    if (lista == nullptr) return nuevo;
    Proceso* temp = lista;
    while (temp->siguiente != nullptr) temp = temp->siguiente;
    temp->siguiente = nuevo;
    return lista;
}

Proceso* EliminarProceso(Proceso* lista, int id) {
    if (lista == nullptr) return nullptr;
    if (lista->ID == id) {
        Proceso* aux = lista->siguiente;
        delete lista;
        return aux;
    }
    Proceso* anterior = lista;
    Proceso* actual = lista->siguiente;
    while (actual != nullptr) {
        if (actual->ID == id) {
            anterior->siguiente = actual->siguiente;
            delete actual;
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return lista;
}

Proceso* BuscarProceso(Proceso* lista, int id) {
    while (lista != nullptr) {
        if (lista->ID == id) return lista;
        lista = lista->siguiente;
    }
    return nullptr;
}

void ModificarPrioridad(Proceso* lista, int id, int nuevaPrioridad) {
    Proceso* p = BuscarProceso(lista, id);
    if (p != nullptr) p->Prioridad = nuevaPrioridad;
}

// =====================
// PLANIFICADOR DE CPU
// =====================

NodoCola* EncolarProceso(NodoCola* cola, Proceso* proceso) {
    NodoCola* nuevo = new NodoCola{proceso, nullptr};
    if (cola == nullptr || proceso->Prioridad < cola->proceso->Prioridad) {
        nuevo->siguiente = cola;
        return nuevo;
    }
    NodoCola* temp = cola;
    while (temp->siguiente != nullptr && temp->siguiente->proceso->Prioridad <= proceso->Prioridad) {
        temp = temp->siguiente;
    }
    nuevo->siguiente = temp->siguiente;
    temp->siguiente = nuevo;
    return cola;
}

NodoCola* EjecutarProceso(NodoCola* cola, RegistroHistorial*& historial) {
    if (cola == nullptr) return nullptr;
    NodoCola* nodo = cola;
    Proceso* proceso = nodo->proceso;
    cola = cola->siguiente;
    int tiempo;
    cout << "Ingrese tiempo de ejecucion para el proceso " << proceso->Nombre << ": ";
    cin >> tiempo;
    RegistroHistorial* nuevo = new RegistroHistorial{proceso->ID, proceso->Nombre, tiempo, nullptr};
    if (historial == nullptr) {
        historial = nuevo;
    } else {
        RegistroHistorial* temp = historial;
        while (temp->siguiente != nullptr) temp = temp->siguiente;
        temp->siguiente = nuevo;
    }
    delete nodo;
    return cola;
}

// =====================
// GESTOR DE MEMORIA
// =====================

NodoMemoria* AsignarMemoria(NodoMemoria* pila, int id, int tamano) {
    NodoMemoria* nodo = new NodoMemoria{id, tamano, pila};
    return nodo;
}

NodoMemoria* LiberarMemoria(NodoMemoria* pila) {
    if (pila == nullptr) return nullptr;
    NodoMemoria* temp = pila;
    pila = pila->siguiente;
    delete temp;
    return pila;
}

// =====================
// HISTORIAL DE PROCESOS
// =====================

void MostrarHistorial(RegistroHistorial* historial) {
    while (historial != nullptr) {
        cout << "Proceso " << historial->Nombre << " (ID: " << historial->ID << ") ejecutado por "
             << historial->TiempoEjecucion << " segundos.\n";
        historial = historial->siguiente;
    }
}


int main() {
    Proceso* lista = nullptr;
    NodoCola* cola = nullptr;
    NodoMemoria* pila = nullptr;
    RegistroHistorial* historial = nullptr;

    // PENDIENTE: 
    // AGREGAR EL MENÚ DE OPCIONES
    // AGREGAR LA PERSISTENCIA DE DATOS

    return 0;
}
