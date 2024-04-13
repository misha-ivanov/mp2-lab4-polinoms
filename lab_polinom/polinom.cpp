#include "list.h"
#include "polinom.h"
#include <iostream>

Polinom::Polinom(Polinom& _p) {
	Node<Monom>* tmp_head = poli.HeadOut();
	Node<Monom>* tmp_p_head = _p.poli.HeadOut();
	while (tmp_p_head->next != nullptr) {
		tmp_head->next = new Node<Monom>(tmp_p_head->next->data);
		tmp_head = tmp_head->next;
		tmp_p_head = tmp_p_head->next;
	}
}

//This SearchSimilar function was modified and written beneath

/*void Polinom::SearchSimilar() {
	Node<Monom>* tmp_head = poli.HeadOut();
	while (tmp_head ->next != nullptr) {
		Node<Monom>* tmp = tmp_head->next;
		while (tmp->next != nullptr) {
			if (tmp_head->next->data.deg == tmp->next->data.deg) {
				tmp_head->next->data.k = tmp_head->next->data.k + tmp->next->data.k;
				poli.Delete(tmp->next);
			}
			if (tmp->next != nullptr)
				tmp = tmp->next;
		}
		tmp_head = tmp_head->next;
	}
}*/

void Polinom::SearchSimilar() {
	Node<Monom>* tmp_head = poli.HeadOut();
	while (tmp_head->next != nullptr && tmp_head->next->next != nullptr) {
		if (tmp_head->next->data.deg == tmp_head->next->next->data.deg) {
			tmp_head->next->data.k = tmp_head->next->data.k + tmp_head->next->next->data.k;
			poli.Delete(tmp_head->next->next);
		}
		else
			tmp_head = tmp_head->next;
	}
	DeleteZeroMonoms();
}

void Polinom::Push(Monom monom) {
	poli.Push(monom);
	poli.Sort();
	DeleteZeroMonoms();
	SearchSimilar();
}

void Polinom::Show() {
	Node<Monom>* tmp = poli.HeadOut();
	cout << "Your polinom: ";
	while (tmp->next != nullptr) {
		if (tmp == poli.HeadOut()) {
			if (tmp->next->data.k != 1 && tmp->next->data.k != -1 || tmp->next->data.deg == 0)
				cout << tmp->next->data.k;
			else {
				if (tmp->next->data.k == -1)
					cout << "-";
			}
			if(tmp->next->data.deg / 100 != 0)
				cout << " x^" << tmp->next->data.deg / 100;
			if (tmp->next->data.deg / 10 % 10 != 0)
				cout << " y^" << tmp->next->data.deg / 10 % 10;
			if (tmp->next->data.deg % 100 != 0)
				cout << " z^" << tmp->next->data.deg % 10;
		}
		else {
			if (tmp->next->data.k >= 0)
				cout << " + ";
			else
				cout << " - ";
			if(tmp->next->data.k != 1 && tmp->next->data.k != -1)
				cout << abs(tmp->next->data.k);
			if (tmp->next->data.deg / 100 != 0)
				cout << " x^" << tmp->next->data.deg / 100;
			if (tmp->next->data.deg / 10 % 10 != 0)
				cout << " y^" << tmp->next->data.deg / 10 % 10;
			if (tmp->next->data.deg % 100 != 0)
				cout << " z^" << tmp->next->data.deg % 10;
		}
		tmp = tmp->next;
	}
}

void Polinom::DeleteZeroMonoms() {
	Node<Monom>* tmp_head = poli.HeadOut();
	while (tmp_head->next != nullptr) {
		if ((tmp_head->next->data.k < 0.000001) && (tmp_head->next->data.k > -0.000001))
			poli.Delete(tmp_head->next);
		else
			tmp_head = tmp_head->next;
	}
}


//this Sort works correctly but was replaced into List file

/*void Polinom::Sort() {
	Node<Monom>* tmp_head = poli.HeadOut();
	Node<Monom>* tmp_swap = poli.HeadOut(); // empty node for swapping
	Node<Monom>* tmp_prev = poli.HeadOut(); // storage for pointer to tmp_head
	Node<Monom>* tmp = poli.HeadOut(); // next node after tmp_head
	int len = 0, f = 1, j, i = 0;
	
	while (tmp_head->next != nullptr) {
		len++;
		tmp_head = tmp_head->next;
	}
	while(i < len && f == 1){
		tmp_prev = poli.HeadOut();
		tmp_head = poli.HeadOut()->next;
		tmp = tmp_head->next;
		j = len - i - 1;
		while (j > 0) {
			if (tmp_head->data.deg < tmp->data.deg) { // swapping
				tmp_swap = tmp->next;
				tmp->next = tmp_head;
				tmp_prev->next = tmp;
				tmp_head->next = tmp_swap;
				f = 1;
				tmp_swap = tmp;
				tmp = tmp_head;
				tmp_head = tmp_swap;

			}
			tmp = tmp->next;
			tmp_head = tmp_head->next;
			tmp_prev = tmp_prev->next;
			j--;
		}
		i++;
	}
}*/

void Polinom::operator +=(Polinom& p) {
	Node<Monom>* tmp_head = poli.HeadOut();
	Node<Monom>* tmp_p_head = p.poli.HeadOut();
	Node<Monom>* tmp = poli.HeadOut(); // storage for temporary pointer
	while (tmp_head->next != nullptr && tmp_p_head->next != nullptr) {
		if (tmp_head->next != nullptr && tmp_p_head->next != nullptr && (tmp_head->next->data.deg == tmp_p_head->next->data.deg)) {
			tmp_head->next->data.k = tmp_head->next->data.k + tmp_p_head->next->data.k;
			tmp_head = tmp_head->next;
			tmp_p_head = tmp_p_head->next;
		}
		else
			if (tmp_head->next->data.deg > tmp_p_head->next->data.deg) {
				tmp_head = tmp_head->next;
			}
			else {
				tmp = tmp_head->next;
				tmp_head->next = new Node<Monom>(tmp_p_head->next->data, tmp_head->next);
				tmp_p_head = tmp_p_head->next;
				tmp_head = tmp_head->next;
			}
	}
	if(tmp_p_head->next != nullptr)
		while (tmp_p_head->next != nullptr) {
			tmp_head->next = new Node<Monom>(tmp_p_head->next->data);
			tmp_p_head = tmp_p_head->next;
			tmp_head = tmp_head->next;
		}
	DeleteZeroMonoms();
}

Polinom& Polinom::operator =(Polinom& _p) {
	Polinom* result = new Polinom(_p);
	poli = result->poli;
	/*Node<Monom>* tmp_head = poli.HeadOut();
	Node<Monom>* tmp_p_head = _p.poli.HeadOut();
	while (tmp_p_head->next != nullptr) {
		tmp_head->next = new Node<Monom>(tmp_p_head->next->data);
		tmp_head = tmp_head->next;
		tmp_p_head = tmp_p_head->next;
	}*/

	return *this;
}

Polinom& Polinom::operator +(Polinom& _p) {
	Polinom* result = new Polinom(*this);
	*result += _p;
	return *result;
}

Polinom& Polinom::operator *(double p) {
	Polinom* result = new Polinom(*this);
	Node<Monom>* tmp_head = result->poli.HeadOut();
	while (tmp_head->next != nullptr) {
		tmp_head->next->data.k = tmp_head->next->data.k * p;
		tmp_head = tmp_head->next;
	}
	result->DeleteZeroMonoms();
	return *result;
}

Polinom& Polinom::operator -(Polinom& _p) {
	Polinom* result = new Polinom(*this);
	*result += _p * -1;
	return *result;
}

Polinom& Polinom::operator *(Polinom& _p) {
	Polinom* result = new Polinom();
	Node<Monom>* tmp_head = this->poli.HeadOut();
	Node<Monom>* tmp_p_head = _p.poli.HeadOut();
	Monom* new_node;
	while (tmp_head->next != nullptr) {
		Node<Monom>* tmp_p_head = _p.poli.HeadOut();
		while (tmp_p_head->next != nullptr) {
			new_node = new Monom(tmp_head->next->data.k * tmp_p_head->next->data.k, tmp_head->next->data.deg + tmp_p_head->next->data.deg);
			result->Push(*new_node);
			tmp_p_head = tmp_p_head->next;
		}
		tmp_head = tmp_head->next;
	}
	result->DeleteZeroMonoms();
	return *result;
}