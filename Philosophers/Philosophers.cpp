//#include <thread>
//#include <iostream>
//#include <string>
//#include <mutex>
//
//using namespace std;
//using namespace chrono;
//
//
//
//void waiting(bool* forks, int leftFork, int rightFork, string tabulation, string philisopherName, int loopIteration) {
//	if (forks[leftFork] && forks[rightFork]) {
//		forks[leftFork] = !forks[leftFork];
//		forks[rightFork] = !forks[rightFork];
//		eating(forks, leftFork, rightFork, loopIteration, tabulation, philisopherName);
//
//	}
//	else thinking(tabulation, philisopherName, loopIteration);
//	cout << endl;
//}
//
//int main() {
//	bool forks[] = { true, true, true, true, true };
//
//	for (int i = 0; i < 20; i++) {
//		thread philisopherA(waiting, forks, 0, 1, "\t", "A",i);
//		thread philisopherB(waiting, forks, 1, 2, "\t\t", "B",i);
//		thread philisopherC(waiting, forks, 2, 3, "\t\t\t", "C",i);
//		thread philisopherD(waiting, forks, 3, 4, "\t\t\t\t", "D",i);
//		thread philisopherE(waiting, forks, 4, 0, "\t\t\t\t\t", "E",i);
//
//		philisopherA.join();
//		philisopherB.join();
//		philisopherC.join();
//		philisopherD.join();
//		philisopherE.join();
//
//		cout << endl;
//	}
//
//	system("pause");
//}

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
	bool isFree = true;
};

void eating(vector<Fork>& forks, int leftFork, int rightFork, int philosopher) {
	string tabulation(philosopher, '\t');
	string out = tabulation + "Philosopher " + to_string(philosopher) + " is eating.\n";
	cout << out;
	forks[leftFork].isFree = !forks[leftFork].isFree;
	forks[rightFork].isFree = !forks[rightFork].isFree;
}

void thinking(int philosopher) {
	string tabulation(philosopher, '\t');
	string out = "Philosopher " + to_string(philosopher) + " is thinking.\n";
	cout << out;
}

void waiting(vector<Fork>& forks, int leftFork, int rightFork, int philosopher, int tabulation) {
	int seconds = 1;
	auto endTimer = time(NULL) + seconds;

	random_device random;
	uniform_int_distribution<int> int_distribution(0, 100);

	int delay = int_distribution(random);
	this_thread::sleep_for(microseconds(delay));

	if (rightFork > forks.size())
		rightFork = 0;

	while (time(NULL) < endTimer) {
		if (forks[leftFork].isFree && forks[rightFork].isFree) {
			forks[leftFork].isFree = !forks[leftFork].isFree;
			forks[rightFork].isFree = !forks[rightFork].isFree;
			string tab(philosopher, '\t');
			string out = tab + to_string(philosopher) + " is eating.\n";
			cout << out;
			forks[leftFork].isFree = !forks[leftFork].isFree;
			forks[rightFork].isFree = !forks[rightFork].isFree;
		}
		else {
			string tab(philosopher, '\t');
			string out = tab + to_string(philosopher) + " is thinking.\n";
			cout << out;
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

	for (int i = 0; i < numOfPhilisophers; i++) {
		vectorOfPhilosophers.emplace_back(waiting, ref(vectorOfForks), i, i + 1, i + 1, i);
	}

	for (thread& thread : vectorOfPhilosophers) {
		thread.join();
	}
	system("pause");
}