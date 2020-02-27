//Go-Back n
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand((unsigned) time(0));
	int numFrames, n, randnum, dropped = 0, flag = 0;

	cout << "Window size: ";
	cin >> n;
	cout << "No. of frames to be sent: ";
	cin >> numFrames;

	for (int i = 1; i <= numFrames + 1; i++) {
		if (i == numFrames + 1) {
			if (flag && dropped > 0) {
				i = dropped - 1;
				flag = 0;
				cout << "\nFrame " << dropped << " not acknowledged. Resending..."; 
			}
		}
		else {
			if (flag && i >= dropped + n) {
				i = dropped - 1; //reset to first dropped packet
				flag = 0;
				cout << "\nFrame " << dropped << " not acknowledged. Resending..."; 
			}
			else {
				cout << "\nSending frame " << i << "...";
				randnum = rand() % 4;
				if (randnum) {
					cout << "Frame " << i << " acknowledged.";
				}
				else if (!flag) {
					dropped = i;
					flag = 1;
				}
			}
		}
	}
	cout << '\n';
	return 0;
}