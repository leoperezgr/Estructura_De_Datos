#include <iostream>
#include <stdio.h>

using namespace std;


int fibo(int n)
{
    int local_res =0;
    if(n==0)
    {
        return 0;
    }
    if (n==1)
    {
        return 1;
    }
    else
    {
        local_res = fibo(n-1) + fibo(n-2);  //f(n) = f(n-1) + f(n-2)
        cout<< local_res<<endl;
        return local_res;
    }

}


int main(int argc, char const *argv[])
{
    int n=5;
    int resultado = fibo(n);

    int fibo_tail(int n, int base1,int base2)
    {
        if (n==0)
        {
            return base1;
        }
        else if (n==1)
        {
            return base2;
        }
    }

    cout<<resultado<<endl;
}