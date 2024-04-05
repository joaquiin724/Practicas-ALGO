#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cassert>
using namespace std;

void resuelve2(vector<vector<int>> & matriz2d , int i_sumidero,int j_sumidero,int &losas,int &sumideros){
    for(int i  =0; i< matriz2d.size(); i++){
        losas++;
        for(int j = 0; j< matriz2d.size();j++){
            if (i == i_sumidero && j == j_sumidero){
                matriz2d[i][j] =sumideros;
            }
            else{
                matriz2d[i][j] =losas;
            }
        }
    }
    
}
string getSumidero(int i_sumidero,int j_sumidero,int n){
    if(i_sumidero < n/2 ){
        if(j_sumidero < n/2)
            return  "si";
        else
            return "sd";

    }
    else{
        return (j_sumidero < n/2) ? "ii" : "id";
    }
}

void resuelve(vector<vector<int>>&mat ,int i_sumidero,int j_sumidero,int inicio_i, int inicio_j ,int final_i ,int final_j ,int mat_size,int &los){
    int n= mat_size;
    int auxi_sumidero;
    int auxj_sumidero; 
    int sumideros = 0;

    string id_sumidero = getSumidero(i_sumidero,j_sumidero,n);
    if(n == 2){
        resuelve2(mat, i_sumidero, j_sumidero, los,sumideros);
    }
    else{

        if(id_sumidero == "si"){
            resuelve(mat,i_sumidero,j_sumidero,0,0,n/2-1,n/2-1,n/2,los);
            cout<<los;
            resuelve(mat,n/2-1,n/2,0,n/2,n/2-1,n-1,n/2,los);
            cout<<los;
            resuelve(mat,n/2,n/2 - 1,n/2,0,n-1,n/2-1,n/2,los);
            cout<<los;
            resuelve(mat,n/2,n/2,n/2,n/2,n-1,n-1,n/2,los);
            cout<<los;

        }
        else if(id_sumidero == "sd" ){
            resuelve(mat,n/2 -1,n/2 -1,0,0,n/2-1,n/2 -1,n/2,los);
            resuelve(mat,i_sumidero,j_sumidero,0,n/2,n/2-1,n-1,n/2,los);
            resuelve(mat,n/2,n/2-1 ,n/2,0,n-1,n/2-1,n/2,los);
            resuelve(mat,n/2,n/2,n/2,n/2,n-1,n-1,n/2,los);
        }
        else if(id_sumidero == "ii" ){
            resuelve(mat,n/2 -1,n/2 -1,0,0,n/2-1,n/2 -1,n/2,los);
            resuelve(mat,n/2-1,n/2,0,n/2,n/2-1,n-1,n/2,los);
            resuelve(mat,i_sumidero, j_sumidero, n/2, 0, n-1,n/2-1 ,n/2,los);
            resuelve(mat,n/2,n/2,n/2,n/2,n-1,n-1,n/2,los);
        }
        else{
            resuelve(mat,n/2 -1,n/2 -1,0,0,n/2-1,n/2 -1,n/2,los);
            resuelve(mat,n/2-1,n/2,0,n/2,n/2-1,n-1,n/2,los);
            resuelve(mat,n/2,n/2-1 ,n/2,0,n-1,n/2-1,n/2,los);
            resuelve(mat,i_sumidero,j_sumidero ,n/2,n/2,n-1,n-1,n/2,los);
        }
    }


    
}
void printm(const vector<vector<int>> &mat){
    for (int i = 0; i< mat.size();i++){
        cout << " ";
        for (int j=0; j<mat.size();j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
int main(int argc ,char *argv[]){
    int n = 4;
    int losa = 1;
    vector<vector<int>> matriz(n,vector<int>(n));
    resuelve(matriz,0,1,0,0,n,n,n,losa);
    cout << endl;
    printm(matriz);
    return 0;

}