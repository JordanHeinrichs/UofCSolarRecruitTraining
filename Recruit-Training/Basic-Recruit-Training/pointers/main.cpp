/*
First read through main() and make predictions on what the outpout of each variable will be where indicated.
After doing that add a function prototype at the top for a function called mySwap() that will return type void.
You will pass two variables in as argument, one will be the pointer p. The other one will be an interger pointer you make that points to the variable y.
In the function mySwap you will swap the values of the two arguments so the values are changed inside main()
*/

#include <iostream>

using namespace std;

void foo(int *a, int b);
void bar(int *a, int b);
void mySwap(int *p1, int *p2);

int main()
{
    int x = 3;
    int y = 4;
    int *p = &x;
    int *p2 = &y;

    mySwap(p, p2);

    //TODO in the line below predict what what is going to be output
    cout << "Predicted value of p: " /* << before mySwap: 0x61ff04 (address of X) after mySwap: 0x61ff04 (address of X) */ << endl;
    cout << "Actual value of p: " << p << endl;
    cout << "Predicted value &x: " /* << before mySwap: 0x61ff04 (address of X) after mySwap: 0x61ff04 (address of X) */ << endl;
    cout << "Actual value &x: " << &x << endl;
    cout << "Predicted value of *p: " /* << before mySwap: 3 after mySwap: 4*/ << endl;
    cout << "Actual value of *p: " << *p << endl;
    
    foo(p, x);
    
    cout << "Predicted value of *p: " /* << before mySwap: 42 after mySwap: 42 */ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of x: " /* << before mySwap: 42 after mySwap: 42*/ << endl;
    cout << "Actual value of x: " << x << endl;
    foo(p, y);

    cout << "Predicted value of *p: " /* << before mySwap: 42 after mySwap: 42 */ << endl;
    cout << "Actual value of *p: " << *p << endl;
    cout << "Predicted value of y: " /* << before mySwap: 4 after mySwap: 3*/ << endl;
    cout << "Actual value of y: " << y << endl;

    //start writing mySwap here
    
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

void mySwap(int *p1, int *p2)
{
    int temp = *p1;  // Store the value pointed to by p1 in a temporary variable
    *p1 = *p2;       // Update the value pointed to by p1 with the value pointed to by p2
    *p2 = temp;      // Update the value pointed to by p2 with the value stored in the temporary variable
}
