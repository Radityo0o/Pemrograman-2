#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

void hitungKuadrat(int a) {
	int hasil = a * a;
	cout << "-> Hasil Kuadrat Dari " << a << " = " << hasil << endl;
}

void addrPointer(int* inputPtr) {
	cout << "-> Address " << *inputPtr << " = " << inputPtr << endl;
}

void akarBosqu(float b) {
	float hasilAkar = sqrt(b);
	cout << "-> Hasil Akar Dari " << b << " = " << hasilAkar << endl;
}

int main() {
	int x;
	char yt;

	cout << "-------------------------" << endl;
	cout << "|	Pointer		|" << endl;
	cout << "-------------------------" << endl;

	do {
		cout << "Input Nilai X: ";
		cin >> x;
		cout << endl;

		addrPointer(&x);
		hitungKuadrat(x);
		akarBosqu(x);

		cout << endl;
		cout << "Input Nilai Lagi?(Y/T): ";
		cin >> yt;
		cout << endl; 
	} while (yt == 'Y' || yt == 'y');
	cout << "Program Selesai!" << endl;
	return 0;
}
