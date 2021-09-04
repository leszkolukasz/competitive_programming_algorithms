/* This file defines hashing algorithm. */

#include <cstdint>
#include <vector>
#include <string>


/* Implementation of hashing algorithm.
 *
 * Variables
 * ---------
 * word - word to be hashed
 * modulo - modulo for the formula
 * prime - prime for the formula
 * hash - hash calculated for every prefix
 * power - subsequent powers of prime
 * 
 * Examples
 * ---------
 * Hash hello("hello");
 * Hash ll("ll");
 * std::cout << hello.getHash() << '\n';
 * std::cout << hello.getHash(2, 3) << '\n';
 * std::cout << ll.getHash() << '\n';
 */
class Hash
{
public:
    std::string word;
    int32_t modulo;
    int32_t prime;
    std::vector <int32_t> hash;
    std::vector <int32_t> power;

    Hash(std::string word, int32_t modulo = 1e9+7, int32_t prime = 257)
        :word(word), modulo(modulo), prime(prime)
    {
        int32_t lenght = word.length();
        power.assign(lenght + 1, 1);
        hash.assign(lenght + 1, 0);

        for(int32_t i = 1; i <= lenght; i++)
            power[i] = (power[i - 1] * 1LL * prime) % modulo;

        for(int32_t i = 1; i <= lenght; i++)
            hash[i] = (hash[i - 1] * 1LL * prime + word[i - 1]) % modulo;
    }

    //0 indexed
    int getHash(int32_t l = 0, int32_t r = -1)
    {
        if(r == -1)
            r = word.length()-1;
        return ((hash[r + 1] - hash[l] * 1LL * power[r - l + 1]) % modulo + modulo) % modulo;
    }
};