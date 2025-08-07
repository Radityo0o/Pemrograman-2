#include <iostream>
#include <cmath>
using namespace std;

int rekX(int n) {

	if (n > 1){

		return n * rekX(n - 1);

	}
	else {

		return 1;

	}

}

int rekP(int m) {

	if (m > 1) {

		return m + rekP(m - 1);

	}
	else {

		return 1;

	}

}

int main() {

	int x, p;
	char menu, yt;

awal:
	cout << "-----------------------" << endl;
	cout << "| KALKULATOR REKURSIF |" << endl;
	cout << "-----------------------" << endl << endl;
	cout << "A. Faktorial Rekursif" << endl;
	cout << "B. Penjumlahan Rekursif" << endl;
	cout << endl << "Pilihan anda: ";
	cin >> menu;

	if (menu == 'A' || menu == 'a') {

		cout << "Masukkan angka: ";
		cin >> x;
		cout << endl << x << "! = ";
		for (int i = 1; i <= x; i++) {

			cout << i;
			if (i != x) {

				cout << " x ";

			}

		}

		cout << " = " << rekX(x) << endl;

	}
	else if (menu == 'B' || menu == 'b') {

		cout << "Masukkan angka: ";
		cin >> p;
		cout << endl << p << "+ = ";
		for (int i = 1; i <= p; i++) {

			cout << i;
			if (i != p) { 
			
				cout << " + "; 
			
			}

		}

		cout << " = " << rekP(p) << endl;

	}
	else {

		goto akhir;

	}

	cout << "Masukkan Data Lagi (Y/T)? ";
	cin >> yt;
	cout << endl;

	if (yt == 'Y' || yt == 'y') {
		goto awal;
	}
	else {
		goto akhir;
	}

akhir:
	return 0;

}