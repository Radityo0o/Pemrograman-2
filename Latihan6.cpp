#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

void headerUtama() {
	cout << "-------------------------" << endl;
	cout << "|	Pointer		|" << endl;
	cout << "-------------------------" << endl;
}

void menuUtama() {
	cout << "A. Pointer" << endl;
	cout << "B. Exit" << endl;
}

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

void inputA() {
	int x;
	cout << "Input Nilai X: ";
	cin >> x;
	cout << "-------------------" << endl;
	cout << endl;

	addrPointer(&x);
	hitungKuadrat(x);
	akarBosqu(x);

	cout << endl;
}

int main() {
	char yt;
	char inputMenu;

	headerUtama();
	menuUtama();
	cout << "-> ";
	cin >> inputMenu;
	if (inputMenu == 'A' || inputMenu == 'a')
	{
		do
		{
			cout << endl;
			inputA();
			cout << "Input Nilai Lagi? (Y/T): ";
			cin >> yt;
		} while (yt == 'Y' || yt == 'y');
	}
	else if (inputMenu == 'B' || inputMenu == 'b')
	{ 
		goto akhir;
	}
	else
	{
		cout << "Invalid Input!" << endl;
		return 0;
	}
akhir:	
	cout << "Program Selesai!" << endl;
	return 0;
}
