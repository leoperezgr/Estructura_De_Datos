#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdio>
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

int mesAInt(const string& mon){
    string m = mon; for(char& c: m) c = tolower((unsigned char)c);
    if(m=="ene") return 1; if(m=="feb") return 2; if(m=="mar") return 3;
    if(m=="abr") return 4; if(m=="may") return 5; if(m=="jun") return 6;
    if(m=="jul") return 7; if(m=="ago") return 8; if(m=="sep") return 9;
    if(m=="oct") return 10; if(m=="nov") return 11; if(m=="dic") return 12;
    return 0;
}
\
string normalizeFecha(const string& s) {
    size_t a = s.find_first_not_of(' ');
    if (a == string::npos) {
        return "";
    }
    size_t b = s.find_last_not_of(' ');
    string t = s.substr(a, b - a + 1);

    size_t p1 = t.find(' ');
    if (p1 == string::npos) {
        return "";
    }
    string mes = t.substr(0, p1);

    size_t p2 = t.find(' ', p1 + 1);
    if (p2 == string::npos) {
        return "";
    }
    int d = stoi(t.substr(p1 + 1, p2 - (p1 + 1)));

    string hms = t.substr(p2 + 1);
    size_t c1 = hms.find(':');
    if (c1 == string::npos) {
        return "";
    }
    size_t c2 = hms.find(':', c1 + 1);
    if (c2 == string::npos) {
        return "";
    }
    int h = stoi(hms.substr(0, c1));
    int m = stoi(hms.substr(c1 + 1, c2 - (c1 + 1)));
    int s2 = stoi(hms.substr(c2 + 1));

    for (char &c : mes) {
        c = tolower((unsigned char)c);
    }
    if (mes == "ene") {
        mes = "Ene";
    } else if (mes == "feb") {
        mes = "Feb";
    } else if (mes == "mar") {
        mes = "Mar";
    } else if (mes == "abr") {
        mes = "Abr";
    } else if (mes == "may") {
        mes = "May";
    } else if (mes == "jun") {
        mes = "Jun";
    } else if (mes == "jul") {
        mes = "Jul";
    } else if (mes == "ago") {
        mes = "Ago";
    } else if (mes == "sep") {
        mes = "Sep";
    } else if (mes == "oct") {
        mes = "Oct";
    } else if (mes == "nov") {
        mes = "Nov";
    } else if (mes == "dic") {
        mes = "Dic";
    } else {
        return "";
    }

    char buf[20];
    snprintf(buf, sizeof(buf), "%s %02d %02d:%02d:%02d", mes.c_str(), d, h, m, s2);
    return string(buf);
}

bool fechaMenorIgual(const string& A, const string& B) {
    if (A.size() < 3 || B.size() < 3) { return A <= B; }
    int Ma = mesAInt(A.substr(0, 3)), Mb = mesAInt(B.substr(0, 3));
    if (Ma != Mb) { return Ma < Mb; }
    int Da = stoi(A.substr(4, 2)), Db = stoi(B.substr(4, 2));
    if (Da != Db) { return Da < Db; }
    int Ha = stoi(A.substr(7, 2)), Hb = stoi(B.substr(7, 2));
    if (Ha != Hb) { return Ha < Hb; }
    int Mia = stoi(A.substr(10, 2)), Mib = stoi(B.substr(10, 2));
    if (Mia != Mib) { return Mia < Mib; }
    int Sa = stoi(A.substr(13, 2)), Sb = stoi(B.substr(13, 2));
    return Sa <= Sb;
}

bool fechaMenor(const string& A, const string& B) {
    if (A.size() < 3 || B.size() < 3) { return A < B; }
    int Ma = mesAInt(A.substr(0, 3)), Mb = mesAInt(B.substr(0, 3));
    if (Ma != Mb) { return Ma < Mb; }
    int Da = stoi(A.substr(4, 2)), Db = stoi(B.substr(4, 2));
    if (Da != Db) { return Da < Db; }
    int Ha = stoi(A.substr(7, 2)), Hb = stoi(B.substr(7, 2));
    if (Ha != Hb) { return Ha < Hb; }
    int Mia = stoi(A.substr(10, 2)), Mib = stoi(B.substr(10, 2));
    if (Mia != Mib) { return Mia < Mib; }
    int Sa = stoi(A.substr(13, 2)), Sb = stoi(B.substr(13, 2));
    return Sa < Sb;
}

//Busqueda Binaria 

//Busca la primera posicion donde el valor de la fecha es mayor o igual
int limiteInferiorFecha(Orden arr[], int n, const string& clave) {
    int izquierda = 0, derecha = n;
    while (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (fechaMenor(arr[medio].fecha, clave)) { izquierda = medio + 1; }
        else { derecha = medio; }
    }
    return izquierda;
}

//Busca la primera posicion donde el valor de la fecha es mayor o igual
int limiteSuperiorFecha(Orden arr[], int n, const string& clave) {
    int izquierda = 0, derecha = n;
    while (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        if (!fechaMenor(clave, arr[medio].fecha)) { izquierda = medio + 1; }
        else { derecha = medio; }
    }
    return izquierda;
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
        if (fechaMenorIgual(L[i].fecha, R[j].fecha))
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


//Main
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
        o.fecha = normalizeFecha(trim(linea.substr(0, linea.find("R:"))));
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

    // Solicitar rango de fechas al usuario
    string fechaInicio, fechaFin;
    cout << "\nIngresa fecha de inicio (Ej: Jan 01 00:00:00): ";
    getline(cin, fechaInicio);
    fechaInicio = normalizeFecha(trim(fechaInicio));
    cout << "Ingresa fecha de fin   (Ej: Dec 31 23:59:59): ";
    getline(cin, fechaFin);
    fechaFin    = normalizeFecha(trim(fechaFin));

    // Mostrar resultados
    int lo = limiteInferiorFecha(ordenes, count, fechaInicio);
    int hi = limiteSuperiorFecha(ordenes, count, fechaFin);

    bool encontrado = false;
    for(int i=lo; i<hi; ++i)
    {
        encontrado = true;
        cout << ordenes[i].fecha << " | "
             << ordenes[i].restaurante << " | "
             << ordenes[i].platillo << " | $"
             << ordenes[i].precio << endl;
    }

    if (!encontrado) {
        cout << "No se encontraron registros en ese rango de fechas." << endl;
    } else {
        // Preguntar si se quiere guardar
        char opcion;
        cout << "\n¿Desea guardar los resultados en un archivo? (s/n): ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') 
        {
            ofstream busqArchivo("resultado_busqueda.txt");
            for (int i=lo; i<hi; ++i) 
            {
                busqArchivo << ordenes[i].fecha << " | "
                            << ordenes[i].restaurante << " | "
                            << ordenes[i].platillo << " | $"
                            << ordenes[i].precio << endl;
            }
            busqArchivo.close();
            cout << "Resultados guardados en resultado_busqueda.txt\n";
        }
    }

    delete[] ordenes;
    return 0;
}