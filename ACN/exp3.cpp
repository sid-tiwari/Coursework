//Selective repeat ARQ
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void delay() {
	for (int i = 0; i < 10000; i++)
		for(int j = 0; j < 10000; j++)
			;
}

void flush(vector <int> &nacked, int ws, int div) {
	int temp;
	cout << "Receiver: Window full.\n";
	cout << "Sender: Resending NACK frames...\n";
	delay();
	for (auto itr = nacked.begin(); itr != nacked.end(); itr++) {
		temp = div * ws + (*itr);
		cout << "Sender: Sent frame " << temp << '\n';
		delay();
		cout << "Receiver: Frame " << temp << " ACK.\n";
	}
}

int main() {
	srand((unsigned) time(0));
	int numFrames, ws, seq, randnum, div, temp;
	vector <int> nacked;

	cout << "Window size: ";
	cin >> ws;

	cout << "No. of frames to be sent: ";
	cin >> numFrames;

	for (int i = 0; i < numFrames; i++) {
		//i -> frame no.
		//seq -> sequence no.
		div = i / ws;
		seq = i % ws;

		cout << "Sender: Sent frame " << i << '\n';
		delay();
		randnum = rand() % 3;
		if (randnum) {
			cout << "Receiver: Frame " << i << " ACK.\n";
		}
		else {
			cout << "Receiver: Frame " << i << " NACK.\n";
			nacked.push_back(seq);
		}

		//flush NACKs if window is full
		if (seq == ws - 1 && nacked.size() > 0) {
			flush(nacked, ws, div);
			nacked.clear();
		}
	}
	if (nacked.size() > 0) {
		flush(nacked, ws, div);
		nacked.clear();
	}
	cout << "All frames successfully sent.\n";
	return 0;
}

	