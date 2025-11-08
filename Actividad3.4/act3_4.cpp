#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

//Nodo de Arbol, este servira para los 3 arboles
class NodeTree {
public:
    string nombre;
    int numOrdenes;
    double ventasTotal;
    NodeTree *left, *right, *up;

    NodeTree(string n, int ord = 0, double ventas = 0.0) {
        nombre = n;
        numOrdenes = ord;
        ventasTotal = ventas;
        left = NULL;
        right = NULL;
        up = NULL;
    }
};

//BST 1: Ordenado por nombre, servira para acumular datos
class BST_Nombre {
public:
    NodeTree *root;

    BST_Nombre() {
        root = NULL;
    }
    

    //Busqueda del restaurante por nombre
    //Complejidad O(1)
    NodeTree* search(string nombre) {
        NodeTree* aux = this->root;
        while (aux != NULL) {
            if (nombre < aux->nombre) aux = aux->left;
            else if (nombre > aux->nombre) aux = aux->right;
            else return aux;
        }
        return NULL;
    }

    //Inserta restaurante
    //Complejidad O(1)
    void insert(string nombre, double monto) {
        if (root == NULL) {
            root = new NodeTree(nombre, 1, monto);
            return;
        }

        NodeTree* aux = root;
        NodeTree* parent = NULL;
        while (aux != NULL) {
            parent = aux;
            if (nombre == aux->nombre) {
                aux->numOrdenes++;
                aux->ventasTotal += monto;
                return; 
            }
            if (nombre < aux->nombre) aux = aux->left;
            else aux = aux->right;
        }

        //crear y enlazar
        NodeTree* nuevo = new NodeTree(nombre, 1, monto);
        if (nombre < parent->nombre) parent->left = nuevo;
        else parent->right = nuevo;
        nuevo->up = parent;
    }

    //Recorre el arbol (inorder) para enviar nodos ya ordenados por nombre
    //Complejidad O(n)
    void inorder(NodeTree* nodo, NodeTree** arreglo, int& idx) {
        if (nodo == NULL) return;
        inorder(nodo->left, arreglo, idx);
        arreglo[idx++] = nodo;
        inorder(nodo->right, arreglo, idx);
    }
};

//BST 2: Ordenado por numeros de ordenes, de manera descendente
class BST_Ordenes {
public:
    NodeTree *root;
    BST_Ordenes() {
        root = NULL;
    }

    //Inserta un nodo en el arbol ordenado por el numero de ordenes
    //Complejidad O(n)
    void insert(string nombre, int ordenes, double ventas) {
        NodeTree* nuevo = new NodeTree(nombre, ordenes, ventas);

        if (root == NULL) {
            root = nuevo;
            return;
        }

        NodeTree* aux = root;
        while (aux != NULL) {
            if (ordenes > aux->numOrdenes ||
               (ordenes == aux->numOrdenes && nombre < aux->nombre)) {
                if (aux->left == NULL) {
                    aux->left = nuevo;
                    nuevo->up = aux;
                    return;
                }
                aux = aux->left;
            }
            else {
                if (aux->right == NULL) {
                    aux->right = nuevo;
                    nuevo->up = aux;
                    return;
                }
                aux = aux->right;
            }
        }
    }

    //Muestra los primero 10 nodos del arbol
    //Complejidad O(1)
    void topK(NodeTree* nodo, int& count) {
        if (nodo == NULL || count >= 10) return;
        topK(nodo->left, count);
        if (count < 10) {
            cout << count + 1 << ". " << nodo->nombre
                 << " - Ordenes: " << nodo->numOrdenes
                 << " - Ventas: $" << nodo->ventasTotal << endl;
            count++;
        }
        topK(nodo->right, count);
    }

    //Guarda todos los valors del arbol en el archivo
    //Complejidad O(n)
    void toFile(NodeTree* nodo, ofstream& out) {
        if (nodo == NULL) return;
        toFile(nodo->left, out);
        out << nodo->nombre << " " << nodo->numOrdenes << " " << nodo->ventasTotal << endl;
        toFile(nodo->right, out);
    }
};

//BST 2: Ordenado por ventas totales, de manera descendente
class BST_Ventas {
public:
    NodeTree *root;
    BST_Ventas() {
        root = NULL;
    }

    //Inserta basado en ventas totales
    //Complejidad O(n)
    void insert(string nombre, int ordenes, double ventas) {
        NodeTree* nuevo = new NodeTree(nombre, ordenes, ventas);

        if (root == NULL) {
            root = nuevo;
            return;
        }

        NodeTree* aux = root;
        while (aux != NULL) {
            if (ventas > aux->ventasTotal ||
               (ventas == aux->ventasTotal && nombre < aux->nombre)) {
                if (aux->left == NULL) {
                    aux->left = nuevo;
                    nuevo->up = aux;
                    return;
                }
                aux = aux->left;
            }
            else {
                if (aux->right == NULL) {
                    aux->right = nuevo;
                    nuevo->up = aux;
                    return;
                }
                aux = aux->right;
            }
        }
    }

    //Top 10 ventas
    //Complejidad O(n)
    void topK(NodeTree* nodo, int& count) {
        if (nodo == NULL || count >= 10) return;
        topK(nodo->left, count);
        if (count < 10) {
            cout << count + 1 << ". " << nodo->nombre
                 << " - Ventas: $" << nodo->ventasTotal
                 << " - Ordenes: " << nodo->numOrdenes << endl;
            count++;
        }
        topK(nodo->right, count);
    }

    //Recorrido para guardar archivo completo
    //Complejidad O(n)
    void toFile(NodeTree* nodo, ofstream& out) {
        if (nodo == NULL) return;
        toFile(nodo->left, out);
        out << nodo->nombre << " " << nodo->numOrdenes << " " << nodo->ventasTotal << endl;
        toFile(nodo->right, out);
    }
};

//Funciones para parsear el archivo
//Complejidad O(1)
string extraerRestaurante(string linea) {
    size_t pos1 = linea.find("R:");
    size_t pos2 = linea.find(" O:");
    if (pos1 != string::npos && pos2 != string::npos)
        return linea.substr(pos1 + 2, pos2 - pos1 - 2);
    return "";
}

double extraerPrecio(string linea) {
    size_t pos1 = linea.find("(");
    size_t pos2 = linea.find(")");

    if (pos1 != string::npos && pos2 != string::npos) {
        string precio = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        return atof(precio.c_str());
    }
    return 0.0;
}

//Carga de archivo
//Complejidad O(n)
void leerArchivo(BST_Nombre* arbol) {
    ifstream archivo("orders.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir ordenes.txt" << endl;
        return;
    }

    string linea;
    int total = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        string restaurante = extraerRestaurante(linea);
        double precio = extraerPrecio(linea);

        if (!restaurante.empty() && precio > 0) {
            arbol->insert(restaurante, precio);
            total++;
        }
    }

    archivo.close();
    cout << "Total ordenes procesadas: " << total << endl;
}

//Main
int main() {
    BST_Nombre* arbol1 = new BST_Nombre();
    leerArchivo(arbol1);

    NodeTree* arreglo[5000];
    int idx = 0;
    arbol1->inorder(arbol1->root, arreglo, idx);

    BST_Ordenes* arbol2 = new BST_Ordenes();
    BST_Ventas* arbol3 = new BST_Ventas();

    for (int i = 0; i < idx; i++) {
        arbol2->insert(arreglo[i]->nombre, arreglo[i]->numOrdenes, arreglo[i]->ventasTotal);
        arbol3->insert(arreglo[i]->nombre, arreglo[i]->numOrdenes, arreglo[i]->ventasTotal);
    }

    cout << "\nTop 10 por numero de ordenes:\n";
    int count = 0;
    arbol2->topK(arbol2->root, count);

    cout << "\nTop 10 por ventas:\n";
    count = 0;
    arbol3->topK(arbol3->root, count);

    ofstream archivo1("restaurantes_por_ordenes.txt");
    arbol2->toFile(arbol2->root, archivo1);
    archivo1.close();

    ofstream archivo2("restaurantes_por_ventas.txt");
    arbol3->toFile(arbol3->root, archivo2);
    archivo2.close();

    return 0;
}
