// g++ main.cpp -o main; ./main
// Actividad 2.3 - Sistema de ordenamiento de órdenes de restaurantes
// Archivo de entrada: orders.txt
// Complejidad general del programa: O(n log n) debido al quicksort

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>


using namespace std;

// Estructura para almacenar información de una orden
struct Order {
    string month;      // Mes en texto
    int day;          // Día
    int hour;         // Hora
    int minute;       // Minuto
    int second;       // Segundo
    string restaurant; // Nombre del restaurante
    string dish;      // Platillo ordenado
    int monthNum;     // Mes en número para ordenamiento

    Order() : day(0), hour(0), minute(0), second(0), monthNum(0) {}
};

// Función para convertir mes de texto a número - Complejidad: O(1)
int monthToNumber(string month) {
    if (month == "ene" || month == "Ene") return 1;
    if (month == "Feb") return 2;
    if (month == "Mar") return 3;
    if (month == "Abr") return 4;
    if (month == "May") return 5;
    if (month == "Jun") return 6;
    if (month == "Jul") return 7;
    if (month == "Ago") return 8;
    if (month == "Sep") return 9;
    if (month == "Oct") return 10;
    if (month == "Nov") return 11;
    if (month == "Dic") return 12;
    return 0;
}

// ----------------------- NODO PARA LISTA DOBLEMENTE ENLAZADA -----------------------
template <class T>
class Node {
public:
    T value;
    Node<T> *prev;
    Node<T> *next;

    Node(T valor) {
        this->value = valor;
        this->prev = NULL;
        this->next = NULL;
    }
};

// ----------------------- LISTA DOBLEMENTE ENLAZADA CIRCULAR -----------------------
template <class T>
class List {
    Node<T> *first;
    Node<T> *last;
    int size;

public:
    List() {
        this->first = NULL;
        this->last = NULL;
        this->size = 0;
    }

    int getSize() { return size; }
    Node<T>* getFirst() { return this->first; }
    Node<T>* getLast() { return this->last; }
    bool isEmpty() { return size == 0; }

    // Insertar al principio - Complejidad: O(1)
    void insertFirst(T newValue) {
        Node<T> *nuevo = new Node<T>(newValue);
        Node<T> *aux = this->first;

        nuevo->next = aux;
        this->first = nuevo;

        if (this->size == 0) {
            this->last = nuevo;
        } else {
            aux->prev = nuevo;
        }

        this->first->prev = this->last;
        this->last->next = this->first;

        this->size++;
    }

    // Insertar al final - Complejidad: O(1)
    void insertLast(T newValue) {
        Node<T> *nuevo = new Node<T>(newValue);
        Node<T> *aux = this->last;

        nuevo->prev = aux;
        last = nuevo;

        if (this->size == 0) {
            first = nuevo;
        } else {
            aux->next = nuevo;
        }

        first->prev = last;
        last->next = first;
        this->size++;
    }

    // Eliminar primero - Complejidad: O(1)
    void deleteFirst() {
        if (size == 0) return;

        Node<T> *aux = this->first;

        if (size == 1) {
            first = NULL;
            last = NULL;
            delete aux;
            size = 0;
            return;
        }

        Node<T> *segundo = aux->next;
        segundo->prev = this->last;
        last->next = segundo;

        delete aux;

        this->first = segundo;
        this->size--;
    }

    // Eliminar último - Complejidad: O(1)
    void deleteLast() {
        if (size == 0) return;

        Node<T> *aux = this->last;

        if (size == 1) {
            first = NULL;
            last = NULL;
            delete aux;
            size = 0;
            return;
        }

        Node<T> *penultimo = this->last->prev;
        penultimo->next = this->first;
        first->prev = penultimo;

        delete aux;

        this->last = penultimo;
        this->size--;
    }

    // Mostrar lista - Complejidad: O(n)
    void showList() {
        if (size == 0) {
            cout << "Lista vacía" << endl;
            return;
        }

        Node<T> *aux = this->first;
        int i = 0;

        while (i < this->size) {
            Order ord = aux->value;
            cout << ord.month << " " << ord.day << " " 
                 << ord.hour << ":" << ord.minute << ":" << ord.second 
                 << " R:" << ord.restaurant 
                 << " O:" << ord.dish << endl;
            aux = aux->next;
            i++;
        }
    }

    // Guardar en archivo - Complejidad: O(n)
    void saveToFile(string filename) {
        ofstream file(filename.c_str());

        if (!file.is_open()) {
            cout << "Error al abrir archivo para escritura" << endl;
            return;
        }

        Node<T> *aux = this->first;
        int i = 0;

        while (i < this->size) {
            Order ord = aux->value;
            file << ord.month << " " << ord.day << " " 
                 << ord.hour << ":" << ord.minute << ":" << ord.second 
                 << " R:" << ord.restaurant 
                 << " O:" << ord.dish << endl;
            aux = aux->next;
            i++;
        }

        file.close();
        cout << "\nDatos guardados en: " << filename << endl;
    }
};

// ----------------------- STACK USANDO LISTA -----------------------
template <class T>
class Stack {
    List<T> lista;

public:
    Stack() {}

    int getSize() { return this->lista.getSize(); }
    bool isEmpty() { return this->lista.getSize() == 0; }

    void show() { this->lista.showList(); }

    // Push - Complejidad: O(1)
    void push(T newValue) {
        this->lista.insertFirst(newValue);
    }

    // Pop - Complejidad: O(1)
    T pop() {
        if (isEmpty()) {
            return NULL;
        }
        T aux = this->lista.getFirst()->value;
        this->lista.deleteFirst();
        return aux;
    }
};

// ----------------------- FUNCIONES DE COMPARACIÓN -----------------------

// Compara dos órdenes por restaurante y luego por fecha - Complejidad: O(1)
bool compareOrders(Order a, Order b) {
    // Primero por restaurante
    if (a.restaurant != b.restaurant) {
        return a.restaurant < b.restaurant;
    }

    // Si son del mismo restaurante, por fecha
    if (a.monthNum != b.monthNum) return a.monthNum < b.monthNum;
    if (a.day != b.day) return a.day < b.day;
    if (a.hour != b.hour) return a.hour < b.hour;
    if (a.minute != b.minute) return a.minute < b.minute;
    return a.second < b.second;
}

// ----------------------- QUICKSORT ITERATIVO CON LISTA Y STACK -----------------------

// Partición para quicksort en lista - Complejidad: O(n)
template <class T>
Node<T>* partition(Node<T>* L, Node<T>* R) {
    Node<T>* i = NULL;
    Node<T>* j = L;
    Node<T>* pivot = R;
    T aux;

    while (j != R) {
        if (compareOrders(j->value, pivot->value)) {
            if (i == NULL) {
                i = L;
            } else {
                i = i->next;
            }

            aux = j->value;
            j->value = i->value;
            i->value = aux;
        }
        j = j->next;
    }

    if (i == NULL) {
        i = L;
    } else {
        i = i->next;
    }

    aux = pivot->value;
    pivot->value = i->value;
    i->value = aux;

    return i;
}

// Quicksort iterativo usando Stack - Complejidad: O(n log n) promedio
void quicksort(List<Order>& datos) {
    if (datos.getSize() <= 1) return;

    Stack<Node<Order>*> stack;

    Node<Order>* L = datos.getFirst();
    Node<Order>* R = datos.getLast();
    Node<Order>* pivot;

    stack.push(L);
    stack.push(R);

    while (!stack.isEmpty()) {
        R = stack.pop();
        L = stack.pop();

        if (L == NULL || R == NULL) continue;

        pivot = partition<Order>(L, R);

        // Verificar sublista izquierda
        if (L != pivot && L != pivot->prev) {
            stack.push(L);
            stack.push(pivot->prev);
        }

        // Verificar sublista derecha
        if (R != pivot && R != pivot->next) {
            stack.push(pivot->next);
            stack.push(R);
        }
    }
}

// ----------------------- BÚSQUEDA Y FILTRADO -----------------------

// Busca y muestra órdenes de un restaurante - Complejidad: O(n)
void searchByRestaurant(List<Order>& datos, string restaurantName) {
    transform(restaurantName.begin(), restaurantName.end(), restaurantName.begin(), ::tolower);  
    //Vamos a convertir en minusculas el input del usuario

    Node<Order>* aux = datos.getFirst();
    int count = 0;

    cout << "\n========================================" << endl;
    cout << "Órdenes de: " << restaurantName << endl;
    cout << "========================================" << endl;

    for (int i = 0; i < datos.getSize(); i++) {
        string restLower = aux ->value.restaurant;
        transform(restLower.begin(), restLower.end(), restLower.begin(), ::tolower); 
        //Con esto se crea una copia del nombre del restaurante en minisculas para facilitar al usuario

        if (restLower == restaurantName) {
            Order ord = aux->value;
            cout << ord.month << " " << ord.day << " " 
                 << ord.hour << ":" << ord.minute << ":" << ord.second 
                 << " O:" << ord.dish << endl;
            count++;
        }
        aux = aux->next;
    }

    cout << "\nTotal de registros: " << count << endl;
    cout << "========================================\n" << endl;
}

// ----------------------- FUNCIÓN PRINCIPAL -----------------------

int main() {
    List<Order> ordenes;

    // 1. LECTURA DEL ARCHIVO - Complejidad: O(n)
    string filename = "orders.txt";

    cout << "Intentando abrir: " << filename << endl;
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "No se encontró orders.txt en el directorio actual." << endl;
        cout << "Ingrese la ruta completa del archivo (o presione Enter para salir): ";
        getline(cin, filename);

        if (filename.empty()) {
            cout << "Programa cancelado." << endl;
            return 1;
        }

        file.open(filename.c_str());

        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo: " << filename << endl;
            return 1;
        }
    }

    string line;

    while (getline(file, line)) {
        Order order;
        istringstream iss(line);

        string timeStr;

        iss >> order.month >> order.day >> timeStr;

        // Parsear hora:minuto:segundo
        sscanf(timeStr.c_str(), "%d:%d:%d", &order.hour, &order.minute, &order.second);

        // Obtener resto de la línea
        string resto;
        getline(iss, resto);

        // Encontrar R: y O:
        size_t rPos = resto.find("R:");
        size_t oPos = resto.find("O:");

        if (rPos != string::npos && oPos != string::npos) {
            order.restaurant = resto.substr(rPos + 2, oPos - rPos - 3);
            order.dish = resto.substr(oPos + 2);

            // Limpiar espacios
            order.restaurant.erase(0, order.restaurant.find_first_not_of(" "));
            order.restaurant.erase(order.restaurant.find_last_not_of(" ") + 1);
        }

        order.monthNum = monthToNumber(order.month);
        ordenes.insertLast(order);
    }

    file.close();

    // 2. ORDENAMIENTO - Complejidad: O(n log n)
    quicksort(ordenes);

    // 3. BÚSQUEDA POR RESTAURANTE
    string restaurantName;
    cout << "\nIngrese el nombre del restaurante a buscar: ";
    getline(cin, restaurantName);

    searchByRestaurant(ordenes, restaurantName);

    // 4. GUARDAR RESULTADO ORDENADO - Complejidad: O(n)
    ordenes.saveToFile("ordenes_ordenadas.txt");

    cout << "\nPrograma finalizado exitosamente." << endl;

    return 0;
}