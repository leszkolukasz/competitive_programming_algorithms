/* This file defines KMP algorithm */

#include <cstdint>
#include <vector>
#include <string>

/*
 * Implementation of KMP algorithm
 * 
 * Parameters
 * ----------
 * word - word to calculate KMP for
 * 
 * Examples
 * --------
 * auto x = kmp("aaaabaa");
 * for(auto u: x)
 *      std::cout << u << " ";
 */
std::vector<int32_t> kmp(const std::string& word)
{
    std::vector<int32_t> prefix_sufix(word.length() + 1, -1);

    for(int32_t i = 0, j = -1; i < word.length(); i++)
	{
        while(j >= 0 && word[j] != word[i])
			j = prefix_sufix[j];

        prefix_sufix[i + 1] = ++j;
    }

    return std::vector<int32_t>(prefix_sufix.begin() + 1, prefix_sufix.end());
}