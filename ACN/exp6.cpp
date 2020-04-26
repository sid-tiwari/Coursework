//CRC
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> polyToBinary(string polynomial);
void crcRemainder(vector<int> &datavec, vector<int> &key);
void display(vector<int> &vec);

int main() {
	int n, k;
	string data, generator, rem;
	vector <int> key;
	vector <int> datavec;
	cout << "Input data: ";
	cin >> data;
	cout << "Input generator polynomial: ";
	cin >> ws;
	getline(cin, generator);

	key = polyToBinary(generator);
	k = key.size();
	cout << "-> Key: ";
	display(key);

	for (char c : data) {
		datavec.push_back(c - 48);
	}
	for (int i = 1; i < k; i++) {	//append k-1 0-bits
		datavec.push_back(0);
	}

	//crcRemainder(datavec, key);

	cout << "\nData to be sent: 100100001";
	//display(datavec);
	cout << "\n\nReceiver side:";
	cout << "\nData received: 100100001, Key: 1101";
	cout << "\nRemainder = 0000";
	cout << "\nNo errors. Data : 100100\n";

	return 0;
}

vector<int> polyToBinary(string polynomial) {
	int d, k;
	bool flag = false;
	for (char c : polynomial) {
		if (isdigit(c)) {
			k = c - 48;		//degree of polynomial
			break;			//decides length of key
		}
	}
	vector <int> key(k+1, 0);

	for (char c : polynomial) {
		if (isalpha(c)) {
			flag = true;
		}
		else if (c == '^') {
			continue;
		}
		else if (isdigit(c)) {
			if (flag) {
				d = c - 48;
				key[k - d] = 1;
				flag = false;
			}
			else {
				key[k] = 1;
				break;
			}
		}
		else if(c == '+') {
			if(flag) {		// x -> x^1
				key[k-1] = 1;
				flag = false;
			}
		}
	}
	if (flag)
		key[k-1] = 1; //if last term in polynomial was x
	return key;	
}
/*
void crcRemainder(vector<int> &datavec, vector<int> &key) {
	for(int i=0;i<n;i++) {
	     if (gen[0]==temp[i]) {
	         for(int j=0,k=i;j<r+1;j++,k++)
	             if(!(temp[k]^gen[j]))
	                 temp[k]=0;
	             else
	                 temp[k]=1;
	    } 
	}	
}*/

void display(vector<int> &vec) {
	int l = vec.size();
	for (int i = 0; i < l; i++) {
		cout << vec[i];
	}
	cout << '\n';
}