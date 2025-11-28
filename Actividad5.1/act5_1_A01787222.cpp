#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <math.h>
#include <limits.h>

using namespace std;

//Estructura de elemento
struct Element {
    char strKey[50];
    int  intKey;
    int  item;
    bool free;
    bool neverUsed;
};

//Clase Hash
class Hash {
    public:
        int maxSize;
        int currentSize;

        Element *table;

        Hash(int size);

        int computeKey(const char *str);
        int hash1(int key);
        int hash2(int key);
        int hashFunction(int key, int i);

        void show();
        void insert(const char *str, int item);
        int  find(const char *str);
        bool update(const char *str, int newItem);
        bool remove(const char *str);
};

//constructor que inicializa la tabla
//Complejidad: O(N)
Hash::Hash(int size)
{
    int i;
    maxSize     = size;
    currentSize = 0;

    table = (Element *) malloc(maxSize * sizeof(Element));

    for (i = 0; i < maxSize; i++) {
        table[i].strKey[0] = '\0';
        table[i].intKey    = -1;
        table[i].item      = 0;
        table[i].free      = true;
        table[i].neverUsed = true;
    }
}

//convierte un string a suma ASCII
//Complejidad: O(N)
int Hash::computeKey(const char *str)
{
    int suma = 0;
    int i = 0;
    while (str[i] != '\0') {
        suma += (int)str[i];
        i++;
    }
    return suma;
}

//primera funcion hash
//Complejidad: O(1)
int Hash::hash1(int key)
{
    return key % maxSize;
}

//segunda funcion hash
//Complejidad: O(1)
int Hash::hash2(int key)
{
    int h2 = 7 - (key % 7);
    if (h2 == 0) h2 = 1;
    return h2;
}

//combina h1 y h2 para double hashing
//Complejidad: O(1)
int Hash::hashFunction(int key, int i)
{
    int h1_ = hash1(key);
    int h2_ = hash2(key);
    int index = (h1_ + i * h2_) % maxSize;
    if (index < 0) index += maxSize;
    return index;
}

//imprime toda la tabla hash
//Complejidad: O(N)
void Hash::show()
{
    int i;
    cout << "Indice\tEstado\t\tLlave\tIntKey\tItem" << endl;
    for (i = 0; i < maxSize; i++) {
        cout << i << "\t";

        if (table[i].neverUsed) {
            cout << "-1\t-1\t-1\t-1" << endl;
        }
        else if (table[i].free) {
            cout << "Libre\t\t-\t" << table[i].intKey << "\t-" << endl;
        }
        else {
            cout << "Ocupado\t" << table[i].strKey << "\t" << table[i].intKey << "\t" << table[i].item << endl;
        }
    }
}

//inserta un elemento usando double hashing
//Complejidad: O(N)
void Hash::insert(const char *str, int item)
{
    if (currentSize == maxSize) {
        cout << "La tabla hash esta llena. No se puede insertar." << endl;
        return;
    }

    int key = computeKey(str);
    int i   = 0;
    int index;

    while (i < maxSize) {
        index = hashFunction(key, i);

        if (table[index].free) {
            strcpy(table[index].strKey, str);
            table[index].intKey = key;
            table[index].item = item;
            table[index].free = false;
            table[index].neverUsed = false;
            currentSize++;
            return;
        }
        i++;
    }

    cout << "No se pudo insertar (no se encontro espacio disponible)." << endl;
}

//busca un elemento por su llave
//Complejidad: O(N)
int Hash::find(const char *str)
{
    int key = computeKey(str);
    int i   = 0;
    int index;

    while (i < maxSize) {
        index = hashFunction(key, i);

        if (table[index].neverUsed) {
            return -1;
        }

        if (!table[index].free && strcmp(table[index].strKey, str) == 0) {
            return index;
        }

        i++;
    }

    return -1;
}

//actualiza el item de una llave
//Complejidad: O(N)
bool Hash::update(const char *str, int newItem)
{
    int pos = find(str);
    if (pos == -1) {
        return false;
    }

    table[pos].item = newItem;
    return true;
}

//elimina un elemento
//Complejidad: O(N)
bool Hash::remove(const char *str)
{
    int pos = find(str);
    if (pos == -1) {
        return false;
    }

    table[pos].free = true;
    return true;
}

//main
int main(int argc, char* argv[])
{
    Hash H(11);

    cout << "Insertando (Ana, 65)" << endl;
    H.insert("Ana", 65);
    H.show();

    cout << "Insertando (Lola, 30)" << endl;
    H.insert("Lola", 30);
    H.show();

    cout << "Insertando (Anahi, 24)" << endl;
    H.insert("Anahi", 24);
    H.show();

    cout << "Insertando (Aldo, 35)" << endl;
    H.insert("Aldo", 35);
    H.show();

    cout << "Insertando (Aba, 20)" << endl;
    H.insert("Aba", 20);
    H.show();

    cout << "Insertando (Lalo, 36)" << endl;
    H.insert("Lalo", 36);
    H.show();

    cout << "Insertando (Lorena, 25)" << endl;
    H.insert("Lorena", 25);
    H.show();

    cout << "Actualizando (Anahi, 24) -> (Anahi, 23)" << endl;
    if (H.update("Anahi", 23)) {
        cout << "Update exitoso." << endl;
    } else {
        cout << "No se encontro la llave." << endl;
    }
    H.show();

    cout << "Eliminando (Aldo, 35)" << endl;
    if (H.remove("Aldo")) {
        cout << "Remove exitoso." << endl;
    } else {
        cout << "No se encontro la llave." << endl;
    }
    H.show();

    cout << "Buscando (Anahi)" << endl;
    int pos = H.find("Anahi");
    if (pos == -1)
        cout << "Anahi NO encontrada." << endl;
    else
        cout << "Encontrada en indice " << pos << ", item = " << H.table[pos].item << endl;

    cout << "Buscando (Aldo)" << endl;
    pos = H.find("Aldo");
    if (pos == -1)
        cout << "Aldo NO encontrado." << endl;
    else
        cout << "Encontrado en indice " << pos << ", item = " << H.table[pos].item << endl;

    cout << "Insertando (Leyla, 36)" << endl;
    H.insert("Leyla", 36);
    H.show();

    return 0;
}
