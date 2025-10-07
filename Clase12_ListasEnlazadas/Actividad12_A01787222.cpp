#include <iostream>
#include <string>

using namespace std;

// Compilar y ejecutar 
// rm out.exe; g++ linkedList.cpp -o out.exe; ./out.exe


// class node: un valor y un puntero a otro nodo
class Node
{	public:

		int value;		//	valor almacenado
		Node *next;		//	puntero a otro nodo
	
		Node(int value)
		{	this->value = value;
			this->next = NULL;
		}

};


//  Clase lista enlazada simple: 

class List
{	Node *first;   // Puntero al nodo inicial 
	int size;      // y numero de elementos totales

	public:
		List() 
		{	first = NULL; 
			size = 0;
		}
		
		int getSize(){ return size; } 	// Devuelve cuantos elementos hay
		void showList(); 				// Imprime los elementos

		Node* find(int, int*);		// Encuentra un valor y devuelve la direccion del nodo
		

		void insertLast(int);		//	Agregua valor al inicio
		void insertFirst(int);		//	Agrega valor al fianl


		bool insertAtIndex(int, int); // <-- Actividad
		void update(int, int);		// <--- Actividad cambiar el valor en un indice
		
		void deleteFirst();
		void deleteLast();			// <--- Actividad	
		void deleteAtIndex(int);	// <--- Actividad

};


void List::showList()
{	// Define un contador i = 0
	int i = 0;
	

	// Imprime cuantos elementos hay en la lista
	cout << "Size " << this->size <<endl;
	
	//	Usa un nodo auxiliar, cuyo valor inicial es first para recorrer la lista
	Node *aux = this-> first;
	

	//	Mientras el auxiliar no sea null... 
	while(aux != NULL){
		// Imprime el valor de i y del nodo
		cout << "i = " << i << "\t" << "value = " << aux -> value << endl;
		//  Avanza en la lista, haciendo que aux = aux->next
		aux = aux -> next;
	    
	    //  Aumenta el contador i
		i++;
	}
}

//Complejidad O(n)
void List::insertFirst(int newValue)
{	// Crea un nodo nuevo llamando al constructor de nodo
	// Sintaxis: clase *nombre = new  constructor_clase( params ); 
	Node *nuevo = new Node(newValue);
	

	// Enlaza el nodo nuevo para apuntar a first como su siguiente
	nuevo -> next = first;
	

	// Actualiza first, ahora es el nodo nuevo
	this ->first = nuevo;
	

	// Aumenta la cantidad de elementos en la lista
	this-> size++;
	
}

//Complejidad O(1)
void List::insertLast(int newValue)
{	

	// Si la lista esta vacia, inserta el nuevo valor al inicio
    if(this->size==0)
    {
        this->insertFirst(newValue);
    }


	// Si no... 
		// Crea un nodo nuevo 
        Node *nuevo = new Node(newValue);

		//	Usa un nodo auxiliar, cuyo valor inicial es first para recorrer la lista:
        Node *aux = this->first;
		//	Mientras el siguiente auxiliar no sea null... 
        while(aux -> next != NULL)
        {
		//  Avanza en la lista para llegar al ultimo nodo, haciendo que aux = aux->next
        aux = aux->next;
        }

		
		// Enlaza aux con el nodo nuevo y aumenta el contador de elementos
        aux->next = nuevo;
        this->size++;

}

//O(1)
bool List::insertAtIndex(int index, int newValue) {
    if (index < 0 || index > this->size) 
	{
		cout << "Afuera del size" << endl;
        return false;
    }

    // Si va al inicio
    if (index == 0) {	
        insertFirst(newValue);
        return true;
    }

    // Si va al final
    if (index == this->size) {
        insertLast(newValue);
        return true;
    }

    // Crear nodo nuevo
    Node* nuevo = new Node(newValue);

    // Avanzar hasta el nodo anterior al índice
    Node* aux = this->first;
    for (int i = 0; i < index - 1; i++) {
        aux = aux->next;
    }

    nuevo->next = aux->next;  
    aux->next = nuevo;      

    this->size++;
    return true;
}

//0(1)
void List::deleteFirst ()
{	// Asigna first a un nodo auxiliar
	Node *aux = this -> first;

	// Haz que first sea el siguiente auxiliar...
	// ... de modo que el nodo next de first se vuelve el nuevo first
	first = aux -> next;
	
	// Elimina auxiliar con delete. Sintaxis delete nombre_ptr;
	delete aux;

	// Actualiza el numero de elementos de la lista
	this -> size--;

}

//O(n)
void List::deleteLast()
{	// Asigna first a un nodo auxiliar
	Node *aux = this -> first;
	
	while (aux ->next-> next != NULL)
	{
		aux = aux -> next;
	}
	
	delete aux->next;
	aux -> next = NULL;
	
	this -> size --;

}

//O(n)
void List::deleteAtIndex(int index)
{
    if (index < 0 || index > this->size) 
	{
		cout << "Afuera del size" << endl;
        return;
    }
    if(index == 0)
    {
        deleteFirst();
        return;
    }
    if(index == this->size)
    {
        deleteLast();
        return;
    }

    Node *aux = this->first;
    int i;

    for(i = 0; i< index-1; i++) //Agrego el index -1 y creo un nuevo nodo porque sino se queda infinitamente en 1's
    {
        aux = aux ->next;
    }

    Node* toDelete = aux->next;
    aux->next   = toDelete->next;
    delete toDelete;
    this->size--;
}

//O(n)
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
    
//O(n)
Node *List::find(int value, int* index)
{
    Node *aux = this-> first; //Hacemos un aux

    int i=0;

    while(aux != NULL) //Recorremos hasta el final
    {
        if( aux -> value == value) //Buscamos el valor dentro del  Nodo
        {
            *index = i; //Guardamos el indice
            return aux; //Regresamos el nodo
        }
        aux = aux -> next;
        i++;
    }
    //Si no lo encontramos
    *index = -1;
    return NULL;
}

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

    int idx;
    Node* a = list.find(2, &idx);   
    if(a != NULL)
    {
        cout<<"Encontrado en la memoria "<< a<< " index "<< idx<<" valor: "<< a->value<<endl;
    }
    else
    {
        cout << "Valor no encontrado"<< endl;
    }

    return 0;
}
