//Stop and Wait ARQ

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
	srand((unsigned) time(0));
	int numFrames, randnum;

	cout << "No. of frames to be sent: ";
	cin >> numFrames;

	for (int i = 1; i <= numFrames; i++) {
		cout << "Sending frame (Frame no. " << i << ")...\n";
		randnum = rand() % 4;
		if (randnum) {
			cout << "ACK for frame no. " << i << " received.\n";
		}
		else {
			cout << "No ACK for frame no. " << i << "...Resending...\n";
			i = i - 1;
		}
	}
	return 0;
}