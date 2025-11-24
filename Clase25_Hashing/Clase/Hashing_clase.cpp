#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;


//	Una clase para un elemento de la tabla
template<class T>
class Element {
	public:
		string str_key;		//	Llave string, como "Ana" 
		int int_key	;	//	Llave entera, resultante de la llave string
		
		int h_key;		//	Indice real asignado con base en int_key

		T item; 		//	El objeto asociado con la llave

		bool free; 		//	Una bandera para saber si este elemento de la tabla esta libre o no

		//	Constructor
		Element<T> ()
		{	str_key = "";
			int_key = -1;
			h_key = -1;
			item = -1;
			free = true; 
		}
};

//	Una clase que sera la tabla hash
template<class T>
class Hash 
{	public:
		int maxSize; 		//	tamaño maximo
		int currentSize;	//	tamaño actual
		int i;				// contador de colisiones
		
		Element<T> **table;	//	puntero a arreglo de los elementos
		
		Hash(int size)
		{	int j;
			maxSize = size;
			currentSize = 0;
			i = 0;
			// Sintaxis: 
			// var = new tipo_dato*[num_elems]
			table = new Element<T>*[maxSize];

			for(j = 0; j < maxSize; j++ )
			{	table[j] = new Element<T>();	}

		}

		void show();				//	ver toda la tabla
		void insert(string, T);		//	agregar un elemento nuevo, recibe key y value
		//void remove(string);		//	revomer uno por su key
		int find(string);			//	encontrar el indice de una key
};


template<class T> 
void Hash<T>::show( )
{	int j;



}



template<class T> 
void Hash<T>::insert(string str_key, T value)	// Recibe algo como insert( "Annie", 23) 
{	
	  int key;   //  valor numerico del string
	  int h_key; //  index real para el elemento
	  int flag;  //  bandera, indica cuando finalaizo el insert

	  //  Verifca que hay espacio
	  //  Calcula la key
	  //  Contador de colisiones inicia en 0
	  //  Inicializa flag en 0

	  // mientras no haya encontrado lugar
	  // calcuala la siguiente h_key para intentar
	  // si table[h_key] esta libre
	  // Guardar el elemento en el indice table[h_key]
	  // table[h_key] ya no esta libre
	  // guarda sus atriburos: str_key, int_key, y h_key
	  // rompe el ciclo, con flag = 1
	  // Aumenta currentSize
	  //  Si no, aumentta el contador de colisiones

	  // Si no hubo espacio, imprime 'tabla llena'	

}


int main() 
{	
	Hash<int> htable(10);

	htable.insert("Ana", 24);		htable.show();
	// htable.insert("Annie", 30);		htable.show();

	// htable.insert("Armando", 45);   htable.show();
	// htable.insert("Alex", 60);		htable.show();
	// htable.insert("Axel", 28);		htable.show();
	// htable.insert("Andrea", 32);	htable.show();

	// htable.insert("Bill", 32);		htable.show();
	// htable.insert("Veronica", 32);	htable.show();
	// htable.insert("Karla", 32);		htable.show();
	// htable.insert("Laura", 32);		htable.show();

	// htable.insert("Luis", 32);
	// htable.show();

	// htable.find("Alex");
}