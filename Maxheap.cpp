#include "Maxheap.h"

void HeapifyMax(int *data,int length,int index){
    int left{index*2+1};
    int right{index*2+2};
    int toSwap{index};
    if(left<length && data[left]>data[index])
        toSwap=left;
    if(right<length && data[right]>data[index] && data[right]>data[left])
        toSwap=right;
    int temp{};
    if(index!=toSwap){
        temp=data[index];
        data[index]=data[toSwap];
        data[toSwap]=temp;
        HeapifyMax(data,length,toSwap);
    }
}

MaxHeap::MaxHeap(){}

void MaxHeap::setData(int *data,int length){
    this->data=new int[length];
    for(int i=0;i<length;++i)
        this->data[i]=data[i];
}

int* MaxHeap::getData(){return data;}

void MaxHeap::setLength(int length){this->length=length;}

int MaxHeap::getLength(){return length;}

void MaxHeap::Build(){
    // length/2-1 is the last node with atleast one child
    for(int i=((length/2)-1);i>=0;--i){
        // heapify i: O(logn)
        HeapifyMax(data,length,i);
    }
    setData(data,length);
    setLength(length);
}

int MaxHeap::findMax(){return data[0];}

void MaxHeap::Insert(int n){
    // to add space for the new item
    setLength(++length);
    int *newData=new int[getLength()];
    newData=data;
    newData[getLength()-1]=n;
    // new item's index
    int index{getLength()-1};
    // loop for heaps length
    for(int i=0;i<(int)log2(getLength());++i){
        HeapifyMax(newData,getLength(),(index-1)/2);
        index=(index-1)/2;
    }
    setData(newData,getLength());
    setLength(getLength());
}

void MaxHeap::Delete(){
    // swap first and last item
    int temp{data[0]};
    data[0]=data[getLength()-1];
    data[getLength()-1]=temp;
    // reduce length by one to delete the last item
    setLength(getLength()-1);
    // length/2-1 is the last node with at least one child
    for(int i=((length/2)-1);i>=0;--i){
        // heapify i: O(logn)
        HeapifyMax(data,length,i);
    }
    setData(data,length);
}
