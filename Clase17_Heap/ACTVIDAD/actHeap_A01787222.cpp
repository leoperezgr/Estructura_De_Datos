#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

template <class T>
class Heap 
{	public:
    T *data;				 				
    int maxSize;
    int currentSize; 

    Heap (int n)
    {
      maxSize = n;
      currentSize = 0;
      data = new T[maxSize];
    }

    ~Heap() 
    {
      delete[] data;
      maxSize = 0; 
      currentSize = 0;
    }		

    bool isEmpty();
    bool isFull();
    T getTop();
    int	parent(int);
    int left(int);
    int right(int);
    void push(T);
    T pop();
    void heapify(int);
    void swap(int, int);
    void show();
};

template <class T>
bool Heap<T>::isEmpty()
{
  //O(1)
  return currentSize == 0;
}

template <class T>
bool Heap<T>::isFull()
{
  //O(1)
  return currentSize == maxSize;
}

template <class T>
T Heap<T>::getTop()
{
  // O(1)
  if (!this->isEmpty())
  {
    return data[0];
  }
  else
  {
    cout << "Error: heap vacio\n";
  }
}

template <class T>
int Heap<T>::parent(int j)
{
  //O(1)
  int p = (j - 1) / 2;
  return p;
}

template <class T>
int Heap<T>::left(int j)
{
  //O(1)
  int l = 2*j + 1;
  return l;
}

template <class T>
int Heap<T>::right(int j)
{
  // O(1)
  int r = 2*j + 2;
  return r;
}

template <class T>
void Heap<T>::push(T value)
{
  // O(log n)
  if (!this->isFull())
  {
    int j = currentSize;
    int p = parent(j);

    while (j > 0 && value < data[p])
    {
      data[j] = data[p];
      j = p;
      p = parent(j);
    }

    data[j] = value;
    currentSize++;
  }
  else
  {
    cout << "Error: heap lleno\n";
  }
}

template <class T>
void Heap<T>::swap(int a, int b)
{
  //O(1)
  T aux = data[a];
  data[a] = data[b];
  data[b] = aux;
}

template <class T>
void Heap<T>::heapify(int index)
{
	// O(log n)
	while (true)
	{
		int l = left(index);
		int r = right(index);
		int i = index;

		if (l < currentSize && data[l] < data[i])
		{
			i = l;
		}
		if (r < currentSize && data[r] < data[i])
		{
			i = r;
		}

		if (i == index)
		{
			break;
		}

		swap(index, i);
		index = i;
	}
}

template <class T>
T Heap<T>::pop()
{
  // O(log n)
  if (!this->isEmpty())
  {
    T minVal = data[0];
    T last = data[currentSize - 1];
    currentSize--;

    if (currentSize == 0)
    {
      return minVal;
    }

    int j = 0;
    int l = left(j);

    while (l < currentSize)
    {
      int r = right(j);
      int c = l;

      if (r < currentSize && data[r] < data[l])
      {
        c = r;
      }

      if (last <= data[c])
      {
        break;
      }

      data[j] = data[c];
      j = c;
      l = left(j);
    }

    data[j] = last;
    return minVal;
  }
  else
  {
    cout << "Error: heap vacio\n";
    exit(1);
  }
}
template <class T>
void Heap<T>::show()
{
  // O(n)
  int i;
  int level = 0;
  cout << "Size: " << currentSize << endl;

  i = pow(2, level);
  while (i - 1 < currentSize)
  {
    cout << "\t" << data[i - 1] << "(" << level << ")";
    i++;
    if ((i) == pow(2, level + 1))
    {
      cout << endl;
      level++;
    }
  }
  cout << endl;
}

int main(int, char**) 
{
  int n = 20;
  Heap<int> heap(n);

  cout<<"1.- Agregar los elementos: 2, 1, 5, 7, 9, 8, 4, 3, 6, 7"<<endl;
  int inicial[] = {2,1,5,7,9,8,4,3,6,7};
  for (int x : inicial) 
  {
    heap.push(x); 
  }
  heap.show();

  cout<<"2. Eliminar el valor en el top. "<<endl;
  heap.pop(); heap.show();

  cout <<"3.- Agregar los valores 3, 1 y 4."<<endl;
  heap.push(3); heap.show();
  heap.push(1); heap.show();
  heap.push(4); heap.show();

  cout <<"4.- Extraer los valores del montículo hasta que quede vacío. Muestra los valores extraídos. Deberían aparecer en orden ascendente. "<<endl;
  cout << "Valores extraidos (ascendente):";
  while (!heap.isEmpty())
  {
    cout << ' ' << heap.pop();
  }
  cout << '\n';

  return 0;
}