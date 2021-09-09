/* This file implements different kinds of segment tree. */

#include <cstdint>
#include <vector>
#include <iostream>

int64_t highest_bit(int64_t x)
{
    int cnt = 0;
    while(x)
    {
        cnt++;
        x >>= 1;
    }

    return cnt;
}

/*
 * Point-Point segment tree implementation
 *
 * Default implementation adds value to a single position, and queries sum
 * over the range.
 * 
 * Examples
 * --------
 * PointPointSegmentTree tree(100, 0);
 * tree.insert(0, 10);
 * tree.insert(1, 5);
 * std::cout << tree.query(0, 99) << '\n';
 */
struct PointPointSegmentTree
{
    std::vector<int32_t> nodes;
    int32_t number_of_nodes;
    int32_t shift;

    PointPointSegmentTree(int32_t number_of_nodes=0, int32_t default_value=0)
        : number_of_nodes(number_of_nodes)
    {
        shift = highest_bit(number_of_nodes);
        nodes.resize(1LL << (shift+1));
        shift = 1 << shift;
        fill(nodes.begin(), nodes.end(), default_value);
    }

    /* Build nodes from predefined values.
     *
     * Parameters
     * ----------
     * array - array to build from. Can both vector<int> and int[].
     * array_size - size of 'array'
     * 
     * Examples
     * -------
     * PointPointSegmentTree tree;
     * vector<int> nodes{1, 5, 8, 15};
     * tree.build_from_array(nodes, nodes.size());
     * std::cout << tree.query(0, 0) << "\n";
     * std::cout << tree.query(0, 1) << "\n";
     * std::cout << tree.query(1, 3) << "\n";
     */
    template<class T>
    void build_from_array(T& array, int32_t array_size)
    {
        shift = highest_bit(number_of_nodes);
        nodes.resize(1LL << (shift+1));
        shift = 1 << shift;

        for(int32_t i = 0; i < array_size; i++)
            nodes[i+shift] = array[i];

        for(int32_t i = nodes.size()/2-1; i >= 1; i--)
            nodes[i] = nodes[2*i] + nodes[2*i+1];
    }

    void insert(int32_t position, int32_t value)
    {
        position += shift;
        nodes[position] = value;
        position >>= 1;

        while(position)
        {
            nodes[position] = nodes[2*position] + nodes[2*position+1];
            position >>= 1;
        }
    }

    int32_t query(int32_t lf, int32_t rt)
    {
        lf += shift, rt += shift;
        int32_t result = nodes[lf];
        
        if(lf != rt)
            result += nodes[rt];

        while(lf/2 != rt/2)
        {
            if(lf%2 == 0)
                result += nodes[lf+1];
            if(rt&1)
                result += nodes[rt-1];

            lf >>= 1, rt >>= 1;
        }

        return result;
    }
};

int main()
{
    using namespace std;
    PointPointSegmentTree tree;
    vector<int> nodes{1, 5, 8, 15};
    tree.build_from_array(nodes, nodes.size());
    cout << tree.query(0, 0) << "\n";
    cout << tree.query(0, 1) << "\n";
    cout << tree.query(1, 3) << "\n";
}