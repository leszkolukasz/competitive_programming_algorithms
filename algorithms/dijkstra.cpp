/* This file defines Dijkstra's algorithm. */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

const int32_t INF = 1000'000'005LL;

/* Struct that holds information about candiate in queue. */
struct Candidate
{
    int32_t distance;
    int32_t id;

    bool operator()(Candidate a, Candidate b)
    {
        if(a.distance < b.distance)
            return false;

        else if(a.distance > b.distance)
            return true;

        else
            return a.id < b.id;
    }
};

/* Struct that holds information about edges. */
struct Edge
{
    int32_t to;
    int32_t cost;
};

/*
 * Implementation of Dijkstra's algorithm
 *
 * Parameters
 * ----------
 * graph - graph representation using adjacency list format
 * distance - array which keeps distances in the graph. Can be both int[] and vector<int>
 * graph_size - number of nodes in the graph
 * starting_point - vertex to start from
 * 
 * Usage
 * -----
 * int32_t distance[4];
 * std::vector<std::vector<Edge> > graph = {
 *      {{1, 1}, {2, 4}},
 *      {{2, 2}, {3, 3}},
 *      {{3, 1}},
 *      {}
 * };
 * dijkstra(graph, distance, 4, 0);
 */
template<class T>
void dijkstra(std::vector<std::vector<Edge> >& graph, T& distance, int32_t graph_size, int32_t starting_point=0)
{
    for(int32_t i = 0; i < graph_size; i++)
        distance[i] = INF;
    distance[starting_point] = 0;

    std::priority_queue<Candidate, std::vector<Candidate>, Candidate> min_queue;
    min_queue.push({0, 0});

    while(!min_queue.empty())
    {
        auto candidate = min_queue.top();
        min_queue.pop();

        if(candidate.distance != distance[candidate.id])
            continue;

        for(auto edge: graph[candidate.id])
        {
            if(candidate.distance + edge.cost < distance[edge.to])
            {
                distance[edge.to] = candidate.distance + edge.cost;
                min_queue.push({distance[edge.to], edge.to});
            }
        }
    }
}