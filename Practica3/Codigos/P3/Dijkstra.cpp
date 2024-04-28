#include <iostream>
#include <climits>

using namespace std;

// Número máximo de vértices en el grafo
#define V 6

// Función auxiliar para encontrar el vértice con la distancia mínima
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index;
  
    for (int v = 0; v < V; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
  
    return min_index;
}

// Función para imprimir el arreglo de distancias
void printSolution(int dist[]) {
    cout << "Distancias mínimas desde el vértice origen:\n";
    for (int i = 0; i < V; i++)
        cout << i << " -> " << dist[i] << endl;
}

// Función para implementar el algoritmo de Dijkstra
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // Arreglo para almacenar la distancia mínima desde el vértice origen
    bool visited[V]; // Arreglo para marcar los vértices visitados
  
    // Inicializar todas las distancias como infinito y ninguno visitado
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;
  
    // La distancia del vértice origen a sí mismo siempre es 0
    dist[src] = 0;
  
    // Encontrar las distancias mínimas para todos los vértices
    for (int count = 0; count < V - 1; count++) {
        // Encontrar el vértice con la distancia mínima
        int u = minDistance(dist, visited);
  
        // Marcar el vértice como visitado
        visited[u] = true;
  
        // Actualizar la distancia de los vértices adyacentes al vértice seleccionado
        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v]  && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
  
    // Imprimir las distancias mínimas
    printSolution(dist);
}

int main() {
    // Ejemplo de grafo representado como matriz de adyacencia
    int graph[V][V] = {
        {0, 2, 0, 1, 0, 0},
        {2, 0, 3, 2, 0, 0},
        {0, 3, 0, 0, 1, 0},
        {1, 2, 0, 0, 3, 2},
        {0, 0, 1, 3, 0, 1},
        {0, 0, 0, 2, 1, 0}
    };
  
    dijkstra(graph, 0); // Llamada a la función Dijkstra con el vértice origen 0
  
    return 0;
}
