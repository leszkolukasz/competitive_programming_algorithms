#include <algorithm>
#include <cstdint>

const uint64_t L_INF = 1000'000'000'000'000'005LL;


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
 * uint64_t x[3][3] = {{0, 1, L_INF}, {L_INF, 0, 1}, {1, L_INF, 0}};
 * floyd_warshall(x, 3);
 */
template<class T>
void floyd_warshall(T& graph, uint32_t dimension)
{
    for (int k = 0; k < dimension; k++)
        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; ++j)
                if (graph[i][k] < L_INF && graph[k][j] < L_INF)
                    graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]); 
}