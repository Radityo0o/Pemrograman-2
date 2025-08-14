#define _CRT_SECURE_NO_WARNINGS
#include "menupesan.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main() {
    Kelass kelas;
    string username, password;
    char ch;
    bool loginBerhasil = false;

    // Login system
    while (!loginBerhasil) {
        kelas.clearScreen();
        cout << "|=======================================|\n";
        cout << "|                                       |\n";
        cout << "|      Booking Hotel? Disini Aja        |\n";
        cout << "|                                       |\n";
        cout << "|=======================================|\n";
        cout << endl;
        cout << "=========      Login Sistem     =========" << endl;
        cout << endl;
        cout << "Silahkan Masukkan Username dan Password\n";
        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        password = "";

        while (true) {
            ch = _getch(); // Ambil karakter tanpa menampilkannya

            if (ch == '\r') { // Enter ditekan
                break; 
            }
            else if (ch == '\b') { // Backspace ditekan
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b"; // Hapus bintang dari layar
                }
            }
            else {
                password.push_back(ch);
                cout << '*'; // Tampilkan bintang
            }
        }

        if (username == "user" && password == "user123") {
            loginBerhasil = true;
        }
        else {
            cout << "\nLogin gagal! Silakan coba lagi.\n";
            kelas.enterToContinue(); // Tunggu input sebelum ulang
        }
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
        case 6:
            kelas.displayRoomStock();  // Menu baru: Lihat stok kamar
            break;
        case 7:
            kelas.manageStock();       // Menu baru: Kelola stok (admin)
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            kelas.enterToContinue();
        }
    }

    return 0;
}
