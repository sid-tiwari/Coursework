//Diffie Hellman Key Exchange
#include <iostream>
#include <cstdlib>	
#include <ctime>
#include <vector>

using namespace std;

int modpower(int x, int y, int p);

int main() {
	int n = 1000;

	srand((unsigned) time(0));
	int a, b, k_a, k_b;
	int a_send, b_send;	// a_send -> A, b_send -> B

	vector <int> is_prime(n+1, 1);  //primes[i] == 1 -> prime, 0 -> composite
	//Sieve of eratosthenes
	for (int i = 2; i*i <= n; i++) {
		if(is_prime[i]) {
			for (int j = i*i; j <= n; j += i) {
				is_prime[j] = 0;
			}
		}
	}
	//List of primes
	vector <int> primes;
	for (int i = 2; i <= n; i++) {
		if (is_prime[i]) {
			primes.push_back(i);
		}
	}

	//choosing a random prime number
	int index = rand() % (primes.size());
	int p = primes[index];
	cout << "\nAlice and Bob: p = " << p;

	//choosing a small random number
	int g = rand() % 10 + 2;
	cout << "\nAlice and Bob: g = " << g;

	a = rand() % 1000; //private for Alice
	b = rand() % 1000;	//private for Bob
	cout << "\n(Alice: a = " << a;
	cout << "\n Bob: b = " << b << ")"; 

	a_send = modpower(g, a, p);	//being sent to Bob
	b_send = modpower(g, b, p);	//being sent to Alice
	cout << "\n\nAlice: received B = " << b_send;
	cout << "\nBob: received A = " << a_send;

	k_a = modpower(b_send, a, p); //key calculated with Alice
	k_b = modpower(a_send, b, p); //key calculated with Bob

	if (k_a != k_b)
		cout << "\n\nError in key exchange!";
	else {
		cout << "\n\nAlice: Key = " << k_a;
		cout << "\nBob: Key = " << k_b; 
	}
	cout << '\n';
	return 0;
}

int modpower(int x, int y, int p) { // x^y mod p
	int res = 1; 
    x = x % p;
    while (y > 0) {  
        // If y is odd, multiply x with result
        if (y & 1)  
            res = (res*x) % p;  
        // y must be even now  
        y = y >> 1; // y = y/2  
        x = (x * x) % p;  
    }  
    return res;
}