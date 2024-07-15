#include "Graph.h"

void BubbleSort(int* arr,int length){
    for(int i=0;i<length;++i){
        for(int j=0;j<length-1-i;++j){
            if(arr[j]>arr[j+1]){
                int temp{arr[j]};
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

int removeDuplicates(int* arr,int length){
    if(length==0||length==1)
        return length;
    int newLength{0};
    for(int i=0;i<length-1;i++)
        if(arr[i]!=arr[i+1])
            arr[newLength++]=arr[i];
    arr[newLength++]=arr[length-1];
    return newLength;
}

int Graph::notDiscovered(int num){
    for(int i=0;i<getLength();i++)
        if(discovered[i]==num)
            return 0;
    return 1;
}

void Graph::discoveredAdd(int num){
    for(int i=0;i<getLength();i++){
        if(discovered[i]==-1){
            discovered[i]=num;
            break;
        }
    }
}

void Graph::discoveredRemove(int num){
    for(int i=0;i<getLength();i++){
        if(discovered[i]==num)
            discovered[i]=-1;
    }
}

void Graph::clearNotDiscoverd(){
    int *newDiscovered=new int[getLength()];
    for(int i=0;i<getLength();++i)
        newDiscovered[i]=-1;
    //delete[] discovered;
    discovered=newDiscovered;
}

Graph::Graph(){}

void Graph::Build(){
    clearNotDiscoverd();
}

void Graph::setData(int *data,int length){
    this->data=new int[length];
    for(int i=0;i<length;++i)
        this->data[i]=data[i];
}

int* Graph::getData(){return data;}

void Graph::setLength(int length){this->length=length;}

int Graph::getLength(){return length;}

void Graph::setNodes1(int *data,int length){
    int newLength=length/3;
    this->nodes1=new int[newLength];
    for(int i=0;i<newLength;++i)
        this->nodes1[i]=data[3*i];
}

int* Graph::getNodes1(){return nodes1;}

void Graph::setNodes2(int *data,int length){
    int newLength=length/3;
    this->nodes2=new int[newLength];
    for(int i=0;i<newLength;++i)
        this->nodes2[i]=data[3*i+1];
}

int* Graph::getNodes2(){return nodes2;}

void Graph::setEdges(int *data,int length){
    int newLength=length/3;
    this->edges=new int[newLength];
    for(int i=0;i<newLength;++i)
        this->edges[i]=data[3*i+2];
}

int* Graph::getEdges(){return edges;}

int Graph::getDifferentNodes(){
    int allNodes[(getLength()/3)*2];
    for(int i=0;i<getLength()/3;++i)
        allNodes[i]=nodes1[i];
    for(int i=0;i<getLength()/3;++i)
        allNodes[(getLength()/3)+i]=nodes2[i];
    int differentNodes[(getLength()/3)*2];
    // initialize all to -100 (empty)
    for(int i=0;i<(getLength()/3)*2;++i)
        differentNodes[i]=-100;
    int newLength{0};
    int toAdd{};
    for(int i=0;i<(getLength()/3)*2;++i){
        toAdd=1;
        for(int j=0;j<((getLength()/3)*2)&&toAdd;++j)
            if(allNodes[i]==differentNodes[j])
                toAdd=0;
        if(toAdd==1)
            differentNodes[newLength++]=allNodes[i];
    }
    return newLength;
}

int Graph::getDifferentEdges(){
    int edgeLength{0};
    for(int i=0;i<getLength()/3;++i)
        ++edgeLength;
    return edgeLength;
}

void Graph::initializeSmallest(int num){smallest=num;}

int Graph::CSP(int from,int to,int sum){
    for(int i=0;i<getLength()/3;++i){
        if((nodes1[i]==from&&nodes2[i]==to)||(nodes1[i]==to&&nodes2[i]==from)){
            sum+=edges[i];
            if(sum<smallest){
                smallest=sum;
            }
            sum-=edges[i];
        }
        else if(nodes1[i]==from&&notDiscovered(nodes2[i])){
            discoveredAdd(nodes1[i]);
            CSP(nodes2[i],to,sum+edges[i]);
            discoveredRemove(nodes1[i]);
        }
        else if(nodes2[i]==from&&notDiscovered(nodes1[i])){
            discoveredAdd(nodes2[i]);
            CSP(nodes1[i],to,sum+edges[i]);
            discoveredRemove(nodes2[i]);
        }
    }
    return smallest;
}

int* Graph::getAllNodesSet(int &newLength){
    int *allNodes;
    allNodes=new int[(getLength()/3)*2];
    for(int i=0;i<getLength()/3;i++)
        allNodes[i]=nodes1[i];
    for(int i=0;i<getLength()/3;i++)
        allNodes[getLength()/3+i]=nodes2[i];
    BubbleSort(allNodes,(getLength()/3)*2);
    newLength=removeDuplicates(allNodes,(getLength()/3)*2);
    return allNodes;
}

int* Graph::getComponentNodes(int* currents,int currentsLength,int &newLength){
    int toContinue{0};
    for(int i=0;i<currentsLength;++i)
        if(notDiscovered(currents[i]))
            discoveredAdd(currents[i]);
    for(int j=0;j<currentsLength;++j){
        for(int i=0;i<getLength()/3;++i){
            if(nodes1[i]==currents[j]&&notDiscovered(nodes2[i])){
                discoveredAdd(nodes2[i]);
                toContinue=1;
            }
            if(nodes2[i]==currents[j]&&notDiscovered(nodes1[i])){
                discoveredAdd(nodes1[i]);
                toContinue=1;
            }
        }
    }
    int currentLength{0};
    for(int i=0;i<getLength();++i)
        if(discovered[i]!=-1)
            ++currentLength;
    int *currentComponents;
    currentComponents=new int[currentLength];
    int index=0;
    for(int i=0;i<getLength();++i)
        if(discovered[i]!=-1)
            currentComponents[index++]=discovered[i];
    newLength=currentLength;
    if(!toContinue)
        return currentComponents;

    int* result = getComponentNodes(currentComponents, currentLength, newLength);
    delete[] currentComponents;
    return result;
}

int Graph::FCC(int *uncheckedNodes,int uncheckedLength,int components){
    int *currentComponentNodes;
    int currentLength{0};
    int passedArray[1];
    passedArray[0]=uncheckedNodes[0];
    currentComponentNodes=getComponentNodes(passedArray,1,currentLength);
    int *newUncheckedNodes=new int[uncheckedLength];
    int newLength{0};
    for(int i=0;i<uncheckedLength;++i){
        int toAdd=1;
        for(int j=0;j<currentLength;++j){
            if(uncheckedNodes[i]==currentComponentNodes[j]){
                toAdd=0;
                break;
            }
        }
        if(toAdd)
            newUncheckedNodes[newLength++]=uncheckedNodes[i];
    }
    delete[] currentComponentNodes;
    if (newLength == 0) {
        delete[] newUncheckedNodes;
        return components;
    }
    int rs = FCC(newUncheckedNodes, newLength, components + 1);
    delete[] newUncheckedNodes;
    return rs;
}

void Graph::Insert(int number1,int number2,int weight,int& toAdd){
    toAdd=1;
    for(int j=0;j<getLength()/3;++j)
        if((nodes1[j]==number1&&nodes2[j]==number2)||(nodes1[j]==number2&&nodes2[j]==number1))
            toAdd=0;
    if(toAdd){
        int newLength{getLength()};
        newLength+=3;
        setLength(newLength);
        int *newNodes1;
        int *newNodes2;
        int *newEdges;
        newNodes1=new int[getLength()/3];
        newNodes2=new int[getLength()/3];
        newEdges=new int[getLength()/3];
        int i{0};
        for(i=0;i<(getLength()/3)-1;++i){
            newNodes1[i]=nodes1[i];
            newNodes2[i]=nodes2[i];
            newEdges[i]=edges[i];
        }
        newNodes1[i]=number1;
        newNodes2[i]=number2;
        newEdges[i]=weight;
        int newNodes[getLength()];
        for(int j=0;j<getLength()/3;++j)
        {
            newNodes[3*j]=newNodes1[j];
            newNodes[3*j+1]=newNodes2[j];
            newNodes[3*j+2]=newEdges[j];
        }
        setNodes1(newNodes,getLength());
        setNodes2(newNodes,getLength());
        setEdges(newNodes,getLength());
    }
}

void Graph::Delete(int number1,int number2,int& toAdd){
    toAdd=0;
    int index{};
    for(int j=0;j<getLength()/3;++j)
        if((nodes1[j]==number1&&nodes2[j]==number2)||(nodes1[j]==number2&&nodes2[j]==number1)){
            toAdd=1;
            index=j;
        }
    if(toAdd){
        int *newNodes1;
        int *newNodes2;
        int *newEdges;
        newNodes1=new int[getLength()/3-1];
        newNodes2=new int[getLength()/3-1];
        newEdges=new int[getLength()/3-1];
        for(int i=0;i<index;++i){
            newNodes1[i]=nodes1[i];
            newNodes2[i]=nodes2[i];
            newEdges[i]=edges[i];
        }
        for(int i=index+1;i<getLength()/3;++i){
            newNodes1[i-1]=nodes1[i];
            newNodes2[i-1]=nodes2[i];
            newEdges[i-1]=edges[i];
        }
        int newLength{getLength()-3};
        setLength(newLength);
        int newNodes[getLength()];
        for(int j=0;j<getLength()/3;++j)
        {
            newNodes[3*j]=newNodes1[j];
            newNodes[3*j+1]=newNodes2[j];
            newNodes[3*j+2]=newEdges[j];
        }
        setNodes1(newNodes,getLength());
        setNodes2(newNodes,getLength());
        setEdges(newNodes,getLength());
    }
}

int Graph::SmallestEdge(){
    int smallestEdge{10000};
    int index{};
    for(int i=0;i<getLength();++i){
        if(discovered[i]!=-1){
            for(int j=0;j<getLength()/3;++j){
                if(nodes1[j]==discovered[i]&&notDiscovered(nodes2[j])&&edges[j]<smallestEdge){
                    index=j;
                    smallestEdge=edges[j];
                }
                if(nodes2[j]==discovered[i]&&notDiscovered(nodes1[j])&&edges[j]<smallestEdge){
                    index=j;
                    smallestEdge=edges[j];
                }
            }
        }
    }
    if(notDiscovered(nodes1[index]))
        discoveredAdd(nodes1[index]);
    else if(notDiscovered(nodes2[index]))
        discoveredAdd(nodes2[index]);
    return smallestEdge;
}

// using Prim's algorithm
int Graph::MST(){
    int result{0};
    int *allNodes;
    int allNodesLength{0};
    allNodes=getAllNodesSet(allNodesLength);
    discoveredAdd(allNodes[0]);
    int discoveredCount{0};
    // it needs as many loops as the different node count - 1
    while (discoveredCount!=(allNodesLength-1)){
        ++discoveredCount;
        result+=SmallestEdge();
    }
    return result;
}
