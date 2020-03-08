//S-DES subkey generation
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void display(vector<int> &vec);
void lcs(vector<int> &vec);

int main() {
	srand((unsigned) time(0));
	vector<int> rkey(10, 0);	//initial 10-bit random key
	vector<int> key(10, 0);	//key after P10
	vector<int> lsl, lsr;	//5-bit halves
	vector<int> subkey1(8, 0), subkey2(8, 0); //8-bit subkeys
	
	//Generate 10-bit random key
	for (int i = 0; i < 10; i++) {
		rkey[i] = rand() % 2;
	}
	//rkey = {1,0,1,0,0,0,0,0,1,0};
	cout << "\nInitial random key: ";
	display(rkey);
	//P10 permutation - 3,5,2,7,4,10,1,9,8,6
	key[0] = rkey[2];
	key[1] = rkey[4];
	key[2] = rkey[1];
	key[3] = rkey[6];
	key[4] = rkey[3];
	key[5] = rkey[9];
	key[6] = rkey[0];
	key[7] = rkey[8];
	key[8] = rkey[7];
	key[9] = rkey[5];
	cout << "\nAfter P10: ";
	display(key);

	//Divide into halves. Left circular shift each half
	for (int i = 0; i < 5; i++) {
		lsl.push_back(key[i]);
	}
	lcs(lsl);	//left circular shift done on left half
	cout << "Left half after LS-1: ";
	display(lsl);

	for (int i = 5; i < 10; i++) {
		lsr.push_back(key[i]);
	}
	lcs(lsr);
	cout << "Right half after LS-1: ";
	display(lsr);

	//Subkey 1 - P8 - 6,3,7,4,8,5,10,9 (1,2 discarded)
	subkey1[0] = lsr[0]; //6th bit
	subkey1[1] = lsl[2]; //3rd bit
	subkey1[2] = lsr[1]; //7th bit
	subkey1[3] = lsl[3]; //4th bit
	subkey1[4] = lsr[2]; //8th bit
	subkey1[5] = lsl[4]; //5th bit
	subkey1[6] = lsr[4]; //10th bit
	subkey1[7] = lsr[3]; //9th bit
	cout << "\nSubkey 1: ";
	display(subkey1);

	//2 x Left circular shifts on halves for subkey 2
	lcs(lsl);
	lcs(lsl);
	cout << "\nLeft half after LS-2: ";
	display(lsl);

	lcs(lsr);
	lcs(lsr);
	cout << "Right half after LS-2: ";
	display(lsr);

	//Subkey 2 - P8 - 6,3,7,4,8,5,10,9
	subkey2[0] = lsr[0]; //6th bit
	subkey2[1] = lsl[2]; //3rd bit
	subkey2[2] = lsr[1]; //7th bit
	subkey2[3] = lsl[3]; //4th bit
	subkey2[4] = lsr[2]; //8th bit
	subkey2[5] = lsl[4]; //5th bit
	subkey2[6] = lsr[4]; //10th bit
	subkey2[7] = lsr[3]; //9th bit
	cout << "\nSubkey 2: ";
	display(subkey2);
	return 0;
}

void display(vector<int> &vec) {
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		cout << *i;
	}
	cout << '\n';
}

void lcs(vector<int> &vec) {
	vec.push_back(vec[0]);
	vec.erase(vec.begin());
}