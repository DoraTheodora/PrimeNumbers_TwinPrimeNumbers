/*!   \mainpage Prime numbers and their twins - CONCURRENT and/or PARALLEL
      \author Theodora Tataru, Student No: C00231174\n  
      \date 25 January 2020 
      \copyright  License: GNU Affero General Public License v3.0 
      \section Abstract class
      \subsection Describing the functions for the prime class
*/
#include "Primes.h"
#include <iostream>
#include <omp.h>

/*! \fn Primes::~Primes() = default
    \brief The destructor of the class
*/
Primes::~Primes() = default;

/*! \fn bool Primes::isPrime(int n)
    \param n The numbers that need to be checked if is prime or not
    \brief A method checks if the number given as a parameter is prime or not.
*/
bool Primes::isPrime(int n)
{
    number = n;
    int half = number/2;
    bool isPrime = true;
    //#pragma omp parallel for num_threads(8) 
    for(int i = 2; i <= half; i++)
    {
        //std::cout << "Thread ::isPrime: " <<  omp_get_thread_num() << std::endl;
        if(number%i==0 && isPrime)
            isPrime = false;
    }
    return isPrime;
}

/*! \fn void Primes::numbersPrimeLessThen(int N)
    \param N The number that represents the upper limit of checking prime numbers
    \brief Method that returns all the prime numbers less then N, and all the twin prime numbers less then N
*/
void Primes::numbersPrimeLessThen(int N)
{
    int thisPrime = 0;
    int prevPrime = 0;
    int sum = 0;
    std::cout << "Twins: ";
    #pragma omp parallel for num_threads(8) 
    for(int i = N; i >=2; i--)
    {
        std::cout << "Thread ::numbersPrimeLessThen: " <<  omp_get_thread_num() << std::endl;
        #pragma omp critical
        if(isPrime(i))
        {
            prevPrime = thisPrime;
            thisPrime = i;
            twins(prevPrime, thisPrime);
            sum++;
        }
    }
    std::cout << std::endl << "Number of prime numbers less then " << N << ": " << sum << std::endl;
}

/*! \fn void Primes::twins(int firstPrime, int secondPrime)
    \param int firstPrime
    \param int secondPrime
    \brief Method checks is 2 prime numbers are twins
*/
void Primes::twins(int firstPrime, int secondPrime)
{
    if(firstPrime-secondPrime == 2)
        std::cout << " (" << firstPrime << "," << secondPrime << ") ";
}