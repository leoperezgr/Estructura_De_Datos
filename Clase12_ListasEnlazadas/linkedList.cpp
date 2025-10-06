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



/*Inserta nodo nuevo al inicio de la lista*/
//Complejidad O(1)
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



// Insertar nuevo nodo al final 
void List::insertLast(int newValue)
{	

	// Si la lista esta vacia, inserta el nuevo valor al inicio
    if(this->size==0)
    {
        this->insertFirst(newValue);
    }
    
    else
    {
            Node *nuevo = new Node(newValue);
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



// Inserta en un indice especifico
// ... regresa verdadero si la operacion salio bien
bool List::insertAtIndex(int index, int newValue )
{
	
	

	//	Si va al inicio, usa insertFirst
	
	//	Si va al final, usa insertLast

	// Si va enmedio, insertar verificado el indice:  
		//  Crea el nodo nuevo
		//	Usa un nodo auxiliar para recorrer la lista
		// 	Usa i como contador para el indice

		// Usa un while para recorrer la lista, contando con i
			// Cuando llegues al indice, agrega el nodo el nodo	
	
	//	Si no... 	
		// cout << "Indice no valido" << endl;
		return false; 

}

// 	Elimina el primer elemento de la lista
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

void List::deleteLast ()
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


int main(int argc, char* argv[]) 
{	List list;

	cout << " Nada por ahora :[" << endl; 

	//list.insertFirst(1); 	list.showList();
	//list.insertFirst(0); 	list.showList();

	// list.insertFirst(1); 	list.showList();
	// list.insertFirst(0); 	list.showList();

	list.insertLast(2); 	list.showList();
	list.insertLast(4); 	list.showList();

	// list.insertAtIndex(3, 3); 	list.showList();

	//list.deleteFirst(); 	list.showList();
	list.deleteLast(); 		list.showList();
	// list.insertLast(5); 	list.showList();

	// list.deleteAtIndex(3); 	list.showList();
	//list.deleteLast(3); 	list.showList();
	// list.insertLast(4); 	list.showList();


	// int index;
	// Node *a = list.find(3, &index);
	// cout << "Encontrado en memoria: " << a << " index: " << index << endl;
}