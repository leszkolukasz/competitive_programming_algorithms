/* This file defines FIND & UNION algorithm. */

#include <cstdint>
#include <vector>

/*
 * FIND algorithm.
 * 
 * Parameters
 * ----------
 * id - id number to find leader for
 * leader - array where i-th element holds leader of the i-th 'id'. Can be both vector<int> and int[]
 * 
 * Returns
 * -------
 * leader of the 'id'
 * 
 * Examples
 * --------
 * int leader[2] = {0, 1};
 * std::vector<int> group_size(2, 1);
 * std::cout << FIND(0, leader);
 */
template <class T>
int FIND(int32_t id, T& leader)
{
    if(leader[id] == id)
        return id;
    else
        return (leader[id] = FIND(leader[id], leader));
}

/*
 * UNION algorithm.
 * 
 * Parameters
 * ----------
 * id_a - first id to unite
 * id_b - second id to unite
 * leader - array where i-th element holds leader of the i-th 'id'. Can be both vector<int> and int[]
 * group_size - array where i-th element holds group size of i-th 'id' but only if 'i' is a leader
 * 
 * Examples
 * --------
 * int leader[2] = {0, 1};
 * std::vector<int> group_size(2, 1);
 * UNION(0,1, leader, group_size);
 */
template <class T, class D>
void UNION(int32_t id_a, int32_t id_b, T& leader, D& group_size)
{
    id_a = FIND(id_a, leader);
    id_b = FIND(id_b, leader);

    if(group_size[id_a] < group_size[id_b])
    {
        auto copy = id_a;
        id_b = id_a;
        id_a = id_b;
    }

    leader[id_b] = id_a;
    group_size[id_a] += group_size[id_b];
}