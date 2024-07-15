#include "Minheap.h"

void HeapifyMin(int *data,int length,int index){
    int left{index*2+1};
    int right{index*2+2};
    int toSwap{index};
    if(left<length && data[left]<data[index])
        toSwap=left;
    if(right<length && data[right]<data[index] && data[right]<data[left])
        toSwap=right;
    int temp{};
    if(index!=toSwap){
        temp=data[index];
        data[index]=data[toSwap];
        data[toSwap]=temp;
        HeapifyMin(data,length,toSwap);
    }
}

MinHeap::MinHeap(){}

void MinHeap::setData(int *data,int length){
    this->data=new int[length];
    for(int i=0;i<length;++i)
        this->data[i]=data[i];
}

int* MinHeap::getData(){return data;}

void MinHeap::setLength(int length){this->length=length;}

int MinHeap::getLength(){return length;}

void MinHeap::Build(){
    // length/2-1 is the last node with atleast one child
    for(int i=((length/2)-1);i>=0;--i){
        // heapify i: O(logn)
        HeapifyMin(data,length,i);
    }
    setData(data,length);
    setLength(length);
}

int MinHeap::findMin(){return data[0];}

void MinHeap::Insert(int n){
    // to add space for the new item
    setLength(++length);
    int *newData=new int[getLength()];
    newData=data;
    newData[getLength()-1]=n;
    // new item's index
    int index{getLength()-1};
    // loop for heaps length
    for(int i=0;i<(int)log2(getLength());++i){
        HeapifyMin(newData,getLength(),(index-1)/2);
        index=(index-1)/2;
    }
    setData(newData,getLength());
    setLength(getLength());
}

void MinHeap::Delete(){
    // swap first and last item
    int temp{data[0]};
    data[0]=data[getLength()-1];
    data[getLength()-1]=temp;
    // reduce length by one to delete the last item
    setLength(getLength()-1);
    // length/2-1 is the last node with at least one child
    for(int i=((length/2)-1);i>=0;--i){
        // heapify i: O(logn)
        HeapifyMin(data,length,i);
    }
    setData(data,length);
}
