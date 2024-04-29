#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <iomanip> 
#include <chrono>

using namespace std;



void vectorGenerator ( const int & size, vector<double> &v){
    
    const int MAX_ASSETS_VALUE=10;

    srand48(time(NULL));

    for (int i=0; i<size; i++){
        v.push_back(drand48()*MAX_ASSETS_VALUE);
    }
}

void inheritance(vector<double> & father, vector<double> son1, vector <double> son2){


    //Ordenamos el vector
    sort(father.begin(),father.end());

    //Dividimos el vector entre dos por un numero aleatorio
    srand(time(NULL));
    int partition=rand() % father.size();

    //Vemos cual es el rango mas grande de las dos particiones y sobre ese rango incluiremos los
    //valores mas grandes
    int range=(partition > (father.size()-partition))? partition : (father.size()-partition);

   
    for (int i = 0; i<father.size();++i){
        //Lo hago con dos if para que tenga la forma de los algoritmos voraces

        //En el if se encuentra son1 que sera el que obtenga el maximo beneficio
        //ya que se cogeran el mayor numero de elementos posibles empezando por el
        //mas grande, ya que se encuentran ordenados de mayor a menor
        if(i<range){
            son1.push_back(father.back());
            father.pop_back();
        }else{
            son2.push_back(father.back());
            father.pop_back();
        }
    }
}


void showVector(ofstream &output, const vector<double>& son1, const vector<double> & son2) {
    // Configurar la salida para mostrar números con tres decimales
    output << fixed << setprecision(3);
    double sum1=0,sum2=0;

    output<<"Hijo 1(mayor beneficio):\n";
    for (int i = 0; son1.size();++i ){
        output<<son1[i];
        sum1+=son1[i];
    }
    output<<"El beneficio obtenido por el hijo 1 es: " << sum1 << endl;

    output << "Hijo 2:\n";
    for (int i = 0; son2.size();++i ){
        output<<son2[i];
        sum2+=son2[i];
    }
    output<<"El beneficio obtenido por el hijo 2 es: " << sum2 << endl;

    output << endl;
}

int main(int argc, char *argv[]) {

    if(argc != 3){
        cout << "Numero incorrecto de parametros\n";
        return 1; 
    }

    //Creamos el vector
    int v_size=atoi(argv[1]);
    vector<double> v,son1,son2;
    vectorGenerator(v_size,v);

    //Vemos cuanto tiempo tarda en ejecutarse la funcion
    auto start = chrono::high_resolution_clock::now();
    //Resolvemos problema 1
    inheritance(v,son1,son2);
    auto end = chrono::high_resolution_clock::now();
    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<std::endl;
    

    //Imprimimos por otro archivo el reultaddo de como quedarian los vectores
    ofstream output((string)argv[2]);

    if (!output.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    
    showVector(output,son1,son2);

    output.close();

    return 0;
  
}
