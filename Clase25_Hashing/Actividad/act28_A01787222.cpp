#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

//Clase de los elementos
template<class T>
class Element {
    public:
        string str_key;
        int int_key;
        int h_key;
        T item;

        bool free;
        bool neverUsed;

        Element() {
            str_key = "";
            int_key = -1;
            h_key = -1;
            item = T();
            free = true;
            neverUsed = true;
        }
};

//Clase del Hash
template<class T>
class Hash {
    public:
        int maxSize;
        int currentSize;

        Element<T> **table;

        Hash(int size) {
            maxSize = size;
            currentSize = 0;

            table = new Element<T>*[maxSize];
            for (int j = 0; j < maxSize; j++) {
                table[j] = new Element<T>();
            }
        }

        int computeKey(string str_key);
        int hashFunction(int key, int i);
        void show();
        void insert(string, T);
        int  find(string);
        bool update(string, T);
        bool remove(string);
};

//Convierte la llave string a una llave entera, con la suma ASCII.
//Complejidad: O(n)
template<class T>
int Hash<T>::computeKey(string str_key) {
    int key = 0;
    for (int i = 0; i < (int)str_key.size(); i++) {
        key += (unsigned char)str_key[i];
    }
    return key;
}

//Función hash con linear probing.
//Complejidad: O(1)
template<class T>
int Hash<T>::hashFunction(int key, int i) {
    return (key + i) % maxSize;
}

//Muestra toda la tabla hash.
//Complejidad: O(n)
template<class T>
void Hash<T>::show() {

    cout <<"\nTabla: "<<endl;
    for (int j = 0; j < maxSize; j++) {
        cout << j << ":\t";
        if (!table[j]->free) {
            cout << table[j]->str_key << "\t"
                 << table[j]->int_key << "\t"
                 << table[j]->item;
        } else {
            cout << "-1";
        }
        cout << endl;
    }
}

//Inserta un nuevo elemento.
//Complejidad O(n)
template<class T>
void Hash<T>::insert(string str_key, T value) {
    if (currentSize >= maxSize) {
        cout << "Tabla llena. No se pudo insertar..." << str_key << endl;
        return;
    }

    int key = computeKey(str_key);
    int iCol = 0;
    int h_key;
    bool flag = false;

    while (iCol < maxSize && !flag) {
        h_key = hashFunction(key, iCol);

        if (table[h_key]->free) {
            table[h_key]->str_key = str_key;
            table[h_key]->int_key = key;
            table[h_key]->h_key = h_key;
            table[h_key]->item = value;

            table[h_key]->free = false;
            table[h_key]->neverUsed = false;

            currentSize++;
            flag = true;
        } else {
            iCol++;
        }
    }

    if (!flag) {
        cout << "No se encontró espacio para " << str_key << " (tabla llena)." << endl;
    }
}

//Busca un elemento por su llave.
//Complejidad O(n)
template<class T>
int Hash<T>::find(string str_key) {
    int key = computeKey(str_key);
    int iCol = 0;
    int h_key;

    while (iCol < maxSize) {
        h_key = hashFunction(key, iCol);

        if (table[h_key]->neverUsed && table[h_key]->free) {
            break;
        }

        if (!table[h_key]->free && table[h_key]->str_key == str_key) {
            cout << "Elemento " << str_key << " encontrado en indice "
                 << h_key << " con valor " << table[h_key]->item << "." << endl;
            return h_key;
        }

        iCol++;
    }

    cout << "Elemento " << str_key << " no encontrado." << endl;
    return -1;
}

//Actualiza el valor asociado a una llave existente.
//Complejidad: O(n)
template<class T>
bool Hash<T>::update(string str_key, T newValue) {
    int pos = find(str_key);
    if (pos == -1) {
        cout << "No se pudo actualizar " << str_key << " (no existe)." << endl;
        return false;
    }

    table[pos]->item = newValue;
    cout << "Elemento " << str_key << " actualizado a " << newValue << endl;
    return true;
}

//Elimina un elemento por su llave.
//Complejidad: O(n)
template<class T>
bool Hash<T>::remove(string str_key) {
    int pos = find(str_key);
    if (pos == -1) {
        cout << "No se pudo eliminar " << str_key << " (no existe)." << endl;
        return false;
    }

    table[pos]->free    = true;
    table[pos]->str_key = "";
    table[pos]->int_key = -1;
    table[pos]->h_key = -1;
    table[pos]->item = T();

    currentSize--;
    cout << "Elemento " << str_key << " eliminado." << endl;
    return true;
}

//MAIN
int main() {

    Hash<int> htable(10);
    htable.insert("Ana", 65);   htable.show();
    htable.insert("Lola", 30);   htable.show();
    htable.insert("Anahi", 24);   htable.show();
    htable.insert("Aldo", 35);   htable.show();
    htable.insert("Aba", 20);   htable.show();
    htable.insert("Lalo", 36);   htable.show();
    htable.insert("Lorena", 25);   htable.show();

    cout << "\nActualizando Anahi, 24 a (Anahi, 23" << endl;
    htable.update("Anahi", 23);
    htable.show();

    cout << "\nEliminando (Aldo, 35)" << endl;
    htable.remove("Aldo");
    htable.show();

    cout << "\nBuscando Anahi" << endl;
    htable.find("Anahi");
    htable.show();

    cout << "\nBuscando Aldo" << endl;
    htable.find("Aldo");
    htable.show();

    cout << "\nInsertando (Leyla, 36)" << endl;
    htable.insert("Leyla", 36);
    htable.show();

    return 0;
}
