#pragma once
#include <type_traits>
#include <iostream>
#include <memory>

using namespace std;

class Cargo;

class IBase {
public:
	virtual size_t Weight() const = 0;
	virtual size_t Volume() const = 0;
	virtual string Info() const = 0;
	virtual void operator ++() = 0;
	virtual void Print() { cout << Info() << endl; }
};

class ICar:public IBase {
public:
	virtual bool CanTake(const Cargo& cargo) const = 0;
};

bool operator < (const IBase& l, const IBase& r) {
	int wl = l.Weight(),
		wr = r.Weight();
	return wl < wr || (wl == wr && l.Volume() < r.Volume());
}

inline bool operator > (const IBase& l, const IBase& r) {
	int wl = l.Weight(),
		wr = r.Weight();
	return wl > wr || (wl == wr && l.Volume() > r.Volume());
}

class CWeight {
protected:
	size_t weight;
	CWeight(size_t _v):weight(_v){}
};

class CVolume {
protected:
	size_t volume;
	CVolume(size_t _v) :volume(_v) {}
};

template<typename BaseType, typename ...Types>
class CBase :public BaseType, public Types...{
protected:
	template<typename ...Args>
	CBase(Args&&...params) :BaseType(), Types(forward<Args>(params))...{}
	inline virtual size_t DefaultWeight() const = 0;
	inline virtual size_t DefaultVolume() const = 0;

public:
	size_t Weight() const override final {
		if constexpr (disjunction_v<is_same<Types, CWeight>...>)
			return this->weight;
		else return DefaultWeight();
	}
	size_t Volume() const override final {
		if constexpr (disjunction_v<is_same<Types, CVolume>...>)
			return this->volume;
		else return DefaultVolume();
	}
	void operator ++() override {
		if constexpr (disjunction_v<is_same<Types, CWeight>...>)
			++(this->weight);
		if constexpr (disjunction_v<is_same<Types, CVolume>...>)
			++(this->volume);
	}
};

class Cargo:public CBase<IBase,CWeight,CVolume>{
public:
	Cargo(size_t weight, size_t volume) :CBase<IBase,CWeight,CVolume>(weight, volume) {}
	string Info() const override {
		return string("Cargo. Weight = " + to_string(Weight()) + ". Volume = " + to_string(Volume()) + ".");
	}
protected:
	inline size_t DefaultWeight() const override { return 0; }
	inline size_t DefaultVolume() const override { return 0; }
};

template<typename ...Types>
class Car :public CBase<ICar,Types...>{
	using Base = CBase<ICar, Types...>;
public:
	template<typename...Args>
	Car(Args&&...params): Base(forward<Args>(params)...){}
	string Info() const override {
		string capacityInfo;
		if constexpr (disjunction_v<is_same<Types, CVolume>...>)
			capacityInfo += "Capacity = " + to_string(this->Volume()) + ".";
		return string("Car. Carrying = " + to_string(this->Weight()) + ". " + capacityInfo);
	}
	bool CanTake(const Cargo& cargo) const override{
		return this->Weight() >= cargo.Weight() && this->Volume() >= cargo.Volume();
	}
protected:
	inline size_t DefaultWeight() const override { return SIZE_MAX; }
	inline size_t DefaultVolume() const override { return SIZE_MAX; }
};

template<typename Type,
typename=enable_if_t<is_base_of_v<IBase,Type>>>
class Named :public Type {
	string name;
public:
	template<typename...Args>
	Named(const char* _name,Args&&...params) :Type(forward<Args>(params)...), name(_name) {}
	string Info() const override {
		if constexpr (is_base_of_v<ICar, Type>) {
			string ret = "Car with name " + name + ". Carrying = " + to_string(this->Weight()) + ". ";
			if constexpr (is_base_of_v<CVolume, Type>)
				ret += "Capacity = " + to_string(this->Volume()) + ".";
			return ret;
		}
		else
			return string("Cargo with name "+name+". Weight = " + to_string(this->Weight()) + ". Volume = " + to_string(this->Volume()) + ".");
	}
};

using FullCar=Car<CWeight,CVolume>;
using HalfCar = Car<CWeight>;

auto MakeCar() {
	return unique_ptr<ICar>(new FullCar(1 + rand() % 100, 1 + rand() % 100));
}

auto MakePartialCar() {
	return unique_ptr<ICar>(new HalfCar(1 + rand() % 100));
}

auto MakeRandomCar() {
	return rand() % 2 == 0 ?MakePartialCar() : MakeCar();
}

auto MakeCargo() {
	return make_unique<Cargo>(1 + rand() % 100, 1 + rand() % 100);
}

auto MakeRandom() {
	switch (rand() % 3) {
	case 0: return static_cast<unique_ptr<IBase>>(MakeCar());
	case 1: return static_cast<unique_ptr<IBase>>(MakePartialCar());
	default:return static_cast<unique_ptr<IBase>>(MakeCargo());
	}
}

template<typename Type>
bool BaseGreater(Type& l, Type& r) {
	return *(l.get()) > *(r.get());
}

template<typename Type>
void Add(const Type& val) {
	++val;
}

template<typename Type>
void Add(Type& val) { ++val; }

template<typename Type>
void Add(unique_ptr<Type>& val) { ++(*val); }

template<typename Iterator>
void Add(Iterator first, Iterator last) {
	if (first == last) return;
	Add(*first);
	Add(++first, last);
}