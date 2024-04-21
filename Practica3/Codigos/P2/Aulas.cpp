#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct tiempo{
    int hora;
    int min;
    tiempo(int h , int m){
        hora = h;
        min = m ;
    }
};
struct examen{
    tiempo inicio;
    tiempo duración;
    examen(tiempo t , tiempo t1) : inicio(t), duración(t1){}
};
struct compare{
    bool operator()(const examen&a,const examen&b){
        if(a.inicio.hora==b.inicio.hora){
            return a.inicio.min < b.inicio.min;
        }
        return a.inicio.hora < b.inicio.hora;
    }
};

void generadorHoras(int n,vector<examen> & v){
    srand(time(nullptr));
    int m,h;
    for(int i =0; i<n; i++) {
       m = rand()%60;
       h = rand()%24;
       v.push_back(examen(tiempo(h,m),tiempo(1,30)));

    }
    
}
void generadorDuración(int h , int min ){
    srand(time(nullptr));
    

}
void printv(const vector<examen>&v){
    for(int i = 0; i< v.size(); i++){
        cout << v[i].inicio.hora << ":" << v[i].inicio.min << " - "<< v[i].duración.hora << ":" << v[i].duración.min << "\n";
    }
}

int main(int argc, char* argv[]) {
    vector<examen> horarios;
    generadorHoras(10, horarios);
    sort(horarios.begin(),horarios.end(),compare());
    printv(horarios);
}
