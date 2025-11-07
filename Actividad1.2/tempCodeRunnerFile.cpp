//Actividad 1.2 | Jesus Leonardo Perez Guerrero
/*
Realiza una aplicación en C++,  en donde dado n elementos de entrada que son almacenados en un arreglo de objetos, realice las siguientes funciones de ordenamiento. 
Debe ser posible parametrizar  si los elementos se ordenan de manera ascendente o descendente. 

Los objetos representarían items y sus precios: 


Iron Sword – 50 gold

Leather Armor – 75 gold

Health Potion – 10 gold

Mana Potion – 12 gold

Steel Shield – 60 gold

Bow & 20 Arrows – 40 gold

Magic Ring – 120 gold

Fire Spell Scroll – 30 gold

Traveler’s Boots – 25 gold

Amulet of Protection – 200 gold
*/

#include <iostream>
#include <string>

using namespace std;

class item //representa el articulo con nombre y precio
{
    private:
    string nombre;
    int precio;

    public:
    item() : nombre(""), precio(0) {}
    item(string nombre, int precio)
    {
        this->nombre = nombre;
        this->precio = precio;
    }
    
    //Getters
    string getNombre()
    {
        return nombre;
    }

    int getPrecio()
    {
        return precio;
    }

    //Mostrar info
    void info()
    {
        cout <<"Nombre: " << nombre <<"; Precio: "<< precio << " gold"<< endl;
    }
    //sobrecarga del operador
    bool operator>(const item& other)
    {
    return this->precio > other.precio;
    }

    bool operator<(const item &other) const
    {
        return this->precio < other.precio;
    }

    bool operator<=(const item &other) const
    {
        return this->precio <= other.precio;
    }

    bool operator>=(const item &other) const
    {
        return this->precio >= other.precio;
    }
};



//Bubble sort
void bubbleSort(item *A, int n, bool asc)
{	
    int i;
    int j;

    for(i = 0; i < n - 1; i++)
    {
        bool change = false;
        for(j = 0; j < n - i - 1; j++)
        {
            if(asc)
            {
                if(A[j].getPrecio() > A[j + 1].getPrecio())  //ascendente
                {
                    item aux = A[j + 1];
                    A[j + 1] = A[j];
                    A[j] = aux;
                    change = true;
                }
            }
            else
            {
                if(A[j].getPrecio() < A[j + 1].getPrecio())  //descendente
                {
                    item aux = A[j + 1];
                    A[j + 1] = A[j];
                    A[j] = aux;
                    change = true;
                }
            }
        }
        if(change == false)
        {
            break;
        }
    }
}

//Swap Sort
void swapSort(item* A, int n, bool asc)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (asc) 
            {
                if (A[i].getPrecio() > A[j].getPrecio()) {
                    item aux = A[i];
                    A[i] = A[j];
                    A[j] = aux;
                }
            } else {
                if (A[i].getPrecio() < A[j].getPrecio()) {
                    item aux = A[i];
                    A[i] = A[j];
                    A[j] = aux;
                }
            }
        }
    }
}

//Selection Sort
void selectionSort(item* A, int n, bool asc)
{
    for (int i = 0; i < n - 1; i++)
    {
        int idx = i;  //indice del mínimo o máximo
        for (int j = i + 1; j < n; j++)
        {
            if (asc) {
                if (A[j].getPrecio() < A[idx].getPrecio()) {
                    idx = j;
                }
            } else {
                if (A[j].getPrecio() > A[idx].getPrecio()) {
                    idx = j;
                }
            }
        }
        if (idx != i) {
            item aux = A[i];
            A[i] = A[idx];
            A[idx] = aux;
        }
    }
}

//Instertion Sort
void insertionSort(item* A, int n, bool asc)
{
    for (int i = 1; i < n; i++)
    {
        item key = A[i];
        int j = i - 1;

        if (asc) {
            //ascendente
            while (j >= 0 && A[j].getPrecio() > key.getPrecio())
            {
                A[j + 1] = A[j];
                j--;
            }
        } else {
            //descendente
            while (j >= 0 && A[j].getPrecio() < key.getPrecio())
            {
                A[j + 1] = A[j];
                j--;
            }
        }
        A[j + 1] = key;
    }
}

//Merge
void merge(item* A, int l, int m, int r, bool asc)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    item* L = new item[n1];
    item* R = new item[n2];

    for (int i = 0; i < n1; i++) L[i] = A[l + i];
    for (int j = 0; j < n2; j++) R[j] = A[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2)
    {
        if (asc) 
        {
            if (L[i].getPrecio() <= R[j].getPrecio()) {
                A[k++] = L[i++];
            } else 
            {
                A[k++] = R[j++];
            }
        } else 
        {
            if (L[i].getPrecio() >= R[j].getPrecio()) 
            {
                A[k++] = L[i++];
            } else 
            {
                A[k++] = R[j++];
            }
        }
    }

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(item* A, int l, int r, bool asc)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(A, l, m, asc);
        mergeSort(A, m + 1, r, asc);
        merge(A, l, m, r, asc);
    }
}

//QuickSort
int partitionAsc(item* A, int l, int r)
{
    item pivot = A[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        if (A[j].getPrecio() < pivot.getPrecio())
        {
            i++;
            item aux = A[i]; A[i] = A[j]; A[j] = aux;
        }
    }
    item aux = A[i + 1]; A[i + 1] = A[r]; A[r] = aux;
    return i + 1;
}

int partitionDesc(item* A, int l, int r)
{
    item pivot = A[r];
    int i = l - 1;
    for (int j = l; j <= r - 1; j++)
    {
        if (A[j].getPrecio() > pivot.getPrecio())
        {
            i++;
            item aux = A[i]; A[i] = A[j]; A[j] = aux;
        }
    }
    item aux = A[i + 1]; A[i + 1] = A[r]; A[r] = aux;
    return i + 1;
}

void quickSortRecAsc(item* A, int l, int r)
{
    if (l < r)
    {
        int p = partitionAsc(A, l, r);
        quickSortRecAsc(A, l, p - 1);
        quickSortRecAsc(A, p + 1, r);
    }
}

void quickSortRecDesc(item* A, int l, int r)
{
    if (l < r)
    {
        int p = partitionDesc(A, l, r);
        quickSortRecDesc(A, l, p - 1);
        quickSortRecDesc(A, p + 1, r);
    }
}

void quickSort(item* A, int n, bool asc)
{
    if (asc) 
    {
        quickSortRecAsc(A, 0, n - 1);
    } else 
    {
        quickSortRecDesc(A, 0, n - 1);
    }
}

//Pedimos el algoritmo
int pedirAlgoritmo() {
    int algo;
    string algoritmos[] = 
    {
        "Bubble Sort","Swap Sort","Selection Sort",
        "Insertion Sort","Merge Sort","Quick Sort"
    };

    cout << "\nElige un algoritmo de ordenamiento:\n";
    for (int i = 0; i < 6; i++) 
    {
        cout << i + 1 << ". " << algoritmos[i] << '\n';
    }

    cout << "Opcion: ";
    cin >> algo;
    while (algo <= 0 || algo >= 7) {
        cout << "No se encuentra, intenta de nuevo: ";
        cin >> algo;
    }

    cout << "Elegiste: " << algoritmos[algo - 1] << '\n';
    return algo;
}

//Pedire direccion
bool direccion()
{
    string direc;
    cout << "Ascendente o Descendente A/D: ";
    cin>> direc;
    while (!(direc == "A" || direc == "a"|| direc == "d" || direc == "D"))
    {
        cout << "No se encuentra, intenta de nuevo (A/D): ";
        cin >> direc;
    }

    if(direc == "A" || direc == "a")
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{   
    item i1 ("Sword", 50);
    item i2 ("Leather Armor", 75);
    item i3 ("Health Potion", 10);
    item i4 ("Mana Potion",12);
    item i5 ("Steel Shield", 60);
    item i6 ("Bow and 20 Arrows",40);
    item i7 ("Magic Ring",120);
    item i8 ("Fire Spell Scroll",30);
    item i9 ("Traveler’s Boots",25);
    item i10 ("Amulet of Protection",200);

    const int n = 10;

    item store[n] = { i1, i2, i3, i4, i5, i6, i7, i8, i9, i10 }; //Generamos el arreglo de objetos

    cout<< "Lista no ordenada: ";
    for(int i = 0; i < n; i++)
    {
        store[i].info();
    }

    int algo = pedirAlgoritmo();
    bool direc = direccion();

    if (algo == 1) {
    bubbleSort(store, n, direc);
    }
    else if (algo == 2) {
        swapSort(store, n, direc);
    }
    else if (algo == 3) {
        selectionSort(store, n, direc);
    }
    else if (algo == 4) {
        insertionSort(store, n, direc);
    }
    else if (algo == 5) {
        mergeSort(store, 0, n - 1, direc);
    }
    else { //entonces es 6
        quickSort(store, n, direc);
    }

    cout << "\nLista ordenada:\n";
    for (int i = 0; i < n; i++) {
        store[i].info();
    }

    return 0;
    
}

