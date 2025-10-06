#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

class Stack {
    private:
        int *data;
        int topIdx;
        int maxSize;
        int size;
    public:
        Stack(int maxSize);
        ~Stack();
        void push(int);
        int pop();
        bool isEmpty();
        int getSize();
        int getTop();
        void show();
};

Stack::Stack(int maxSize) //O(1) inicializa pila
{
    this->maxSize = maxSize;
    this->data = (int *) malloc(this->maxSize * sizeof(int));
    this->topIdx = -1;
    this->size = 0;
}

Stack::~Stack() //O(1) libera memoria
{
    free(this->data);
}

void Stack::push(int value) //O(1) inserta en la cima
{
    if (this->size < this->maxSize)
    {
        this->data[++this->topIdx] = value;
        this->size++;
    }
    else cout << "Pila llena" << endl;
}

int Stack::pop() //O(1) saca de la cima
{
    if (!this->isEmpty())
    {
        int val = this->data[this->topIdx--];
        this->size--;
        cout << "Extrajo " << val << endl;
        return val;
    }
    else { cout << "Pila vacia" << endl; return -1; }
}

bool Stack::isEmpty() //O(1) revisa si vacía
{ return (this->size == 0); }

int Stack::getSize() //O(1) devuelve tamaño
{ return this->size; }

int Stack::getTop() //O(1) consulta cima
{
    if (!this->isEmpty()) return this->data[this->topIdx];
    else { cout << "Pila vacia" << endl; return -1; }
}

void Stack::show() //O(n) muestra pila
{
    cout << "Fila tamaño = " << this->size << "\tCima = ";
    for (int i = this->topIdx; i >= 0; --i) cout << this->data[i] << (i ? " " : "");
    cout << endl;
}

class Queue {
    private:
        int *data;
        int front;
        int end;
        int maxSize;
        int size;
    public:
        Queue(int maxSize);
        ~Queue();
        void enqueue(int);
        int dequeue();
        int getFront();
        int getTop();
        bool isEmpty();
        bool isFull();
        int  getSize();
        void show();
};

Queue::Queue(int maxSize) //O(1) inicializa fila
{
    this->maxSize = maxSize;
    this->data = (int *) malloc(this->maxSize * sizeof(int));
    this->front = 0;
    this->end = 0;
    this->size = 0;
}

Queue::~Queue() //O(1) libera memoria
{ free(this->data); }

void Queue::enqueue(int value) //O(1) inserta al final
{
    if (!this->isFull())
    {
        this->data[this->end] = value;
        this->end = (this->end + 1) % this->maxSize;
        this->size++;
    }
    else cout << "Fila llena" << endl;
}

int Queue::dequeue() //O(1) elimina del frente
{
    if (!this->isEmpty())
    {
        int val = this->data[this->front];
        this->front = (this->front + 1) % this->maxSize;
        this->size--;
        cout << "Extrajo " << val << endl;
        return val;
    }
    else { cout << "Fila vacia" << endl; return -1; }
}

int Queue::getFront() //O(1) consulta frente
{
    if (!this->isEmpty()) return this->data[this->front];
    else { cout << "Fila vacia" << endl; return -1; }
}

int Queue::getTop() //O(1) alias frente
{ return this->getFront(); }

bool Queue::isEmpty() //O(1) revisa si vacía
{ return (this->size == 0); }

bool Queue::isFull() //O(1) revisa si llena
{ return (this->size == this->maxSize); }

int Queue::getSize() //O(1) devuelve tamaño
{ return this->size; }

void Queue::show() //O(n) muestra fila
{
    cout << "Tamaño fila = " << this->size << "\tFrente = ";
    for (int i = 0; i < this->size; ++i)
    {
        int idx = (this->front + i) % this->maxSize;
        cout << this->data[idx] << (i + 1 < this->size ? " " : "");
    }
    cout << endl;
}

class PriorityQueue {
    private:
        int *data;
        int maxSize;
        int size;
    public:
        PriorityQueue(int maxSize);
        ~PriorityQueue();
        void enqueue(int);
        int dequeue();
        bool isEmpty();
        bool isFull();
        int  getSize();
        int  getTop();
        void show();
};

PriorityQueue::PriorityQueue(int maxSize) //O(1) inicializa fila prioridad
{
    this->maxSize = maxSize;
    this->data = (int *) malloc(this->maxSize * sizeof(int));
    this->size = 0;
}

PriorityQueue::~PriorityQueue() //O(1) libera memoria
{ free(this->data); }

void PriorityQueue::enqueue(int value) //O(n) inserta ordenado
{
    if (this->isFull()) { cout << "Fila de prioridad llena" << endl; return; }
    int i = this->size - 1;
    while (i >= 0 && this->data[i] > value) { this->data[i + 1] = this->data[i]; --i; }
    this->data[i + 1] = value;
    this->size++;
}

int PriorityQueue::dequeue() //O(n) elimina menor
{
    if (!this->isEmpty())
    {
        int val = this->data[0];
        for (int i = 1; i < this->size; ++i) this->data[i - 1] = this->data[i];
        this->size--;
        cout << "Extrajo " << val << endl;
        return val;
    }
    else { cout << "Fila de prioridad vacia" << endl; return -1; }
}

bool PriorityQueue::isEmpty() //O(1) revisa si vacía
{ return (this->size == 0); }

bool PriorityQueue::isFull() //O(1) revisa si llena
{ return (this->size == this->maxSize); }

int PriorityQueue::getSize() //O(1) devuelve tamaño
{ return this->size; }

int PriorityQueue::getTop() //O(1) devuelve menor valor
{
    if (!this->isEmpty()) return this->data[0];
    else { cout << "Fila de prioridad vacia" << endl; return -1; }
}

void PriorityQueue::show() //O(n) muestra fila
{
    cout << "Tamaño = " << this->size << "\tMenor primero = ";
    for (int i = 0; i < this->size; ++i) cout << this->data[i] << (i + 1 < this->size ? " " : "");
    cout << endl;
}

int main() {
    Stack pila(10);
    Queue fila(10);
    PriorityQueue filaP(10);

    cout << "Prueba de Pila \n";
    pila.push(10);
    pila.push(20);
    pila.push(30);
    pila.show();
    cout << "Top: " << pila.getTop() << endl;
    pila.pop();
    pila.show();

    cout << "\nPrueba de Fila \n";
    fila.enqueue(30);
    fila.enqueue(10);
    fila.enqueue(20);
    fila.show();
    cout << "Top: " << fila.getTop() << endl;
    fila.dequeue();
    fila.show();

    cout << "\nPrueba de Fila de Prioridad \n";
    filaP.enqueue(5);
    filaP.enqueue(10);
    filaP.enqueue(1);
    filaP.show();
    cout << "Top: " << filaP.getTop() << endl;
    filaP.dequeue();
    filaP.show();

    return 0;
}