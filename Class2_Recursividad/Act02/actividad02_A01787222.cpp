//Jesus Leonardo Perez Guerrero A01787222
//Actividad 02

#include <iostream>
#include <stdio.h>

using namespace std;

//1. Metodo Iterativo
int sumaIterativa(int n) //Aqui haremos un while que acumulara n y despues le restamos 1 hasta que sea 0, entonces sumaria de n hasta 1
{
    int iterativo_res = 0;
    while(n!=0) // Si n no es 0 seguira acumulando
    {
        iterativo_res += n;
        n -= 1; //Le restamos 1 a n hasta que sea 0 y pare

    }

    return iterativo_res; //Regresamos la suma de n hasta 1
}

//2. Metodo recursivo
int sumaRecursiva(int n) //Aqui vamos a hacer una suma del numero n + (n-1) hasta que llegue n llegue a 0
{
    int recursivo_res = 0;
    if(n == 0) //Cuando sea 0 pare de sumar, es decir suma de n hasta 1
    {
        return 0;
    }
    else
    {
        recursivo_res = n + sumaRecursiva(n-1); //aquì hacemos la suma de n + la propia funcion para que se repita con n-1
        return recursivo_res;
    }
}

//3. Metodo Directo
int sumaDirecta(int n) //Aqui para hacer la suma directa, encontramos la siguiente formula f(n) = ((1 + n)*n)/2, esto daria el mismo resultado 
{
    int suma_directa = ((n+1)*n)/2;
    return suma_directa;
}

int main(int argc, char const *argv[])
{
    int n = 100;

    //Llamamos a todas las funciones, los 3 metodos
    int iterativa = sumaIterativa(n);
    int recursiva = sumaRecursiva(n);
    int directa = sumaDirecta(n);

    //Imprimimos
    cout <<"Con el metodo iterativo nos da: " << iterativa << endl;
    cout <<"Con el metodo recursivo nos da: " << recursiva << endl;
    cout <<"Con el metodo directo nos da: " << directa << endl;


}
