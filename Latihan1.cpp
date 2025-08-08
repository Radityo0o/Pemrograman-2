#include <iostream>
#include <cmath>

using namespace std;

const double g = 10.0;
const double pi = 3.14;

// Fungsi menghitung HMax dan XMax
double hmax(double v0, double a);
double xmax(double v0, double a);

// Fungsi hitung HMax
double hmax(double v0, double a) {
    double radian = a * pi / 180;
    return (v0 * v0 * sin(radian) * sin(radian) / (2 * g));
}

// Fungsi hitung XMax
double xmax(double v0, double a) {
    double radian = a * pi / 180;
    return (v0 * v0 * sin(2 * radian)) / g;
}

int main() {
    double v0, a;
    char yt, menu;

awal:
    cout << "======================================" << endl;
    cout << "=== PROGRAM MENGHITUNG XMax & HMax ===" << endl;
    cout << "======================================" << endl;
    cout << "\nMENU :\n";
    cout << "A. Menghitung HMax\nB. Menghitung XMax\nC. Keluar\n";
    cout << "\nMasukkan Pilihan: ";
    cin >> menu;

    if (menu == 'A' || menu == 'a') {
        cout << "Input Kecepatan Awal (m/s): ";
        cin >> v0;
        cout << "Input Sudut Elevasi (derajat): ";
        cin >> a;
        cout << "\nKetinggian maksimum peluru adalah : " << hmax(v0, a) << " m" << endl;
    }
    else if (menu == 'B' || menu == 'b') {
        cout << "Input Kecepatan Awal (m/s): ";
        cin >> v0;
        cout << "Input Sudut Elevasi (derajat): ";
        cin >> a;
        cout << "\nJarak maksimum peluru adalah : " << xmax(v0, a) << " m" << endl;
    }
    else if (menu == 'C' || menu == 'c') {
        goto akhir;
    }

    cout << "Masukkan Data Lagi (Y/T)? ";
    cin >> yt;
    cout << endl;
    if (yt == 'Y' || yt == 'y') {
        goto awal;
    }
    else if (yt == 'T' || yt == 't') {
        goto akhir;
    }

akhir:
    return 0;
}
