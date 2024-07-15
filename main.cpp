#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "Minheap.h"
#include "Maxheap.h"
#include "Graph.h"
#include "AVLTree.h"
#include "Hashtable.h"

using namespace std;

int* getData(int& returningLength,string filename){
    ifstream infile;
    infile.open(filename);
    if(!infile.is_open())
        cout<<"Couldn't open file to build min heap...";
    else{
        // initial capacity of array
        int capacity{10};
        int* data=new int[capacity];
        // how many numbers we have
        int length{0};
        int n{};
        while(infile>>n){

            if(length==capacity){
                // create new temporary array
                int *temp;
                capacity+=10;
                temp=new int[capacity];
                for(int i=0;i<length;++i)
                    temp[i]=data[i];
                delete[] data;
                data=temp;
            }
            data[length++]=n;
        }
        returningLength=length;
        return data;
        infile.close();
    }
    return 0;
}

int main()
{
    ifstream commands("commands.txt");
    ofstream output("output.txt");
    // try to open the 'commands.txt' and 'output.txt' file
    if(!commands.is_open()||!output.is_open())
        cout<<"Could not open file 'commands.txt'...";
    else{
        string line;
        // create each data structs (empty) to be in scope of all actions
        MinHeap minHeap;
        MaxHeap maxHeap;
        Graph graph;
        AVLTree avlTree;
        HashTable* hashTable = nullptr;
        /* every line is a command */
        while(getline(commands,line)){
            /* array of strings (5 max because of the command types)
            where each string represents a word of each line*/
            string words[5];
            // how many words we have in each sentence
            int wordcount{0};
            // each word can be at most of 100 characters
            char word[100];
            // index to put the new letter in the word
            int index{0};
            for(int i=0;i<(int)line.length();i++){
                if (line[i]==' '){
                    // to not start with empty characters ex. "  BUILD..."
                    if(index>0){
                        // end of the word
                        word[index]='\0';
                        // to make char* to string with 'string.assign(char *)'
                        words[wordcount++].assign(word);
                        index=0;
                    }
                }
                else{
                    word[index++]=line[i];
                }
            }
            if (index>0){
                // check for last word
                word[index]='\0';
                words[wordcount++].assign(word);
            }
            // MINHEAP
            if(words[1]=="MINHEAP"){
                if(words[0]=="BUILD"){
                    // words[2] is the filename we want
                    int length{};
                    int *data;
                    data = getData(length,words[2]);
                    // initialize data given from filename
                    minHeap.setData(data,length);
                    // initialize length
                    minHeap.setLength(length);
                    minHeap.Build();
                    int *newData;
                    newData=minHeap.getData();
                    output<<"Build MinHeap: ";
                    for(int i=0;i<minHeap.getLength();++i)
                        output<<newData[i]<<' ';
                }
                else if(words[0]=="GETSIZE"){
                    output<<"MinHeap size: "<<minHeap.getLength();
                }
                else if(words[0]=="FINDMIN"){
                    output<<"MinHeap min: "<<minHeap.findMin();
                }
                else if(words[0]=="INSERT"){
                    // words[2] is the number we want to insert
                    int number = stoi(words[2]);
                    minHeap.Insert(number);
                    int *newData;
                    newData=minHeap.getData();
                    output<<"New MinHeap after insertion of "<<number<<": ";
                    for(int i=0;i<minHeap.getLength();++i)
                        output<<newData[i]<<' ';
                }
                else if(words[0]=="DELETEMIN"){
                    minHeap.Delete();
                    int *newData;
                    newData=minHeap.getData();
                    output<<"New MinHeap after deleting min: ";
                    for(int i=0;i<minHeap.getLength();++i)
                        output<<newData[i]<<' ';
                }
            }
            // MAXHEAP
            if(words[1]=="MAXHEAP"){
                if(words[0]=="BUILD"){
                    // words[2] is the filename we want
                    int length{};
                    int *data;
                    data = getData(length,words[2]);
                    // initialize data given from filename
                    maxHeap.setData(data,length);
                    // initialize length
                    maxHeap.setLength(length);
                    maxHeap.Build();
                    int *newData;
                    newData=maxHeap.getData();
                    output<<"Build MaxHeap: ";
                    for(int i=0;i<maxHeap.getLength();++i)
                        output<<newData[i]<<' ';
                }
                else if(words[0]=="GETSIZE"){
                    output<<"MaxHeap size: "<<maxHeap.getLength();
                }
                else if(words[0]=="FINDMAX"){
                    output<<"MaxHeap max: "<<maxHeap.findMax();
                }
                else if(words[0]=="INSERT"){
                    // words[2] is the number we want to insert
                    int number = stoi(words[2]);
                    maxHeap.Insert(number);
                    int *newData;
                    newData=maxHeap.getData();
                    output<<"New MaxHeap after insertion of "<<number<<": ";
                    for(int i=0;i<maxHeap.getLength();++i)
                        output<<newData[i]<<' ';
                }
                else if(words[0]=="DELETEMAX"){
                    maxHeap.Delete();
                    int *newData;
                    newData=maxHeap.getData();
                    output<<"New MaxHeap after deleting min: ";
                    for(int i=0;i<maxHeap.getLength();++i)
                        output<<newData[i]<<' ';
                }
            }
            // GRAPH
            if(words[1]=="GRAPH"){
                if(words[0]=="BUILD"){
                    // words[2] is the filename we want
                    int length{};
                    int *data;
                    data = getData(length,words[2]);
                    // initialize data given from filename
                    graph.setData(data,length);
                    graph.setLength(length);
                    int *newData;
                    newData=graph.getData();
                    graph.Build();
                    graph.setNodes1(newData,graph.getLength());
                    graph.setNodes2(newData,graph.getLength());
                    graph.setEdges(newData,graph.getLength());
                    int *nodes1;
                    nodes1=graph.getNodes1();
                    int *nodes2;
                    nodes2=graph.getNodes2();
                    int *edges;
                    edges=graph.getEdges();
                    output<<"Build Graph: ";
                    output<<"Nodes 1: ";
                    for(int i=0;i<graph.getLength()/3;++i)
                        output<<nodes1[i]<<' ';
                    output<<", Nodes 2: ";
                    for(int i=0;i<graph.getLength()/3;++i)
                        output<<nodes2[i]<<' ';
                    output<<", Edges: ";
                    for(int i=0;i<graph.getLength()/3;++i)
                        output<<edges[i]<<' ';
                }
                else if(words[0]=="GETSIZE"){
                    output<<"Graph's size: Nodes: "<<graph.getDifferentNodes();
                    output<<", Edges: "<<graph.getDifferentEdges();
                }
                else if(words[0]=="COMPUTESHORTESTPATH"){
                    graph.initializeSmallest(100000);
                    graph.clearNotDiscoverd();
                    int number1 = stoi(words[2]);
                    int number2 = stoi(words[3]);
                    if(graph.CSP(number1,number2,0)==100000)
                        output<<number1<<" and "<<number2<<" are not connected";
                    else{
                        output<<"Shortest Path between "<<number1<<" and "<<number2<<" : ";
                        output<<graph.CSP(number1,number2,0);
                    }
                }
                else if(words[0]=="INSERT"){
                    int number1 = stoi(words[2]);
                    int number2 = stoi(words[3]);
                    int weight = stoi(words[4]);
                    int toAdd{0};
                    graph.Insert(number1,number2,weight,toAdd);
                    if(toAdd){
                        int *nodes1;
                        nodes1=graph.getNodes1();
                        int *nodes2;
                        nodes2=graph.getNodes2();
                        int *edges;
                        edges=graph.getEdges();
                        output<<"Insert "<<number1<<" with "<<number2<<" and weight "<<weight<<": ";
                        output<<"Nodes 1: ";
                        for(int i=0;i<graph.getLength()/3;++i)
                            output<<nodes1[i]<<' ';
                        output<<", Nodes 2: ";
                        for(int i=0;i<graph.getLength()/3;++i)
                            output<<nodes2[i]<<' ';
                        output<<", Edges: ";
                        for(int i=0;i<graph.getLength()/3;++i)
                            output<<edges[i]<<' ';
                    }
                    else
                        output<<"Edge between "<<number1<<" and "<<number2<<" already exists.";
                }
                else if(words[0]=="DELETE"){
                    int number1 = stoi(words[2]);
                    int number2 = stoi(words[3]);
                    int toAdd{0};
                    graph.Delete(number1,number2,toAdd);
                    if(toAdd){
                        int *nodes1;
                        nodes1=graph.getNodes1();
                        int *nodes2;
                        nodes2=graph.getNodes2();
                        int *edges;
                        edges=graph.getEdges();
                        output<<"Delete edge "<<number1<<" with "<<number2<<": ";
                        output<<"Nodes 1: ";
                        for(int i=0;i<graph.getLength()/3;++i)
                            output<<nodes1[i]<<' ';
                        output<<", Nodes 2: ";
                        for(int i=0;i<graph.getLength()/3;++i)
                            output<<nodes2[i]<<' ';
                        output<<", Edges: ";
                        for(int i=0;i<graph.getLength()/3;++i)
                            output<<edges[i]<<' ';
                    }
                    else
                        output<<"Edge between "<<number1<<" and "<<number2<<" doesn't exist.";
                }
                else if(words[0]=="FINDCONNECTEDCOMPONENTS"){
                    graph.clearNotDiscoverd();
                    int *allNodes;
                    allNodes=new int[(graph.getLength()/3)*2];
                    int newLength{};
                    allNodes=graph.getAllNodesSet(newLength);
                    int connectedComponents{};
                    connectedComponents=graph.FCC(allNodes,newLength,1);
                    output<<"Graph's connected components: "<<connectedComponents;
                }
                else if(words[0]=="COMPUTESPANNINGTREE"){
                    graph.clearNotDiscoverd();
                    int *allNodes;
                    allNodes=new int[(graph.getLength()/3)*2];
                    int newLength{};
                    allNodes=graph.getAllNodesSet(newLength);
                    int connectedComponents{};
                    connectedComponents=graph.FCC(allNodes,newLength,1);
                    if(connectedComponents==1){
                        graph.clearNotDiscoverd();
                        output<<"Minimum Spanning Tree Weight: "<<graph.MST();
                    }
                    else
                        output<<"Components are more than one and spanning tree cannot be computed";
                }
            }
            // AVLTREE
            if (words[1] == "AVLTREE") {
                if (words[0] == "BUILD"){
                    // words[2] is the filename we want
                    int length;
                    int* data = getData(length, words[2]);
                    // initialize data and length given from filename
                    avlTree.buildFromFile(data, length);
                    output << "Build AVLTree:";
                    for (int i=0;i<avlTree.getSize();i++)
                        output<<data[i]<<' ';
                }
                else if (words[0] == "GETSIZE") {
                    output << "Size of AVL Tree: " << avlTree.getSize();
                }
                else if (words[0] == "FINDMIN") {
                    output << "AVL Tree's min: " << avlTree.findMin();
                }
                else if (words[0] == "INSERT") {
                     // words[2] is the number we want to insert
                    int number = stoi(words[2]);
                    avlTree.insert(number);
                    output << "The number: " << number<<" inserted in the AVLTree";
                }
                else if (words[0] == "DELETE") {
                    // words[2] is the number we want to delete
                    int number = stoi(words[2]);
                    avlTree.deleteNode(number);
                    output << "The number: " << number << " deleted in the AVLTree";
                }
                else if (words[0] == "SEARCH") {
                    //words[2] is the number we are searching
                    int value = stoi(words[2]);
                    if (avlTree.search(value)) {
                        output << "Search of the value " << value << " was: SUCCESSFUL";
                    }
                    else {
                        output << "Search of the value " << value << " was: FAILURE";
                    }
                }
            }
            // HASHTABLE
            if (words[1] == "HASHTABLE") {
                if (words[0]=="BUILD"){
                    if (hashTable != nullptr) {
                        //we delete the previous Hashtable if there is one
                        delete hashTable;
                    }
                    //allocating dynamically new hashtable and building it from file
                    hashTable = new HashTable(100);
                    hashTable->buildFromFile(words[2]);
                        output << "Built HashTable.";
                }
                else if (words[0] == "GETSIZE"){
                    output<< "Size of Hashtable: "<< hashTable->getsize();
                }
                else if (words[0] == "INSERT") {
                    //we insert the key and value in the hashtable
                    int key = stoi(words[2]);
                    //int value = stoi(words[3]);
                     hashTable->insert(key);
                    output << "Inserted: "<< key<< " into Hashtable.";
                }
                else if (words[0] == "SEARCH") {
                    //we search the key and value in the hashtable
                    int key = stoi(words[2]);
                    if (hashTable->search(key)) {
                        output << "Found key " << key << " in Hashtable.";
                    }
                    else {
                        output << "Key " << key << " not found in Hashtable.";
                    }
                }
            }
            output<<'\n';
        }
        output.close();
        commands.close();
    }
    return 0;
}
