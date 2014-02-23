//
//  main.cpp
//  FibonacciSeries
//
//  Created by Zhe Jia on 2/22/14.
//  Copyright (c) 2014 Zhe Jia. All rights reserved.
//

/*
 This is my solution to the Fibonacci Series challenge from CodeEval.com.
 The main objective is to calculate N many Nth fibonacci values, therefore I will persist my previous calculation to prevent recalculation the same values.
 */

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//All calculated Fib values will be stored here.
vector<unsigned long> fibonacciVector {0, 1};

vector<int> getInputFromFile(string fileName)
{
    vector<int> inputFibonacciRequests;
    
    ifstream inFile(fileName);
	string value;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			inFile>>value;
			inputFibonacciRequests.push_back(atoi(value.c_str()));
		}
		inFile.close();
	}
	else {
		cout<<"File not found."<<endl;
	}
    inputFibonacciRequests.pop_back();

    return inputFibonacciRequests;
}

void calculateNthFib(int count)
{
    long currentCount = fibonacciVector.size();
    unsigned long leadingFib = fibonacciVector[currentCount-1];  //N-1
    unsigned long laggingFib = fibonacciVector[currentCount-2];  //N-2
    while (currentCount < count) {
        leadingFib = leadingFib + laggingFib;
        fibonacciVector.push_back(leadingFib);
        laggingFib = leadingFib - laggingFib;
        currentCount++;
    }
    cout << leadingFib << endl;
}

void getNthFib(int count)
{
    if (fibonacciVector.size()>count) {
        cout << fibonacciVector[count] << endl;
    } else {
        calculateNthFib(count);
    }
}

int main(int argc, const char * argv[])
{
    if (argc != 2) {
        cout << "No input file name found.";
    } else {
        vector<int> inputFibRequests = getInputFromFile(argv[1]);
        
        for (int i = 0; i < inputFibRequests.size(); i++) {
            int requestedValue = inputFibRequests[i];
            getNthFib(requestedValue);
        }
    }
    
    return 0;
}

















