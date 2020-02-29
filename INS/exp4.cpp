//Polyalphabetic substitution cipher - Vigenere cipher

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

	string plaintext, keyword, key, encrypted = "";
	string ciphertext, decrypted = "";

	cout << "Keyword: ";
	cin >> keyword;
	transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
	int ksize = keyword.size();

	cout << "\nENCRYPTION\nPlaintext: ";
	cin >> plaintext;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	int psize = plaintext.size();

	//Key generation for encryption
	key = "";
	if (ksize > psize) {
		key = keyword.substr(0, psize);
	}
	else {
		for (int i = 0; i < psize/ksize; i++) {
			key += keyword;
		}
		key += keyword.substr(0, (psize % ksize));
	}

	//encryption
	for (int i = 0; i < psize; i++) {
		encrypted.push_back((plaintext[i] - 97 + key[i] - 97) % 26 + 97);
	}
	cout << "Encrypted text: " << encrypted << '\n';

	cout << "\nDECRYPTION\nCiphertext: ";
	cin >> ciphertext;
	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::tolower);
	int csize = ciphertext.size();

	//Key generation for decryption
	key = "";
	if (ksize > csize) {
		key = keyword.substr(0, csize);
	}
	else {
		for (int i = 0; i < csize/ksize; i++) {
			key += keyword;
		}
		key += keyword.substr(0, (csize % ksize));
	}

	//decryption
	for (int i = 0; i < csize; i++) {
		decrypted.push_back((ciphertext[i] - 97 - key[i] + 97 + 26) % 26 + 97);
	}
	cout << "Decrypted text: " << decrypted << '\n';

	return 0;
}