/*
 * Lab2 Ex1 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <iostream>

using namespace std;

#define RANGE 100000

bool isPrime[RANGE + 1];

// MODIFIES: isPrime[]
// EFFECTS: fill in isPrime[], true for prime, false otherwise
void generateIsPrime(int *table) {
    // TODO: implement Eratosthenes Sieve Algorithm

}

int main() {
    // TODO: generate lookup table
	int prime_table[RANGE + 1] = { 1,1 };
	generateIsPrime(prime_table);
    // TODO: read input and check if each num is prime

    return 0;
}