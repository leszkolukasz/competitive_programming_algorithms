/*
 * This file defines sieve of eratosthenes
 */

#include <cstdint>
#include <vector>

/*
 * Simple sieve of eratosthenes
 *
 * Parameters
 * ----------
 * range - range [1, 'range'] for which you want to find prime numbers
 * is_prime - bool vector with i-th element true if 'i' is a prime number and false otherwise
 * 
 * Examples
 * --------
 * std::vector<bool> is_prime(101);
 * sieve_of_eratosthenes(100, is_prime);
 */
void sieve_of_eratosthenes(int32_t range, std::vector<bool>& is_prime)
{
    is_prime[0] = is_prime[1] = false;
    std::fill(is_prime.begin()+2, is_prime.end(), true);

    for(int32_t j = 4; j <= range; j += 2)
        is_prime[j] = false;

    for(int32_t i = 3; i*i <= range; i += 2)
        if(is_prime[i])
            for(int32_t j = i*i; j <= range; j += i)
                is_prime[j] = false;
}
