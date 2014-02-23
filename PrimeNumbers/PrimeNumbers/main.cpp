//
//  main.cpp
//  PrimeNumbers
//
//  Created by Zhe Jia on 2/23/14.
//  Copyright (c) 2014 Zhe Jia. All rights reserved.
//

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

vector<unsigned long> primeList {2, 3};

vector<unsigned long> getInputFromFile(string fileName)
{
    vector<unsigned long> inputPrimeRequests;
    
    ifstream inFile(fileName);
	string value;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			inFile>>value;
			inputPrimeRequests.push_back(strtoul(value.c_str(), NULL, 0));
		}
		inFile.close();
	}
	else {
		cout<<"File not found."<<endl;
	}
    inputPrimeRequests.pop_back();
    
    return inputPrimeRequests;
}

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

void generateNecessaryPrimesForValue(unsigned long value)
{
    while (primeList[primeList.size()-1]<value) {
        getNextPrime();
    }
}

void printPrimesLessThanValue(unsigned long value)
{
    long counter = 0;
    while (primeList[counter]<value) {
        cout<<primeList[counter];
        if (primeList[counter+1]<value) {
            cout<<",";
        }
        counter++;
    }

}


int main(int argc, const char * argv[])
{

    // insert code here...
    if (argc != 2) {
        cout << "No input file name found.";
    } else {
        vector<unsigned long> inputPrimeRequests = getInputFromFile(argv[1]);
        
        for (int i = 0; i<inputPrimeRequests.size(); i++) {
            generateNecessaryPrimesForValue(inputPrimeRequests[i]);
            printPrimesLessThanValue(inputPrimeRequests[i]);
            cout<<endl;
        }
    }
    
    return 0;
}

