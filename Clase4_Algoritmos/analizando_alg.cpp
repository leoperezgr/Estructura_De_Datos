#include <iostream>
using namespace std;


int pows(int n, int a)
{
    int aux = 0;
    if(n==0)
    {
        return 1;
    }
    else if(n%2==0)
    {
        aux = pows(n/2,a);
        return aux * aux;
    }
    else
    {
        aux = pows((n-1)/2,a);
        return aux * aux *a;
    }
    
}



int main(int argc, char const *argv[])
{
    int n= 6;
    int a=2;

    cout<< pows(n,a)<<endl;
    
}
