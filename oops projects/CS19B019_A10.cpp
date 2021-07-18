#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class MineSweeper{
    private:
        int** grid;
        int boardsize;
        int nummines;
        int revealedcount=0;
        int check=0;
        int checkneighbourcells(int x,int y);
        void checkfurther(int x,int y);
    public:
        /*constructor*/
        MineSweeper(int n,int m){
            grid = new int*[n];
            for(int i=0;i<n;i++){
                grid[i]=new int[n];
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    grid[i][j]=-2;
                }
            }
            boardsize=n;
            nummines=m;
        }
       /*Destructor*/
      ~MineSweeper(){
          for(int i=0;i<boardsize;i++){
              delete [] grid[i];
          }
          delete [] grid;
       }
       void markmines(int position);
       void playgame(int x,int y);
       void printrevealed();
       int checkwinorloss();
};

/**
 *markmines  - Marks the respective cell of grid with -1 to indicate a mine
 *@parameters      - position to be marked as mine
 *@return          - returns nothing
**/
void MineSweeper::markmines(int position){
    int x = position/boardsize;
    int y = position%boardsize;
    grid[x][y]=-1;
}

/**
 *checkneighbourcells   - Checks all the surrounding cells of a given cell and count no of mines sourrounding
 *@parameters           - x,y denoting position of cell to be checked
 *@return               - returns number of mines surrounding to the input cell
**/
int MineSweeper::checkneighbourcells(int x, int y){
    int count=0;
    for(int i=x-1;i<=x+1;i++){
        for(int j=y-1;j<=y+1;j++){
            if(i<boardsize && i>=0 && j<boardsize && j>=0){
                if(grid[i][j]==-1){
                    count++;
                }
            }
        }
    }
    return count;
}

/**
 *playgame      - 1) if the clicked position is mine Prints Lost
                  2) if the clicked position is not mine and has mines surrounding then nothing is revealed except the
                     clicked postion
                  3) if the clicked position is not mine and has no mines surrounding then all the surrounding cells are                      revealed and all the cells sorrounding to these are also explored further
                  
 *@parameters   - int x,y position where player clicked
 *@return       - returns nothing
**/
void MineSweeper::playgame(int x,int y){
    int count = checkneighbourcells(x,y);
    if(grid[x][y]==-1){
        check=1;
        cout<<"Lost"<<endl;
    }
    else if(count>0){
        if(grid[x][y]==-2){
            revealedcount++;
            grid[x][y]=count;
        }
        printrevealed();
    }
    else if(count==0){
        if(grid[x][y]==-2){
            revealedcount++;
        }
        grid[x][y]=0;
        checkfurther(x,y);
        printrevealed();
    }
}

/**
 *checkfurther   - checks input cell neighbours and if none of them are mines, all of them are revealed and                                this function is recursively called for all these neighbours and explore further.
 *@parameters    - x,y representing position of cell to be explored
 *@return        - returns nothing
**/
void MineSweeper::checkfurther(int x, int y){
    int count = checkneighbourcells(x,y);
    grid[x][y]=count;
    if(count==0){
        for(int i=x-1;i<=x+1;i++){
            for(int j=y-1;j<=y+1;j++){
                if(i<boardsize && i>=0 && j<boardsize && j>=0){
                    if(grid[i][j]==-2){
                         revealedcount++;
                         checkfurther(i,j);
                    }
                }
             }
        }
    }   
}

/**
 *printrevealed   -  prints Won if revealedcount reaches boardsize*boardsize-nummines else the number of cells that have                          been revealed up to this point which are not mines 
 *@parameters     -  no input
 *@return         -  nothing
**/
void MineSweeper::printrevealed(){
    if(revealedcount==boardsize*boardsize-nummines){
        check=1;
        cout<<"Won"<<endl;
    }
    else{
         cout<<revealedcount<<endl;
    } 
}

int MineSweeper::checkwinorloss(){
    return check;
}
/***********************************************************************/
int main() {
     int n;
     int m;
     cin>>n>>m;
     MineSweeper boardgame(n,m);            //declaring object of MineSweeper class
     int mineposition;
     for(int i=0;i<m;i++){
         cin>>mineposition;
         boardgame.markmines(mineposition); //marking mines 
     }
    int a; 
    int b;
    //taking input until eof 
    while(!cin.eof()){
        cin>>a>>b;
        boardgame.playgame(a, b);
        //whenever winorloss bit is 1 break the while loop
        if(boardgame.checkwinorloss()==1){
            break;
        }
    }
    return 0;
}
