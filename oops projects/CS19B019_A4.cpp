#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

 template <class T> class Vector{
     
        private:
            size_t currentCapacity;
            size_t currentSize;
            T* vec;
     
        public:
            /*constructors*/
            Vector(size_t c){
                vec = new T[c];
                currentCapacity = c;
                currentSize = 0;
            }
     
            Vector(size_t c, T x){
                vec = new T[c];
                currentCapacity = c;
                for(size_t i=0;i<c;i++){
                    vec[i]=x;
                }
                currentSize = c;
            }
     
            Vector(){
                vec = new T[1];
                currentCapacity = 1;
                currentSize = 0;
            }
            size_t capacity();
            size_t size();
            void push(T x);
            void pop();
            T front();
            T back();
            T operator[] (size_t i){
                if(i>=currentSize){
                    return -1;
                }
                return vec[i];
            }
            void sort();
            ~Vector();
        protected:
            size_t partition(size_t lb,size_t ub);
            void quicksort(size_t lb,size_t ub);
     
    };

/**
 *capacity     - used to find currentCapacity of vector
 *@parameters  - no parameters
 *@return      - currentCapacity
**/
template<class T>
size_t Vector<T>::capacity(){
    return currentCapacity;
}

/**
 *size         - used to find currentSize of vector
 *@parameters  - no parameters
 *@return      - currentSize
**/
template<class T>
size_t Vector<T>::size(){
    return currentSize;
}

/**
 *push         - insert into first unassigned position, if there is no vacant space then doubles vector and then pushes
 *@parameters  - x element to be pushed
 *@return      - does not return anything
**/
template<class T>
void Vector<T>::push(T x){
     if(currentSize==currentCapacity){
        T* temp;
        currentCapacity = 2*currentCapacity;
        temp = new T[currentCapacity];
        for(size_t i = 0;i<currentSize;i++){
            temp[i] = vec[i];
        }
        temp[currentSize] = x;
        delete [] vec;
        vec = temp;
        currentSize=currentSize+1;
    }
    else{
        vec[currentSize] = x;
        currentSize=currentSize+1;
    }
}

/**
 *pop          - deletes the last assigned position
 *@parameters  - no parameters
 *@return      - does not return anything
**/
template<class T>
void Vector<T>::pop(){
    if(currentSize!=0){
        currentSize = currentSize - 1;
    }
}

/**
 *front        - used to find first element in vector 
 *@parameters  - no parameters
 *@return      - returns first element in vector if present else returns -1
**/
template<class T>
T Vector<T>::front(){
    T x;
    x= currentSize==0 ?  -1 :  vec[0];
    return x;
}

/**
 *back         - used to find first element in vector 
 *@parameters  - no parameters
 *@return      - returns last element in vector if present else returns -1
**/
template<class T>
T Vector<T>::back(){
    T x;
    x= currentSize==0 ?  -1 :  vec[currentSize-1];
    return x;
}

/**
 *partition    - used to find correct position of pivot by changing suitably vector inplace 
 *@parameters  - takes lowerbound and upperbound 
 *@return      - returns correct position of pivot
**/
template<class T>
size_t Vector<T>::partition(size_t lb,size_t ub){
    size_t start = lb;
    size_t end   = ub;
    T pivot = vec[lb];
    while(start<end){
        while(vec[start]<=pivot&&start<=ub){
            start++;
        }
        while(vec[end]>pivot&&end>=lb){
            end--;
        }
        if(start<end){
            T temp;
            temp = vec[start];
            vec[start]=vec[end];
            vec[end]=temp;
        }
    }
    vec[lb]=vec[end];
    vec[end]=pivot;
    return end;
}

/**
 *quicksort    - implements recursive quicksort by using partition function to find pivot position in each recursion
 *@parameters  - takes lowerbound and upperbound
 *@return      - does not return anything but changes the vector inplace to sorted order
**/
template<class T>
void Vector<T>::quicksort(size_t lb, size_t ub){
    if(lb<ub){
        size_t pivpos = partition(lb,ub);
        if(pivpos!=lb){
            quicksort(lb,pivpos-1);
        }
        if(pivpos!=ub){
            quicksort(pivpos+1, ub);
        }     
    }
}

/**
 *front        - calles the qicksort function and prints sorted vector
 *@parameters  - no parameters
 *@return      - returns nothing
**/
template<class T>
void Vector<T>::sort(){
    quicksort(0,currentSize-1);
    for(size_t i=0;i<currentSize;i++){
        cout<<vec[i]<<" ";
    }
    cout<<"\n";
}

/*destructor for Vector class*/
template<class T>
Vector<T>::~Vector(){
    delete [] vec;
}
/******************************************End of Vector Class*********************************************************/
/**
 *Getintfromseq -  converts sequence into integers
 *@parameters   -  sequence  to be converted , start index,length
 *@return       -  returns integer 
**/
int Getintfromseq(string sequence,int start,int len){
    int trav;                          
    int sum=0;                         
    for(trav=start;trav<len;trav++){
        int x=(sequence[trav]-'0');    
        sum=x+(sum*10);               
    }
    return sum;                        
    
}
/**
 *inputfunc    - used to take input from user
 *@parameters  - no of quireis,vector
 *@return      - returns nothing
**/
void inputfunc(int q,Vector<int> &v){
    string s;
    int b;
    size_t a;
    while(q>0){
        cin>>s;
        if(s=="capacity"){
            cout<<v.capacity()<<"\n";
        }
        else if(s=="push"){
            cin>>b;
            v.push(b);
        }
        else if(s=="pop"){
            v.pop();
        }
        else if(s=="front"){
            cout<<v.front()<<"\n";
        }
        else if(s=="back"){
            cout<<v.back()<<"\n";
        }
        else if(s=="size"){
            cout<<v.size()<<"\n";
        }
        else if(s=="sort"){
            v.sort();
        }
        else if(s=="element"){
            cin>>a;
            cout<<v[a];
            cout<<"\n";
        }
        q--;
    }
}
int main() {
    string s;
    int b;
    int x;
    Vector<int> v;
    getline(cin,s);
    size_t p=6;
    int j;
    while(s[p]==' '){
        p++;
    }
    if(p==s.length()){
        Vector<int> v;
         int q;
         cin>>q;
         inputfunc(q,v);
    }
    else{
        while(s[p]==' '){
            p++;
        }
        j=p;
        while(s[p]!=' '&&p!=s.length()){
            p++;
        }
        b = Getintfromseq(s,j,p);
        if(p==s.length()){
             Vector<int> v((b));
             int q;
             cin>>q;
             inputfunc(q, v);
        }
        else{
            while(s[p]==' '){
                p++;
            }
            j=p;
            while(s[p]!=' '&&p!=s.length()){
                 p++;
            }
            x = Getintfromseq(s,j,p);
            Vector<int> v(b,x);
            int q;
            cin>>q;
            inputfunc(q,v);
        }
    }
    
    return 0;
}
   
