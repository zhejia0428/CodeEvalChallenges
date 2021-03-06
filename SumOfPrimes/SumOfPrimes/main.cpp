//
//  main.cpp
//  SumOfPrimes
//
//  Created by Zhe Jia on 2/22/14.
//  Copyright (c) 2014 Zhe Jia. All rights reserved.
//

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdio>
#include <ctime>

using namespace std;

vector<unsigned long> primeList {2, 3};


bool varifyForPrime(unsigned long candidatePrime)
{
    bool isPrime = false;
    if (candidatePrime & 1) {       //Odd numbers only
        
        long knownPrimeIndex = 1;   //Start at position 1 (3)
        bool canBePrime = true;
        while (knownPrimeIndex < primeList.size() && canBePrime) {
            if (candidatePrime%primeList[knownPrimeIndex] == 0) {
                //Not a prime
                canBePrime = false;
                knownPrimeIndex = primeList.size();
            }
            else if (primeList[knownPrimeIndex]*primeList[knownPrimeIndex] > candidatePrime){
                /* 
                 Non-primes are numbers made up of primes: N = p1^c1 * p2^c2 * p3^c3... ex: 36 = 2^2 * 3^3 = 2^2 * 3^2
                 To check for primes we don't need to find all p1...pn, we only need to determin p1 exists.
                 We can condense p1^c1 to x and p2^c2 to x1... -> N = x * x1...xn = xn * xn-1...x
                 Best case for this check is if N = 2^1 * c2p2... since we only need to check if the number is even.  Best case being we immediately determing N is not a prime number.
                 Worst case we need to check is if N = p1^2.  Worst case being we need to check most of the primes to determing that N is not a prime.
                 N = p1^2 is the upper bound for the prime we need to check to determing if N is prime.
                 -> max value for p1 is N^(1/2)
                 */
                knownPrimeIndex = primeList.size();
            }
            knownPrimeIndex++;
        }
        if (canBePrime) {
            isPrime = true;
        }
    }
    return isPrime;
}

void getNextPrime()
{
    bool hasNextPrime = false;
    unsigned long lastPrime = primeList[primeList.size()-1];
    unsigned long candidatePrime = lastPrime;
    
    while (hasNextPrime == false) {
        candidatePrime++;
        bool isPrime = varifyForPrime(candidatePrime);
        
        if (isPrime) {
            hasNextPrime = true;
        }
    }
    
    primeList.push_back(candidatePrime);
    
}

long sumPrimeList()
{
    long sum = 0;
    long count = 0;
    while (count < primeList.size()) {
        sum += primeList[count];
        count++;
    }
    return sum;
}

int main(int argc, const char * argv[])
{

    clock_t start;
    double duration;
    
    start = clock();
    
    int counter = 0;
    while (primeList.size() != 16000) {
        getNextPrime();
        counter++;
    }
    
    cout << sumPrimeList() << endl;
    
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << "printf: "<< duration <<'\n';
    cout << primeList[primeList.size()-1]<<endl;
    return 0;
}

