/* This file implements LCA algorithm */

#include <cstdint>
#include <vector>
#include <iostream>

/* Calculate 1st, 2nd, 4th, 8th, 16th, 32th, ..., ancestor for each nodes
 *
 * Parameters
 * ----------
 * parents - array of parents for each node in tree. Parent of root is root. Can be both vector<int> and int[]
 * number_of_nodes - number of nodes in tree
 * 
 * Returns
 * -------
 * array of 1st, 2nd, 4th, 8th, 16th, 32th, ..., ancestor for each nodes
 */
template <class T>
std::vector<std::vector<int32_t> > calculate_ancestors(T& parents, int32_t number_of_nodes)
{
    std::vector<std::vector<int32_t> > ancestors(number_of_nodes, std::vector<int32_t>(21, 0));
    for(int32_t i = 0; i < number_of_nodes; i++)
        ancestors[i][0] = parents[i];

    for(int32_t k = 1; k < 21; k++)
        for(int32_t i = 0; i < number_of_nodes; i++)
            ancestors[i][k] = ancestors[ancestors[i][k - 1]][k - 1];

    return ancestors;
}


/* Calculate lca of 'a' and 'b'
 *
 * Parameters
 * ----------
 * a - first node
 * b - second node
 * depth - depth of the node in tree (e.g. distance from node to root)
 * ancestors - result of calculate_ancestors function
 * 
 * Returns
 * -------
 * lca for 'a' and 'b'
 * 
 * Examples
 * --------
 * vector<int> parents{0, 0, 0, 2, 2};
 * vector<int> depth{0, 1, 1, 2, 2};
 * auto ancestors = calculate_ancestors(parents, parents.size());
 * std::cout << lca(3, 4, depth, ancestors) << "\n";
 * std::cout << lca(1, 4, depth, ancestors) << "\n";
 */
template<class T, class D>
int32_t lca(int32_t a, int32_t b, T& depth, D& ancestors)
{
    if (depth[b] < depth[a])
        std::swap(a, b);

    for(int32_t i = 20; i >= 0; i--)
        if (depth[ancestors[b][i]] >= depth[a])
            b = ancestors[b][i];

    if (a == b)
        return a;

    for(int i = 20; i >= 0; i--)
    {
        if (ancestors[a][i] != ancestors[b][i])
        {
            a = ancestors[a][i];
            b = ancestors[b][i];
        }
    }

    return ancestors[a][0];
}