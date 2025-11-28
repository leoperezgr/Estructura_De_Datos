#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <math.h>
#include <limits.h>

using namespace std;

char restaurantes[200][120];
char platos[4000][120];
int preciosMenu[200][4000];
int ordenPlatos[200][200];
int numPlatosResta[200];

int numR = 0;
int numP = 0;

double city[900][900];
int restaX[200];
int restaY[200];


//acepta cualquier entrada en las salida de busquedas
//Complejidad O(n)
void toLowerCase(char *s) {
    for (int i = 0; s[i]; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + 32;
        }
    }
}

// busca un restaurante por nombre
//Complejidad O(n)
int findRestaurante(const char* name) {
    char temp1[120], temp2[120];
    strcpy(temp1, name);
    toLowerCase(temp1);

    for (int i = 0; i < numR; i++) {
        strcpy(temp2, restaurantes[i]);
        toLowerCase(temp2);

        if (strcmp(temp1, temp2) == 0) return i;
    }
    return -1;
}


//busca un plato por nombre
//Complejidad O(n)
int findPlato(const char* name) {
    char temp1[120], temp2[120];
    strcpy(temp1, name);
    toLowerCase(temp1);

    for (int i = 0; i < numP; i++) {
        strcpy(temp2, platos[i]);
        toLowerCase(temp2);

        if (strcmp(temp1, temp2) == 0) return i;
    }
    return -1;
}


//carga todos los restaurantes, platos y precios desde el archivo
//Complejidad O(n^2)
void cargarMenu(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir menuFile.txt\n";
        return;
    }

    int d1, d2, d3;
    file >> d1 >> d2 >> d3;
    file.ignore();

    memset(preciosMenu, 0, sizeof(preciosMenu));
    memset(numPlatosResta, 0, sizeof(numPlatosResta));

    char linea[300];
    while (file.getline(linea, 300)) {
        if (strlen(linea) < 5) continue;

        char *R = strstr(linea, "R:");
        char *O = strstr(linea, "O:");
        if (!R || !O) continue;

        R += 2;

        char nombreR[120];
        int lenR = O - R - 1;
        strncpy(nombreR, R, lenR);
        nombreR[lenR] = '\0';

        O += 2;

        char *paren = strstr(O, "(");
        char nombreP[120];
        int lenP = paren - O;
        strncpy(nombreP, O, lenP);
        nombreP[lenP] = '\0';

        int precio = 0;
        sscanf(paren, "(%d)", &precio);

        int idR = findRestaurante(nombreR);
        if (idR == -1) {
            strcpy(restaurantes[numR], nombreR);
            idR = numR++;
        }

        int idP = findPlato(nombreP);
        if (idP == -1) {
            strcpy(platos[numP], nombreP);
            idP = numP++;
        }

        preciosMenu[idR][idP] = precio;
        ordenPlatos[idR][numPlatosResta[idR]] = idP;
        numPlatosResta[idR]++;
    }

    file.close();
}

//imprime todos los platos que ofrece un restaurante
//Complejidad O(n)
void menuDeRestaurante(const char* name) {
    int id = findRestaurante(name);
    if (id == -1) {
        cout << "No existe el restaurante.\n";
        return;
    }

    cout << "\nMenu de " << name << ":\n";

    for (int i = 0; i < numPlatosResta[id]; i++) {
        int idP = ordenPlatos[id][i];
        cout << " - " << platos[idP] << " $" << preciosMenu[id][idP] << "\n";
    }
}

//imprime todos los restaurantes que venden un plato
//Complejidad O(n)
void restaurantesConPlato(const char* name) {
    int id = findPlato(name);
    if (id == -1) {
        cout << "El plato no existe.\n";
        return;
    }

    cout << "\nRestaurantes que venden " << name << ":\n";
    for (int r = 0; r < numR; r++) {
        if (preciosMenu[r][id] > 0) {
            cout << " - " << restaurantes[r] << " $" << preciosMenu[r][id] << "\n";
        }
    }
}

//carga la matriz de adyacencia de la ciudad
//Complejidad O(n^2)
void cargarCity(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir city30x30.txt\n";
        return;
    }

    for (int i = 0; i < 900; i++)
        for (int j = 0; j < 900; j++)
            city[i][j] = 1e9;

    char linea[200];
    while (file.getline(linea, 200)) {
        int x1, y1, x2, y2;
        double w;
        
        if (sscanf(linea, "(%d, %d) (%d, %d) %lf", &x1, &y1, &x2, &y2, &w) == 5) {
            int u = x1 * 30 + y1;
            int v = x2 * 30 + y2;
            city[u][v] = w;
            city[v][u] = w;
        }
    }

    file.close();
}

//carga el nombre y ubicacion de cada restaurante
//Complejidad O(n)
void cargarRestaPlaces(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir restaPlaces.txt\n";
        return;
    }

    char linea[200];
    while (file.getline(linea, 200)) {
        if (strlen(linea) < 3) continue;

        char nombre[120];
        int x, y;

        char *paren = strstr(linea, "(");
        int len = paren - linea;

        strncpy(nombre, linea, len);
        nombre[len - 1] = '\0';

        sscanf(paren, "(%d, %d)", &x, &y);

        strcpy(restaurantes[numR], nombre);
        restaX[numR] = x;
        restaY[numR] = y;
        numR++;
    }

    file.close();
}

//calcula las distancias minimas desde un nodo usando dijkstra
//Complejidad O(n^2)
void dijkstra(int src, double dist[], int parent[]) {
    int visited[900];

    for (int i = 0; i < 900; i++) {
        dist[i] = 1e9;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int c = 0; c < 900 - 1; c++) {
        int u = -1;
        double best = 1e9;

        for (int i = 0; i < 900; i++) {
            if (!visited[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < 900; v++) {
            if (city[u][v] < 1e9) {
                if (dist[u] + city[u][v] < dist[v]) {
                    dist[v] = dist[u] + city[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

//imprime el camino completo desde el origen al destino
//Complejidad O(n)
void imprimirRuta(int dest, int parent[]) {
    int path[1000];
    int len = 0;

    int cur = dest;
    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    cout << "Numero de aristas: " << (len - 1) << "\n";

    cout << "Ruta: ";
    for (int i = len - 1; i >= 0; i--) {
        int x = path[i] / 30;
        int y = path[i] % 30;
        cout << "(" << x << "," << y << ") ";
    }
    cout << "\n";
}

//procesa todas las ordenes y calcula sus rutas
//Complejidad O(n^2)
void procesarOrdenes(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir orders30x30.txt\n";
        return;
    }

    char linea[300];

    while (file.getline(linea, 300)) {
        if (strlen(linea) < 5) continue;

        char nombreR[120], nombreP[120];
        int precio, dx, dy;

        char *R = strstr(linea, "R:") + 2;
        char *O = strstr(linea, "O:");
        int lenR = O - R - 1;
        strncpy(nombreR, R, lenR);
        nombreR[lenR] = '\0';

        O += 2;
        char *parenP = strstr(O, "(");
        int lenP = parenP - O;
        strncpy(nombreP, O, lenP);
        nombreP[lenP] = '\0';

        sscanf(parenP, "(%d)", &precio);

        char *destStr = strrchr(linea, '(');
        sscanf(destStr, "(%d, %d)", &dx, &dy);

        int idR = findRestaurante(nombreR);

        if (idR == -1) {
            cout << "Restaurante no encontrado: " << nombreR << "\n";
            continue;
        }

        int origen = restaX[idR] * 30 + restaY[idR];
        int destino = dx * 30 + dy;

        double dist[900];
        int parent[900];

        dijkstra(origen, dist, parent);

        cout << "\nOrden: " << nombreR << " -> (" << dx << "," << dy << ")\n";
        cout << "Platillo: " << nombreP << "\n";
        cout << "Precio: $" << precio << "\n";
        cout << "Distancia total: " << dist[destino] << "\n";

        imprimirRuta(destino, parent);
    }

    file.close();
}

// muestra el menu de opciones al usuario
//Complejidad O(n)
void mostrarMenu() {
    cout << "\nSISTEMA DE DELIVERY\n\n";
    cout << "1. Buscar menu de restaurante\n";
    cout << "2. Buscar platillo\n";
    cout << "3. Salir\n\n";
    cout << "Seleccione una opcion: ";
}

// ejecuta el programa principal
//Complejidad O(n^2)
int main() {
    cargarRestaPlaces("restaPlaces.txt");
    cargarMenu("menuFile.txt");
    cargarCity("city30x30.txt");

    procesarOrdenes("orders30x30.txt");

    int opcion = 0;
    char nombre[120];

    while (opcion != 3) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "\nRestaurantes disponibles:\n";
                for (int i = 0; i < numR; i++) {
                    cout << " - " << restaurantes[i] << "\n";
                }
                cout << "\nIngrese el nombre del restaurante: ";
                cin.getline(nombre, 120);
                toLowerCase(nombre);
                menuDeRestaurante(nombre);
                break;

            case 2:
                cout << "\nIngrese el nombre del platillo: ";
                cin.getline(nombre, 120);
                restaurantesConPlato(nombre);
                toLowerCase(nombre);
                break;

            case 3:
                cout << "\nRegrese pronto!\n";
                break;

            default:
                cout << "\nOpcion no valida. Intente de nuevo.\n";
                break;
        }
    }

    return 0;
}
