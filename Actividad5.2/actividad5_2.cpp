#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <cctype>

using namespace std;

//IMPLEMENTACION DE HASH TABLE
template <class T> class Element {
public:
    string str_key;
    int int_key;
    int h_key;
    T item;
    bool free;

    Element<T>() {
        str_key = "";
        int_key = -1;
        h_key = -1;
        item = T();
        free = true;
    }
};

template <class T> class Hash {
public:
    int maxSize;
    int currentSize;
    int i;
    Element<T> **table;

    Hash(int size) {
        int j;
        maxSize = size;
        currentSize = 0;
        i = 0;
        table = new Element<T> *[maxSize];

        for (j = 0; j < maxSize; j++) {
            table[j] = new Element<T>();
        }
    }

    ~Hash() {
        for (int j = 0; j < maxSize; j++) {
            delete table[j];
        }
        delete[] table;
    }

    void show();
    void insert(string, T);
    void remove(string);
    void update(string, T);
    T find(string);
    bool exists(string);
};

//helper para mayusculas y minisculas
string toLowerStr(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = tolower((unsigned char)s[i]);
    }
    return s;
}

//helper para quitar espacios al inicio y al final
string trimStr(string s) {
    size_t start = s.find_first_not_of(' ');
    size_t end   = s.find_last_not_of(' ');
    if (start == string::npos) {
        return "";
    }
    return s.substr(start, end - start + 1);
}

//Complejidad: O(n) 
//Muestra el contenido de la tabla hash
template <class T> 
void Hash<T>::show() {
    int j;
    for (j = 0; j < maxSize; j++) {
        cout << j << " " << table[j]->str_key << " " << table[j]->int_key << " " 
             << table[j]->h_key << " " << table[j]->item << endl;
    }
    cout << "\n";
}

//Complejidad O(n) 
//Inserta una llave y su valor en la tabla hash
template <class T>
void Hash<T>::insert(string str_key, T value) {
    int key;
    int h_key;
    int flag;

    if (currentSize == maxSize) {
        cout << "Tabla llena\n";
    } else {
        key = int(str_key[0]);
        i = 0;
        flag = 0;

        while (flag == 0 && i < maxSize) {
            h_key = (key + i) % maxSize;
            if (table[h_key]->free == true) {
                table[h_key]->str_key = str_key;
                table[h_key]->int_key = key;
                table[h_key]->h_key = h_key;
                table[h_key]->item = value;
                table[h_key]->free = false;
                flag = 1;
                currentSize++;
            } else {
                i++;
            }
        }
    }
}

//Complejidad O(n) 
//Busca el valor asociado a una llave en la tabla hash
template <class T>
T Hash<T>::find(string str_key) {
    int key = int(str_key[0]);
    int h_key;
    i = 0;
    int intentos = 0;

    while (intentos < maxSize) {
        h_key = (key + i) % maxSize;
        if (!table[h_key]->free && table[h_key]->str_key == str_key) {
            return table[h_key]->item;
        } else if (table[h_key]->free && table[h_key]->str_key == "") {
            T empty = T();
            return empty;
        } else {
            i++;
        }
        intentos++;
    }

    T empty = T();
    return empty;
}

//Complejidad O(n)
//Verifica si una llave existe en la tabla hash
template <class T>
bool Hash<T>::exists(string str_key) {
    int key = int(str_key[0]);
    int h_key;
    i = 0;
    int intentos = 0;

    while (intentos < maxSize) {
        h_key = (key + i) % maxSize;
        if (!table[h_key]->free && table[h_key]->str_key == str_key) {
            return true;
        } else if (table[h_key]->free && table[h_key]->str_key == "") {
            return false;
        }
        i++;
        intentos++;
    }
    return false;
}

//Complejidad O(n)
//Elimina una llave de la tabla hash (no implementado)
template <class T>
void Hash<T>::remove(string str_key) {
}

//Complejidad O(n)
//Actualiza el valor asociado a una llave (no implementado)
template <class T>
void Hash<T>::update(string str_key, T value) {
}


//ESTRUCTURAS PARA ALMACENAR DATOS
struct PlatoInfo {
    char nombre[120];
    int precio;

    PlatoInfo() {
        strcpy(nombre, "");
        precio = 0;
    }

    PlatoInfo(const char* n, int p) {
        strcpy(nombre, n);
        precio = p;
    }
};

struct MenuRestaurante {
    PlatoInfo* platos;
    int numPlatos;
    int capacidad;

    MenuRestaurante() {
        capacidad = 50;
        platos = new PlatoInfo[capacidad];
        numPlatos = 0;
    }

    ~MenuRestaurante() {
        delete[] platos;
    }

    void agregar(const char* nombrePlato, int precio) {
        if (numPlatos >= capacidad) {
            capacidad *= 2;
            PlatoInfo* nuevo = new PlatoInfo[capacidad];
            for (int i = 0; i < numPlatos; i++) {
                nuevo[i] = platos[i];
            }
            delete[] platos;
            platos = nuevo;
        }
        strcpy(platos[numPlatos].nombre, nombrePlato);
        platos[numPlatos].precio = precio;
        numPlatos++;
    }
};

struct RestauranteConPrecio {
    char nombre[120];
    int precio;
};

struct ListaRestaurantes {
    RestauranteConPrecio* restaurantes;
    int numResta;
    int capacidad;

    ListaRestaurantes() {
        capacidad = 50;
        restaurantes = new RestauranteConPrecio[capacidad];
        numResta = 0;
    }

    ~ListaRestaurantes() {
        delete[] restaurantes;
    }

    void agregar(const char* nombreResta, int precio) {
        if (numResta >= capacidad) {
            capacidad *= 2;
            RestauranteConPrecio* nuevo = new RestauranteConPrecio[capacidad];
            for (int i = 0; i < numResta; i++) {
                nuevo[i] = restaurantes[i];
            }
            delete[] restaurantes;
            restaurantes = nuevo;
        }
        strcpy(restaurantes[numResta].nombre, nombreResta);
        restaurantes[numResta].precio = precio;
        numResta++;
    }

    void ordenar() {
        for (int i = 0; i < numResta - 1; i++) {
            for (int j = 0; j < numResta - i - 1; j++) {
                if (restaurantes[j].precio > restaurantes[j + 1].precio) {
                    RestauranteConPrecio temp = restaurantes[j];
                    restaurantes[j] = restaurantes[j + 1];
                    restaurantes[j + 1] = temp;
                }
            }
        }
    }
};

struct Ubicacion {
    int x, y;

    Ubicacion() : x(0), y(0) {}
    Ubicacion(int _x, int _y) : x(_x), y(_y) {}

    double distanciaA(int destX, int destY) {
        return sqrt(pow(x - destX, 2) + pow(y - destY, 2));
    }
};

struct RestauranteCercano {
    char nombre[120];
    double distancia;
    Ubicacion ubicacion;
};

//TABLAS HASH GLOBALES
Hash<MenuRestaurante*>* hashMenus = new Hash<MenuRestaurante*>(500);
Hash<ListaRestaurantes*>* hashPlatos = new Hash<ListaRestaurantes*>(5000);
Hash<Ubicacion*>* hashUbicaciones = new Hash<Ubicacion*>(500);

char todosRestaurantes[200][120];
int numTotalRestaurantes = 0;

//GRAFO DE LA CIUDAD
double city[900][900];

//CARGAR MENU
//Complejidad: O(n)
//Carga la informacion de restaurantes y platos desde el archivo de menu
void cargarMenu(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir menu.txt\n";
        return;
    }

    int d1, d2, d3;
    file >> d1 >> d2 >> d3;
    file.ignore();

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

        // normalizar nombre de restaurante
        string cleanR = trimStr(string(nombreR));
        strncpy(nombreR, cleanR.c_str(), sizeof(nombreR));
        nombreR[sizeof(nombreR) - 1] = '\0';

        O += 2;

        char *paren = strstr(O, "(");
        if (!paren) continue;

        char nombreP[120];
        int lenP = paren - O;
        strncpy(nombreP, O, lenP);
        nombreP[lenP] = '\0';

        // normalizar nombre de plato
        string cleanP = trimStr(string(nombreP));
        strncpy(nombreP, cleanP.c_str(), sizeof(nombreP));
        nombreP[sizeof(nombreP) - 1] = '\0';

        int precio = 0;
        sscanf(paren, "(%d)", &precio);

        string keyR(nombreR);
        keyR = trimStr(keyR);
        keyR = toLowerStr(keyR);
        MenuRestaurante* menu = hashMenus->find(keyR);
        if (menu == NULL || !hashMenus->exists(keyR)) {
            menu = new MenuRestaurante();
            hashMenus->insert(keyR, menu);
        }
        menu->agregar(nombreP, precio);

        string keyP(nombreP);
        keyP = trimStr(keyP);
        keyP = toLowerStr(keyP);
        ListaRestaurantes* lista = hashPlatos->find(keyP);
        if (lista == NULL || !hashPlatos->exists(keyP)) {
            lista = new ListaRestaurantes();
            hashPlatos->insert(keyP, lista);
        }
        lista->agregar(nombreR, precio);
    }

    file.close();
}

//CONSULTAS DEL MENU
//Complejidad O(n) 
//Muestra el menu de un restaurante
void menuDeRestaurante(const char* name) {
    string key(name);
    key = trimStr(key);
    key = toLowerStr(key);

    if (!hashMenus->exists(key)) {
        cout << "No existe el restaurante.\n";
        return;
    }

    MenuRestaurante* menu = hashMenus->find(key);

    cout << "\n\tMenu de " << name << "\n";
    for (int i = 0; i < menu->numPlatos; i++) {
        cout << " - " << menu->platos[i].nombre 
             << " $" << menu->platos[i].precio << "\n";
    }
}

//MOSTRAR TODOS LOS RESTAURANTES
//Complejidad O(n log n)
//Imprime todos los restaurantes ordenados alfabeticamente
void mostrarTodosLosRestaurantes() {
    string lista[200];
    for (int i = 0; i < numTotalRestaurantes; i++) {
        lista[i] = todosRestaurantes[i];
    }

    for (int i = 0; i < numTotalRestaurantes - 1; i++) {
        for (int j = 0; j < numTotalRestaurantes - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                string temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    cout << "\n\tLISTA DE RESTAURANTES DISPONIBLES\n";
    for (int i = 0; i < numTotalRestaurantes; i++) {
        cout << " - " << lista[i] << "\n";
    }
    cout << "\n";
}

//Complejidad O(n)
//Muestra restaurantes que venden un plato ordenados por precio
void restaurantesConPlato(const char* name) {
    string key(name);
    key = trimStr(key);
    key = toLowerStr(key);

    if (!hashPlatos->exists(key)) {
        cout << "El plato no existe.\n";
        return;
    }

    ListaRestaurantes* lista = hashPlatos->find(key);
    lista->ordenar();

    cout << "\nRestaurantes que venden " << name << " (ordenados por precio)\n";
    for (int i = 0; i < lista->numResta; i++) {
        cout << " - " << lista->restaurantes[i].nombre 
             << " $" << lista->restaurantes[i].precio << "\n";
    }
}

//MOSTRAR TODOS LOS PLATILLOS
//Complejidad O(n log n)
//Imprime todos los platillos disponibles ordenados alfabeticamente
void mostrarTodosLosPlatillos() {
    string lista[5000];
    int count = 0;

    for (int i = 0; i < hashPlatos->maxSize; i++) {
        if (!hashPlatos->table[i]->free) {
            lista[count++] = hashPlatos->table[i]->str_key;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (lista[j] > lista[j + 1]) {
                string temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    cout << "\n\tLISTA DE PLATILLOS DISPONIBLES\n";
    for (int i = 0; i < count; i++) {
        cout << " - " << lista[i] << "\n";
    }
    cout << "\n";
}

// CARGAR UBICACIONES
// Complejidad: O(n)
//Carga ubicaciones de restaurantes desde el archivo de posiciones
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
        if (!paren) continue;
        int len = paren - linea;
        strncpy(nombre, linea, len);
        nombre[len - 1] = '\0';

        // normalizar nombre de restaurante
        string clean = trimStr(string(nombre));
        strncpy(nombre, clean.c_str(), sizeof(nombre));
        nombre[sizeof(nombre) - 1] = '\0';

        sscanf(paren, "(%d, %d)", &x, &y);

        Ubicacion* ubi = new Ubicacion(x, y);

        string key(nombre);
        key = trimStr(key);
        key = toLowerStr(key);
        hashUbicaciones->insert(key, ubi);
        strcpy(todosRestaurantes[numTotalRestaurantes++], nombre);
    }

    file.close();
}


//CARGAR GRAFO CITY
//Complejidad: O(V^2 + E)
//Carga el grafo de la ciudad en una matriz de adyacencia
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


//DIJKSTRA
//Complejidad: O(V^2)
//Calcula las distancias minimas desde un origen usando Dijkstra con matriz
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

//IMPRIMIR RUTA
//Complejidad O(n)
//Imprime la ruta desde el origen hasta un destino usando el arreglo parent
void imprimirRuta(int dest, int parent[]) {
    int path[1000];
    int len = 0;

    int cur = dest;
    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    cout << "Ruta: ";
    for (int i = len - 1; i >= 0; i--) {
        int x = path[i] / 30;
        int y = path[i] % 30;
        cout << "(" << x << "," << y << ")";
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
}


//ENCONTRAR 3 RESTAURANTES MAS CERCANOS
//Complejidad O(V^2 + E)
//Encuentra los 3 restaurantes mas cercanos al usuario usando Dijkstra y muestra sus menus
void restaurantesCercanos(int userX, int userY) {
    int src = userX * 30 + userY;

    double dist[900];
    int parent[900];

    dijkstra(src, dist, parent);

    RestauranteCercano cercanos[3];

    for (int i = 0; i < 3; i++) {
        cercanos[i].distancia = 1e9;
        strcpy(cercanos[i].nombre, "");
    }

    for (int i = 0; i < numTotalRestaurantes; i++) {
        string key(todosRestaurantes[i]);
        key = trimStr(key);
        key = toLowerStr(key);

        if (!hashUbicaciones->exists(key)) continue;

        Ubicacion* ubi = hashUbicaciones->find(key);
        int nodeR = ubi->x * 30 + ubi->y;
        double d = dist[nodeR];

        if (d >= 1e9) continue;

        for (int j = 0; j < 3; j++) {
            if (d < cercanos[j].distancia) {
                for (int k = 2; k > j; k--) {
                    cercanos[k] = cercanos[k - 1];
                }
                strcpy(cercanos[j].nombre, todosRestaurantes[i]);
                cercanos[j].distancia = d;
                cercanos[j].ubicacion = *ubi;
                break;
            }
        }
    }

    cout << "3 RESTAURANTES MAS CERCANOS A (" << userX << "," << userY << ") VIA GRAFO\n";
    for (int i = 0; i < 3; i++) {
        if (cercanos[i].distancia < 1e9) {
            cout << (i + 1) << ". " << cercanos[i].nombre << "\n";
            cout << "   Distancia: " << cercanos[i].distancia << " unidades\n";
            cout << "   Ubicacion: (" << cercanos[i].ubicacion.x 
                 << "," << cercanos[i].ubicacion.y << ")\n";

            menuDeRestaurante(cercanos[i].nombre);

            int nodeR = cercanos[i].ubicacion.x * 30 + cercanos[i].ubicacion.y;
            cout << "   Ruta recomendada:\n";
            imprimirRuta(nodeR, parent);
            cout << "\n";
        }
    }
}


//PROCESAR ORDENES
//Complejidad: O(n * V^2)
//Procesa ordenes y calcula rutas de entrega desde los restaurantes a destinos
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

        char *R = strstr(linea, "R:");
        char *O = strstr(linea, "O:");
        if (!R || !O) continue;

        R += 2;
        int lenR = O - R - 1;
        strncpy(nombreR, R, lenR);
        nombreR[lenR] = '\0';

        string cleanR = trimStr(string(nombreR));
        strncpy(nombreR, cleanR.c_str(), sizeof(nombreR));
        nombreR[sizeof(nombreR) - 1] = '\0';

        O += 2;
        char *parenP = strstr(O, "(");
        if (!parenP) continue;
        int lenP = parenP - O;
        strncpy(nombreP, O, lenP);
        nombreP[lenP] = '\0';

        string cleanP = trimStr(string(nombreP));
        strncpy(nombreP, cleanP.c_str(), sizeof(nombreP));
        nombreP[sizeof(nombreP) - 1] = '\0';

        sscanf(parenP, "(%d)", &precio);

        char *destStr = strrchr(linea, '(');
        if (!destStr) continue;
        sscanf(destStr, "(%d, %d)", &dx, &dy);

        string key(nombreR);
        key = trimStr(key);
        key = toLowerStr(key);

        if (!hashUbicaciones->exists(key)) {
            cout << "Restaurante no encontrado: " << nombreR << "\n";
            continue;
        }

        Ubicacion* ubi = hashUbicaciones->find(key);

        int origen = ubi->x * 30 + ubi->y;
        int destino = dx * 30 + dy;

        double dist[900];
        int parent[900];

        dijkstra(origen, dist, parent);

        cout << "\n\tORDEN\n";
        cout << "Restaurante: " << nombreR << "\n";
        cout << "Platillo: " << nombreP << "\n";
        cout << "Precio: $" << precio << "\n";
        cout << "Destino: (" << dx << "," << dy << ")\n";
        cout << "Distancia total: " << dist[destino] << " unidades\n";
        imprimirRuta(destino, parent);
    }

    file.close();
}


//MENU 
// Complejidad: O(1)
void mostrarMenu() {
    cout << "\n\tSISTEMA DE DELIVERY"<< endl;
    cout << "1. Buscar menu de restaurante\n";
    cout << "2. Buscar restaurantes que venden un platillo\n";
    cout << "3. Encontrar 3 restaurantes mas cercanos\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}

//MAIN
int main() {
    cout << "Cargando datos...\n";

    cargarRestaPlaces("restaPlaces.txt");
    cargarMenu("menuFile.txt");
    cargarCity("city30x30.txt");

    cout << "Datos cargados correctamente!\n";
    cout << "Total de restaurantes: " << numTotalRestaurantes << "\n";

    cout << "\n\tPROCESANDO ORDENES DEL ARCHIVO \n";
    procesarOrdenes("orders30x30.txt");

    int opcion = 0;
    char nombre[120];
    int x, y;

    while (opcion != 4) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                mostrarTodosLosRestaurantes();
                cout << "\nIngrese el nombre del restaurante: ";
                cin.getline(nombre, 120);
                menuDeRestaurante(nombre);
                break;

            case 2:
                mostrarTodosLosPlatillos();
                cout << "\nIngrese el nombre del platillo: ";
                cin.getline(nombre, 120);
                restaurantesConPlato(nombre);
                break;

            case 3:
                cout << "\nIngrese su ubicacion:\n";
                while (true) {
                    cout << "X (0 a 29): ";
                    cin >> x;

                    if (cin.fail() || x < 0 || x > 29) {
                        cin.clear();        
                        cin.ignore(9999, '\n'); 
                        cout << "Valor invalido. Intente de nuevo.\n";
                    } else break;
                }

                while (true) {
                    cout << "Y (0 a 29): ";
                    cin >> y;

                    if (cin.fail() || y < 0 || y > 29) {
                        cin.clear();
                        cin.ignore(9999, '\n');
                        cout << "Valor invalido. Intente de nuevo.\n";
                    } else break;
                }

                cin.ignore();
                restaurantesCercanos(x, y);
                break;

            case 4:
                cout << "\nHasta luego!\n";
                break;

            default:
                cout << "\nOpcion no valida. Intente de nuevo.\n";
                break;
        }
    }

    return 0;
}
