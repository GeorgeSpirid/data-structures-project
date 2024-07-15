#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class Graph{
    // given array from file
    int *data;
    int length;
    int *nodes1;
    int *nodes2;
    int *edges;
    int *discovered;
    // for CSP
    int smallest;
public:
    Graph();
    void Build();
    void setData(int *data,int length);
    int* getData();
    void setLength(int length);
    int getLength();
    void setNodes1(int *data,int length);
    int* getNodes1();
    void setNodes2(int *data,int length);
    int* getNodes2();
    void setEdges(int *data,int length);
    int* getEdges();
    void initializeSmallest(int num);
    void discoveredAdd(int num);
    void discoveredRemove(int num);
    void clearNotDiscoverd();
    int getDifferentNodes();
    int getDifferentEdges();
    int CSP(int from,int to,int sum);
    int notDiscovered(int num);
    int* getAllNodesSet(int &newLength);
    int* getComponentNodes(int* currents,int currentsLength,int &newLength);
    int FCC(int *uncheckedNodes,int uncheckedLength,int components);
    void Insert(int number1,int number2,int weight,int& toAdd);
    void Delete(int number1,int number2,int& toAdd);
    int SmallestEdge();
    // minimum spanning tree
    int MST();
};

#endif // GRAPH_H
