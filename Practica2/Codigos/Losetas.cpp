#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cassert>
using namespace std;
struct pos{
    int i;
    int j;
};
void resuelve2(vector<vector<int>> & matriz2d , pos p){
    for(int i  =0; i< matriz2d.size(); i++){
        for(int j = 0; j< matriz2d.size();j++){
            if (p.i == i && p.j == j){
                matriz2d[i][j] =0;
            }
            else{
                matriz2d[i][j] =1;
            }
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
    int rows = 2,cols =2;
    vector<vector<int>> matriz(rows,vector<int>(cols));
    pos sumidero;
    sumidero.i = 0;
    sumidero.j = 0;
    resuelve2(matriz,sumidero);
    printm(matriz);
    return 0;
}