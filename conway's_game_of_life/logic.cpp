#include <iostream>
using namespace std;


void game_of_life(int **arr){
    int **temp=new int*[5];
    for(int i =0;i<5;i++){
        temp[i]=new int [5];
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
                temp[i][j]=arr[i][j];
        }
    }

        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                int count=0;
                if(i-1>=0 && j-1>=0 && arr[i-1][j-1]==1){
                    count++;
                }
                if(i-1>=0 && arr[i-1][j]==1){
                    count++;
                }
                if(i-1>=0 && j+1<5 && arr[i-1][j+1]==1){
                    count++;
                }
                if(j-1>=0 && arr[i][j-1]==1){
                    count++;
                }
                if(j+1<5 && arr[i][j+1]==1){
                    count++;
                }
                if(i+1<5 && j-1>=0 && arr[i+1][j-1]==1){
                    count++;
                }
                if(i+1<5 && arr[i+1][j]==1){
                    count++;
                }
                if(i+1<5 && j+1<5 && arr[i+1][j+1]==1){
                    count++;
                }
    
                if(arr[i][j]==0 && count==3){
                    temp[i][j]=  1;
                }
                else if(arr[i][j]==  0 && count!=3){
                    temp[i][j]=  0;
                }
                else if(arr[i][j]==  1 && (count==2 || count==3)){
                    temp[i][j]=  1;
                }
                else if(arr[i][j]==  1 && (count<2 || count>3)){
                    temp[i][j]=  0;
                }
    
            }
        }
    
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                    arr[i][j]=temp[i][j];
            }
        }

    for(int i=0;i<5;i++){
        delete[] temp[i];
    }
    delete[] temp;

}

void display(int **arr){
    for(int i =0;i<5;i++){
        for(int j =0;j<5;j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}


void makecell(int **arr){
   for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cin>>arr[i][j];
        }
   }
   cout<<endl;
}


int main(){
    int **arr = new int*[5];
    for(int i = 0; i < 5; i++){
        arr[i] = new int[5];
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            arr[i][j] = 0;
        }
    }
     makecell(arr);
     game_of_life(arr);
     display(arr);
     
    for (int i =0;i<5;i++){
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}