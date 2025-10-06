// Compilar y ejecutar
//   g++ sortAlgorithms.cpp -o run.exe;  ./run.exe 



#include <iostream>
#include <cstdlib>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>



using std::cin;
using std::cout;
using std::endl;


//	Ordenamiento burbuja
void bubbleSort( int *A, int n)
{	int i;
	int j;
	int indexMin;

	for(i=0; i<n-1;i++)
	{
		bool change = false;
		for(j=0; j<n-1;j++)
		{
			if(A[j]>A[j+1])
			{
				
				int aux = A[j+1];
				A[j+1] = A[j];
				A[j] = aux;
				change = true;
			}
			
		}
		if(change==false)
			{
				break;
			}
	}
	return;
}


//	Ordenamiento por intercambio
void swapSort (int *A, int n)
{	
int i,j,aux;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(A[i]>A[j])
            {
                aux=A[i];
                A[i]=A[j];
                A[j]=aux;
            }
        }

    }
	return;
}



//	Ordenamiento por seleccion
void selectionSort(int *A, int n)
{	
	int i;
	int j;

	for(i = 0;i < n; i++)
	{
		int indexMin = i;
		for(j = i + 1; j < n; j++)
		{
			if(A[j]<A[indexMin])
			{
				indexMin = j;
			}
		}
		int Aux = A[indexMin];
		A[indexMin] = A[i];
		A[i] = Aux;
	}

    
    return;
}



//	Print the array
void printArray (int *A, int n)
{	int i;
	cout<<"Arreglo:\t";
	for (i = 0; i < n; i++)
	{	cout<<' '<<A[i];	}
	cout<<endl;

	return;
}

int main(int argc, char* argv[]) 
{	
	const int n = 10;						//	Elementos totales
	int asorted1 [n] = { 8, 4, 1, 7, 9, 3, 5, 2, 10, 6 };

	int asorted2 [n] = { 8, 4, 1, 7, 9, 3, 5, 2, 10, 6 };
	
	int asorted3 [n] = { 8, 4, 1, 7, 9, 3, 5, 2, 10, 6 };
	
	printArray(asorted1, n);
	
	cout << "\nSeleccion-Sort "<< endl;
	selectionSort(asorted1, n);
	printArray(asorted1, n);
	
	cout << "\n\nBubble-Sort "<< endl;
	bubbleSort(asorted2, n);
	printArray(asorted2, n);

	cout << "\n\nSwap-Sort "<< endl;
	swapSort(asorted3, n);
	printArray(asorted3, n);

}








