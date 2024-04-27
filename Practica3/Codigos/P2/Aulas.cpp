#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>

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
    tiempo final;
    examen(tiempo t , tiempo t1) : inicio(t), final(t1){}
};

struct compare{
    bool operator()(const examen&a,const examen&b){
        if(a.inicio.hora==b.inicio.hora){
            return a.inicio.min < b.inicio.min;
        }
        return a.inicio.hora < b.inicio.hora;
    }
};

/**
 * @brief generador de examenes 
 * 
 * @param n numero de examenes que se quieren
 * @param dh limite de duracion de horas  del examen 
 * @param dm limite de duracion de minutos del examen
 * @param v vector de examenes
 */
void generadorExamen(int n,int dh,int dm,vector<examen> & v){
    srand(time(nullptr));
    for(int i =0; i<n; i++) {
        int h = rand()%dh;
        int m = rand()%dm;

       v.push_back(examen(tiempo(rand()%24,rand()%60),tiempo((h + rand()%dh)%24,rand()%dm)));

    }
    
}

void printv(const vector<examen>&v){
    for(int i = 0; i< v.size(); i++){
        cout<<v[i].inicio.hora << ":" << v[i].inicio.min << " - "<< v[i].final.hora << ":" << v[i].final.min << " \n";
    }
}

// Función para imprimir el contenido de una cola
void imprimirCola(queue<examen> cola) {
    // Mientras la cola no esté vacía
    while (!cola.empty()) {
        // Imprimir el frente de la cola
        cout<<cola.front().inicio.hora << ":" << cola.front().inicio.min << " - "<< cola.front().final.hora << ":" << cola.front().final.min << " \n";
        // Eliminar el elemento del frente de la cola
        cola.pop();
    }
    cout << endl;
}
bool sesolapan(examen e1,examen e2){
    if(e1.final.hora == e2.inicio.hora){
        return e1.final.min >e2.inicio.min;
    }
        return e1.final.hora > e2.inicio.hora;
}
int minAulas(vector<examen> & v){
    int naulas = 1;
    vector<queue<examen>> horario;
    horario.push_back(queue<examen>());
    horario[0].push(v[0]);
    int i;
    for(int nex = 0;nex < v.size();nex++){
        i=0;
        while(i<horario.size() && (sesolapan(horario[i].back(),v[nex]))){i++;}
        
        if(i==horario.size()){
            horario.push_back(queue<examen>());
            horario[i].push(v[nex]);
            naulas++;
        }
        else{
            horario[i].push(v[nex]);
        }
    }
   for(int i = 0; i<horario.size();i++){
        cout <<i<< endl;
        imprimirCola(horario[i]);
    }
    return naulas;
}

int main(int argc, char* argv[]) {
    vector<examen> horarios;
    horarios.push_back(examen(tiempo(10,0),tiempo(12,0)));
    horarios.push_back(examen(tiempo(11,30),tiempo(12,0)));
    horarios.push_back(examen(tiempo(12,0),tiempo(13,30)));
    horarios.push_back(examen(tiempo(12,15),tiempo(13,0)));
    horarios.push_back(examen(tiempo(13,0),tiempo(15,0)));
    horarios.push_back(examen(tiempo(13,27),tiempo(13,52)));
    horarios.push_back(examen(tiempo(14,0),tiempo(17,0)));

    sort(horarios.begin(),horarios.end(),compare());
    printv(horarios);
    cout << "=========================================="<<endl;
   int n = minAulas(horarios);
   cout << "numero de aulas : "<<n<<endl;

    return 0;
}
