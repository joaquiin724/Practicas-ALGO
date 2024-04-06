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
#include <random>
using namespace std;
int losas = 1;
int i_sumidero ,j_sumidero;


void resuelve2(vector<vector<int>> & matriz2d){
    for(int i  =0; i< matriz2d.size(); i++){
        for(int j = 0; j< matriz2d.size();j++){
            if(matriz2d[i][j] == 0 ){
                matriz2d[i][j] = losas;
            }
        }
    }
    losas++;
    
}
void getSumidero(int & x_sumidero , int & y_sumidero , vector<vector<int>> & mat ,int n){
    for(int i = 0; i< n; i++){
        for(int j = 0; j<n; j++){
            if(mat[i][j] != 0){
                x_sumidero = i;
                y_sumidero = j;
            }
        }
    }
}

void enlosar(int i1, int j1,int i2 , int j2 , int i3 , int j3,vector<vector<int>> &mat){
    mat[i1][j1] = losas;
    mat[i2][j2] = losas;
    mat[i3][j3] = losas;
    losas++;
}

void resolver(int n,int i,int j,vector<vector<int>> &mat){
    if(n == 2){
        losas++;
        for(int l = 0; l< n; l++){
            for(int k = 0; k<n; k++){
                if(mat[i+l][j+k] == 0){
                    mat[i+l][j+k] = losas;
                }
            }
        }
    }
    else{
        int i_sumidero,j_sumidero;
        getSumidero(i_sumidero, j_sumidero,mat,n);
        //Superior Izquierda 
        if(i_sumidero < i + n/2  && j_sumidero < j + n/2){
            enlosar(i+n/2-1,j+n/2,i+n/2,j+n/2-1,i+n/2,j+n/2,mat);
        }
        //Inferior izqwuierda
        else if(i_sumidero >= i+n/2 && j_sumidero < j +n/2){ 
            enlosar(i+n/2-1,j+n/2 -1, i+n/2 -1 , j+n/2 , i+n/2 ,j + n/2 ,mat);
        }
        //Superior derecha
        else if(i_sumidero < i +n/2 && j_sumidero >= n/2 + j){ //Superior izquierda
            enlosar(i+n/2-1,j+n/2 -1, i+n/2 , j+n/2-1 , i+n/2 ,j + n/2 ,mat);
        }
        //Inferior Derecha
        else{
            enlosar(i+n/2-1,j+n/2 -1, i+n/2 , j+n/2-1 , i+n/2 -1 ,j + n/2 ,mat);
        }
        resolver(n/2,i,j,mat);
        resolver(n/2,i+n/2,j,mat);
        resolver(n/2,i,j+n/2,mat);
        resolver(n/2, i+n/2, j+n/2, mat);
    }


}

void generarcasos(int &i_sum, int &j_sum ,int &n){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1,8);
    n = distribution(gen);
    n= pow(2,n);
    uniform_int_distribution<int> distribution1(0,n-1);
    i_sum = distribution1(gen);
    j_sum = distribution1(gen);
}






void printm(const vector<vector<int>> &mat){
    for (int i = 0; i< mat.size();i++){
        cout << "  ";
        for (int j=0; j<mat.size();j++){
            cout << mat[i][j] << "  ";
        }
        cout << endl;
    }
}
int main(int argc ,char *argv[]){
    int n;
    int i,j;
    int casos = 1;
    
    for(int l = 0; l< casos; l++){
        generarcasos(i, j,n);
        vector<vector<int>> matriz(n,vector<int>(n,0));
        matriz[i][j] =-1;
        resolver(n,0,0,matriz);
        matriz[i][j] =0;
        cout << endl;
        printm(matriz);
    
    }
    return 0;

}