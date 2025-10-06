#include <iostream>

using namespace std;


int busquedaSec(int *A, int x, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(x == A[i])
        {
            return i;
        }
    }
    return -1;
}

int busquedaBinaria(int A[],int l, int r, int x)
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
        return busquedaBinaria(A,l, i-1,x);
    }
    else
    {
        return busquedaBinaria(A,i+1,r,x);
    }
    
    
}

// Merge
void merge(int *A, int l, int m, int r) 
{
    int s1 = m - l + 1; //Indice de la seccion 1
    int s2 = r - m; // Inidice de la seccion 2
    int *L = new int[s1]; //Crear un arreglo temporal con la seccion 1
    int *R = new int[s2]; //Crea un arreglo temporal con la seccion 2

    for (int i = 0; i < s1; i++)  //Copia todos los elementos del arreglo que pertenecen a la seccion 1
    {
        L[i] = A[l + i];
    } 
    
    for (int j = 0; j < s2; j++) //Copia todos los elementos del arreglo que pertencen a la seccion 2
    {
        R[j] = A[m + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < s1 && j < s2)  // Va comparando ambos arreglos el de la seccion 1 y la seccion 2
    {
        if (L[i] <= R[j]) //Aqui cambiaría a >= si fuera desc
        {
            A[k++] = L[i++];
        }
        else 
        {
            A[k++] = R[j++];
        }
    }
    while (i < s1) //Si quedan sobrante de la seccion 1 //Aqui cambiaría a > si fuera desc
    {
        A[k++] = L[i++];
    }
    while (j < s2) //Si quedan sobrantes de la seccion 2 //Aqui cambiaría a > si fuera desc
    {
         A[k++] = R[j++];
    }
    delete[] L;
    delete[] R;
}

// MergeSort
void mergeSort(int *A, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(A, l, m); //Junta los de la izquierda
        mergeSort(A, m + 1, r); //Junta los de la derecha
        merge(A, l, m, r); //Junta todo
    }
}

// Imprimir arreglo
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

int main() {
    int arr1[10] = {5, 2, 9, 1, 6, 3, 8, 4, 7, 0};
    int arr2[10] = {5, 2, 9, 1, 6, 3, 8, 4, 7, 0};
    int n = 10;

    // Merge Sort
    mergeSort(arr1, 0, n - 1);
    cout << "Ordenado con Merge Sort: ";
    printArray(arr1, n);
    
    int x = 4;
    int l = 0;
    int r = n-1;
    int busqueda = busquedaBinaria(arr1,l,r,x);
    if(busqueda == -1)
    {
         cout<<"El numero "<< x << " no está"<< endl;
    }
    else
    {
         cout<<"El numero "<< x << " esta en la posición " << busqueda<< endl;
    }

    return 0;
}
