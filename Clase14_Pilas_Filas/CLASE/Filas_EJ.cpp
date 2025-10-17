//  g++ filasEj.cpp -o filasEj ; ./filasEj.exe

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

class Queue {
    private:
        int *data;
        int front;
        int end;
        int maxSize;
        int size;   // número de elementos actuales

    public:
        Queue(int maxSize)
        {   
            this->maxSize = maxSize;
            this->data = (int *) malloc(this->maxSize * sizeof(int));
            this->front = 0;
            this->end = 0;
            this->size = 0;
        }

        ~Queue()
        {   
            free(this->data);
        }

        void enqueue(int);
        int dequeue();
        int getFront();
        bool isEmpty();  
        bool isFull();
};

void Queue::enqueue(int value)
{   
    if (!this->isFull())
    {
        this->data[this->end] = value;
        this->end = (this->end + 1) % this->maxSize;
        this->size++;
    }
    else
    {
        cout << "Fila llena" << endl;
    }
}

int Queue::dequeue()
{   
    if (!this->isEmpty())
    {
        int val = this->data[this->front];
        this->front = (this->front + 1) % this->maxSize;
        this->size--;
        cout << "Extrajo " << val << endl;
        return val;
    }
    else
    {
        cout << "Fila vacia" << endl;
        return -1;
    }
}

int Queue::getFront()
{   
    if (!this->isEmpty())
        return this->data[this->front];
    else
    {
        cout << "Fila vacia" << endl;
        return -1;
    }
}

bool Queue::isEmpty()
{
    return (this->size == 0);
}

bool Queue::isFull()
{
    return (this->size == this->maxSize);
}

int main(int argc, char *argv[])
{   
    int i;
    int maxSize = 10;

    Queue *queue = new Queue(maxSize);

    cout << "Esta vacia? " << queue->isEmpty() 
         << "\nEsta llena? " << queue->isFull() << endl;

    for (i = 0; i < maxSize + 2; i++)
    {   
        queue->enqueue(i);
    }
    
    while (!queue->isEmpty())
    {   
        queue->dequeue();
    }

    return 0;
}