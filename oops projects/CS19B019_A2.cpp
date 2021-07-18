#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Matrix{
    protected:
        int **A;
        int rows;
        int coloumns;
    public:
        void createMatrix(int n,int m);
        void insertValue(int elem,int i,int j);
        int  binarySearch(int x,int k);
        void matrixSearch(int y);
        void freeMatrix();
};

/**
 *createMatrix - Dynamically allocates memory of size n*m using new keyword 
 *@parameters  - n is the no of rows,m is no of coloumns in the matrix of square matrix
 *@return      - does not return anything
**/
void Matrix::createMatrix(int n, int m){
    A = new int*[n];
    for(int i=0;i<n;i++)
      {
        A[i]=new int[m];
      }
    rows=n;
    coloumns=m;
}

/**
 *insertValue  - assign elem to mat[i][j]
 *@parameters  - i and j are the positions at which value to be assigned
 *@return      - does not return anything
**/
void Matrix::insertValue(int elem,int i,int j){
    A[i][j]=elem;
}

/**
 *freeMatrix   - deallocates the dynamically created 2D matrix
 *@parameters  - no parameters
 *@return      - returns nothing
**/
void Matrix::freeMatrix(){
    for(int i=0;i<rows;i++)
      {
        delete [] A[i];
      }
    delete [] A;
}
/**
 *binarySearch  - Searches for element x in the kth row of the matrix using binary search
 *@parameters   - x is elemented to be searched,k is the row of the matrix in which we have to search
 *@return       - returns the int which is largest index such that A[j][k]<=x.If no such index can be found,returns -1 
**/
int Matrix::binarySearch(int x,int k){
    int left=0;
    int right=coloumns-1;
    while(left<=right)
      {
        int mid=left+(right-left)/2;
        if(A[k][mid]<=x){
            left=mid+1;
        }
        else if(A[k][mid]>x){
            right=mid-1;
        }
      }
    return right;
}

/**
 *matrixSearch  - Searches for element y in the entire matrix by traversing the whole matrix rowwise using two iterators
 *@parameters   - y is the element to be searched
 *@return       - returns nothing but prints the indices at which y is present.if no such indices prints -1 -1
**/
void Matrix::matrixSearch(int y){
    int i=0;
    int j=0;
    int x=0;
    for(i=0;i<rows;i++)
      {
        for( j=0;j<coloumns;j++)
          {
            if(A[i][j]==y){
                x=1;
                break;
            }
          }
        if(x==1){
            break;
        }
      }
    if(i!=rows){
    cout<<i<<" "<<j;
    }
    if(i==rows){
        cout<<"-1"<<" "<<"-1";
    }
}
/*******************************************End of Matrix Class********************************************************/

/*MatrixMedian is Public inherited class of Matrix . The public and protected elements of Matrix class will public and protected elements of MatrixMedian Class respectively */

class MatrixMedian : public Matrix{
    public:
        int findMedian();
    private:
        int upperBound(int x,int k);
        int maxinColoumn(int c);
        int mininColoumn(int c);
};

/**
 *upperBound   - This method uses the inherited binarySearch() method to find the smallest index j such that A[j][k]>x
 *@parameters  - x is elemented to be searched,k is the row of the matrix in which we have to search
 *@return      - returns the int which is smallest index such that A[j][k]>x.If no such index can be found,returns -1
**/
int MatrixMedian::upperBound(int x,int k){
    if(binarySearch(x,k)!=coloumns-1){
        return binarySearch(x, k)+1;
    }
    return -1;
}

/**
 *findMedian   - computes overall median of the given matrix using binary search 
 *@parameters  - This method takes no parameters
 *@return      - returns an integer
 *@TimeComplexity - O(nlogm) 
 *@SpaceComplexity - O(1)
**/
int MatrixMedian::findMedian(){
    int mid;
    int reqnum=(rows*coloumns+1)/2;
    int matmax=maxinColoumn(coloumns-1);
    int matmin=mininColoumn(0);
    while(matmin<matmax){
         mid = matmin+(matmax-matmin)/2;
        int position=0;
        int i=0;
        while(i<rows){
            position+=upperBound(mid,i)!=-1?upperBound(mid,i):coloumns;
            i++;
        }
        if(position>=reqnum){
            matmax=mid;
        }
        else {
            matmin=mid+1;
        }

    }
    return matmax;
}

int MatrixMedian::maxinColoumn(int c){
    int max=A[0][c];
     for(int i=0;i<rows;i++){
        if(max<A[i][c]){
            max=A[i][c];
        }
    }
    return max;
}

int MatrixMedian::mininColoumn(int c){
    int min=A[0][c];
    for(int i=0;i<rows;i++){
         if(min>A[i][c]){
            min=A[i][c];
        }
    }
    return min;
}
/****************************************End of MatrixMedian Class*****************************************************/

int main() {
    int n;
    int m;
    int q;
    int result;
    cin>>n>>m;
    MatrixMedian object;        /*Declaratrion of MatrixMedian object which is inherited class of Matrix class*/
    object.createMatrix(n,m);   
    for(int i=0;i<n;i++)
      {
        for(int j=0;j<m;j++)
          {
            int elem;
            cin>>elem;
            object.insertValue(elem,i,j);
          }
      }
    cin>>q;
    string s;
    for(int i=0;i<q;i++)
      {
        cin>>s;
        if(s=="BS"){
            int x;
            int k;
            cin>>x>>k;
            result =object.binarySearch(x,k);
            cout<<result;
            cout<<"\n";
        }
        else if(s=="MS"){
            int y;
            cin>>y;
            object.matrixSearch(y);
            cout<<"\n";
        }
        else if(s=="Median"){
            result=object.findMedian();
            cout<<result;
            cout<<"\n";
        }
      }
    object.freeMatrix();           /*Deallocating the dynamically created space*/
    return 0;
}