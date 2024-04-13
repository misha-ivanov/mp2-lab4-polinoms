#include "list.h"
#include "polinom.h"
#include <vector>


int main() {
	vector<Polinom*> v; // storage of polinoms
	
	Polinom* A = new Polinom();
	Monom* M;

	int status = 2; // 0 - finish the program, 1 - add monom into this polinom

	double k;
	double tmp;
	int deg;
	int term1, term2; // numbers of polioms for actions


	cout << "WELCOME to the POLINOM CREATOR !!!" << endl << "Here you can add as much monoms and polinoms of 'xyz' view as you want and make some arithmetic operations with them (+, -, *)." << endl;
	while (status != 0) {
		switch (status) {
		case 0:
			cout << "Have a nice day :)";
			return 0;
		case 1: // CREATE NEW MONOM
			cout << "Creating new monom. Please, enter:" << endl << "coefficient: ";
			cin >> k;
			cout << endl << "Degree of x: ";
			cin >> tmp;
			deg = tmp * 100;
			cout << endl << "Degree of y: ";
			cin >> tmp;
			deg = deg + tmp * 10;
			cout << endl << "Degree of z: ";
			cin >> tmp;
			deg = deg + tmp;
			M = new Monom(k, deg);
			A->Push(*M);
			status = 0;
			break;
		case 2: // CREATE NEW POLINOM
			A = new Polinom();
			status = 1;
			break;
		case 3: // SAVE POLINOM
			cout << "Previous polinom was saved" << endl;
			v.push_back(A);
			status = 0;
			break;
		case 4: // SHOW EXISTING POLINOMS
			for (int i = 0; i < v.size(); i++) {
				cout << "#" << i + 1 << "   ";
				v[i]->Show();
				cout << endl;
			}
			status = 0;
			break;
		case 5: // OPEARTIONS WITH POLINOMS
			A = new Polinom();
			cout << "Choose an operation beneath:" << endl
				<< "1 - CONJUNCTION (+)" << endl
				<< "2 - SUBTRACTION (-)" << endl
				<< "3 - MULTIPLICATION (*)" << endl;
			cin >> status;
			switch (status) {
			case 1:  // +
				cout << "List of existing polinoms:" << endl;
				for (int i = 0; i < v.size(); i++) {
					cout << "#" << i + 1 << "   ";
					v[i]->Show();
					cout << endl;
				}
				while (status == 1) {
					cout << "Choose number of first term: ";
					cin >> term1;
					cout << "Choose number of second term: ";
					cin >> term2;
					if (term1 < 1 || term2 < 1 || term1 > v.size() || term2 > v.size()) {
						cout << "You have entered non existing polinom. Try again.";
						status = 1;
					}
					else
						status = 0;
				}
				*A = *v[term1 - 1] + *v[term2 - 1];
				break;
			case 2: // -
				cout << "List of existing polinoms:" << endl;
				for (int i = 0; i < v.size(); i++) {
					cout << "#" << i + 1 << "   ";
					v[i]->Show();
					cout << endl;
				}
				while (status == 2) {
					cout << "Choose number of first term: ";
					cin >> term1;
					cout << "Choose number of second term: ";
					cin >> term2;
					if (term1 < 1 || term2 < 1 || term1 > v.size() || term2 > v.size()) {
						cout << "You have entered non existing polinom. Try again.";
						status = 2;
					}
					else
						status = 0;
				}
				*A = *v[term1 - 1] - *v[term2 - 1];
				break;
			case 3: // *
				cout << "Would you like to multiply a polinom by a number or another polinom? Choose an option beneath:" << endl
					<< "0 - NUMBER" << endl
					<< "1 - POLINOM" << endl;
				cin >> status;
				if (status == 0) {
					cout << "List of existing polinoms:" << endl;
					for (int i = 0; i < v.size(); i++) {
						cout << "#" << i + 1 << "   ";
						v[i]->Show();
						cout << endl;
					}
					status = 1;
					while (status == 1) {
						cout << "Choose number of polinom: ";
						cin >> term1;
						if (term1 < 1 || term1 > v.size()) {
							cout << "You have entered non existing polinom. Try again.";
							status = 1;
						}
						else
							status = 0;
					}
					cout << "Choose number to multiply: ";
					cin >> term2;
					*A = *v[term1 - 1] * double(term2);
				}
				if (status == 1) {
					cout << "List of existing polinoms:" << endl;
					for (int i = 0; i < v.size(); i++) {
						cout << "#" << i + 1 << "   ";
						v[i]->Show();
						cout << endl;
					}
					while (status == 1) {
						cout << "Choose number of first term: ";
						cin >> term1;
						cout << "Choose number of second term: ";
						cin >> term2;
						if (term1 < 1 || term2 < 1 || term1 > v.size() || term2 > v.size()) {
							cout << "You have entered non existing polinom. Try again.";
							status = 1;
						}
						else
							status = 0;
					}
					*A = *v[term1 - 1] * *v[term2 - 1];
				}
				break;
			default:
				break;
			}
			cout << "Your active polinom is:  ";
			A->Show();
			cout << "Would you like to save it? Choose an option beneath:" << endl
				<< "0 - NO" << endl
				<< "1 - YES" << endl;
			cin >> status;
			if (status == 1) {
				v.push_back(A);
				cout << "Previous polinom was saved" << endl;
			}
			status = 0;
			break;
		default:
			break;
		}
		if (status != 1) {
			cout << endl << "Choose an option beneath:" << endl
				<< "0 - FINISH THE PROGRAM" << endl
				<< "1 - CREATE NEW MONOM" << endl
				<< "2 - CREATE NEW POLINOM" << endl
				<< "3 - SAVE ACTIVE POLINOM" << endl
				<< "4 - SHOW EXISTING POLINOMS" << endl
				<< "5 - OPERATIONS WITH POLINOMS" << endl;
			cin >> status;
		}
	}
}