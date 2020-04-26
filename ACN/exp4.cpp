//Bit-stuffing
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {

	string input;
	cout << "Input data bits: ";
	cin >> input;
	vector<char> bits(input.begin(), input.end());

	int count = 0;
	for (int i = 0; i < bits.size(); ++i) {
		if (bits[i] == '0') {
			count = 0;
		}
		else {
			count += 1;
			if (count == 5) {
				bits.insert(bits.begin() + i + 1, '0');
			}
		}
	}
	cout << "Bit-stuffed data: ";
	for (char x: bits) {
		cout << x;
	}
	cout << '\n';

	return 0;
}