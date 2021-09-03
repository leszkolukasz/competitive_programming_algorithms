/* This file defines Bellman-Ford algorithm. */
#include <algorithm>
#include <cstdint>
#include <vector>

const int32_t INF = 1000'000'005LL;

/*Struct that keeps information about edges in graph*/
struct Edge
{
    int32_t from;
    int32_t to;
    int32_t cost;
};

/*
 * Implementation of Bellman-Ford algorithm
 *
 * Parameters
 * ----------
 * edges - edges in graph
 * distance - array which keeps distances in the graph. Can be both int[] and vector<int>
 * graph_size - number of nodes in the graph
 * starting_point - vertex to start from
 * 
 * Usage
 * -----
 * vector<Edge> edges = {{0, 1, -1}, {1, 2, -1}, {0, 3, 2}};
 * long long distance[4];
 * bellman_ford(edges, distance, 4, 0);
 */
template<class T>
void bellman_ford(std::vector<Edge>& edges, T& distance, int32_t graph_size, int32_t starting_point=0)
{
    for(int32_t i = 0; i < graph_size; i++)
        distance[i] = INF;
    distance[starting_point] = 0;
    
    for(int32_t i = 0; i < graph_size-1; i++)
    {
        bool updated = false;
        for(int32_t j = 0; j < edges.size(); j++)
            if (distance[edges[j].from] < INF)
                if(distance[edges[j].to] > distance[edges[j].from] + edges[j].cost)
                {
                    distance[edges[j].to] = distance[edges[j].from] + edges[j].cost;
                    updated = true;
                }

        if(!updated)
            break;
    }
}
