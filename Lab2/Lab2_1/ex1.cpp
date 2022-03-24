/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1] = { 1,1 };

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], 0 for prime, 1 otherwise
void generateIsPrime() {
	// TODO: implement Eratosthenes Sieve Algorithm
	int num = 0;
	while (num < 100001) {
		if (isPrime[num] == 1) {
			num++;
			continue;
		}
		for (int i = 2; num * i < 100001; ++i) {
			isPrime[num * i] = 1;
		}
		num++;
	}
}

int main() {
	// TODO: generate lookup table
	generateIsPrime();
	// TODO: read input and check if each num is prime
	int lime_number = 0;
	int sequence = 0;
	cin >> lime_number;
	while (lime_number > 0) {
		cin >> sequence;
		int prime = isPrime[sequence];
		if (prime == 0)
			cout << sequence << ' '; 
		lime_number--;
	}
	return 0;
}