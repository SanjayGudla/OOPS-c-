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
class Graph{

    protected:
     int vertices;
     vector<list<pair<int,int>>> adjlist ;  // adjlist is a vector of lists where each term in list is a pair
     int uptodate=0; //keeps track whether mst corresponding to graph is uptodate

    public:
     //constructor
     Graph(int n){
         adjlist.resize(n);
         vertices = n;
     }
     void AddV();
     void AddE(int a,int b, int w);
     void DelE(int a,int b);
 };

/**
 *AddV          - Adds a new vertex.
 *@parameters   - no parameters
 *@return       - returns nothing
**/
void Graph::AddV(){
    vertices = vertices + 1;
    adjlist.resize(vertices);
    uptodate=0;
}

/**
 *AddE          -  Adds an edge from vertex a to vertex b of weight w.  writes an error message to the standard                            error stream if the vertex indices is invalid.
 *@parameters   -  vertex a ,vertex b,weight w
 *@return       - returns nothing
**/

void Graph::AddE(int a,int b,int w){
    if(a>=vertices||b>=vertices){
        cerr<<"error";
        return;
    }
    pair<int,int> p;
    pair<int,int> q;
    p.first=b;
    p.second=w;
    auto it = adjlist[a].begin();
    adjlist[a].insert(it,p);   //adding pair at start of adjlist[a]
    p.first=a;
    it=adjlist[b].begin();
    adjlist[b].insert(it,p);  //adding pair at start of adjlist[b]
    uptodate=0;
}


/**
 *DelE          -  Deletes the edge from vertex a to vertex b.  writes an error message to the standard error                              stream if the edge does not exist or vertex indices is invalid.
 *@parameters   -  vertex a,vertex b
 *@return       -  returns nothing
**/
void Graph::DelE(int a,int b){
    //if a or b is greater than number of vertices then vertices are invalid
    if(a>=vertices||b>=vertices){
        cerr<<"error";
        return;
     }
    pair<int,int> p;
    auto it = adjlist[a].begin();
    for(it=adjlist[a].begin();it!=adjlist[a].end();it++){
        p = *it;
        if(p.first==b){
            adjlist[a].remove(p);
            break;
        }
    }
    //if b is not there in adjacency list of a then print error
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
    uptodate=0;
}
/********************************************END OF GRAPH CLASS********************************************************/ class MST: public Graph{

    public:
     //constructor
     MST(int n):Graph(n){};
     void Prims(int v);
     void Kruskal();
     void TreeUptodate();
     void DisplayTree();

    private:
     vector<list<pair<int,int>>> Tree;         //this is adjacency list corredsponding to MST
     list<pair<pair<int,int>,int>> inclist;    //stores (edges+vertex pair) of MST in increasing order of edge weight
     list<pair<pair<int,int>,int>> inclist1;
     void addE(int a,int b,int w);
     void FindPostoinsert(int a,int b,int weight, list<pair<pair<int,int>,int>>& inputlist);
     int RecursiveDFS(int v,int* visitedset,int parent);
     int detectCycle();
};

/**
 *AddE          -  Adds an edge from vertex a to vertex b of weight w to Tree.  writes an error message to the standard                     error stream if the vertex indices is invalid.
 *@parameters   -  vertex a ,vertex b,weight w
 *@return       - returns nothing
**/

void MST::addE(int a,int b,int w){
    if(a>=vertices||b>=vertices){
        cerr<<"error";
        return;
    }
    pair<int,int> p;
    pair<int,int> q;
    p.first=b;
    p.second=w;
    auto it = Tree[a].begin();
    Tree[a].insert(it,p);
    p.first=a;
    it=Tree[b].begin();
    Tree[b].insert(it,p);
}

/**
 *FindPostoinsert - finds position in given inputlist and insert a new element into the list at that position
 *@parameters     - a,b vertices and weight , inputlist in which element to be inserted                                   *@return     - returns nothing
**/
void MST::FindPostoinsert(int a,int b,int weight,list<pair<pair<int,int>,int>>& inputlist){
    auto it = inputlist.begin();
    pair<pair<int,int>,int> q;
    while(it!=inputlist.end()){
        q = *it;
        if(q.second<weight){
            it++;
        }
        else if(q.second==weight && q.first.first<a){
            it++;
        }
        else if(q.second==weight && q.first.first==a && q.first.second<b){
            it++;
        }
        else {break;}
    }
    //it now is modified to correct position to be inserted
    inputlist.insert(it,make_pair(make_pair(a,b),weight)); //inserting the element into inputlist
}

/**
 *Prims      -  Computes a minimum weight spanning tree of the graph using prim's algorithm starting at the vertex src and             stores int Tree
 *@parameters  - source vertex src                                                                                          *@return     -  returns nothing but  Prints the sum of weights of all the edges in the minimum spanning tree
**/
void MST::Prims(int src){
    if(src>vertices-1){
        cerr<<"Invalid Source Vertex"<<endl;
        return;
    }

    //clearing and resizing the tree,inclist,inclist1
    Tree.resize(vertices);
    for(int i=0;i<vertices;i++){
        Tree[i].clear();
    }
    inclist.clear();

    int visitedset[vertices];  //this array maintains already visited vertices
    int parent[vertices];      //this array maintains parent of every vertex int mst
    int key[vertices];         //this array maintains edge weights between vertices and their parents

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> prioque; //min heap

    for(int i=0;i<vertices;i++){  //initiliazing above three arrays
        parent[i]=-1;
        visitedset[i]=0;
        key[i]=INT_MAX;
    }

    key[src]=0;
    prioque.push(make_pair(0,src));
    int cost=0;      //keeps track of total minimum cost of spanning tree

    while(!prioque.empty()){

        int u=prioque.top().second;
        if(visitedset[u]==0){
            cost=cost+prioque.top().first;  //if the popped vertex is already not visited the update cost
        }

        prioque.pop();
        visitedset[u]=1;

        for(auto it=adjlist[u].begin();it!=adjlist[u].end();it++){//for all adjacent vertices of popped vertex
            int w=(*it).first;
            int weight=(*it).second;
            if(visitedset[w]==0 && key[w]>weight){  //if not visited and current key > weight the insert into prioque
                key[w]=weight;
                prioque.push(make_pair(weight,w));
                parent[w]=u;
            }
        }
    }

    //as key , parent arrays are updated corresponding to minimum spanning tree insert into Tree.inclist
     for(int i=0;i<vertices;i++){
        if(i!=src){
            addE(i,parent[i],key[i]);
            if(i<parent[i]){
                FindPostoinsert(i,parent[i],key[i],inclist);
            }
           else{
                FindPostoinsert(parent[i],i,key[i],inclist);
            }
        }

     }
    uptodate=1;
    cout<<cost<<endl;
}

/**
 *RecursiveDFS - recursively implement DFS
 *@parameters  - takes a vertex ,its parent and visitedset                                                                 *@return     - returns 1 if cycle exists in the component of input vetex else 0
**/
int MST::RecursiveDFS(int v,int* visitedset,int parent){
    visitedset[v]=1;
    for(auto it=Tree[v].begin();it!=Tree[v].end();it++){
             pair<int,int> q;
             q=*it;
             int i=q.first;
            if(visitedset[i]==0){
                if( RecursiveDFS(i,visitedset,v)==1){
                    return 1;
                }
            }
            else if(i!=parent){
                return 1;
            }
    }
    return 0;
}

/**
 *Detect Cycle - detect cycle in the graph by using recursive implementation of DFS on each component
 *@parameters  - no parameters                                                                                             *@return     - returns 1 if cycle exists in the Graph else 0
**/
int MST::detectCycle(){
    int* visitedset=new int[vertices];
    for(int i=0;i<vertices;i++){
        visitedset[i]=0;
    }
    for(int i=0;i<vertices;i++)
      {
        if(visitedset[i]==0){
            if(RecursiveDFS(i,visitedset,-1)==1){
                return 1;
            }
        }
      }
    return 0;
}

/**
 *Kruskal      - Computes a minimum weight spanning forest of the graph using Kruskal algorithm and stores  in                          the Tree.
 *@parameters  - No Parameters                                                                                             *@return     -  returns nothing but  Prints the sum of weights of all the edges in the minimum spanning forest
**/
void MST::Kruskal(){
    //clearing and resizing the tree,inclist,inclist1
    Tree.resize(vertices);
    for(int i=0;i<vertices;i++){
        Tree[i].clear();
    }
    inclist.clear();
    inclist1.clear();//used to store the (edge+vertexpair) of graph in increasing order of weight
    int a;
    int b;
    int weight;
    int numedges=0;//keeps track of number of edges in the graph

    //storing the (edge+vertexpair) of graph in inclist1 in increasing order
    for(int i=0;i<vertices;i++){
        a =i;
        pair<int,int> q;
        for(auto it=adjlist[i].begin();it!=adjlist[i].end();it++){
             q=*it;
             b=q.first;
             weight=q.second;
            if(a<b){
                FindPostoinsert(a,b,weight,inclist1); //using FindPostoinsert at correct position
                numedges++;
            }
        }
    }

    int cost=0;
    int i=0;
    while(i!=numedges){
        a=inclist1.front().first.first;
        b=inclist1.front().first.second;
        weight=inclist1.front().second;
        addE(a,b,weight);//adding edge to the tree
        //detectCycle() tells after adding edge to spanning forest whether any cycle is formed or not
        if(detectCycle()==0){
            inclist.push_back(inclist1.front());
            cost=cost+weight;   //if cycle is not formed update cost and also push (edge+vertexpair) into inclist
        }
        else{
            Tree[a].pop_front();
            Tree[b].pop_front(); //if cycle is formed remove the added edge from Spanning Forest
        }
        inclist1.pop_front();  //popping out front of inclist1 as that edge was checked
        i++;
    }
    uptodate=1;
    cout<<cost<<endl;
}

/**
 *TreeUptodate  - checks if the minimum spanning tree/forest is uptodate i.e. no edges/vertices are added/deleted to                     the graph after Prims,Kruskal was run
 *@parameters  - No Parameters                                                                                             *@return     - Prints YES if the tree is uptodate, NO otherwise
**/
void MST::TreeUptodate(){
    if(uptodate==0){
        cout<<"NO"<<endl;
    }
    else{
        cout<<"YES"<<endl;
    }
}

/**
 *DisplayTree  - Output the edges of the spanning tree in the ascending order of edge weight.if edge weights are same
                 then corresponding vertex pairs are checked
 *@parameters  - No Parameters                                                                                             *@return     - prints the edges of the spanning tree
**/
void MST::DisplayTree(){
    for(auto it=inclist.begin();it!=inclist.end();it++){
        pair<pair<int,int>,int> q;
        q=*it;
        cout<<q.first.first<<" "<<q.first.second<<" "<<q.second<<endl;
    }
}
/**********************************************************************************************************************/
int main() {
    int num;                             //number of verties
    cin>>num;
    int q;
    cin>>q;                              //number of queries
    MST Tree(num);
    string s;
    int m;
    int n;
    int o;
    for(int i=0;i<q;i++){
        cin>>s;
        if(s=="ADDV"){
           Tree.AddV();                  //calling AddV function
        }
        else if(s=="ADDE"){
            cin>>m;
            cin>>n;
            cin>>o;
            Tree.AddE(m,n,o);            //calling AddE function
        }
        else if(s=="DELE"){
            cin>>m;
            cin>>n;
            Tree.DelE(m,n);              //calling DelE function
        }
        else if(s=="Kruskal"){
            Tree.Kruskal();              //calling Kruskal function
        }
        else if(s=="Prims"){
            cin>>m;
            Tree.Prims(m);               //calling Prims function
        }
        else if(s=="DisplayTree"){
            Tree.DisplayTree();          //calling DisplayTree function
        }
        else if(s=="TreeUptodate"){
            Tree.TreeUptodate();         //calling TreeUptodate function
        }
    }
    return 0;
}
