//RSA

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int modpower(int x, int y, int p);
int getCoprime(int x);

int main() {
	srand((unsigned) time(0));
	string message, decrypted;
	vector <int> encrypted;
	int index, p, q, n, totient, e, d, m;
	int len = 100;
	vector <int> is_prime(len+1, 1);  //primes[i] == 1 -> prime, 0 -> composite
	//Sieve of eratosthenes
	for (int i = 2; i*i <= len; i++) {
		if(is_prime[i]) {
			for (int j = i*i; j <= len; j += i) {
				is_prime[j] = 0;
			}
		}
	}
	//List of primes
	vector <int> primes;
	for (int i = 2; i <= len; i++) {
		if (is_prime[i]) {
			primes.push_back(i);
		}
	}

	index = rand() % (primes.size());
	p = primes[index];	//private
	index = rand() % (primes.size());
	q = primes[index];	//private

	n = p * q; //public
	//Euler's totient function
	totient = (p - 1) * (q - 1); //private

	e = getCoprime(totient); //public

	d = -1;
	for(int i = 1; i < 1000;i++) {
		if ((totient * i + 1) % e == 0) {
			d = (totient * i + 1) / e;	//private
			break;
		}
	}

	cout << "\nAlice: Public key - n = " << n << ", e = " << e;
	cout << "\n(Private key - p = " << p << ", q = " << q << ", d = " << d << ")";
	
	//Encryption
	cout << "\n\nMessage to be sent by Bob: ";
	getline(cin, message);
	for (char c : message) {
		if (isspace(c)) {
			m = 27;
		}
		else if (isupper(c)) {
			m = c - 'A';
		}
		else {
			m = c - 'a';
		}
		encrypted.push_back(modpower(m, e, n));
	}
	cout << "\nBob: ";
	for (int x : encrypted) {
		cout << x << ' ';
	}
	cout << '\n';

	//Decryption
	decrypted = "";
	for (int x : encrypted) {
		m = modpower(x, d, n);
		if (m == 27) {
			decrypted.append(1, ' ');
		}
		else {
			decrypted.append(1, 'a' + m);
		}
	}	
	cout << "\nAlice: Decrypted message - " << decrypted;
	cout << '\n';
	return 0;
}

int modpower(int x, int y, int p) { // x^y mod p
	int res = 1; 
    x = x % p;
    while (y > 0)  
    {  
        // If y is odd, multiply x with result
        if (y & 1)  
            res = (res*x) % p;  
        // y must be even now  
        y = y>>1; // y = y/2  
        x = (x*x) % p;  
    }  
    return res;
}

int getCoprime(int x) {
	vector <int> coprimes;
	for(int i = 2; i < x; i++) {
		if (__gcd(i, x) == 1) {
			coprimes.push_back(i);
		}
	}
	int len = coprimes.size();
	if (len > 0) {
		return coprimes[rand() % (len / 4)];
		//choosing among smaller values of e
	}

	return -1;
}