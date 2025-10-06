#include <iostream>
#include <cstdlib>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

int busquedaSecuencial(int *A, int n, int x)
{	
	int i;
	for(i = 0;i < n; i++)
	{
		if(A[i] == x)
		{
			return i;
		}
	}

	return -1;
}

int busquedaBinaria(int A[], int l, int r, int n, int x)
{	
    int i;

    while(l <= r )
    {
        i = l + (r-l)/2;
        if (A[i] == x)
        {
            return i;
        }
        else if (x < A[i])
        {
            r = i -1;
        }
        else 
        l = i + 1;

    }

    return -1;	
}


int busquedaBinariaRec(int A[],int l, int r, int x)
{   
    int i;

    if (l > r)
    {
        return -1;
    }
    i = l + (r-l)/2;
    if(x== A[i])
    {
        return i;
    }
    else if(x<A[i])
    {
        return busquedaBinariaRec(A,l, i-1,x);
    }
    else
    {
        return busquedaBinariaRec(A,i+1,r,x);
    }
    
    
}


int main(int argc, char const *argv[])
{
    const int n = 10;		//	Elementos totales
	int x;					//	Elemento a buscar
	
	int indexSeq, indexBin, indexBinRec;

	//	Arreglos: ordenado y desornado
	int sorted [n] =  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	
	int asorted [n] = { 8, 4, 1, 7, 9, 3, 5, 2, 10, 6 };

    //cin >> x;
    x = 4;

    int i;
	cout<<"Ordenado:\t";
	for (i = 0; i < n; i++) 	{	cout<<sorted[i]<<' '; } 
	cout<<endl;

	cout<<"Desordenado:\t";
	for (i = 0; i < n; i++) 	{	cout<<asorted[i]<<' '; } 
	cout<<endl<<endl;

    //Busqueda Secuencial con el array desordenado
    cout<< "Buscando x = " << x << " en asorted con busqueda secuencial: "<< endl;
	indexSeq = busquedaSecuencial(asorted, n, x);
	cout << "Resultado: " << indexSeq << " " << endl;
	cout << "Accesando: " << asorted[indexSeq] << endl<< endl;

    //Busqueda secuencial con el array ordenado
	cout << "Buscando x = " << x << " en sorted con busqueda secuencial: "<< endl;
	indexSeq = busquedaSecuencial(sorted, n, x);
	cout << "Resultado " << indexSeq <<endl;
	cout << "Accesando: " << sorted[indexSeq] << endl<< endl;

    //Busqueda Binaria
    int l = 0;
    int r = n- 1;

    //Iterativa
    cout << "Buscando x = " << x << " en sorted con busqueda binaria: "<<endl; ;
	indexBin = busquedaBinaria(sorted,l,r, n, x);
	cout << "Resultado  " << indexBin << endl;
    cout << "Accesando: " << sorted[indexBin] << endl<< endl;


    cout << "Buscando x = " << x << " en sorted con busq. binaria recursiva: "<<endl ;
	indexBinRec = busquedaBinariaRec(sorted, l, r, x);	
	cout << "Resultado  " << indexBinRec << endl;
    cout << "Accesando: " << sorted[indexBin] << endl<< endl;

    
}
