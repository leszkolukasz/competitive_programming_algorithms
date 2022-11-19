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
 * Range-Point segment tree implementation
 *
 * Default implementation adds value to a single position, and queries sum
 * over the range.
 * 
 * Warning
 * -------
 * insert and query functions are 1-indexed.
 * 
 * Examples
 * --------
 * RangePointSegmentTree tree(100, 0);
 * tree.insert(0, 10);
 * tree.insert(1, 5);
 * std::cout << tree.query(0, 99) << '\n';
 */
struct RangePointSegmentTree
{
    std::vector<int32_t> nodes;
    int32_t number_of_nodes;
    int32_t shift;

    RangePointSegmentTree(int32_t number_of_nodes=0, int32_t default_value=0)
        : number_of_nodes(number_of_nodes)
    {
        shift = highest_bit(number_of_nodes);
        nodes.resize(1LL << (shift+1));
        shift = 1 << shift;

        for(int32_t i = shift; i < nodes.size(); i++)
            nodes[i] = default_value;
        for(int32_t i = shift-1; i >= 1; i--)
            nodes[i] = nodes[2*i] + nodes[2*i+1];
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
     * RangePointSegmentTree tree;
     * vector<int> nodes{1, 5, 8, 15};
     * tree.build_from_array(nodes, nodes.size());
     * std::cout << tree.query(0, 0) << "\n";
     * std::cout << tree.query(0, 1) << "\n";
     * std::cout << tree.query(1, 3) << "\n";
     */
    template<class T>
    void build_from_array(T& array, int32_t array_size)
    {
        number_of_nodes = array_size;
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

/*
 * Point-Range segment tree implementation
 *
 * Default implementation adds value to a range, and queries sum at a given point.
 * 
 * Warning
 * -------
 * insert and query functions are 1-indexed.
 * 
 * Examples
 * --------
 * PointRangeSegmentTree tree(100, 0);
 * tree.insert(0, 50, 59);
 * tree.insert(50, 50, 100);
 * std::cout << tree.query(49) << "\n";
 * std::cout << tree.query(50) << "\n";
 * std::cout << tree.query(51) << "\n";
*/
struct PointRangeSegmentTree
{
    std::vector<int32_t> nodes;
    int32_t number_of_nodes;
    int32_t shift;

    PointRangeSegmentTree(int32_t number_of_nodes=0, int32_t default_value=0)
        : number_of_nodes(number_of_nodes)
    {
        shift = highest_bit(number_of_nodes);
        nodes.resize(1LL << (shift+1));
        shift = 1 << shift;
        
        for(int32_t i = shift; i < nodes.size(); i++)
            nodes[i] = default_value;
        for(int32_t i = shift-1; i >= 1; i--)
            nodes[i] = nodes[2*i] + nodes[2*i+1];
    }

    /* Build nodes from predefined values.
     *
     * Parameters
     * ----------
     * array - array to build from. Can both vector<int> and int[].
     * array_size - size of 'array'
     * 
     * Examples
     * --------
     * For more examples see PointPointSegment tree docs
     */
    template<class T>
    void build_from_array(T& array, int32_t array_size)
    {
        number_of_nodes = array_size;
        shift = highest_bit(number_of_nodes);
        nodes.resize(1LL << (shift+1));
        shift = 1 << shift;

        for(int32_t i = 0; i < array_size; i++)
            nodes[i+shift] = array[i];
    }

    void insert(int32_t lf, int32_t rt, int32_t value)
    {
        lf += shift;
        rt += shift;

        nodes[lf] += value;
        if(lf != rt)
            nodes[rt] += value;

        while(lf/2 != rt/2)
        {
            if(lf%2 == 0)
                nodes[lf+1] += value;
            if(rt&1)
                nodes[rt-1] += value;

            lf >>= 1, rt >>= 1;
        }
    }

    int32_t query(int32_t position)
    {
        position += shift;
        int32_t result = 0;

        while(position)
        {
            result += nodes[position];
            position >>= 1;
        }

        return result;
    }
};


/*
 * Range-Range segment tree implementation
 *
 * Default implementation adds value to a range, and queries sum over a range.
 * 
 * Warning
 * -------
 * insert and query functions are 1-indexed.
 * 
 * Examples
 * --------
 * RangeRangeSegmentTree tree(5, 0);
 * tree.insert(1, 1, 10);
 * tree.insert(2, 2, 20);
 * tree.insert(1, 5, 100);
 * std::cout << tree.query(1, 1) << "\n";
 * std::cout << tree.query(2, 2) << "\n";
 * std::cout << tree.query(3, 5) << "\n";
*/
struct RangeRangeSegmentTree
{
    std::vector<int32_t> nodes;
    std::vector<int32_t> lazy_nodes;
    int32_t number_of_nodes;
    int32_t shift;

    RangeRangeSegmentTree(int32_t number_of_nodes=0, int32_t default_value=0)
        : number_of_nodes(number_of_nodes)
    {
        shift = highest_bit(number_of_nodes);
        nodes.resize(1LL << (shift+1));
        lazy_nodes.resize(1LL << (shift+1));
        shift = (1 << shift);
        build_with_deafult(default_value);
    }

    void build_with_deafult(int32_t default_value=0, int32_t node=1,
        int32_t node_range_lf=-1, int32_t node_range_rt=-1)
    {
        if(node_range_lf == -1)
            node_range_lf = 1, node_range_rt = number_of_nodes;

        if(node_range_lf > node_range_rt)   
            return;

        if(node_range_lf == node_range_rt)
        {
            nodes[node] = default_value;
            return;
        }
        
        build_with_deafult(default_value, 2*node,
            node_range_lf, (node_range_lf + node_range_rt) / 2);
        build_with_deafult(default_value, 2*node+1, 
            (node_range_lf + node_range_rt) / 2 + 1, node_range_rt);

        nodes[node] = nodes[2*node] + nodes[2*node+1];
    }

    /* Build nodes from predefined values.
     *
     * Parameters
     * ----------
     * array - array to build from. Can both vector<int> and int[].
     * array_size - size of 'array'
     * 
     * Examples
     * --------
     * RangeRangeSegmentTree tree(1);
     * vector<int> nodes{1, 5, 8, 15};
     * tree.build_from_array(nodes, nodes.size());
     * std::cout << tree.query(1, 1) << "\n";
     * std::cout << tree.query(1, 2) << "\n";
     * std::cout << tree.query(2, 4) << "\n";
     */
    template<class T>
    void build_from_array(T& array, int32_t array_size, int32_t node=1,
        int32_t node_range_lf=-1, int32_t node_range_rt=-1)
    {
        if(node_range_lf == -1)
        {
            number_of_nodes = array_size;
            shift = highest_bit(number_of_nodes);
            nodes.resize(1LL << (shift+1));
            lazy_nodes.resize(1LL << (shift+1));
            shift = (1 << shift);
            node_range_lf = 1, node_range_rt = number_of_nodes;
        }   

        if(node_range_lf > node_range_rt)   
            return;

        if(node_range_lf == node_range_rt)
        {
            nodes[node] = array[node_range_lf-1];
            return;
        }
        
        build_from_array(array, array_size, 2*node, node_range_lf,
            (node_range_lf + node_range_rt) / 2);
        build_from_array(array, array_size, 2*node+1, (node_range_lf + node_range_rt) / 2 + 1,
            node_range_rt);
        
        nodes[node] = nodes[2*node] + nodes[2*node+1];
    }

    void update(int32_t node, int32_t node_range_lf, int32_t node_range_rt)
    {
        if (lazy_nodes[node])
        {
            nodes[node] += lazy_nodes[node]*(node_range_rt-node_range_lf+1);

            if (node < shift)
            {
                lazy_nodes[2 * node] += lazy_nodes[node];
                lazy_nodes[2 * node + 1] += lazy_nodes[node];
            }
        }

        lazy_nodes[node] = 0;
    }

    void insert(int32_t query_range_lf=1, int32_t query_range_rt=1, int32_t value=0,
        int32_t node=1, int32_t node_range_lf=-1, int32_t node_range_rt=-1)
    {
        if(node_range_lf == -1)
            node_range_lf = 1, node_range_rt = number_of_nodes;

        if (node_range_lf > node_range_rt)
            return;

        update(node, node_range_lf, node_range_rt);

        if (node_range_lf > query_range_rt || node_range_rt < query_range_lf)
            return;

        if (node_range_lf >= query_range_lf && node_range_rt <= query_range_rt)
        {
            lazy_nodes[node] += value;
            update(node, node_range_lf, node_range_rt);

            return;
        }

        insert(query_range_lf, query_range_rt, value,
            2*node, node_range_lf, (node_range_lf + node_range_rt) / 2);
        insert(query_range_lf, query_range_rt, value,
            2*node+1, (node_range_lf + node_range_rt) / 2 + 1, node_range_rt);

        nodes[node] = nodes[2*node] + nodes[2*node+1];
    }


    int32_t query(int32_t query_range_lf, int32_t query_range_rt,
        int32_t node=1, int32_t node_range_lf=-1, int32_t node_range_rt=-1)
    {
        if(node_range_lf == -1)
            node_range_lf = 1, node_range_rt = number_of_nodes;

        if (node_range_lf > node_range_rt)
            return 0;

        update(node, node_range_lf, node_range_rt);

        if (node_range_lf > query_range_rt || node_range_rt < query_range_lf)
            return 0;

        if (node_range_lf >= query_range_lf && node_range_rt <= query_range_rt)
            return nodes[node];

        int32_t result = query(query_range_lf, query_range_rt,
            2*node, node_range_lf, (node_range_lf + node_range_rt) / 2);
        result += query(query_range_lf, query_range_rt,
            2*node+1, (node_range_lf + node_range_rt) / 2 + 1, node_range_rt);

        nodes[node] = nodes[2*node] + nodes[2*node+1];

        return result;
    }
};

int main()
{
    using namespace std;
    RangeRangeSegmentTree tree(1);
    vector<int> nodes{1, 5, 8, 15};
    tree.build_from_array(nodes, nodes.size());
    cout << tree.query(1, 1) << "\n";
    cout << tree.query(1, 2) << "\n";
    cout << tree.query(2, 4) << "\n";
}
