#include <iostream>
#include <cmath>
using namespace std;

const double pi = 3.14159265359;
char input, yt;

double luas(double d1, double d2);
double keliling(double a, double b);
double volume(double radius, double tinggi);

double luas(double d1, double d2)
{
	return(0.5 * d1 * d2);
}

double keliling(double a, double b)
{
	return(2 * (a + b));
}

double volume(double radius, double tinggi)
{
	return(pi * (radius * radius) * tinggi);
}

int main() {
	double a, b, d1, d2, radius, tinggi;

awal:	

	cout << "=================\t" << endl;
	cout << "|MARI MENGHITUNG|\t" << endl; 
	cout << "=================\t" << endl; 
	cout << endl << endl;

	cout << "Apa yang ingin anda hitung?" << endl;
	cout << "A. Luas dan Keliling Layang-layang\n" << "B. Volume Tabung" << endl;
	cout << "\n> ";
	cin >> input;
	cout << endl;
	
	if (input == 'A' || input == 'a') {

		cout << "Menghitung Luas dan Keliling Layang-layang" << endl << endl;

		cout << "Input sisi miring 1(a): ";
		cin >> a;
		cout << "Input sisi miring 2(b): ";
		cin >> b;
		cout << "Input diagonal 1(d1): ";
		cin >> d1;
		cout << "Input diagonal 2(d2): ";
		cin >> d2;
		cout << endl;

		cout << "Luas Layang-layang Adalah: " << luas(d1,d2) << "cm2" << endl;
		cout << "Keliling Layang-layang Adalah: " << keliling(a, b) << "cm" << endl;

	}
	else if (input == 'B' || input == 'b') {

		cout << "Menghitung Volume Tabung" << endl << endl;

		cout << "Input Jari-jari Tabung: "; 
		cin >> radius; 
		cout << "Input Tinggi Tabung: ";
		cin >> tinggi;
		cout << endl;
		
		cout << "Volume Tabung Adalah: " << volume(radius, tinggi) << "cm3" << endl;
		
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

