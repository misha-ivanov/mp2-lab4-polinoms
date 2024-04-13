#pragma once

#include "list.h"
#include <iostream>

using namespace std;

struct Monom {
	double k;
	int deg;
public:
	Monom() {
		k = 0;
		deg = 0;
	}

	Monom(double _k, int _deg) {
		if (_deg > 999 || _deg < 0)
			throw "deg_is_out_of_range";
		k = _k;
		deg = _deg;
	}

	void operator =(const Monom m) {
		k = m.k;
		deg = m.deg;
	}

	bool operator >(const Monom m) {
		if (deg > m.deg)
			return true;
		return false;
	}

	bool operator <(const Monom m) {
		if (deg < m.deg)
			return true;
		return false;
	}
};

class Polinom {
	List<Monom> poli;
public:
	Polinom() {
		poli = List<Monom>();
	}

	Polinom(Polinom& p);
	
	List<Monom> PoliOut() { return poli; }

	void SearchSimilar();

	void Push(Monom monom);

	void Show();

	void DeleteZeroMonoms();

	//void Sort();

	void operator +=(Polinom& p);

	Polinom& operator =(Polinom& _p);

	Polinom& operator +(Polinom& _p);

	Polinom& operator -(Polinom& _p);

	Polinom& operator *(double p);

	Polinom& operator *(Polinom& _p);
};
