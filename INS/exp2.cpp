//Monoalphabetic substitution cipher

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

char getkey(map <char, char> key, char value) {
	for (auto itr = key.begin(); itr != key.end(); itr++) {
		if (itr->second == value)
			return (itr->first);
	}
	return '-';
}

int main() {

	string plaintext, ciphertext, encrypted = "", decrypted = "";
	//a->0->f . . . z->25->j
	string key = "fragyilmcpeoztnsxbdvqkhwuj";

	cout << "\nENCRYPTION\nPlaintext: ";
	cin >> plaintext;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);

	//encryption
	for (char c : plaintext) {
		encrypted.push_back(key[c-'a']);
	}
	cout << "Encrypted text: " << encrypted << '\n';

	cout << "\nDECRYPTION\nCiphertext: ";
	cin >> ciphertext;
	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::tolower);

	//decryption
	for (char c : ciphertext) {
		decrypted.push_back(key.find(c) + 'a');
	}
	cout << "Decrypted text: " << decrypted << '\n';

	return 0;
}