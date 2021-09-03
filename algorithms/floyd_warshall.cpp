/* This file defines Floyd-Warshall algorithm */

#include <algorithm>
#include <cstdint>

const int32_t INF = 1000'000'005;


/*
 * Implementation of Floyd-Warshall algorithm
 *
 * Parameters
 * ----------
 * graph - graph in matrix form. Can be both int[][] and vector<vector<int> >
 * dimension - size of one dimension of the graph. Graph must be of the form 'n' x 'n'
 * 
 * Usage
 * -----
 * uint64_t x[3][3] = {{0, 1, INF}, {INF, 0, 1}, {1, INF, 0}};
 * floyd_warshall(x, 3);
 */
template<class T>
void floyd_warshall(T& graph, int32_t dimension)
{
    for (int k = 0; k < dimension; k++)
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; ++j)
                if (graph[i][k] < INF && graph[k][j] < INF)
                    graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]); 
}