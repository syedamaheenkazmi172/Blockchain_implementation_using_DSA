#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct vertex;//this is forward declaration

struct edge {
    vertex* to;
    double amount;
    bool confirmed;
    edge* next;
};

struct vertex {
    string name;
    edge* adj; //this will aid in storing linkedlist
    vertex* next;
};

vertex* findvertex(string name);
vertex* addVertex(string name);
void addEdge(string from, string to, double amount, bool confirmed);
void saveGraph(string filename);
void loadGraph(string filename);

#endif