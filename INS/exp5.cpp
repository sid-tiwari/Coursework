//Hill Cipher
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string encrypt(string text, vector<vector<int> > key);
//string decrypt(string text, vector<vector<int> > keyinverse);
vector<vector<int> > matrixMult(vector<vector<int> > key, 
								vector<vector<int> > text);

int main() {
	string plaintext, ciphertext;

	vector<vector<int> > key {{3, 3},
							  {2, 5}};
	vector<vector<int> > keyinverse {{15, 17}, //inverse mod 26
									 {20, 9}};

	cout << "Input plaintext: ";
	cin >> plaintext;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	//Pre-processing
	int len = plaintext.size();
	if (len % 2)	//since key is 2x2 matrix, need pairs
		plaintext.append("x");
	cout << "Processed plaintext (2x2 key): ";
	for (int i = 0; i < len; i += 2) {
		cout << plaintext[i] << plaintext[i+1] << ' ';
	}
	//Encryption
	string encrypted = encrypt(plaintext, key);
	cout << "\nCiphertext: " << encrypted;

	//Decryption
	cout << "\n\nInput ciphertext: ";
	cin >> ciphertext;
	len = ciphertext.size();
	if (len % 2)
		cout << "Invalid ciphertext. Must have even no. of characters for 2x2 key\n";
	else {
		string decrypted = encrypt(ciphertext, keyinverse);
		cout << "Plaintext: " << decrypted << '\n';
	}
	return 0;
}

string encrypt(string text, vector<vector<int> > key) {
	vector<vector<int> > pt(2, vector<int>(1));
	vector<vector<int> > ct(2, vector<int>(1));
	string encrypted = "";
	int len = text.size();
	for (int i = 0; i < len; i += 2) {
		pt[0][0] = text[i] - 'a';
		pt[1][0] = text[i+1] - 'a';
		ct = matrixMult(key, pt);
		encrypted.append(1, ct[0][0] + 'a');
		encrypted.append(1, ct[1][0] + 'a'); 
	}
	return encrypted;
}

vector<vector<int> > matrixMult(vector<vector<int> > key, 
								vector<vector<int> > text) {
	//key: 2x2, text: 2x1
	vector<vector<int> > result(2, vector<int>(1));
	result[0][0] = key[0][0] * text[0][0] + key[0][1] * text[1][0];
	result[0][0] %= 26;
	result[1][0] = key[1][0] * text[0][0] + key[1][1] * text[1][0];
	result[1][0] %= 26;
	return result;
}