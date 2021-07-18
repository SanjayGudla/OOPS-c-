#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
using namespace std;

typedef struct intnode{
    int item;
    struct intnode *next;
}stacknode;

class Stack{
    public:
    void CreateStack();
    void Push(int x);
    int Pop();
    int Top();
    int IsEmpty();
    private:
    stacknode* top;
};

void Stack::CreateStack(){
    top=NULL;
}

/**
 *Push          - Push an integer “x” into the stack.
 *@parameters   - x is the element to be pushed                                                                          *@return       - returns nothing 
**/
void Stack::Push(int x){
    stacknode* p=new stacknode[1];
    p->item=x;
    p->next=top;
    top=p;
}

/**
 *Pop          - Pop the last element inserted in the stack and return it. If the stack is empty return -1.
 *@parameters  - no Parameters                                                                                             *@return     - returns the popped element
**/
int Stack::Pop(){
    if(top==NULL){
        return -1;
    }
    int x=top->item;
    stacknode* temp=top;
    top=top->next;
    delete [] temp;
    return x;
}

/**
 *Top          - Return the last element inserted in the stack, but do not pop it. If the stack is empty return -1.
 *@parameters  - no Parameters                                                                                             *@return     - returns the top element
**/

int Stack::Top(){
    if(top==NULL){
        return -1;
    }
    return top->item;
}

/**
 *IsEmpty      - Checks wether graph is empty or not
 *@parameters  - no Parameters                                                                                             *@return     - Return 1, if the stack is empty. Else, return 0.
**/
int Stack::IsEmpty(){
    if(top==NULL){
        return 1;
    }
    return 0;
}
/*******************************************End of STACK Class********************************************************/

class Graph{
    private:
    int** adj;
    int size;
    int RecursiveDFS(int v,int* visitedset,int parent);
    void IterativeDFS(int i,int* visitedset);
    
    public:
    void CreateGraph(int n);
    //operator += overloading
    void operator +=(pair <int,int> p){
        int i=p.first;
        int j=p.second;
        if(adj[i][j]==0){
            adj[i][j]=1;
            adj[j][i]=1;
        }
    }
    //operator -= overloading
    void operator -=(pair<int,int> p){
        int i=p.first;
        int j=p.second;
        if(adj[i][j]==1){
            adj[i][j]=0;
            adj[j][i]=0;
        }
    }
    int detectCycle();
    int components();
    int reach(int u,int v);
    void memoryFree();
};

/**
 *CreateGraph  - Constructor,Takes “n” as parameter and initializes the adjacency matrix with all entries as “0”.
 *@parameters  - int n,size of Graph                                                                                       *@return     - returns nothing 
**/
void Graph::CreateGraph(int n){
    adj=new int*[n];
    for(int i=0;i<n;i++){
        adj[i]=new int[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            adj[i][j]=0;
        }
    }
    size=n;
}

/**
 *RecursiveDFS - recursively implement DFS 
 *@parameters  - takes a vertex ,its parent and visitedset                                                                 *@return     - returns 1 if cycle exists in the component of input vetex else 0
**/
int Graph::RecursiveDFS(int v,int* visitedset,int parent){
    visitedset[v]=1;
    for(int i=0;i<size;i++){
        if(adj[v][i]==1){
            if(visitedset[i]==0){
                if( RecursiveDFS(i,visitedset,v)==1){
                    return 1;
                } 
            }
            else if(i!=parent){
                return 1;
            }
        }
      }
    return 0;
}

/**
 *Detect Cycle - detect cycle in the graph by using recursive implementation of DFS on each component
 *@parameters  - no parameters                                                                                             *@return     - returns 1 if cycle exists in the Graph else 0
**/
int Graph::detectCycle(){
    int* visitedset=new int[size];
    for(int i=0;i<size;i++){
        visitedset[i]=0;
    }
    for(int i=0;i<size;i++)
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
 *IterativeDFS - Iteratively implement DFS using Stack
 *@parameters  - takes a vertex and visitedset                                                                            *@return       - returns nothing
**/
void Graph::IterativeDFS(int i,int* visitedset){
    Stack S;
    S.CreateStack();
    visitedset[i]=1;
    S.Push(i);
    while(S.IsEmpty()!=1)
      {
        int v=S.Top();
        int j=0;
        for(j=0;j<size;j++)
          {
            if(adj[v][j]==1&&visitedset[j]==0){
                visitedset[j]=1;
                S.Push(j);
                break;
             }  
          }
          if(j==size){
             S.Pop();
          }
      }
}

/**
 *components -   uses iteratively implemented DFS to calculate no of connected components 
 *@parameters  - no parameters                                                                                     *@return     - returns int which is no of connected components
**/
int Graph::components(){
    int count=0;
    int* visitedset=new int[size];
    for(int i=0;i<size;i++){
        visitedset[i]=0;
    }
  
    for(int i=0;i<size;i++){
        if(visitedset[i]==0){
           IterativeDFS(i,visitedset);
            count++;
        }
    }
    return count;
}

/**
 *reach        -   uses iteratively implemented DFS to find wether a path exist between input vetrices
 *@parameters  -  two vetices                                                                                            *@return     - returns 1 if path exist else 0
**/
int Graph::reach(int u,int v){
    int* visitedset=new int[size];
    for(int i=0;i<size;i++){
        visitedset[i]=0;
    }
    IterativeDFS(u, visitedset);
    if(visitedset[v]==1){
        return 1;
    }
    return 0;
}

void Graph::memoryFree(){
    for(int i=0;i<size;i++){
        delete [] adj[i];
    }
    delete [] adj;
}
/******************************************End of Graph ADT************************************************************/


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int q;
    cin>>q;
    string s;
    int result;
    int x;
    int y;
    Stack object;                 //Derclaration of Stack object
    Graph object1;                //Declaration of Graph object
    object.CreateStack();
    for(int i=0;i<q;i++)
      {
        cin>>s;
        if(s=="push")
          {
            cin>>x;
            object.Push(x);
          }
        else if(s=="pop")
          {
            result=object.Pop();
            cout<<result<<"\n";
          }
        else if(s=="top")
          {
            result=object.Top();
            cout<<result<<"\n";
          }
        else if(s=="empty")
          {
            result=object.IsEmpty();
            cout<<result<<"\n";
          }
    }  
    int n;
    cin>>n;
    int m;
    cin>>m;
    pair<int,int> p;
    object1.CreateGraph(n);
    for(int i=0;i<m;i++)
      {
        cin>>s;
        if(s=="add")
          {
            cin>>x;
            cin>>y;
            p.first=x;
            p.second=y;
            object1+=(p); //using += overloaded operator
          }
        else if(s=="del")
          {
            cin>>x;
            cin>>y;
            p.first=x;
            p.second=y;
            object1-=(p); //using -= overloaded operator
          }
        else if(s=="cycle")
          {
            result=object1.detectCycle();
            cout<<result<<"\n";
          }
        else if(s=="components")
          {
            result=object1.components();
            cout<<result<<"\n";
          }
        else if(s=="reach")
          {
            cin>>x;
            cin>>y;
            result=object1.reach(x,y);
            cout<<result<<"\n";
          }
    }
    object1.memoryFree();
    return 0;
}
