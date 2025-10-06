// Compilar y ejecutar
//   g++ demoSearch.cpp -o executor; 
//   ./executor.exe  ( if you dont use windows, just ./executor ) 

// 	One liner para actualizar el ejecutable y correr 
//   rm ./executor.exe; g++ demoSearch.cpp -o executor; ./executor.exe 5


#include <iostream>
#include <cstdlib>
#include <vector>

using std::cin;
using std::cout;
using std::endl;



int busquedaBinariaRec(int A[], int l, int r, int x)
{	
	return -1;	
}


int busquedaBinaria(int A[], int n, int x)
{   
	return -1;
}

// 
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


int main(int argc, char* argv[]) 
{	
	const int n = 10;		//	Elementos totales
	int x;					//	Elemento a buscar
	
	int indexSeq, indexBin, indexBinRec;

	//	Arreglos: ordenado y desornado
	int sorted [n] =  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };	
	int asorted [n] = { 8, 4, 1, 7, 9, 3, 5, 2, 10, 6 };

	//	Otras formas validas de inicializar
	//	Para mas info: https://cplusplus.com/doc/tutorial/arrays/
	//int a[n];
	//int a [n] = { };
	//int a[] = {1,2,3};
	//int a[] { 10, 20, 30 };
	
	//x = atoi(argv[1]);		//	Valor a buscar, leido desde consola
	cin >> x;
	//x = 4;


	//	Imprimir los arreglos donde se buscara
	int i;
	cout<<"Ordenado:\t";
	for (i = 0; i < n; i++) 	{	cout<<sorted[i]<<' '; } 
	cout<<endl;

	cout<<"Desordenado:\t";
	for (i = 0; i < n; i++) 	{	cout<<asorted[i]<<' '; } 
	cout<<endl;

	
	// cout<<"\nBuscando:\t"<< x <<endl;

	cout<< "Buscando x = " << x << " en asorted con busq. secuencial: "<< endl;
	indexSeq = busquedaSecuencial(asorted, n, x);
	cout << "Resultado: " << indexSeq << " " << endl;
	cout << "Accesando: " << asorted[indexSeq] << endl<< endl;




	cout << "Buscando x = " << x << " en sorted con busq. secuencial: "<< endl;
	indexSeq = busquedaSecuencial(sorted, n, x);
	cout << "Resultado " << indexSeq <<endl;
	cout << "Accesando: " << sorted[indexSeq] << endl<< endl;




	// cout << "Buscando x = " << x << " en sorted con busq. binaria: " ;
	// indexBin = busquedaBinaria(sorted, n, x);
	// cout << "Resultado  " << indexBin << endl<<endl;



	// cout << "Buscando x = " << x << " en sorted con busq. binaria recursiva: " ;
	// indexBinRec = busquedaBinariaRec(sorted, 0, n-1 , x);	
	// cout << "Resultado  " << indexBinRec << endl<< endl;

}
