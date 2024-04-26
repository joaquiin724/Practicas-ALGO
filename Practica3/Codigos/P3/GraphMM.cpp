/**
 * @file GraphMM.cpp
 * @author your name (you@domain.com)
 * @brief Graph implementation using Matrix 
 * @version 0.1
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include <iostream>
#include <vector>
#include <random>

template<typename T>
class Graph {
private:
    std::vector<std::vector<double>> adjMatrix;
    std::vector<T> edgesToPoint;
public:
    Graph(int numVertex) {
        edgesToPoint.reserve(numVertex);
    }

    void updateWeight(int src, int dest, double weight) {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight;
    }

    void updateWeight(int src, int dest) {
        double weight;
        weight = edgesToPoint[src].calculateDistance(edgesToPoint[dest])
        updateWeight(src, dest, weight);
    }   

    T getElement(int position) {
        return edgesToPoint[position];
    }

    void randomGraph() {
        for (int i = 0; i < edgesToPoint.size(); i++) {
            
        }
    }

};