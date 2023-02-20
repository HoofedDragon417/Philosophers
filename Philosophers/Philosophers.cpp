#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <random>
#include <time.h>

using namespace std;
using namespace chrono;

class Fork {
public:
	int isFree = 1;
};

void waiting(vector<Fork>& forks, int leftFork, int rightFork, int philosopher, int tabulation) {
	int seconds = 1;
	auto endTimer = time(NULL) + seconds;

	random_device random;
	uniform_int_distribution<int> int_distribution(0, 100);

	int delay = int_distribution(random);
	this_thread::sleep_for(microseconds(delay));

	int iteration = 0;

	int trueRightFork = rightFork;
	if (rightFork > forks.size())
		trueRightFork = 0;

	while (time(NULL) < endTimer) {
		if (forks.at(leftFork).isFree && forks.at(trueRightFork).isFree) {
			forks.at(leftFork).isFree = (int)!forks.at(leftFork).isFree;
			forks.at(trueRightFork).isFree = (int)!forks.at(trueRightFork).isFree;

			string tab(philosopher, '\t');
			string out = "[" + to_string(iteration) + "]" + tab + "Philosopher " + to_string(philosopher) + " is eating.\n";

			iteration++;

			cout << out;

			forks.at(leftFork).isFree = (int)!forks.at(leftFork).isFree;
			forks.at(trueRightFork).isFree = (int)!forks.at(trueRightFork).isFree;

			this_thread::sleep_for(microseconds(10));
		}
		else {
			string tab(philosopher, '\t');
			string out = "[" + to_string(iteration) + "]" + tab + "Philosopher " + to_string(philosopher) + " is thinking.\n";

			iteration++;

			cout << out;

			this_thread::sleep_for(microseconds(10));
		}
		cout << endl;
	}
}

int main() {
	int numOfPhilisophers;
	vector<thread> vectorOfPhilosophers;
	vector<Fork> vectorOfForks;

	cout << "Input number of philisophers: ";
	cin >> numOfPhilisophers;
	cout << "\n";

	for (int i = 0; i < numOfPhilisophers; i++)
		vectorOfForks.emplace_back();

	for (int i = 0; i < numOfPhilisophers; i++)
		vectorOfPhilosophers.emplace_back(waiting, ref(vectorOfForks), i, i + 1, i + 1, i);

	for (thread& philosopher : vectorOfPhilosophers)
		philosopher.join();
}