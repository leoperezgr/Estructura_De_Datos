#include <iostream>

using namespace std;


//---------------------------------
//  para imprimir arreglos
template <class T>
void show(T *A, int n)
{
    for (int i = 0; i < n; i++) {
        cout << A[i] << "\t";
    }
    cout << endl << endl;
}


// ----------------------- Lista enlazada doble (circular)

template <class T>
class Node
{
public:
    T value;              // valor almacenado
    Node<T> *prev;        // dir del nodo anterior
    Node<T> *next;        // dir del nodo siguiente

    Node(T valor)
    {
        this->value = valor;
        this->prev = NULL;
        this->next = NULL;
    }
};

//  Clase lista enlazada doble: 
template <class T>
class List
{
    Node<T> *first;     // puntero al primer nodo
    Node<T> *last;      // puntero al ultimo nodo 
    int size;           // numero de elementos que tiene la lista

public:
    List()
    {
        this->first = NULL;
        this->last  = NULL;
        this->size  = 0;
    }

    int  getSize()              const  { return size; }
    void showList();             // mostrar en orden
    void showListReverse();      // mostrar en reversa

    // Inserciones
    void insertFirst(T);          // al principio
    void insertLast(T);           // al final
    bool insertAtIndex(int, T);   // en indice

    // Eliminaciones
    void deleteFirst();           // al principio
    void deleteLast();            // al final
    void deleteAtIndex(int);      // en indice

    // Utilidades
    Node<T>* find(T, int*);       // encontrar valor
    void     update(int, T);      // actualizar indice

    Node<T>* getFirst() { return first; }
    Node<T>* getLast()  { return last;  }
};


// inserta en un indice especifico
template<class T>
bool List<T>::insertAtIndex(int index, T newValue)
{
    if (index < 0 || index > this->size) return false;

    if (index == 0) {
        insertFirst(newValue);
        return true;
    }
    if (index == this->size) {
        insertLast(newValue);
        return true;
    }

    Node<T>* nuevo = new Node<T>(newValue);

    // caminar desde first hasta el nodo actualmente en 'index'
    Node<T>* curr = this->first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    // insertar antes de 'curr'
    Node<T>* prev = curr->prev;
    nuevo->next = curr;
    nuevo->prev = prev;
    prev->next  = nuevo;
    curr->prev  = nuevo;

    this->size++;
    return true;
}

template<class T>
Node<T>* List<T>::find(T value, int *index)
{
    if (this->size == 0) {
        if (index) *index = -1;
        return NULL;
    }

    Node<T>* aux = this->first;
    for (int i = 0; i < this->size; i++) {
        if (aux->value == value) {
            if (index) *index = i;
            return aux;
        }
        aux = aux->next;
    }
    if (index) *index = -1;
    return NULL;
}

// elimina al inicio
template<class T>
void List<T>::deleteFirst()
{
    if (this->size == 0) return;

    Node<T>* aux = this->first;

    if (this->size == 1) {
        // un solo elemento
        this->first = this->last = NULL;
        delete aux;
        this->size = 0;
        return;
    }

    // hay 2 o más elementos (lista circular)
    Node<T>* segundo = aux->next;
    segundo->prev = this->last;
    this->last->next = segundo;

    delete aux;
    this->first = segundo;
    this->size--;
}

// inserta al inicio
template<class T>
void List<T>::insertFirst(T newValue)
{
    Node<T> *nuevo = new Node<T>(newValue);
    Node<T> *aux = this->first;

    nuevo->next = aux; 
    this->first = nuevo;

    if (this->size == 0) {
        this->last = nuevo;
    } else {
        aux->prev = nuevo; 
    }

    // circularidad
    this->first->prev = this->last;
    this->last->next  = this->first;
    this->size++;
}


// inserta al final
template<class T>
void List<T>::insertLast(T newValue)
{
    Node<T> *nuevo = new Node<T>(newValue);
    Node<T> *aux = this->last;

    nuevo->prev = aux;
    this->last  = nuevo; 

    if (this->size == 0) {
        this->first = nuevo;
    } else {
        aux->next = nuevo;
    }

    // circularidad
    this->first->prev = this->last;
    this->last->next  = this->first;
    this->size++;
}

template<class T>
void List<T>::deleteLast()
{
    if (this->size == 0) return;

    Node<T>* aux = this->last;

    if (this->size == 1) {
        this->first = this->last = NULL;
        delete aux;
        this->size = 0;
        return;
    }

    Node<T>* nuevoLast = aux->prev;
    nuevoLast->next = this->first;
    this->first->prev = nuevoLast;

    this->last = nuevoLast;
    delete aux;
    this->size--;
}

template<class T>
void List<T>::deleteAtIndex(int index)
{
    if (index < 0 || index >= this->size) return;

    if (index == 0) {
        deleteFirst();
        return;
    }
    if (index == this->size - 1) {
        deleteLast();
        return;
    }

    Node<T>* curr = this->first;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    Node<T>* p = curr->prev;
    Node<T>* n = curr->next;

    p->next = n;
    n->prev = p;

    delete curr;
    this->size--;
}

template<class T>
void List<T>::update(int index, T newValue)
{
    if (index < 0 || index >= this->size) return;
    Node<T>* aux = this->first;
    for (int i = 0; i < index; i++) aux = aux->next;
    aux->value = newValue;
}

template<class T>
void List<T>::showList( )
{
    Node<T> *aux = this->first;
    int i = 0;
    cout << "Size:\t" << this->size << endl;
    while (i < this->size)
    {
        cout << "\t[" << i << "]:\t" << aux->value << endl;
        aux = aux->next;
        i++;
    }
    cout << endl;
}

template<class T>
void List<T>::showListReverse( )
{
    Node<T> *aux = this->last;
    int i = this->size - 1;
    cout << "Size:\t" << this->size << endl;
    while (i >= 0)
    {
        cout << "\t[" << i << "]:\t" << aux->value << endl;
        aux = aux->prev;
        i--;
    }
    cout << endl;
}


//---------------------------------------------------------------------

template <class T>        
class Stack
{
    List<T> lista;

public:
    Stack() {}

    bool isEmpty() const { return lista.getSize() == 0; }

    void push(const T& v) { lista.insertLast(v); }

    void pop() { if (!isEmpty()) lista.deleteLast(); }

    T top() { return lista.getLast()->value; }
};


//------------------ quicksort iterativo con stack, para arreglos --------------------

template <class T>
int partition(T *A, int L, int R)
{
    T pivot = A[R];
    int i = L - 1;
    for (int j = L; j <= R - 1; j++) {
        if (A[j] <= pivot) {
            i++;
            T tmp = A[i]; A[i] = A[j]; A[j] = tmp;
        }
    }
    T tmp = A[i + 1]; A[i + 1] = A[R]; A[R] = tmp;
    return i + 1;
}

struct Range { int L; int R; };

template <class T>
void quicksort(T *A, int n)
{
    if (n <= 1) return;

    Stack<Range> st;
    st.push({0, n - 1});

    while (!st.isEmpty()) {
        Range cur = st.top(); st.pop();
        int L = cur.L, R = cur.R;
        if (L >= R) continue;

        int p = partition(A, L, R);

        // Empujar primero el rango más grande para reducir altura de pila promedio
        int leftSize  = p - 1 - L;
        int rightSize = R - (p + 1);

        if (leftSize > rightSize) {
            if (L <= p - 1)   st.push({L, p - 1});
            if (p + 1 <= R)   st.push({p + 1, R});
        } else {
            if (p + 1 <= R)   st.push({p + 1, R});
            if (L <= p - 1)   st.push({L, p - 1});
        }
    }
}

//------------------------------------------------------------------------

int main(int argc, char* argv[]) 
{
    const int n = 10;
    int   A[n] = {13, 3, 5, 7, 1, 10, 9, 6, 4, 8}; 
    float F[n] = {1.7f, 5.5f, 6.5f, 3.4f, 7.1f, 8.5f, 9.4f, 13.3f, 4.2f, 2.44f}; 

    cout << "Arreglo int (antes):" << endl;
    show(A, n);
    quicksort(A, n);
    cout << "Arreglo int (despues):" << endl;
    show(A, n);

    cout << "Arreglo float (antes):" << endl;
    show(F, n);
    quicksort(F, n);
    cout << "Arreglo float (despues):" << endl;
    show(F, n);

    // Prueba rapida de lista
    // List<int> datos;
    // datos.insertLast(6);
    // datos.insertLast(5);
    // datos.insertLast(3);
    // datos.insertLast(5);
    // datos.insertLast(8);
    // datos.insertLast(7);
    // datos.insertLast(2);
    // datos.insertLast(4);
    // datos.showList();
    // int idx;
    // auto nd = datos.find(8, &idx);
    // cout << "find(8) en indice: " << idx << endl;
    // datos.insertAtIndex(2, 99);
    // datos.showList();
    // datos.deleteAtIndex(3);
    // datos.showList();

    return 0;
}
