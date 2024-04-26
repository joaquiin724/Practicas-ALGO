/**
 * @file Graph.cpp
 * @brief Implementation of an undirected Graph using Adjacency List
 * @version 0.1
 * @date 2024-04-26
 * 
*/

#include <iostream>
#include <list>
#include <random>
#include <vector>

template<typename T>
struct Edge {
    T value;
    Edge* next;
};

template<typename T>
class Graph {
private:
    std::vector<Edge<T>*> adjList;
    int numVertices;
public:
    Graph(int numVertices) : numVertices(numVertices){
        adjList = std::vector<Edge<T>*>(0);
    }

    void addEdge(T src, T dest) {
        Edge<T> *newEdge = new Edge<T>;
        newEdge->value = dest;
        newEdge->next = adjList[src];
        adjList[src] = newEdge;

        newEdge = new Edge<T>;
        newEdge->value = src;
        newEdge->next = adjList[dest];
        adjList[dest] = newEdge;
    }

    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            Edge<T> *temp = adjList[i];
            std::cout << "Vertex " << i << " : ";
            while (temp != nullptr) {
                std::cout << temp->value << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }

    void addVertex(const T& vertex) {
        numVertices++;
        adjList.resize(numVertices);
        adjList[numVertices - 1] = vertex;
    }

    void removeVertex(int vertex) {
        Edge<T> *temp = adjList[vertex];
        while (temp != nullptr) {
            Edge<T> *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        adjList[vertex] = nullptr;
        for (int i = 0; i < numVertices; i++) {
            temp = adjList[i];
            if (temp == nullptr) {
                continue;
            }
            if (temp->value == vertex) {
                Edge<T> *toDelete = temp;
                adjList[i] = temp->next;
                delete toDelete;
            } else {
                while (temp->next != nullptr) {
                    if (temp->next->value == vertex) {
                        Edge<T> *toDelete = temp->next;
                        temp->next = temp->next->next;
                        delete toDelete;
                        break;
                    }
                    temp = temp->next;
                }
            }
        }
    }

    void removeEdge(int src, int dest) {
        Edge<T> *temp = adjList[src];
        if (temp->value == dest) {
            Edge<T> *toDelete = temp;
            adjList[src] = temp->next;
            delete toDelete;
        } else {
            while (temp->next != nullptr) {
                if (temp->next->value == dest) {
                    Edge<T> *toDelete = temp->next;
                    temp->next = temp->next->next;
                    delete toDelete;
                    break;
                }
                temp = temp->next;
            }
        }

        temp = adjList[dest];
        if (temp->value == src) {
            Edge<T> *toDelete = temp;
            adjList[dest] = temp->next;
            delete toDelete;
        } else {
            while (temp->next != nullptr) {
                if (temp->next->value == src) {
                    Edge<T> *toDelete = temp->next;
                    temp->next = temp->next->next;
                    delete toDelete;
                    break;
                }
                temp = temp->next;
            }
        }
    }

    ~Graph() {
        for (int i = 0; i < numVertices; i++) {
            Edge<T> *temp = adjList[i];
            while (temp != nullptr) {
                Edge<T> *toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
    }

    void initializeGraph(std::vector<T>& vertices) {
        srand(time(0));
        for (int i = 0; i < vertices.size(); ++i) {
            addVertex(vertices[i]);
            for (int j = 0; j < numVertices; ++j) {
                if (rand() % 2 == 1) {
                    addEdge(vertices[i], vertices[j]);
                }
            }
        }
    }

};