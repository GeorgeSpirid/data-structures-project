#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void HeapifyMin(int *data,int length,int index);

class MinHeap{
    int *data;
    int length;
public:
    MinHeap();
    void setData(int *data,int length);
    int* getData();
    void setLength(int length);
    int getLength();
    void Build();
    int findMin();
    void Insert(int n);
    void Delete();
};

#endif // MINHEAP_H
