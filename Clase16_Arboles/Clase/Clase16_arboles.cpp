#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;



// Atributos para el nodo: punteros a izquierda y derecha 
// El puntero hacia arriba(padre) es opcional
class NodeTree 
{
public: 
    int data;
    NodeTree* left;
    NodeTree* right;
    NodeTree* up;
	
    NodeTree(int value, NodeTree* parent = nullptr)
        : data(value), left(nullptr), right(nullptr), up(parent) {}
};


class BST 
{
public:
    NodeTree* root;   // el arbol tiene un nodo raiz
	
    // Al crear el arbol, creamos su nodo raiz
    BST(int value)
    {
        root = new NodeTree(value, nullptr);
    }

    NodeTree* search(int);
    void insert(int);
    void remove(int);
    void showTree();

    // agregar recorridos
};

NodeTree* BST::search(int value)
{	
	// Asigna un nodo que nos sirva para recorrer el árbol 
	// aux inicia como la raíz 
	NodeTree* aux = root;

	// mientras que aux no sea null... 
	while (aux != nullptr)
	{	
		// el valor buscado es menor que el del nodo actual??  
		// desplazate al nodo de su izquierda
		if (value < aux->data)
		{
			aux = aux->left;  // bajamos a la izquierda
		}
		// el valor buscado es mayor que el del nodo actual??  
		// desplazate al nodo de su derecha
		else if (value > aux->data) 
		{	
			aux = aux->right; // bajamos a la derecha
		}
		// si no es mayor, ni menor, debe ser igual... 
		else
		{
			// valor encontrado, regresamos el nodo actual
			return aux;
		}
	} 

	// Si llegamos aquí, significa que recorrimos todo el árbol
	// y no encontramos el valor buscado
	return nullptr;
}


void BST::insert(int value)
{	// Comienza por verificar que el valor que se quiere agregar no exista en el arbol... 
	if ( ?? ) 
	{  // Crea el nodo nuevo
		??

	
		// Necesitas encontrar a un nodo que pueda ser el padre del nuevo
		// Inicia desde la raiz... 
		??

		// mientras aux no sea null... 
		// agrega un return cuando consigas agregar el nodo nuevo... 
		while ( ?? )
		{ 	// revisa a que lado de aux deberia quedar el nodo nuevo
			// Va a la izquierda si es menor que el valor en aux
			// y a la derecha si no
			if ( ?? )
			{	// Revisa si el nodo nuevo puede ser el hijo izquierdo de aux  

				// si no, continua buscando un lugar a la izauierda de aux
			}
			else
			{	// Mismo proceso, pero para la derecha


			} 

		}
	}
	else
	{

	}

	
}

void BST::remove(int value)
{

}

int main(int argc, char  *argv[])
{	
	BST *bst = new BST(25);

	//NodeTree *aux = bst->search(25);

	// aux = bst->search(30);

	// bst->insert(20);
	// bst->insert(34);
	// bst->insert(2);
	// bst->insert(22);
	// bst->insert(30);
	// bst->insert(40);
	// bst->insert(26);
	// bst->insert(31);

	// bst->insert(32);
	// bst->insert(45);
	// bst->insert(39);

	// bst->remove(34);

	// NodeTree *aux = bst->search(34);

	// bst->remove(32);
	// bst->remove(31);
	// bst->remove(34);


	//saux = bst->search(4);

	//cout << aux << endl;
	
}