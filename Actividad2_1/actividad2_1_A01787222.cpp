#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int value; //guarda el nodo
    Node* next; //apunta el siguiente nodo
    Node* prev; //apunta el nodo anterior
    Node(int value) : value(value), next(NULL), prev(NULL) {}
}; // aqui se puede definir la lista enlazada doble

class List {
    Node* first; //apunta el primer nodo
    int size; //cantidad de nodos

public:
    List();
    int  getSize();
    void showList();
    void showListReverse();
    Node* find(int, int*);
    void insertLast(int);
    void insertFirst(int);
    bool insertAtIndex(int, int);
    void update(int, int);
    void deleteFirst();
    void deleteLast();
    void deleteAtIndex(int);
};

//O(1), inicializa la lista siendo vacia
List::List() {
    first = NULL;
    size = 0;
}

//O(1), obitene cuantos nodos hay
int List::getSize() {
    return size;
}

//O(n), muestra la lista
void List::showList() {
    cout << "Size " << this->size << endl;
    Node* aux = this->first;
    int i = 0;
    while (aux != NULL) {
        cout << "i = " << i << "\tvalue = " << aux->value << endl;
        aux = aux->next;
        i++;
    }
}

//O(n), muestra la lista al reves
void List::showListReverse() {
    cout << "Size " << this->size << " (reverse)" << endl;
    if (this->first == NULL) {
        return;
    }
    Node* last = this->first;
    while (last->next != NULL) {
        last = last->next;
    }
    int i = this->size - 1;
    while (last != NULL) {
        cout << "i = " << i << "\tvalue = " << last->value << endl;
        last = last->prev;
        i--;
    }
}

//O(n), busca algun valor dentro del nodo
Node* List::find(int value, int* index) {
    Node* aux = this->first;
    int i = 0;
    while (aux != NULL) {
        if (aux->value == value) {
            if (index != NULL) {
                *index = i;
            }
            return aux;
        }
        aux = aux->next;
        i++;
    }
    if (index != NULL) {
        *index = -1;
    }
    return NULL;
}

//O(1), inserta un valor al principio
void List::insertFirst(int newValue) {
    Node* nuevo = new Node(newValue);
    nuevo->next = first;
    nuevo->prev = NULL;
    if (first != NULL) {
        first->prev = nuevo;
    }
    first = nuevo;
    size++;
}

//O(n), inserta un valor al final
void List::insertLast(int newValue) {
    if (this->size == 0) {
        insertFirst(newValue);
        return;
    }
    Node* nuevo = new Node(newValue);
    Node* aux = this->first;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = nuevo;
    nuevo->prev = aux;
    size++;
}

//O(n), inserta un valor en el indice indicado, empezando en 0
bool List::insertAtIndex(int index, int newValue) {
    if (index < 0 || index > this->size) {
        cout << "Afuera del size" << endl;
        return false;
    }
    if (index == 0) {
        insertFirst(newValue);
        return true;
    }
    if (index == this->size) {
        insertLast(newValue);
        return true;
    }

    Node* curr = this->first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    Node* nuevo = new Node(newValue);
    Node* previo = curr->prev;

    nuevo->next = curr;
    nuevo->prev = previo;
    previo->next = nuevo;
    curr->prev = nuevo;

    size++;
    return true;
}

//O(n), cambia un valor dentro del nodo, por otro depende del indice
void List::update(int index, int newValue)
{
    if (index < 0 || index > this->size) //Si no se encuentra el index marca fuera de size
	{
		cout << "Afuera del size" << endl;
        return;
    }

    Node *aux = this -> first; //Node auxiliar para buscar
    int i;

    for(i =0; i<index; i++) //Busca la posicion
    {
        aux = aux->next;
    }

    aux ->value = newValue; //Sustituimos por el nuevo valor, no cambiamos el indice pues esta bien 

}

//O(1), elimina el primer valor
void List::deleteFirst() {
    if (this->size == 0) {
        return;
    }
    Node* aux = this->first;
    this->first = aux->next;
    if (this->first != NULL) {
        this->first->prev = NULL;
    }
    delete aux;
    size--;
}

//O(n), elimina el ulitmo valor
void List::deleteLast() {
    if (this->size == 0) {
        return;
    }
    if (this->size == 1) {
        delete this->first;
        this->first = NULL;
        this->size = 0;
        return;
    }
    Node* last = this->first;
    while (last->next != NULL) {
        last = last->next;
    }
    Node* previo = last->prev;
    previo->next = NULL;
    delete last;
    size--;
}

//O(n), elimina el valor del indice indicado
void List::deleteAtIndex(int index) {
    if (index < 0 || index >= this->size) {
        cout << "Afuera del size" << endl;
        return;
    }
    if (index == 0) {
        deleteFirst();
        return;
    }
    if (index == this->size - 1) {
        deleteLast();
        return;
    }

    Node* curr = this->first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    Node* previo = curr->prev;
    Node* sig = curr->next;

    previo->next = sig;
    sig->prev = previo;

    delete curr;
    size--;
}


 //MAIN
int main(int argc, char const *argv[])
{
    List list;
    list.insertFirst(1); list.showList(); 
    list.insertFirst(0); list.showList(); 
    list.insertLast(2); list.showList(); 
    list.insertLast(4); list.showList(); 
    list.insertLast(5); list.showList(); 
    list.insertAtIndex(3, 3); list.showList(); 
    list.deleteFirst(); list.showList(); 
    list.insertLast(5); list.showList();
    list.deleteAtIndex(3);  list.showList(); 
    list.deleteLast(); list.showList(); 
    list.insertLast(4); list.showList(); 
    list.update(2, 7); list.showList();

    cout << "Lista al reves:" << endl;
    list.showListReverse();

    int idx;
    Node* a = list.find(2, &idx);   
    if (a != NULL) {
        cout << "Encontrado en la memoria " << a << " index " << idx << " valor: " << a->value << endl;
    }
    else {
        cout << "Valor no encontrado" << endl;
    }

    return 0;
}
