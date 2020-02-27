//Playfair cipher
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector< vector<char> > keygen(string key);
string process_plaintext(string plaintext);
string encrypt(string proc_ptext, vector<vector<char> > keysquare, 
				unordered_map <char, pair<int,int> > keymap);
string decrypt(string ciphertext, vector<vector<char> > keysquare, 
				unordered_map <char, pair<int,int> > keymap);

int main() {
	string key, plaintext, ciphertext;
	vector<vector<char> > keysquare(5, vector<char> (5));
	unordered_map <char, pair<int,int> > keymap;

	cout << "\nInput key: ";
	cin >> key;
	transform(key.begin(), key.end(), key.begin(), ::tolower);
	cout << "Input plaintext: ";
	cin >> plaintext;
	transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::tolower);
	//Key generation
	keysquare = keygen(key);
	cout << "\nKey square for encryption: \n";
	for (int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			cout << keysquare[i][j] << " ";
			keymap[keysquare[i][j]] = make_pair(i, j);
		}
		cout << '\n';
	}
	//Processing plaintext before encryption
	string proc_ptext = process_plaintext(plaintext);
	cout << "\nProcessed plaintext: " << proc_ptext << '\n';
	//Encryption
	string encrypted = encrypt(proc_ptext, keysquare, keymap);
	cout << "\nCiphertext: " << encrypted << '\n';

	//Decryption
	cout << "\nInput ciphertext: ";
	cin >> ciphertext;
	transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::tolower);
	string decrypted = decrypt(ciphertext, keysquare, keymap);
	cout << "\nDecrypted plaintext: " << decrypted << '\n';
	return 0;
}

vector<vector<char> > keygen(string key) {
	int current = 0, row = 0, col = 0;
	unordered_map <char, int> dups;
	vector< vector<char> > keysquare(5, vector<char> (5));
	for (char c : key) {
		if (dups.count(c) > 0)
			continue;
		else {
			if (c == 'j')
				dups['i'] += 1;
			else {
				dups[c] = 1;
				keysquare[row][col] = c;
				current++;
				row = current / 5;
				col = current % 5;
			}
		}
	}
	for (char c = 'a'; c <= 'z'; c++) {
		if (dups.count(c) > 0 || c == 'j')
			continue;
		else {
			row = current / 5;
			col = current % 5;
			keysquare[row][col] = c;
			current++;
		}
	}
	return keysquare;
}

string process_plaintext(string plaintext) {
	int len = plaintext.size();
	//separating same characters by inserting x
	for (int i = 1; i < len; i++) {
		if (plaintext[i] == plaintext[i-1]) {
			plaintext.insert(plaintext.begin() + i, 'x');
			len += 1;
		}
	}
	//appending x if odd number of characters
	if (len % 2) 
		plaintext.append("x");

	return plaintext;
}

string encrypt(string proc_ptext, vector<vector<char> > keysquare, 
				unordered_map <char, pair<int,int> > keymap) {
	int len = proc_ptext.size();
	int x1, y1, x2, y2;
	string encrypted = "";
	//encrypting chars pairwise
	for (int i = 0; i < len; i += 2) {
		x1 = keymap[proc_ptext[i]].first;
		y1 = keymap[proc_ptext[i]].second;
		x2 = keymap[proc_ptext[i+1]].first;
		y2 = keymap[proc_ptext[i+1]].second;
		if (x1 == x2) {	   //case 1: same row
			y1 += 1;	//immediate right
			y1 %= 5;	//wrapping around to left
			y2 += 1;
			y2 %= 5;
		}
		else if (y1 == y2) {	//case 2: same column
			x1 += 1;	//immediate below
			x1 %= 5;	//wrapping over to top
			x2 += 1;
			x2 %= 5;
		}
		else {	//case 3: forming rectangle
			swap(y1, y2); //opposite corners of rectangle
						  //staying in same row
		}
		encrypted.append(1, keysquare[x1][y1]);
		encrypted.append(1, keysquare[x2][y2]);
		encrypted.append(1, ' ');
	}
	return encrypted;
}

string decrypt(string ciphertext, vector<vector<char> > keysquare, 
				unordered_map <char, pair<int,int> > keymap) {
	int len = ciphertext.size();
	int x1, y1, x2, y2;
	string decrypted = "";
	if (len % 2) {
		return "Invalid ciphertext. Odd no. of characters!";
	}
	else {
		for (int i = 0; i < len; i += 2) {
			x1 = keymap[ciphertext[i]].first;
			y1 = keymap[ciphertext[i]].second;
			x2 = keymap[ciphertext[i+1]].first;
			y2 = keymap[ciphertext[i+1]].second;
			if (x1 == x2) {	//case 1: same row
				y1 -= 1;	//reversing to immediate left
				if (y1 < 0) y1 = 4;	//wrapping around to right
				y2 -= 1;
				if (y2 < 0) y2 = 4;
			}
			else if (y1 == y2) {	//case 2: same column
				x1 -= 1;	//reversing to immediate above
				if (x1 < 0) x1 = 4;	//wrapping over to bottom
				x2 -= 1;
				if (x2 < 0) x2 = 4;
			}
			else {	//case 3: forming rectangle
				swap(y1, y2); //opposite corners of rectangle
						  	  //staying in same row
			}
			decrypted.append(1, keysquare[x1][y1]);
			decrypted.append(1, keysquare[x2][y2]);
			decrypted.append(1, ' ');
		}
		return decrypted;
	}
}