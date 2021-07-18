#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class EDD{
 private:
     string s1;
     string s2;
     int** matrix;
     int update;
     int minimum(int a,int b);
 public:
     void assign(string a,string b);
     void compdist();
     int  dist();
     void table();
};

int EDD::minimum(int a,int b){
     if(a<b){
         return a;
     }
     return b;
}

/**
 *assign        - sets s1=a,s2=b and dynomically allocate space for matrix,marks update =0
 *@parameters   - two strings a and b
 *@return       - returns nothing
**/
void EDD::assign(string a, string b){
     s1=a;
     s2=b;
     int length1 = a.size()+1;
     int length2 = b.size()+1;
     matrix = new int*[length1];
     for(int i=0;i<length1;i++){
         matrix[i] = new int[length2];
     }
     update = 0;
}

/**
 *compdist      -  Computes the edit distance between the two strings stored in the class.throws ann exception if the                      strings are not initialized,updates the matrix table ,marks update =1 
 *@parameters   -  no parameters
 *@return       -  returns nothing but updates matrix table by dynamic programming approach
**/
void EDD::compdist(){
        if(s1.size() == 0 || s2.size() == 0){
            throw  "strings not found!";
        }
        int insert;
        int del;
        int replace;
        int length1 = s1.size();
        int length2 = s2.size();
        for(int j=0;j<=length2;j++){
            matrix[0][j]=j;
        }
        for(int i=1;i<=length1;i++){
            matrix[i][0]=i;
            for(int j=1;j<=length2;j++){
               insert=matrix[i][j-1]+1;
               del=matrix[i-1][j]+1;
               replace = matrix[i-1][j-1]+1;
               if(s1[i-1]==s2[j-1]){
                   replace = matrix[i-1][j-1];
               }   
               matrix[i][j]=minimum(insert,del);
               matrix[i][j]=minimum(replace,matrix[i][j]);
            }
        }
        update =1;
}

/**
 *dist          -  returns the edit distance between the two strings if matrix is up to date . otherwise calls compdist                    to update matrix and then returns distance,throws an exception if the strings are not initialized
 *@parameters   - no parameters
 *@return       - returns editdistance
**/
int EDD::dist(){
     if(s1.size() == 0 || s2.size() == 0){
            throw  "strings not found!";
     }
    if(update==1){
        return matrix[s1.size()][s2.size()];
    }
    else {
        compdist();
        return matrix[s1.size()][s2.size()];
    }
}

/**
 *table         - outputs the table if available. If not available,runs compdist() and then output the table. 
                  throws an exception if the strings are not initialized
 *@parameters   - no parameters
 *@return       - returns nothing but prints matrix created
**/
void EDD::table(){
     if(s1.size() == 0 || s2.size() == 0){
            throw  "strings not found!";
     }
     int length1 = s1.size();
     int length2 = s2.size();
     if(update==1){
         for(int i=1;i<=length1;i++){
            for(int j=1;j<=length2;j++){
               cout<<matrix[i][j]<<" ";
             }
            cout<<endl;
         }
    }
    else {
        compdist();
        for(int i=1;i<=length1;i++){
           for(int j=1;j<=length2;j++){
              cout<<matrix[i][j]<<" ";
            }
            cout<<endl;
        }
    } 
}

int main() {
    int q;                            //number of queries
    cin>>q;
    string querystring;              
    EDD obj;                          //declaring EDD object
    for(int i=0;i<q;i++){
       cin>>querystring;
       if(querystring=="assign"){
           string a;
           string b;
           cin>>a>>b;
           obj.assign(a,b);            //calling assign function
       }
       else if(querystring=="compdist"){
           try{
               obj.compdist();         //calling ccompdist funtion
           }
           catch(const char*msg){
               cout<<msg<<endl;
           }
       }
       else if(querystring=="dist"){
           try{
              cout<< obj.dist()<<endl;  //calling dist function
           }
           catch(const char*msg){
               cout<<msg<<endl;
           }  
       }
       else if(querystring=="table"){
          try{
               obj.table();             //calling table function
           }
           catch(const char*msg){
               cout<<msg<<endl;
           }  
       }
    }
    return 0;
}
