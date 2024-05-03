
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace ariel {

    class Algorithms {
    public:
        static bool isConnected(const Graph& graph);
        static std::string shortestPath(const Graph& graph, int start, int end); // Changed return type to std::string
        static bool isContainsCycle(const Graph& graph);
        static std::string isBipartite(const Graph& graph);
        //static bool isBipartite(const Graph& graph);
    };

}

#endif /* ALGORITHMS_HPP */
