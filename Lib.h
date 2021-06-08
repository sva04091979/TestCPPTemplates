#pragma once
#include <type_traits>

using namespace std;

class CWeight {
protected:
	size_t weight;
};

class CVolume {
protected:
	size_t volume;
};

template<typename ...Types>
class CBase :public Types...{
protected:
	virtual size_t DefaultWeight() const =0;
	virtual size_t DefaultVolume() const =0;
public:
	size_t Weight() const {
		if constexpr (disjunction_v<is_same<CWeight, Types>...>)
			return CWeight::weight;
		else return DefaultWeight();
	}
	size_t Volume() const {
		if constexpr (disjunction_v<is_same<CVolume, Types>...>)
			return CVolume::volume;
		else return DefaultVolume();
	}
};

template<typename ...Types>
bool operator < (const CBase<Types...>&& l, const CBase<Types ...>&& r) {
	int wl = l.Weight(),
		wr = r.Weight();
	return wl < wr || (wl == wr && wl.Volume() < wr.Volume());
}

class Cargo:public CBase<CWeight,CVolume> {
public:
	Cargo() = default;
	Cargo(size_t _w, size_t _v){
		weight = _w;
		volume = _v;
	}
	size_t DefaultWeight() const override final { return 0; }
	size_t DefaultVolume() const override final { return 0; }
};

template<typename ...Types>
class CarBase :public CWeight, Types ...{
public:
	size_t DefaultWeight() const override final { return SIZE_MAX; }
	size_t DefaultVolume() const override final { return SIZE_MAX; }

};
