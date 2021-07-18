#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Matrix{
    private:
        int **mat;
        int size;
    public:
        void CreateMatrix(int n);
        void InsertValue(int i,int j,int value);
        int GetElements(int i,int j);
        void SpecialSum();
        int FindMaxinRow(int row);     //Returns Max value in a row
        int FindMininRow(int row);     //Returns Min value in a row
        int FindAverage(int row);      //Returns Average Value of the row
        void ModMultiplication();
        void MatrixRightShift(Matrix b,int p);
        void SpecialMatrixAddition(Matrix b);
};

/**
 *CreateMatrix - Dynamically allocates memory of size n*n using new keyword
 *@parameters  - n is the no of rows of square matrix
 *@return      - does not return anything
**/
void Matrix::CreateMatrix(int n){
    mat=new int*[n];
    for(int i=0;i<n;i++)
      {
        mat[i]=new int[n];
      }
    size=n;
}

/**
 *InsertValue  - assign value to mat[i][j]
 *@parameters  - i and j are the positions at which value to be assigned
 *@return      - does not return anything
**/
void Matrix::InsertValue(int i,int j,int value){
    mat[i][j]=value;
}

/**
 *GetElements  - returns the value at mat[i][j]
 *@parameters  - i and j are the positions at which value to be fetched
 *@return      - returns an integer value which is mat[i][j]
**/
int Matrix::GetElements(int i,int j){
    return mat[i][j];
}

/**
 *SpecialSum   - Creates a new matrix mat1 and copies all elements from mat to mat1 in such a way that if i+j is odd       then mat[j][i] is copied to mat1[i][j]

 *@parameters  - no parameters
 *@return      - does not return anything

 *    Method  : Using nested for loops
 *    prints rowwise sum of the mat1
**/
void Matrix::SpecialSum(){
    int mat1[size][size];
    for(int i=0;i<size;i++)
      {
        for(int j=0;j<size;j++)
          {
            if((i+j)%2==1){
                mat1[i][j]=mat[j][i];
            }
            else{
                mat1[i][j]=mat[i][j];
            }
          }
      }
    int sum;
    for(int i=0;i<size;i++)
      {
        sum=0;
        for(int j=0;j<size;j++)
          {
            sum=sum+mat1[i][j];
          }
        cout<<sum;           //printing Row wise Sum
        if(i!=size-1){
            cout<<",";
        }
      }
}

/**
 *ModMultiplication - If row index(i) is divisible by 3, finds the max element of that row. If i gives 1 on division by  3, then finds the minimum element of that row. Otherwise, finds the floor of average of that row. Print the product of   these elements

 *@parameters       - no parameters
 *@return           - does not return anything

 *    Method        : maintains a long long int product variable and updating it each iteration accordingly
**/
void Matrix::ModMultiplication(){
    long long int product=1;
    for(int i=0;i<size;i++)
      {
        if(i%3==0){
            int max=FindMaxinRow(i);
            product=product*max;
        }
        else if(i%3==1){
            int min=FindMininRow(i);
            product=product*min;
        }
        else if(i%3==2){
            int average=FindAverage(i);
            product=product*average;
        }

      }
    cout<<product;
}

int Matrix::FindMaxinRow(int row){
    int max=mat[row][0];
    for(int i=1;i<size;i++)
      {
        if(mat[row][i]>max){
            max=mat[row][i];
        }
      }
    return max;
}

int Matrix::FindMininRow(int row){
    int min=mat[row][0];
    for(int i=1;i<size;i++)
      {
        if(mat[row][i]<min){
            min=mat[row][i];
        }
      }
    return min;
}

int Matrix::FindAverage(int row){
    int sum=0;
    for(int i=0;i<size;i++)
      {
        sum=sum+mat[row][i];
      }
    int average=floor(sum/size);
    return average;
}

/**
 *MatrixRightShift  - Performs right shift operation on each matrix(p times). Prints the sum of these shifted matrices

 *@parameters       - int p (no of times to shift),Matrix b which is a object of Matrix Class type
 *@return           - does not return anything

 *    Method        : takes the sum of matrices and stores it in array arr of Size*Size by calculating index as     (i*size)+j and then shifts this array k times to form arr1 by arr1[(i+k)%(size*size)]=arr[i]
**/
void Matrix::MatrixRightShift(Matrix b,int k){
    int arr[size*size];
    int arr1[size*size];
    int arr2[size*size];
    int arr3[size*size];
    for(int i=0;i<size;i++)
      {
        for(int j=0;j<size;j++)
          {
            arr[(i*size)+j]=mat[i][j];
            arr1[(i*size)+j]=b.GetElements( i,  j);
          }
      }
    for(int i=0;i<size*size;i++)
      {
        arr2[(i+k)%(size*size)]=arr[i];
        arr3[(i+k)%(size*size)]=arr1[i];
      }
    for(int i=0;i<size*size;i++){
        arr3[i]=arr2[i]+arr3[i];
    }
    for(int i=0;i<size*size;i++)
      {
        cout<<arr3[i]<<" ";
        if((i+1)%size==0){
            cout<<"\n";
        }
      }
}

/**
 *SpecialMatrixAddition- performs a transformation on the elements of 1st matrix such that A[i][j] gets swapped with      A[j][i]. Then, add it to the 2nd matrix B and print the resulting matrix

 *@parameters       - Matrix b which is a object of Matrix Class type
 *@return           - does not return anything

 *    Method        : Creates matrix mat1 and copies elements in mat to mat1 in such a way that                                               A[i][j] and A[j][i] are swapped and then adds this mat1 to matrix b
**/
void Matrix::SpecialMatrixAddition(Matrix b){
    int mat1[size][size];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            mat1[i][j]=mat[j][i];
        }
    }
    for(int i=0;i<size;i++)
      {
        for(int j=0;j<size;j++)
          {
            cout<<mat1[i][j]+b.GetElements( i,  j)<<" ";
          }
        cout<<"\n";
      }

}
/**************************************************End of Matrix Class ************************************************/

int main() {
    int q;          /*No of queries*/
    int n;          /*No of rows in Square Matrix*/
    int c;
    int d;
    string s;
    cin>>q;
    cin>>n;
    Matrix objectA;  //declaration of object of Matrix type
    Matrix objectB;
    objectA.CreateMatrix(n);
    objectB.CreateMatrix(n);
    for(int i=0;i<n;i++)
      {
        for(int j=0;j<n;j++)
          {
            cin>>c;
            objectA.InsertValue(i, j, c); /*Inserting Read input values into objectA*/
          }
      }
    for(int i=0;i<n;i++)
      {
        for(int j=0;j<n;j++)
          {
            cin>>d;
            objectB.InsertValue(i, j, d); /*Inserting Read input values into objectB*/
          }
      }
    /*For each query reads the string s and perfoms the respective opeartion */
    for(int i=0;i<q;i++)
      {
        cin>>s;
        if(s=="SPSUM"){
            objectA.SpecialSum();
            cout<<"\n";
        }
        else if(s=="MOD"){
            objectA.ModMultiplication();
            cout<<"\n";
        }
        else if(s=="MRS"){
            int k;
            cin>>k;
            objectA.MatrixRightShift(objectB,k);
        }
        else if(s=="MADD"){
            int x;
            cin>>x;
            if(x==1){
                objectA.SpecialMatrixAddition(objectB);
            }
            else if(x==2){
                objectB.SpecialMatrixAddition(objectA);
            }
        }
      } /*End of For loop*/
    return 0;
}
