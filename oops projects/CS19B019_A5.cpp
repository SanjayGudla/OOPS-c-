#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class BloomBrain{
    private:
        int* seraphic;
        int size;
        int* empty;
        long long int mergesort(int* b,int temp[],int left,int right);
        long long int merge(int* b,int temp[],int left,int mid,int right);
        int maxsubarray(int left,int right);
        int crossingsum(int left,int mid,int right);
        int maximum(int a,int b,int c);
    public:
        //constructor
        BloomBrain(int n){
             seraphic = new int[n];
             size=n;
             empty = new int[n];
             for(int i=0;i<n;i++){
                 empty[i]=0;
             }
        }
        //destructor
        ~BloomBrain(){
            delete [] seraphic;
            delete [] empty;
        }
        void update(int* a);
        void join(int s);
        void leave(int index);
        void play();
        void occupied();
};

/**
 *mergesort     - uses two find number of inversion vectors in array b by divide and conquer
 *@parameters   - left,right,array b, array temp 
 *@return       - returns inversions count in array b
**/
long long int BloomBrain::mergesort(int* b,int temp[],int left,int right){
    int mid;
    long long int invcount=0;
    if(left<right){
        mid = left+(right-left)/2;
        invcount=invcount+mergesort(b,temp,left,mid);
        invcount=invcount+mergesort(b,temp,mid+1,right);
        invcount=invcount+merge(b,temp,left,mid,right);
    }
    return invcount;
}

/**
 *merge        - merges two sub arrays and also finds inversion counts by maintaining two pointers to subarrays
 *@parameters  - left,mid,right,array b, array temp 
 *@return      - returns inversions count possible for these two sub arrays
**/
long long int BloomBrain::merge(int* b,int temp[],int left,int mid,int right){
    int i,j,k;
    long long int invcount=0;
    i=left;
    j=mid+1;
    k=left;
     while(k<=right){
        if((b[i]<=b[j]||j==right+1) && (i!=mid+1)){
            temp[k++]=b[i++];
        }
        else if(b[i]>b[j]||i==mid+1){
            temp[k++]=b[j++];
            invcount=invcount+(mid+1-i);
        }
    }
    for(int i=left;i<=right;i++){
        b[i]=temp[i];
    }
    return invcount;
}

/**
 *update       - It will take an array  as input which indicates the corresponding seraphic number of members.                            prints the number of quality talks possible (between existing members) after the update.
 *@parameters  - no parameters
 *@return      - prints number of quality talks
**/
void BloomBrain::update(int* a){
    for(int i=0;i<size;i++){
        seraphic[i]=a[i];
    }
    int count=0;
    for(int i=0;i<size;i++){
        if(empty[i]==1){
            count++;
        }
    }
    int* b =new int[size-count];
    int j=0;
    for(int i=0;i<size;i++){
        if(empty[i]!=1){
            b[j]=seraphic[i];
            j=j+1;
        }
    }
    int* temp=new int[size-count];
    long long int x = mergesort(b,temp,0, size-count-1);
    cout<<x<<"\n";
    delete [] b;
    delete [] temp;
}

/**
 *join         - It will take one integer value as input which indicates the initial seraphic number of the new joining                  member. This new member will be given the last (highest number) unoccupied room.
 *@parameters  - no parameters
 *@return      - does not return anything
**/
void BloomBrain::join(int s){
    int k=size-1;
    while(empty[k]!=1){
        k--;
    }
    seraphic[k]=s;
    empty[k]=0;
}

/**
 *leave        - It will take one integer value as input, the member occupying that room number will leave the centre.                    The room will be emptied with a 0 seraphic number.
 *@parameters  - no parameters
 *@return      - does not return anything
**/
void BloomBrain::leave(int index){
    empty[index]=1;
    seraphic[index]=0;
}

/**
 *occupied     - This will output the number of existing members in the centre.
 *@parameters  - no parameters
 *@return      - prints current existing members
**/
void BloomBrain::occupied(){
    int k=0;
    for(int i=0;i<size;i++){
        if(empty[i]==0){
            k++;
        }
    }
    cout<<k<<"\n";
}

/**
 *play         - calculates minimum seraphic number that the guru must have so that he will not lose even against the                    best valid group of members
 *@parameters  - no parameters
 *@return      - prints the minimum value guru needed
**/
void BloomBrain::play(){
    int seraphicnum = maxsubarray(0,size-1);
    cout<<seraphicnum<<"\n";
}

/**
 *maxsubarray     - used to calculate maxsubarray sum using divide and conquer
 *@parameters     - left and right pointers of array
 *@return         - returns maximum subarray sum
**/
int BloomBrain::maxsubarray(int left,int right){
    if(left==right){
        return seraphic[1];
    }
    int mid = left+(right-left)/2;
    return maximum(maxsubarray(left,mid),maxsubarray(mid+1,right),crossingsum(left,mid,right));
}

/**
 *crossingsum     - used to find maximum overlapping sum
 *@parameters     - left,right,mid pointers
 *@return         - maximum overlapping sum
**/
int BloomBrain::crossingsum(int left,int mid,int right){
    int sum=0;
    int leftsum=INT_MIN;
    for(int i=mid;i>=left;i--){
        sum = sum+seraphic[i];
        if(sum > leftsum){
            leftsum=sum;
        }
    }
    sum=0;
    int rightsum=INT_MIN;
    for(int i=mid+1;i<=right;i++){
        sum = sum+seraphic[i];
        if(sum > rightsum){
            rightsum=sum;
        }
    }
    return maximum(leftsum,rightsum,leftsum+rightsum);
}

/**
 *maximum      - used to find maximum of three numbers
 *@parameters  - thre numbers of integer type
 *@return      - maximum of three integers given as parameters
**/
int BloomBrain::maximum(int a,int b,int c){
    int max;
    max = a>b?a:b;
    max = c>max?c:max;
    return max;
}

int main() {
    int n;
    cin>>n;
    int q;
    cin>>q;
    string s;
    int a[n];
    BloomBrain object(n);            //Declaring a BloomBrain object and Default constuctor is called
    int b;
    for(int i=0;i<q;i++){
        cin>>s;
        if(s=="update"){
            for(int j=0;j<n;j++){
                cin>>a[j];
            }
            object.update(a);         //calling update function
        }
        else if(s=="play"){
            object.play();            //calling play function 
        }
        else if(s=="join"){
            cin>>b;
            object.join(b);           //calling join function
        }
        else if(s=="leave"){
            cin>>b;
            object.leave(b);           //calling leave function
        }
        else if(s=="occupied"){
            object.occupied();         //calling occupied function
        }
    }
    return 0;
}
