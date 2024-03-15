#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

const int TAM=10;

// int SumaMax (int *v, int inicio, int final){

// }
 
int kadane(int *a, int size){
    int max_so_far = INT_MIN, max_ending_here = 0;
 
    for (int i = 0; i < size; i++) {
        max_ending_here = max_ending_here + a[i];
        if (max_so_far < max_ending_here)
            max_so_far = max_ending_here;
 
        if (max_ending_here < 0)
            max_ending_here = 0;
    }
    return max_so_far;
}


int main(int argc, char *argv[]){
    srand (time(NULL));
    int *v = new int [TAM];
    for (int i=0; i <TAM; i++){
        v[i] = rand() % 10 - rand() % 10;
        cout << v[i] << " ";
    }
    
    //int ourResult = SumaMax(v, inicio, TAM);
    int kadaneResult = kadane(v,TAM);


    // cout << "Nuestro resultado: " << ourResult << endl;
    cout << "Kadane: " << kadaneResult << endl;


}




