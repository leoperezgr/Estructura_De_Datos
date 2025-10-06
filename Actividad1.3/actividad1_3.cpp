#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Orden {
    string fecha;
    string restaurante;
    string platillo;
    int precio;
};

// Función para recortar espacios
string trim(const string &s) {
    size_t start = s.find_first_not_of(" ");
    size_t end = s.find_last_not_of(" ");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Merge Sort por fecha
void merge(Orden arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Orden* L = new Orden[n1];
    Orden* R = new Orden[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].fecha <= R[j].fecha)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(Orden arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Búsqueda binaria exacta por fecha
int busquedaBinaria(Orden arr[], int n, const string& clave) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m].fecha == clave) return m;     // encontrado
        if (arr[m].fecha < clave) l = m + 1;     // buscar derecha
        else r = m - 1;                          // buscar izquierda
    }
    return -1; // no encontrado
}

int main() {
    ifstream archivo("orders.txt");  // archivo local
    if (!archivo) {
        cout << "No se pudo abrir el archivo: orders.txt" << endl;
        return 1;
    }

    // Contar órdenes
    int count = 0;
    string linea;
    while (getline(archivo, linea)) count++;
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Arreglo dinámico
    Orden* ordenes = new Orden[count];
    int idx = 0;

    while (getline(archivo, linea)) {
        Orden o;
        o.fecha = trim(linea.substr(0, 15));
        size_t posR = linea.find("R:");
        size_t posO = linea.find("O:");
        size_t posP = linea.find_last_of("(");
        o.restaurante = trim(linea.substr(posR + 2, posO - (posR + 2)));
        o.platillo    = trim(linea.substr(posO + 2, posP - (posO + 2)));
        o.precio      = stoi(linea.substr(posP + 1, linea.find(")") - posP - 1));
        ordenes[idx++] = o;
    }
    archivo.close();

    // Ordenar por fecha
    mergeSort(ordenes, 0, count - 1);

    // Mostrar primeras 10
    cout << "Primeros 10 registros ordenados por fecha:\n";
    for (int i = 0; i < 10 && i < count; i++) {
        cout << ordenes[i].fecha << " | "
             << ordenes[i].restaurante << " | "
             << ordenes[i].platillo << " | $"
             << ordenes[i].precio << endl;
    }

    // Guardar bitácora completa ordenada
    ofstream outArchivo("bitacora_ordenada.txt");
    for (int i = 0; i < count; i++) {
        outArchivo << ordenes[i].fecha << " | "
                   << ordenes[i].restaurante << " | "
                   << ordenes[i].platillo << " | $"
                   << ordenes[i].precio << endl;
    }
    outArchivo.close();

    // Búsqueda binaria exacta
    string clave;
    cout << "\nIngresa una fecha exacta para buscar (Ej: Jan 01 00:00:00): ";
    getline(cin, clave);

    int pos = busquedaBinaria(ordenes, count, clave);
    if (pos != -1) {
        cout << "Encontrado: " << ordenes[pos].fecha << " | "
             << ordenes[pos].restaurante << " | "
             << ordenes[pos].platillo << " | $"
             << ordenes[pos].precio << endl;

        // Preguntar si desea guardar
        char opcion;
        cout << "\n¿Desea guardar el resultado en un archivo? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            ofstream busqArchivo("resultado_busqueda.txt");
            busqArchivo << ordenes[pos].fecha << " | "
                        << ordenes[pos].restaurante << " | "
                        << ordenes[pos].platillo << " | $"
                        << ordenes[pos].precio << endl;
            busqArchivo.close();
            cout << "Resultado guardado en resultado_busqueda.txt\n";
        }
    } else {
        cout << "No se encontró esa fecha exacta.\n";
    }

    delete[] ordenes;
    return 0;
}