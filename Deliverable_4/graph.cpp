#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include "graph.h"
using namespace std;

vertex* g_head=NULL;

vertex* findvertex(string name){
    vertex* temp=g_head;
    while(temp!=NULL){
        if(temp->name==name)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

vertex* addVertex(string name){
    vertex* v=findvertex(name);
    if(v)
        return v;
    vertex* newvertex=new vertex;
    newvertex->name=name;
    newvertex->adj=NULL;
    newvertex->next=NULL;

    if(g_head==NULL){
        g_head=newvertex;
    }
    else{
        vertex* temp=g_head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newvertex;
    }
    return newvertex;
}

void addEdge(string from, string to, double amount, bool confirmed){
    vertex* vf=addVertex(from);
    vertex* vto=addVertex(to);

    edge* newedge=new edge;
    newedge->to=vto;
    newedge->amount=amount;
    newedge->confirmed=confirmed;
    newedge->next=NULL;


    if (vf->adj==NULL){
        vf->adj=newedge;
    }
    else{
        edge* temp= vf->adj;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=newedge;
    }
}

// void setEdgeConfirmed(string from, string to){
//     vertex* vf=findvertex(from);
//     if(vf==NULL)
//         return;
//     edge* temp=vf->adj;
//     while(temp!=NULL){
//         if(temp->to->name==to){
//             temp->confirmed=true;
//             return;
//         }
//         temp=temp->next;
//     }
// }

void saveGraph(string filename)
{
    ofstream file(filename);
    vertex* tempv=g_head;
    while(tempv!=NULL){
        edge* tempe=tempv->adj;
        while(tempe!=NULL){
            file<<tempv->name<<"|"<<tempe->to->name<<"|"<<tempe->amount<<"|"<<(tempe->confirmed?1:0)<<"\n";
            tempe=tempe->next;
        }
        tempv=tempv->next;
    }
    file.close();
}

void loadGraph(string filename)
{
    ifstream file(filename);
    string line;
    while(getline(file,line)){
        stringstream ss(line);
        string from,to,amountstr,confirmedstr;
        getline(ss,from,'|');
        getline(ss,to,'|');
        getline(ss,amountstr,'|');
        getline(ss,confirmedstr,'|');
        double amount=stod(amountstr);
        bool confirmed=(confirmedstr=="1")?true:false;
        addEdge(from,to,amount,confirmed);
    }
    file.close();
}