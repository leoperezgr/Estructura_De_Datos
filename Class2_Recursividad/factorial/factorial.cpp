#include <iostream>
#include <stdio.h>

using namespace std;

//Definicion recursiva
// n! = n * (n-1)!

int factorial(int n)
{
    cout<<"El valor de n es"<<n<<endl;
    int local_res;
    if (n==0) //0! = 1 (Por definicion)
    {
        return 1;
    }
    else
    {
        local_res = n * factorial(n-1);
        cout<< "local_res: "<< local_res<<endl;
        return local_res;
    }
    
}


int main(int argc, char const *argv[])
{
    int n = 5;
    int fact = factorial(n);
    cout <<"\nEl valor de "<<n<<"! es: "<<fact<<endl;
    
    int total = 1;
    while(n != 0)
    {
        total *= n;
        n = n-1;
    }
    
    cout << "\nEl total es: "<<total<<endl;
    
    
    
}
