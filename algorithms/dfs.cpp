/* This file defines DFS-like algorithms. */

#include <cstdint>
#include <vector>

/*
 * Standard DFS algorithm that traverses through the whole graph described in 'nodes' variable.
 *
 * Parameters
 * ----------
 * nodes - graph representation using adjacency list format
 * current - id of the currently visited node
 * visited - array with i-th element being true if i-th node has already 
 * been visited and false otherwise. Can be both vector<bool>, bitset or bool[]
 * 
 * Examples
 * --------
 * std::vector<std::vector<int> > graph{{1}, {2}, {0}};
 * bool visited[3] = {0, 0, 0};
 * dfs(graph, 0, visited);
 */
template<class T>
void dfs(std::vector<std::vector<int32_t> >& nodes, int32_t current, T& visited)
{
    visited[current] = true;
    for(auto& child: nodes[current])
        if(!visited[child])
            dfs(nodes, child, visited);
}


/*
 * DFS algorithm that traverses tree-like graphs described in 'nodes' variable.
 *
 * Attributes
 * ----------
 * nodes - tree representation using adjacency list format
 * current - id of the currently visited node
 * parent - id of the previously visited node
 * 
 * Examples
 * --------
 * std::vector<std::vector<int> > tree{{1}, {2}, {}};
 * dfs(tree, 0);
 */
void dfs_on_tree(std::vector<std::vector<int32_t> >& nodes, int32_t current, int32_t parent=-1)
{
    for(auto& child: nodes[current])
        if(child != parent)
            dfs_on_tree(nodes, child, current);
}