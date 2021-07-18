#include <cmath>
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <list>
#include <bits/stdc++.h>
using namespace std;
template <class T> class Graph{          
    
    private:
     int vertices;
     vector<list<pair<int,T>>> adjlist ; // adjlist is a vector of lists where each term in list is a pair
     int insertposition(list<pair<int,T>> a,T value,int n);
    
    public:
    /*Constructor*/
     Graph(int n){
         adjlist.resize(n);
         vertices = n;
     }
     void AddV();
     void AddE(int a,int b, T w);
     void DelE(int a,int b);
     void BFS(int a);
     vector<T> SSP(int a);
 };

/**
 *AddV          - Adds a new vertex.
 *@parameters   - no parameters
 *@return       - returns nothing
**/
template <class T>
void Graph<T>::AddV(){
    vertices = vertices + 1;
    adjlist.resize(vertices);
}

/**
 *AddE          -  Adds an edge from vertex a to vertex b of weight w.  writes an error message to the standard                            error stream if the vertex indices is invalid..
 *@parameters   -  vertex a ,vertex b,weight w
 *@return       - returns nothing
**/
template <class T>
void Graph<T>::AddE(int a,int b,T w){
    if(a>=vertices||b>=vertices){
        cerr<<"error";
        return;
    }
    pair<int,T> p;
    pair<int,T> q;
    p.first=b;
    p.second=w;
    auto it = adjlist[a].begin();
    int x =insertposition(adjlist[a],p.second,p.first);
    for(int i=0;i<x;i++){
        it++;
    }
    adjlist[a].insert(it,p); 
    p.first=a;
    it=adjlist[b].begin();
    x =insertposition(adjlist[b],p.second,p.first);
    for(int i=0;i<x;i++){
        it++;
    }
    adjlist[b].insert(it,p);  
}

template <class T>
int Graph<T>::insertposition(list<pair<int,T>> a,T value,int n){
    int i=0;
     auto it = a.begin();
    pair<int,T> q;
    while(it!=a.end()){
        q = *it;
        if(q.second<value){
            it++;
            i++;
        }
        else if(q.second==value && q.first<n){
            it++;
            i++;
        }
        else{
            break;
        }
    }
    return i;
}    

/**
 *DelE          -  Deletes the edge from vertex a to vertex b.  writes an error message to the standard error                              stream if the edge does not exist or vertex indices is invalid.
 *@parameters   -  vertex a,vertex b
 *@return       -  returns nothing
**/
template <class T>
void Graph<T>::DelE(int a,int b){
    //if a or b is greater than number of vertices then vertices are invalid
    if(a>=vertices||b>=vertices){
        cerr<<"error";
        return;
     }
    pair<int,T> p;
    auto it = adjlist[a].begin();
    for(it=adjlist[a].begin();it!=adjlist[a].end();it++){
        p = *it;
        if(p.first==b){
            adjlist[a].remove(p);
            break;
        }
    }
    if(it==adjlist[a].end()){
        cerr<<"error";
    }
     for(it=adjlist[b].begin();it!=adjlist[b].end();it++){
        p = *it;
        if(p.first==a){
            adjlist[b].remove(p);
            break;
        }
    }

}

/**
 *BFS           -  Implements breadth first search on the graph using a queue starting from the vertex a. 
 *@parameters   -  vertex a which is starting vertex
 *@return       -  returns nothing but Prints the BFS order of the vertices reachable from a.
**/
template <class T>
void Graph<T>::BFS(int a){
    int visited[vertices];                //visited array is used for maintaing already visited vertices 
    for(int i=0;i<vertices;i++){
        visited[i]=0;
    }
    queue<int> bfsq;
    pair<int,T> p;
    bfsq.push(a);
    visited[a]=1;
    while(!bfsq.empty()){
        int x= bfsq.front();
        bfsq.pop();
        cout<<x<<" ";
        //push all adjacent vertices of x if not visited into queue
        for(auto it=adjlist[x].begin();it!=adjlist[x].end();it++){
            p = *it;
            if(visited[p.first]==0){
                bfsq.push(p.first);
                visited[p.first]=1;
            }
        }
    }
}

/**
 *SSP           -  Implements Dijkstras Algorithm using Priority queue by modifying BFS
 *@parameters   -  vertex a which is starting vertex
 *@return       -  returns a vector<int> which stores shortest distance of all  vertices from a
**/
template <class T>
vector<T> Graph<T>::SSP(int a){
    vector<T> distance;
    distance.resize(vertices);
    for(int i=0;i<vertices;i++){
        distance[i]=(i!=a)?INT_MAX:0;
    }
    priority_queue<pair<T,int>> prioque;         //declaring a priority queue with key,value pair as element
    pair<T,int> p;
    p.first=0;
    p.second=a;
    prioque.push(p);
    while(!prioque.empty()){
        int u = prioque.top().second;
        prioque.pop();
        for(auto it=adjlist[u].begin();it!=adjlist[u].end();it++){
            int v = (*it).first;
            T weight = (*it).second;
            //updating the value of d(v)if d(u)+w(u,v)<d(v)
            if(distance[v]>distance[u]+weight){
                distance[v]=distance[u]+weight;
                p.first=distance[v];
                p.second=v;
                prioque.push(p);          //if updated push into the priority queue
            }
        }
    }
    return distance;    //returning distance vector
}

/********************************************END OF GRAPH CLASS********************************************************/
int main() {
    int num;                        //number of verties
    cin>>num;
    int q;  
    cin>>q;                         //number of quiries
    Graph<int> G(num);
    string s;
    int m;
    int n;
    int o;
    for(int i=0;i<q;i++){
        cin>>s;
        if(s=="ADDV"){
           G.AddV();               //calling AddV function
        }
        else if(s=="ADDE"){
            cin>>m;
            cin>>n;
            cin>>o;
            G.AddE(m,n,o);         //calling AddE function
        }
        else if(s=="DELE"){
            cin>>m;
            cin>>n;
            G.DelE(m,n);           //calling DelE function 
        }
    }
    for(int i=0;i<2;i++){
        cin>>s;
        if(s=="BFS"){
            cin>>m;
            G.BFS(m);              //calling BFS function
            cout<<"\n";
        }
        else if (s=="SSP"){
            cin>>m;
            vector<int> distance;
            distance=G.SSP(m);      //calling SSP function and storing returned vector into distance
            for(int i=0;i<(int)distance.size();i++){
                cout<<distance[i]<<" ";
            }
            cout<<"\n";
        }
    }
    return 0;
}
