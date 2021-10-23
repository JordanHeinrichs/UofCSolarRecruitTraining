#include <iostream>
/*
First read through main() and make predictions on what the output of each variable will be where indicated.
After doing that add a function prototype at the top for a function called mySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an integer pointer you make that points to the variable y.
In the function mySwap you will swap the values of the two arguments so the values are changed inside main()
*/
using namespace std;

void foo(int *a, int b);
void bar(int *a, int b);
void mySwap(int *a, int *b);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;
    int *j = &y;

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: "  << "&x (which is a memory address)" << endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: "  << "the memory address of x" << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: "  << "3" << endl;
    cout << "Actual value of *p: " << *p << endl;

    foo(p, x);

    cout << "Predicted value of *p: "  << "42" << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: " "42" << endl;
    cout << "Actual value of x: " << x << endl;
    foo(p, y);

    cout << "Predicted value of *p: " "42" << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: " "4" << endl;
    cout << "Actual value of y: " << y << endl;

    //start writing mySwap here
    mySwap(p, j);
    cout << *p << endl;
    cout << *j << endl;

    return 0;
}

void foo(int *a, int b)
{
    *a = 42;
    b = 78;
}

void var(int *a, int b)
{
    *a = 365;
    b = 912;
}

void mySwap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}



