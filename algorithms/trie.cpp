/* This file defines trie data structure. */
#include <cstdint>
#include <string>

/*
 * Implementation of trie algorithm
 *
 * Variables
 * ---------
 * jump - pointer to the next leaf in trie
 * count_endings - count number of words ending in the current leaf
 * count_passing - count number of words having at least one letter in the current leaf
 * 
 * Examples
 * --------
 * trie Trie();
 * trie.add("hello");
 * std::cout << trie.find("hello");
 * trie.remove("hello");
 * std::cout << trie.find("hello");
 */

struct Trie
{
    Trie* jump[26];
    int32_t count_endings;
    int32_t count_passing;

    Trie()
        :count_endings(0), count_passing(0)
    {
        for(int32_t i = 0; i < 26; i++)
            jump[i] = nullptr;
    }

    int32_t get_id(const std::string& word, int32_t index)
    {
        return static_cast<int32_t>(word[index]-'a');
    }

    void add(const std::string& word, int32_t index=0)
    {
        if(index == word.length())
        {
            count_endings++;
            return;
        }

        int32_t id = get_id(word, index);
        if(!jump[id])
            jump[id] = new Trie();

        jump[id]->count_passing++;
        jump[id]->add(word, index+1);
    }

    void remove(const std::string& word, int32_t index=0)
    {
        if(index == word.length())
        {
            count_endings--;
            return;
        }

        int32_t id = get_id(word, index);
        if(!jump[id])
            return;

        jump[id]->count_passing--;
        jump[id]->remove(word, index+1);

        if(!jump[id]->count_passing)
            delete jump[id];
    }

    bool find(const std::string& word, int32_t index=0)
    {
        if(index == word.length())
            return (count_endings > 0);

        int32_t id = get_id(word, index);
        if(!jump[id])
            return false;

        return jump[id]->find(word, index+1);
    }

    void traverse()
    {
        for(int32_t i = 0; i < 26; i++)
            if(jump[i])
                jump[i]->traverse();
    }
};
