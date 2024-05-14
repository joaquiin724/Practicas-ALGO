#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
//TODO: CODIGO DE MIERDA QUE SE SUPONE QUE FUNCIONA, ATENTAMENTE MIGUE, YA LO MEJORARE, ES PARA TENERLO EN EL PORTATIL
const int N = 4;
std::vector<int> final_path(N + 1);
std::vector<bool> visited(N);
int final_res = std::numeric_limits<int>::max();

void copyToFinal(const std::vector<int>& curr_path) {
    std::copy(curr_path.begin(), curr_path.end(), final_path.begin());
    final_path[N] = curr_path[0];
}

int firstMin(const std::vector<std::vector<int>>& adj, int i) {
    int min = std::numeric_limits<int>::max();
    for (int k = 0; k < N; k++) {
        if (adj[i][k] < min && i != k) {
            min = adj[i][k];
        }
    }
    return min;
}

int secondMin(const std::vector<std::vector<int>>& adj, int i) {
    int first = std::numeric_limits<int>::max(), second = std::numeric_limits<int>::max();
    for (int j = 0; j < N; j++) {
        if (i == j) continue;

        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second && adj[i][j] != first) {
            second = adj[i][j];
        }
    }
    return second;
}

void TSPRec(const std::vector<std::vector<int>>& adj, int curr_bound, int curr_weight, int level, std::vector<int>& curr_path) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];

            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];

            if (level == 1) {
                curr_bound -= ((firstMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
            } else {
                curr_bound -= ((secondMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
            }

            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;

                TSPRec(adj, curr_bound, curr_weight, level + 1, curr_path);
            }

            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;

            std::fill(visited.begin(), visited.end(), false);
            for (int j = 0; j <= level - 1; j++) {
                visited[curr_path[j]] = true;
            }
        }
    }
}

void TSP(const std::vector<std::vector<int>>& adj) {
    std::vector<int> curr_path(N + 1, -1);

    int curr_bound = 0;
    std::fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < N; i++) {
        curr_bound += (firstMin(adj, i) + secondMin(adj, i));
    }

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;

    TSPRec(adj, curr_bound, 0, 1, curr_path);
}

int main() {
    std::vector<std::vector<int>> adj = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    TSP(adj);

    std::cout << "Minimum cost: " << final_res << std::endl;
    std::cout << "Path Taken: ";
    for (int i = 0; i <= N; i++) {
        std::cout << final_path[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
