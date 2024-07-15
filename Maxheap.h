#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

void HeapifyMax(int *data,int length,int index);

class MaxHeap{
    int *data;
    int length;
public:
    MaxHeap();
    void setData(int *data,int length);
    int* getData();
    void setLength(int length);
    int getLength();
    void Build();
    int findMax();
    void Insert(int n);
    void Delete();
};

#endif // MAXHEAP_H
