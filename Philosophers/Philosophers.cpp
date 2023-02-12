#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using namespace std;
using namespace chrono;

void eating(bool* forks, int positionOfLeftFork, int positionOfRightFork, int loopIteration, string tabulation, string philisopherName) {
	string out = "[" + to_string(loopIteration) + "]" + tabulation + "Philosopher " + philisopherName + " is eating.\n";
	cout << out;
	this_thread::sleep_for(milliseconds(10));
	forks[positionOfLeftFork] = !forks[positionOfLeftFork];
	forks[positionOfRightFork] = !forks[positionOfRightFork];
}

void thinking(string tabulation, string philisopherName, int loopIteration) {
	string out = "[" + to_string(loopIteration) + "]" + tabulation + "Philosopher " + philisopherName + " is thinking.\n";
	cout << out;
	this_thread::sleep_for(milliseconds(10));
}

void waiting(bool* forks, int positionOfLeftFork, int positionOfRightFork, string tabulation, string philisopherName, int loopIteration) {
	if (forks[positionOfLeftFork] && forks[positionOfRightFork]) {
		forks[positionOfLeftFork] = !forks[positionOfLeftFork];
		forks[positionOfRightFork] = !forks[positionOfRightFork];
		eating(forks, positionOfLeftFork, positionOfRightFork, loopIteration, tabulation, philisopherName);

	}
	else thinking(tabulation, philisopherName, loopIteration);
	cout << endl;
}

int main() {
	bool forks[] = { true, true, true, true, true };

	for (int i = 0; i < 20; i++) {
		thread philisopherA(waiting, forks, 0, 1, "\t", "A",i);
		thread philisopherB(waiting, forks, 1, 2, "\t\t", "B",i);
		thread philisopherC(waiting, forks, 2, 3, "\t\t\t", "C",i);
		thread philisopherD(waiting, forks, 3, 4, "\t\t\t\t", "D",i);
		thread philisopherE(waiting, forks, 4, 0, "\t\t\t\t\t", "E",i);

		philisopherA.join();
		philisopherB.join();
		philisopherC.join();
		philisopherD.join();
		philisopherE.join();

		cout << endl;
	}

	system("pause");
}