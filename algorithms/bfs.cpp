/*This file defines BFS algorithm*/

#include <cstdint>
#include <queue>
#include <vector>

/*
 * Standard BFS algorithm that traverses through the whole graph described in 'nodes' variable.
 *
 * Parameters
 * ----------
 * nodes - graph representation using adjacency list format
 * starting_node - id of the node to start BFS from
 * 
 * Examples
 * --------
 * std::vector<std::vector<int> > graph{{1}, {2}, {0}};
 * bfs(graph, 0);
 */
void bfs(std::vector<std::vector<int32_t> >& nodes, int32_t starting_node)
{
    std::vector<bool> visited(nodes.size(), 0);
    std::queue<int32_t> to_visit;

    visited[starting_node] = true;
    to_visit.push(starting_node);

    while(!to_visit.empty())
    {
        auto current = to_visit.front();
        to_visit.pop();

        for(auto& neighbour: nodes[current])
            if(!visited[neighbour])
            {
                visited[neighbour] = true;
                to_visit.push(neighbour);
            }
    }
}