#include "cArray.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

#include <cstdlib>

using std::exit;

cArray::cArray(void) {

    vectorPointer = 0;
    count = size = 0;

}

cArray::~cArray() {

    delete [] vectorPointer;
    vectorPointer = 0;

}

int cArray::GetSize() const {

    return size;

}

int cArray::GetCount() const {

    return count;

}

int cArray::GetUpperBound() const {

    return count - 1;

}

bool cArray::IsEmpty() const {

    return (count == 0);

}

void cArray::SetSize(int nNewSize) {

    if (nNewSize == size)
        return;
    else {
        int* newVectorPointer = new int[nNewSize];
        size = nNewSize;

        if (nNewSize < count)
            count = nNewSize;

        for (int i = 0; i < count; ++i)
            newVectorPointer[i] = vectorPointer[i];

        delete [] vectorPointer;
        vectorPointer = newVectorPointer;
        newVectorPointer = 0;
    }

}

void cArray::FreeExtra() {

    if (size != count) {
        int* newVectorPointer = new int[count];
        size = count;

        for (int i = 0; i < count; ++i)
            newVectorPointer[i] = vectorPointer[i];

        delete [] vectorPointer;
        vectorPointer = newVectorPointer;
        newVectorPointer = 0;
    }

}

void cArray::RemoveAll() {

    count = 0;

}

int cArray::GetAt(int indx) const {

    if (indx >= 0 && indx <= count - 1)
        return vectorPointer[indx];

    cerr<<endl<<"Index "<<indx<<" out of bounds"<<endl<<endl;
    exit(1);
}

void cArray::SetAt(int n, int indx) {

    if (indx >= 0 && indx <= count - 1) {
        vectorPointer[indx] = n;
        return;
    }

    cerr<<endl<<"Index "<<indx<<" out of bounds"<<endl<<endl;
    exit(1);
}

void cArray::Add(int n) {

    if (count == size) {
        int* newVectorPointer = new int[size += GROWBY];
        //size += GROWBY;

        for (int i = 0; i < count; ++i)
            newVectorPointer[i] = vectorPointer[i];

        delete [] vectorPointer;
        vectorPointer = newVectorPointer;
        newVectorPointer = 0;
    }
    vectorPointer[count] = n;
    ++count;
}

void cArray::Append(cArray *ar) {



    if (size - count < ar->count) {
        int coef = (ar->count - (size - count)) / 10;
        if ( (ar->count - (size - count)) % 10 != 0)
            ++coef;

        int* newVectorPointer = new int[size += coef * GROWBY];
        //size += coef * GROWBY

        for (int i = 0; i < count; ++i)
            newVectorPointer[i] = vectorPointer[i];

        for (int i = 0; i < ar->count; ++i)
            newVectorPointer[count + i] = ar->vectorPointer[i];

        delete [] vectorPointer;
        vectorPointer = newVectorPointer;
        newVectorPointer = 0;
    }
    else {
        for (int i = 0; i < ar->count; ++i)
            vectorPointer[count + i] = ar->vectorPointer[i];
    }
    count += ar->count;
}

void cArray::Copy(cArray *ar) {

    int coef = ar->count / 10;
    if (ar->count % 10 != 0)
        ++coef;

    int* newVectorPointer = new int[size = coef * GROWBY];
    count = ar->count;

    for (int i = 0; i < count; ++i)
        newVectorPointer[i] = ar->vectorPointer[i];

    delete [] vectorPointer;
    vectorPointer = newVectorPointer;
    newVectorPointer = 0;

}

void cArray::InsertAt(int n, int indx) {

  if (indx >= 0 && indx <= count - 1) {
    if (count == size) {
        int* newVectorPointer = new int[size += GROWBY];
        //size += GROWBY;

        for (int i = 0; i < indx; ++i)
            newVectorPointer[i] = vectorPointer[i];
        newVectorPointer[indx] = n;

        for (int i = indx + 1; i < count + 1; ++i)
            newVectorPointer[i] = vectorPointer[i - 1];

        delete [] vectorPointer;
        vectorPointer = newVectorPointer;
        newVectorPointer = 0;
    }
    else {
        for (int i = count - 1; i >= indx; --i)
            vectorPointer[i + 1] = vectorPointer[i];
        vectorPointer[indx] = n;
    }
    ++count;
  }
  else {
      cerr<<endl<<"Index "<<indx<<" out of bounds"<<endl<<endl;
      exit(1);
  }
}

void cArray::RemoveAt(int indx) {

  if (indx >= 0 && indx <= count - 1) {
    for (int i = indx; i <= count - 2; ++i)
        vectorPointer[i] = vectorPointer[i + 1];

    --count;
  }
  else {
      cerr<<endl<<"Index "<<indx<<" out of bounds"<<endl<<endl;
      exit(1);
  }
}

int& cArray::operator [](int indx) {

    if (indx >= 0 && indx <= count - 1) {
        return vectorPointer[indx];
    }
    else {
        cerr<<endl<<"Index "<<indx<<" out of bounds"<<endl<<endl;
        exit(1);
    }
}

void cArray::print() {

    if (count != 0) {
        cout<<endl;

        for (int i = 0; i < count; ++i)
            cout<<vectorPointer[i]<<' ';
    }
    else {
        cout<<endl<<"Array is empty"<<endl<<endl;
    }

    cout<<endl<<endl;
    cout<<"Count: "<<GetCount()<<endl;
    cout<<"Size: "<<GetSize()<<endl;

}
