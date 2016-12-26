#ifndef CARRAY_H
#define CARRAY_H

/*!
 * file: cArray.h
 * cArray class declaration
 * written: 23/02/2016
 * Copyright (c) 2016 by Se.Latyuk
 */

#include <string.h>
#include <stdio.h>

class cArray{
//The minimum number of element slots to allocate if a size increase is necessary.
#define GROWBY 10
public:
    //Constructs an empty array.
    cArray(void);
    ~cArray(void);

        //Attributes
    //Gets the number of elements in this array.
    int GetSize() const;
    //Gets the number of elements in this array.
    int GetCount() const;


    //Returns the largest valid index.
    int GetUpperBound() const;
    //Determines whether the array is empty.
    bool IsEmpty()const;
    //Establishes the size of an empty or existing array; allocates memory if necessary.
    void SetSize( int nNewSize );

        //Operations
    //Frees all unused memory above the current upper bound.
    //This function has no effect on the upper bound of the array.
    void FreeExtra();

    //Removes all the elements from this array.
    void RemoveAll();

        //Element Access
    //Returns the value at a given index.
    int GetAt(int )const;
    //Sets the value for a given index; array not allowed to grow.
    void SetAt(int n, int indx);

        //Growing the Array
    //Adds an element to the end of the array; grows the array if necessary.
    void Add(int);
    //Appends another array to the array; grows the array if necessary
    void Append(cArray *);
    //Copies another array to the array; grows the array if necessary.
    void Copy(cArray *);

        //Insertion/Removal
    //Inserts an element at a specified index.
    void InsertAt(int n, int indx);
    //Removes an element at a specific index.
    void RemoveAt(int );

    //Operators
    //Sets or gets the element at the specified index.
    int& operator [](int);

    void print();
private:
    int count;
    int size;
    int* vectorPointer;

};


#endif // CARRAY_H
