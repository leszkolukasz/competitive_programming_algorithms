/* This file defines Manacher algorithm */

#include <cstdint>
#include <vector>
#include <string>


/*
 * Manacher algorithm implementation.
 *
 * Parameters
 * ----------
 * word - word to run algorithm on
 * 
 * Returns
 * -------
 * vector with calculated maximum length of palindrome for each position
 * 
 * Examples
 * --------
 * auto palindromes = manacher("aaabab");
 * for(auto u: palindromes)
 *      std::cout << u << " ";
 */
std::vector<int32_t> manacher(const std::string& word)
{
    int32_t center = 0, rt = -1, radius = 0;
    std::vector<int32_t> palindrome_radius(2*word.length()-1);

    std::string extended_word = "";
    extended_word.push_back(word[0]);
    for(int32_t i = 0; i < word.length()-1; i++)
    {
        extended_word.push_back('#');
        extended_word.push_back(word[i+1]);
    }

    for(int32_t k = 0; k < extended_word.length(); k++)
    {
        if (k <= rt)
            radius = std::min(palindrome_radius[2 * center - k], rt - k);

        else
            radius = 0;

        while (k - radius >= 0 && k + radius < extended_word.length() &&
            extended_word[k + radius] == extended_word[k - radius])
            radius++;

        radius--;
        palindrome_radius[k] = radius;

        if (k + radius > rt)
        {
            center = k;
            rt = center + radius;
        }
    }

    for(int32_t i = 0; i < palindrome_radius.size(); i++)
    {
        if(extended_word[i] == '#')
            palindrome_radius[i] = ((palindrome_radius[i]+1)/2)*2;

        else
            palindrome_radius[i] = ((palindrome_radius[i])/2)*2 + 1;
    }


    return palindrome_radius;
}