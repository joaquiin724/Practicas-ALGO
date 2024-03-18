#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
using namespace std;
using namespace std;

struct data{
    int  max_izq;
    int  max_dch;
    int  sum;
    int  max_sub;
};



// 5 6 -1 1 1 -5 9 1 -5 -2 
data SumaMax (int *v, int inicio, int final){
    data result, d1, d2;
    if (inicio==final){
        result.max_izq = v[inicio];
        result.max_dch = v[inicio];
        result.sum = v[inicio];
        result.max_sub = v[inicio];
        return (result);
    }

    int mid = (final+inicio)/2;
    (d1)=SumaMax(v, inicio, mid);
    (d2)=SumaMax(v, mid+1, final);
    
    result.max_izq = max(d1.max_izq, d1.sum+d2.max_izq);
    result.max_dch = max(d2.max_dch, d2.sum+d1.max_dch);
    result.sum = d1.sum + d2.sum;
    int max_cross = d1.max_dch + d2.max_izq;
    result.max_sub = max(max(max_cross, d1.max_sub), d2.max_sub);
    return (result);
}
 
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
    const int TAM=11;
    srand (time(NULL));
    int *v = new int [TAM];
    for (int i=0; i <TAM; i++){
        v[i] = rand() % 10 - (rand() % 10);
        cout << v[i] << " ";
    }
    
    int kadaneResult = kadane(v,TAM);


    cout << "Nuestro resultado: " << SumaMax(v, 0, TAM).max_sub << "  ";
    cout << "Kadane: " << kadaneResult << endl;


}
// int main(){
//     const int TAM = 10;
//     int *v = new int[TAM];
    
    
//     srand(time(NULL));

//    for (int i = 0; i < TAM; i++)
//     {
//       v[i] = random() % 10 -(random()%10);
//       cout << v[i] << " ";
//     };

//     cout << "Nuestro resultado: " << SumaMax(v, 0, TAM).max_sub << "  ";
//     cout << "Kadane: " << kadane(v,TAM) << endl ;
//     return 0;
// }



