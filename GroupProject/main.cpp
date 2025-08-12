#define _CRT_SECURE_NO_WARNINGS
#include "kelas.h"
#include <iostream>
using namespace std;

int main() {
    Kelass kelas;

    // Login system
    string username, password;
    kelas.clearScreen();
    cout << "=== Login Sistem ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username != "admin" || password != "admin123") {
        cout << "Login gagal!" << endl;
        return 0;
    }

    // Load existing data
    kelas.loadFromFile();

    // Main menu
    while (true) {
        kelas.clearScreen();
        kelas.headerUtama();
        kelas.menuUtama();
        cout << "Pilih menu: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            kelas.pesanTiket();
            break;
        case 2:
            return 0;
        case 3:
            kelas.readBookings();
            break;
        case 4:
            kelas.updateBooking();
            break;
        case 5:
            kelas.deleteBooking();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            kelas.enterToContinue();
        }
    }

    return 0;
}
