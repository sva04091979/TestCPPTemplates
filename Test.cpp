#include <iostream>
#include <string>
#include "Lib.h"
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

void FirstTask() {
	cout << "First task" << endl;
	using _Car = unique_ptr<ICar>;
	vector<_Car> arr;
	for (int i = 0; i < 10; ++i) {
		arr.push_back(MakeCar());
	}
	sort(arr.begin(), arr.end(), BaseGreater<_Car>);
	for (const auto& it : arr)
		cout << it->Info() << endl;
}

void SecondTask() {
	cout << "Second Task" << endl;
	using _Car = unique_ptr<ICar>;
	list<_Car> cars;
	Cargo cargo(1 + rand() % 100, 1 + rand() % 100);
	cout << cargo.Info() << endl;
	for (int i = 0; i < 10; ++i) {
		cars.push_back(MakeRandomCar());
	}
	cout << "Cars list:" << endl;
	for (const auto& it : cars)
		cout << it->Info() << endl;
	auto it = cars.begin();
	while (it != cars.end()) {
		if (it->get()->CanTake(cargo))
			++it;
		else it = cars.erase(it);
	}
	cout << "-------------------------" << endl;
	for (const auto& it : cars)
		cout << it->Info() << endl;
}

void ThirdTask() {
	cout << "Third Task" << endl;
	vector<int> arr(10);
	iota(arr.begin(), arr.end(), 0);
	for (auto& it : arr)
		cout << it << " ";
	cout << endl;
	Add(arr.begin(),arr.end());
	for (auto& it : arr)
		cout << it << " ";
	cout << endl;
}

void FoursTask() {
	cout << "Fours Task" << endl;
	using item = unique_ptr<IBase>;
	vector<item> obj(10);
	vector<int> num(10);
	iota(num.begin(), num.end(), 0);
	for (int i = 0; i < 10; ++i)
		obj[i]=MakeRandom();
	cout << "Before" << endl;
	for (auto& it : num)
		cout << it << " ";
	cout << endl;
	for (const auto& it : obj)
		cout << it->Info() << endl;
	Add(obj.begin(), obj.end());
	Add(num.begin(), num.end());
	cout << "After" << endl;
	for (auto& it : num)
		cout << it << " ";
	cout << endl;
	for (const auto& it : obj)
		cout << it->Info() << endl;
}

void FifthTask() {
	cout << "Fifth Task" << endl;
	Named<FullCar> fullCar("First",100, 100);
	Named<HalfCar> halfCar("Second", 200);
	Named<Cargo> cargo("Third", 50, 50);
	fullCar.Print();
	halfCar.Print();
	cargo.Print();
}

int main() {
	srand((unsigned int)time(nullptr));
	FirstTask();
	SecondTask();
	ThirdTask();
	FoursTask();
	FifthTask();
}
