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
	if ( search(value) == nullptr ) 
	{  // Crea el nodo nuevo
		NodeTree* nuevo = new NodeTree(value);

	
		// Necesitas encontrar a un nodo que pueda ser el padre del nuevo
		// Inicia desde la raiz... 
		NodeTree* aux = root;

		// mientras aux no sea null... 
		// agrega un return cuando consigas agregar el nodo nuevo... 
		while ( aux != nullptr )
		{ 	// revisa a que lado de aux deberia quedar el nodo nuevo
			// Va a la izquierda si es menor que el valor en aux
			// y a la derecha si no
			if ( value < aux->data )
			{	// Revisa si el nodo nuevo puede ser el hijo izquierdo de aux  
				if (aux->left == nullptr) {
					aux->left = nuevo;
					nuevo->up = aux;
					return;
				}
				// si no, continua buscando un lugar a la izauierda de aux
				aux = aux->left;
			}
			else
			{	// Mismo proceso, pero para la derecha
				if (aux->right == nullptr) {
					aux->right = nuevo;
					nuevo->up = aux;
					return;
				}
				aux = aux->right;
			} 

		}
	}
	else
	{
		// ya existe, no insertamos duplicados
	}

	
}

void BST::remove(int value)
{
	// Buscar el nodo a eliminar
	NodeTree* z = search(value);

	// Si no existe, no hay nada que hacer
	if (z == nullptr) {
		return;
	}

	// Caso 1: z es hoja (no tiene hijos)
	if (z->left == nullptr && z->right == nullptr) {
		NodeTree* p = z->up;
		if (p == nullptr) {
			// z es la raiz y es hoja
			root = nullptr;
		} else {
			// desconectar de su padre
			if (p->left == z) p->left = nullptr;
			else              p->right = nullptr;
		}
		delete z;
		return;
	}

	// Caso 2: z tiene un solo hijo
	if ( (z->left == nullptr) ^ (z->right == nullptr) ) {
		// hijo es el único hijo no nulo
		NodeTree* child = (z->left != nullptr) ? z->left : z->right;
		NodeTree* p = z->up;

		if (p == nullptr) {
			// z es la raiz
			root = child;
			child->up = nullptr;
		} else {
			// enlazar el hijo con el padre de z
			if (p->left == z) p->left = child;
			else              p->right = child;
			child->up = p;
		}
		delete z;
		return;
	}

	// Caso 3: z tiene dos hijos
	// Usamos el sucesor (mínimo del subárbol derecho)
	NodeTree* succ = z->right;
	while (succ->left != nullptr) {
		succ = succ->left;
	}

	// Copiamos el valor del sucesor a z
	z->data = succ->data;

	// Ahora eliminamos el sucesor (tiene a lo más un hijo derecho)
	NodeTree* succChild = (succ->right != nullptr) ? succ->right : nullptr;
	NodeTree* succParent = succ->up;

	if (succParent->left == succ) {
		succParent->left = succChild;
	} else {
		succParent->right = succChild;
	}
	if (succChild != nullptr) {
		succChild->up = succParent;
	}

	delete succ;
}

void BST::showTree()
{
	// (implementación opcional según necesidades del curso)
}

int main(int argc, char  *argv[])
{	
	BST *bst = new BST(25);
	showTree();

	NodeTree *aux = bst->search(25);

	aux = bst->search(30);

	bst->insert(20);
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


	saux = bst->search(4);

	cout << aux << endl;
	
}
