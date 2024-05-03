#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <unordered_set>
#include <stack>
#include <climits>
#include <algorithm>
#include <iostream>

namespace ariel {


bool Algorithms::isConnected(const Graph& graph) {
    // Perform DFS from every vertex
    for (size_t i = 0; i < graph.matrix.size(); ++i) {
        std::vector<bool> visited(graph.matrix.size(), false);
        std::stack<size_t> stack;
        stack.push(i);
        visited[i] = true;

        while (!stack.empty()) {
            size_t current = stack.top();
            stack.pop();

            for (size_t j = 0; j < graph.matrix.size(); ++j) {
                if (graph.matrix[current][j] != 0 && !visited[j]) {
                    stack.push(j);
                    visited[j] = true;
                }
            }
        }

        // If any vertex is unreachable, return false
        for (size_t j = 0; j < graph.matrix.size(); ++j) {
            if (!visited[j]) {
                return false;
            }
        }
    }

    return true;
}

std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
    // Dijkstra's algorithm to find the shortest path
    size_t size = graph.matrix.size();
    std::vector<int> dist(size, INT_MAX);
    std::vector<int> prev(size, -1);
    dist[(size_t)start] = 0;
    //dist[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start));

    while (!pq.empty()) {
        size_t u = (size_t)pq.top().second;
        pq.pop();

        for (size_t v = 0; v < size; ++v) {
            if (graph.matrix[u][v] != 0) {
                int alt = dist[u] + graph.matrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }
    }

    // Construct the path as a string
    std::string path;
     if (prev[(size_t)end] != -1) {
        for (int at = end; at != -1; at = prev[static_cast<size_t>(at)]) {
            if (!path.empty()) {
                path = std::to_string(at) + "->" + path;
            } else {
                path = std::to_string(at);
            }
        }

     } else {
        path = "-1"; // No path exists
     }
    return path;
}

bool Algorithms::isContainsCycle(const Graph& graph) {
    int size = static_cast<int>(graph.matrix.size());
    std::vector<bool> visited(static_cast<size_t>(size), false);
    std::vector<int> parent(static_cast<size_t>(size), -1); // To store parent of each vertex in DFS tree

    for (int i = 0; i < size; ++i) {
        if (!visited[static_cast<size_t>(i)]) {
            std::stack<int> stack;
            stack.push(i);
            while (!stack.empty()) {
                int current = stack.top();
                stack.pop();

                if (visited[static_cast<size_t>(current)]) {
                    // Cycle detected, reconstruct and print the cycle
                    std::vector<int> cycle;
                    cycle.push_back(current);
                    for (int v = parent[static_cast<size_t>(current)]; v != -1 && v != current; v = parent[static_cast<size_t>(v)]) {
                        cycle.push_back(v);
                    }
                    cycle.push_back(current);

                    if (cycle.size() > 2) {
                        // Print the cycle in the correct order
                        std::cout << "The cycle is: ";
                        for (int j = static_cast<int>(cycle.size()) - 1; j > 0; --j) {
                            std::cout << cycle[static_cast<size_t>(j)] << "->";
                        }
                        std::cout << cycle[0] << std::endl;

                        return true;
                    }
                }

                visited[static_cast<size_t>(current)] = true;
                for (int j = 0; j < size; ++j) {
                    if (graph.matrix[static_cast<size_t>(current)][static_cast<size_t>(j)] != 0 && !visited[static_cast<size_t>(j)]) {
                        stack.push(j);
                        parent[static_cast<size_t>(j)] = current;
                    }
                }
            }
        }
    }

    return false;
}





// bool Algorithms::isContainsCycle(const Graph& graph) {
//     size_t size = graph.matrix.size();
//     std::vector<bool> visited(size, false);
//     std::vector<int> parent(size, -1); // To store parent of each vertex in DFS tree

//     for (size_t i = 0; i < size; ++i) {
//         if (!visited[i]) {
//             std::stack<size_t> stack;
//             stack.push(i);
//             while (!stack.empty()) {
//                 size_t current = stack.top();
//                 stack.pop();

//                 if (visited[current]) {
//                     // Cycle detected, reconstruct and print the cycle
//                     std::vector<int> cycle;
//                     cycle.push_back(current);
//                     for (int v = parent[current]; v != -1; v = parent[static_cast<size_t>(v)]) { // Cast to size_t
//                         cycle.push_back(v);
//                     }
//                     cycle.push_back(current);

//                     // Print the cycle
//                     std::cout << "The cycle is:";
//                     for (size_t j = cycle.size() - 2; j < cycle.size(); --j) { // Use size_t for j
//                         std::cout << "->" << cycle[j];
//                     }
//                     std::cout << std::endl;

//                     return true;
//                 }

//                 visited[current] = true;
//                 for (size_t j = 0; j < size; ++j) {
//                     if (graph.matrix[current][j] != 0 && !visited[j]) {
//                         stack.push(j);
//                         parent[j] = static_cast<int>(current); // Cast to int
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }




// bool Algorithms::isContainsCycle(const Graph& graph) {
//     // DFS traversal to check for cycles
//     size_t size = graph.matrix.size();
//     std::vector<bool> visited(size, false);
//     std::stack<int> stack;

//     for (size_t i = 0; i < size; ++i) {
//         if (!visited[i]) {
//             stack.push(i);
//             while (!stack.empty()) {
//                 size_t current = (size_t)stack.top();
//                 stack.pop();
//                 if (visited[current])
//                     return true;
//                 visited[current] = true;
//                 for (size_t j = 0; j < size; ++j) {
//                     if (graph.matrix[current][j] != 0 && !visited[j]) {
//                         stack.push(j);
//                     }
//                 }
//             }
//         }
//     }

//     return false;
// }

std::string Algorithms::isBipartite(const Graph& graph) {
    size_t size = graph.matrix.size();
    std::vector<int> color(size, -1);
    std::queue<int> q;

    for (size_t i = 0; i < size; ++i) {
        if (color[i] == -1) {
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (size_t v = 0; v < size; ++v) {
                    if (graph.matrix[(size_t)u][v] != 0) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[(size_t)u];
                            q.push(v);
                        } else if (color[v] == color[(size_t)u]) {
                            return "0"; // Not bipartite
                        }
                    }
                }
            }
        }
    }

    // Construct the bipartition sets
    std::vector<int> setA, setB;
    for (size_t i = 0; i < size; ++i) {
        if (color[i] == 0) {
            setA.push_back(i);
        } else {
            setB.push_back(i);
        }
    }

    // Sort the sets
    std::sort(setA.begin(), setA.end());
    std::sort(setB.begin(), setB.end());

    // Construct the result string
    if (setA.empty() || setB.empty()) {
        return "0"; // Not bipartite
    }

    std::string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        result += std::to_string(setA[i]);
        if (i != setA.size() - 1) {
            result += ", ";
        }
    }
    result += "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        result += std::to_string(setB[i]);
        if (i != setB.size() - 1) {
            result += ", ";
        }
    }
    result += "}";

    return result;
}
} // namespace ariel
