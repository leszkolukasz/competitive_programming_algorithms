/*This file defines fast exponentiation algorithm with modulo support*/

#include <cstdint>

/*
 * Fast exponentiation algorithm
 *
 * Parameters
 * ----------
 * base - base of the exponentiation
 * exponent - exponent of the exponentiation
 * mod - modulo of the exponentiation
 * 
 * Returns
 * -------
 * (base^exponent)%mod
 * 
 * Example
 * -------
 * fast_exponentiation(2, 32, 1000)
 * 
 * Warning
 * -------
 * You have to watch out if at any point there is no multiplication that results in number bigger than 2^64. If so, then you need to use 128 bit integer type
 */

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