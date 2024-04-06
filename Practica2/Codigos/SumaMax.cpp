#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <cstring>
#include <chrono>
#include <utility>
using namespace std;


struct SumaData{
    int  max_izq;
    int  max_dch;
    int  sum;
    int  max_sub;
};

 
/**
 * Función que recibe un puntero a un vector y su tamaño, y calcula la suma más grande que encuentre
 * en una subsecuencia del array. La idea es la siguiente, se guardará tanto la suma que se hace a lo largo
 * del array continuamente como la máxima, es decir, @b max_current y @b max_global . Cuando se avanza en el array 
 * si la suma de los anteriores junto con el int actual del array es menor que el int actual, se cambiará la suma de 
 * la subsecuencia actual (por sólo el int) y se avanzará en el array, sumando, si es así el caso, los siguientes números.
 * 
 * Destacar que decimos "sí es así el caso" para indicar que si la suma del siguiente int y el nuevo
 * valor de @b max_current es menor al siguiente se cambiará el valor de dicha variable como hemos comentado
 * anteriormente.
 * Es claro que si en algun momento @b max_current supera a @b max_global se acutaliza el valor de @b max_global
 * 
 * @param a Puntero a un vector de int
 * @param size Tamaño del vector
 * @return Suma máxima de la mejor subsecuencia del vector
 * 
*/
pair<int, int> kadane(int *a, int inicio, int size){
    int max_global = a[inicio];
    int max_current = a[inicio];
    int indice=inicio;

    for (int i = inicio+1; i < size; i++) {
        max_current = max(a[i], max_current + a[i]);
        if (max_current > max_global) {
            max_global = max_current;
            indice=i;
        }
    }

    return pair<int, int>(max_global, indice);
}

// 5 6 -1 1 1 -5 9 1 -5 -2 
// SumaData SumaMax (int *v, int inicio, int final){
    // SumaData result, d1, d2;
    // if (inicio==final){
    //     result.max_izq = v[inicio];
    //     result.max_dch = v[inicio];
    //     result.sum = v[inicio];
    //     result.max_sub = v[inicio];
    //     return (result);
    // }

    // int mid = (final+inicio)/2;
    // d1=SumaMax(v, inicio, mid);
    // d2=SumaMax(v, mid+1, final);
    
    // result.max_izq = max(d1.max_izq, d1.sum+d2.max_izq);
    // result.max_dch = max(d2.max_dch, d2.sum+d1.max_dch);
    // result.sum = d1.sum + d2.sum;
    // int max_cross = d1.max_dch + d2.max_izq;
    // result.max_sub = max(max(max_cross, d1.max_sub), d2.max_sub);
    // return (result);
    // NO SE si lo que tenemos sirve porque hay que poner caso base con llamada a kadane o a n²

    // int caso_base=5;

    // if( (final-inicio+1) <= 5){
    //     struct Kadane k=kadane(v, final-inicio+1);
    //     return k;
    // }

    // int mid=(final+inicio)/2;
    // struct Kadane k1= SumaMax(v, inicio, mid);
    // struct Kadane k2=SumaMax(v, mid+1, final);


// }

pair<int,int> SumaMax (int *v, int inicio, int final){

    // Destacar que caso_base es el tamaño de la subsecuencia que se considera como base para
    // aplicar el algoritmo de Kadane. Si aumenta el valor de caso_base, disminuirá el tiempo de ejecución,
    // por lo que el mejor UMBRAl es aquel que tiene a infinito
    int caso_base=10000;

    if( (final-inicio) <= caso_base){
        pair<int,int> k=kadane(v, inicio, final);
        return k;
    }

    int mid=(final+inicio)/2;
    pair<int,int> k1= SumaMax(v, inicio, mid);
    pair<int,int> k2=SumaMax(v, mid, final);

    int max_global=k1.first;
    int indice_inicio=k1.second;
    int indice_final=k2.second;
    int max_current=k1.first;

    int indiceReturn=indice_inicio;
    for (int i = indice_inicio+1; i <= indice_final; i++) {
        max_current = max(v[i], max_current + v[i]);
        if (max_current > max_global) {
            max_global = max_current;
            indiceReturn=i;
        }
    }

    max_global=max(max_global, k2.first);
    if(max_global==k2.first){
        indiceReturn=k2.second;
    }
    pair<int,int> k={max_global, indiceReturn};

    return k;
}



int main(int argc, char *argv[]) {
    int TAM= atoi(argv[1]);
    srandom(TAM);
    int *v = new int [TAM];
    for (int i=0; i <TAM; i++){
        v[i] = rand() % 10 - (rand() % 10);
    }
    
    if (strcmp(argv[2], "1") == 0) { // Time Test Kadane

        auto start = chrono::high_resolution_clock::now();
        kadane(v,0, TAM);
        auto end = chrono::high_resolution_clock::now();
        std::cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<endl;

    } 
    else if (strcmp(argv[2], "2") == 0) { // Time Test DyV
        auto start = chrono::high_resolution_clock::now();
        SumaMax(v, 0, TAM);
        auto end = chrono::high_resolution_clock::now();
        std::cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<endl;
    } 
    else{ // Correctness Test
        int *kadaneVector = new int[TAM];
        for (int i = 0; i < TAM; i++) {
            kadaneVector[i] = v[i];
        }
        // {-1,1,1,10,-10,9,2}
        // int *prueba=new int[7];
        // prueba[0]=-1;
        // prueba[1]=1;
        // prueba[2]=1;
        // prueba[3]=10;
        // prueba[4]=-10;
        // prueba[5]=9;
        // prueba[6]=2;

        int res1 = SumaMax(v, 0, TAM).first;
        int res2 = kadane(v,0, TAM).first;
        if (res1 != res2) {
            std::cout << "Error [" << TAM << "]: " << res1 << " != " << res2 << endl;
        }
        
    }
    return 0;
}