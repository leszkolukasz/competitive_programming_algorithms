/*This module defines primality checking algorithms*/

#include <cstdint>
#include <random>

/*
 * This is slower version of primality checking algorithm. It will always 
 * correctly define primality of 'number'.
 *
 * Complexity
 * ----------
 * O(n*sqrt(n))
 * 
 * Parameters
 * ----------
 * number - number to check primality for
 * 
 * Returns
 * -------
 * true if 'number' is prime else otherwise
 * 
 * Example
 * -------
 * is_prime_slow(101)
 */
bool is_prime_slow(uint64_t number)
{
    if(number == 0 || number == 1)
        return false;

    for(uint64_t i = 2; i * i <= number; i++)
        if(number % i == 0)
            return false;
    return true;
}

/*This is needed for is_prime_fast. For more information see fast_exponatiation.cpp*/
uint64_t fast_exponentiation(uint64_t base, uint64_t exponent, uint64_t mod=UINT64_MAX)
{
    uint64_t result = 1;
    base %= mod;

    while(exponent)
    {
        if(exponent & 1)
            result = result * base % mod;

        base = base * base % mod;
        exponent >>= 1;
    }

    return result;
}

/*
 * This is faster version of primality checking algorithm. Rarely, it will 
 * incorrectly define primality of 'number'. Increasing 'number_of_iterations'
 * should decrease probability of it happening.
 * 
 * Complexity
 * ----------
 * O(n*log(n))
 * 
 * Parameters
 * ----------
 * number - number to check primality for
 * number_of_iterations - number of repetitions of the algorithm
 * 
 * Returns
 * -------
 * true if 'number' is prime else otherwise
 * 
 * Example
 * -------
 * is_prime_fast(101)
 * 
 * Warning
 * -------
 * You have to watch out if at any point there is no multiplication that 
 * results in number bigger than 2^64. If so, then you need to use 128 bit integer type
 */
bool is_prime_fast(uint64_t number, uint32_t number_of_iterations=5)
{
    if(number == 0 || number == 1)
        return false;

    else if(number == 2 || number == 3)
        return true;

    else if(number % 2 == 0)
        return false;

    uint32_t power = 0;
    uint64_t remainder = number - 1;
    while((remainder & 1) == 0)
    {
        power++;
        remainder >>= 1;
    }

    std::random_device device;
    std::mt19937_64 generator(device());
    std::uniform_int_distribution<uint64_t> distribution(2, number-2);
    
    for(int i = 0; i < number_of_iterations; i++)
    {
        uint64_t base = distribution(generator);
        uint64_t result = fast_exponentiation(base, remainder, number);
        bool is_not_prime = true;

        if(result == 1 || result == number-1)
            is_not_prime = false;

        for(int j = 1; j < power; j++)
        {
            result = result * result % number;
            if(result == number-1)
                is_not_prime = false;
        }

        if(is_not_prime)
            return false;
    }

    return true;
}