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
//            else if (primeList[knownPrimeIndex]*primeList[knownPrimeIndex] > candidatePrime){
//                /* 
//                 x * y = candidatePrime such that min value for x is 2 and max value for y is candidatePrime/2 or vise versa.
//                 Which implies that x could be the values 3, 5, 7... up to value i such that x == i and y == i. 
//                 -> x * x = candidatePrime.  The upper bound for x and y is the value i.
//                 */
//                knownPrimeIndex = primeList.size();
//            }
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

