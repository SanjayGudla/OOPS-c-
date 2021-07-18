#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class HLI{
    
    public:
      //destructor
     ~HLI(){
        for(int i=0;i<colours;i++){
            delete [] colourslist[i];
        }
        delete [] colourslist;
        for(int i=0;i<countries;i++){
            delete [] currencylist[i];
        }
        delete [] currencylist; 
     }
    
     void AddEcolour(int a,int b);
     void AddEcurrency(int i,int j,int colour1,int colour2,float value);
     void initialize1(int c);
     void initialize2(int n);
     void Answer(int i,int j,int rate);
    
    private:
    
    int colours;          //stores number of colours
    int countries;        //stores number of countries
    int** colourslist;    //represents adjacency matrix of colour relations
    int** currencylist;   //represents adjacency matrix of currency factors
    list<pair<pair<int,int>,float>> edgelist;  //stores all edges
    int increasingweightcycle=0;
    float BellmannFord(int source,int dest);
};

/**
 *initialize1   - dynamically allocate space for colourslist and initializes it
 *@parameters   - int c 
 *@return       - returns nothing
**/
void HLI::initialize1(int c){
    colourslist = new int*[c];
    for(int i=0;i<c;i++){
        colourslist[i]=new int[c];
    }
    for(int i=0;i<c;i++){
        for(int j=0;j<c;j++){
            colourslist[i][j]=0;
        }
    }
    for(int i=0;i<c;i++){
        colourslist[i][i]=1;
    }
    colours = c;
}

/**
 *initialize2   - dynamically allocate space for currency list and initializes it
 *@parameters   - int n
 *@return       - returns nothing
**/
void HLI::initialize2(int n){
    currencylist = new int*[n];
    for(int i=0;i<n;i++){
        currencylist[i]=new int[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            currencylist[i][j]=INT_MAX;
        }
    }
    countries = n;
}

/**
 *AddEcolour    - assigns 1 to colourslist[a][b] and colourslist[b][a]
 *@parameters   - two integers a and b
 *@return       - returns nothing
**/
void HLI::AddEcolour(int a,int b){
   colourslist[a][b]=1; 
   colourslist[b][a]=1;
}

/**
 *AddEcurrency  - assigns value to currencylist[i][j] if and only if the currencies are treaties 
 *@parameters   - int i,j and int colours1,colours2 and value to be assigned
 *@return       - returns nothing
**/
void HLI::AddEcurrency(int i, int j,int colour1,int colour2, float value){
   if(colourslist[colour1][colour2]==1){
       float x = -1*log2(value); 
       auto it = edgelist.begin();
       edgelist.insert(it,make_pair(make_pair(i,j),x));
       currencylist[i][j]=x;
   }
}

/**
 *BellmannFord  - This is to find shortest path from source to destination and also detects negative edge cycle
 *@parameters   - two strings a and b
 *@return       - returns nothing
**/
float HLI::BellmannFord(int source,int dest){
    float* dist;
    dist = new float[countries];
    for(int i=0;i<countries;i++){
        dist[i]=INT_MAX;
    }
    dist[source]=0;
    int u;
    int v;
    float cost;
    //Iterating through all edges V-1 times
    for(int i=0;i<countries;i++){
        for(auto it = edgelist.begin();it!=edgelist.end();it++){
            pair<pair<int,int>,float> p = *it;
            u = p.first.first;
            v = p.first.second;
            cost=p.second;
            if(dist[u]!=INT_MAX&&dist[u]+cost<dist[v]){
                dist[v]=dist[u]+cost;
            }
        }
    }
    //Again Iterating through all edges one more time to check still any updations are there or not
    //if updation takes place assign 1 to increasingweight cycle
    for(auto it = edgelist.begin();it!=edgelist.end();it++){
            pair<pair<int,int>,float> p = *it;
             u = p.first.first;
             v = p.first.second;
             cost=p.second;
            if(dist[u]!=INT_MAX&&dist[u]+cost<dist[v]){
                dist[v]=dist[u]+cost;
                increasingweightcycle=1;
            }
    }
    return dist[dest];  //returning distance to destination from source
}
/**
 *Answers       - calls BellmannFord function and prints answer 
 *@parameters   - two integers i and j that is source and destination and rate
 *@return       - returns nothing
**/
void HLI::Answer(int i,int j,int rate){
    increasingweightcycle=0;
    float x = BellmannFord(i,j);
    if(x==INT_MAX){
        cout<<"-1"<<endl;
        return;
    }
    if(increasingweightcycle==1){
        cout<<"INF"<<endl;
        return;
    }
    cout<<fixed<<setprecision(3)<<pow(2,-1*x)*rate<<endl;
}


/************************************************************************/
int main() {
    int c;
    cin>>c;
    
    HLI obj;                  //declaring HLL Object
    obj.initialize1(c); 
    
    int m;
    cin>>m;
    int a;
    int b;
    for(int i=0;i<m;i++){
        cin>>a;
        cin>>b;
        obj.AddEcolour(a,b);  //adding edges to the colour adjacency matrix
    }
    int n;
    cin>>n;
    obj.initialize2(n);
    
    int nc[n];
    for(int i=0;i<n;i++){
        cin>>nc[i];            //nc array stores colour codes for each country
    }
    
    float value;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>value;
            obj.AddEcurrency(i,j,nc[i],nc[j],value);  //adding edges to currency adjacency matrix
        }
    }
    int q;
    cin>>q;
    int x;
    int y;
    int z;
    for(int i=0;i<q;i++){
        cin>>x>>y>>z;
        obj.Answer(x,y,z);         // calling Answer to print answers
    }
    return 0;
}
