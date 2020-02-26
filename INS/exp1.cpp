//Caesar cipher

#include <iostream>
#include <string>

using namespace std;

int main() {
	int k; //shift value
	string plaintext, encrypted = "", ciphertext, decrypted = "";
	
	cout << "\nShift value for Caesar cipher: ";
	cin >> k;

	cout << "\nENCRYPTION\nPlaintext: ";
	cin >> plaintext;
	
	//encryption
	int base;
	for (char c : plaintext) {
		if (isupper(c))
			base = 65;	//A-Z : 65-90
		else
			base = 97;	//a-z : 97-122
		encrypted.push_back((c + k - base) % 26 + base);	
	}

	cout << "Encrypted text: " << encrypted << '\n';

	cout << "\nDECRYPTION\nCiphertext: ";
	cin >> ciphertext;

	//decryption
	for (char c : ciphertext) {
		if (isupper(c))
			base = 65;
		else
			base = 97;
		if (c - k < base) c += 26;
		decrypted.push_back(c - k);
	}

	cout << "Decrypted text: " << decrypted << '\n';

	return 0;
}