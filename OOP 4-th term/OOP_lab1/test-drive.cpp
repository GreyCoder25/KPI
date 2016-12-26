#include "cArray.h"

#include <iostream>

using std::cout;
using std::endl;

int main()
{
    //Let's create an object
    cout<<"Creating an empty array(A):"<<endl;
    cArray A;
    //and test how constructor works
    A.print();
    //Now let's make the size of the array - 4
    cout<<"Setting the size of array to 4:"<<endl;
    A.SetSize(4);
    A.print();
    cout<<"Adding new elements:"<<endl;
    //and add some elements
    A.Add(5);
    A.Add(7);
    A.Add(9);
    A.print();
    //now we'll check reallocation
    cout<<"Adding two more elements for checking reallocation correctness:"<<endl;
    A.Add(10);
    A.Add(14);
    A.print();
    //deallocation of extra elements
    cout<<"deallocation the extra elements space:"<<endl;
    A.FreeExtra();
    A.print();

    A.SetSize(10);
    A.print();

    cout<<"Creating one more array(B): "<<endl;
    //Let's create one more object
    cArray B;
    B.SetSize(7);
    B.Add(3);
    B.Add(19);
    B.Add(4);
    B.print();

    cout<<"Append B to A twice:"<<endl;
    A.Append(&B);
    A.print();
    A.Append(&B);
    A.print();

    cout<<"Creating the third array:"<<endl;
    cArray C;
    C.print();
    cout<<"Making array C the copy of A:"<<endl;
    C.Copy(&A);
    C.print();

    cout<<"Checking insert-operation on array B:"<<endl;
    B.InsertAt(55, 2);
    B.print();
    cout<<"Checking insert-operation on array B:"<<endl;
    B.RemoveAt(1);
    B.print();

    cout<<"Removing all elements from the array B:"<<endl;
    B.RemoveAll();
    B.print();
    B.FreeExtra();
    B.print();
    //cout<<A.GetUpperBound()<<endl;
    //cout<<A.IsEmpty()<<endl;

}
