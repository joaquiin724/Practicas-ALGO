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

void resuelve2(vector<vector<int>> & matriz2d , int i_,int j_){
    for(int i  =0; i< matriz2d.size(); i++){
        for(int j = 0; j< matriz2d.size();j++){
            if (i == i_ && j == j_){
                matriz2d[i][j] =0;
            }
            else{
                matriz2d[i][j] =1;
            }
        }
    }
}
void resuelve(vector<vector<int>>&mat ,int i,int j){
    
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
    int rows = 2,cols =2,i=0,j=0;
    vector<vector<int>> matriz(rows,vector<int>(cols));
    resuelve2(matriz,i,j);
    printm(matriz);
    return 0;
}