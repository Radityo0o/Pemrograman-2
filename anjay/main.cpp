#include "project.h"
#include <iostream>
#include <conio.h>
#pragma warning(disable : 4996)
using namespace std;

int main() {
    Kelass kelas;
    string username, password;
    char ch;
    bool loginBerhasil = false;
    bool isAdmin = false;

    while (!loginBerhasil) {
        kelas.clearScreen();
        cout << "|=======================================|\n";
        cout << "|             Agus Aerospace            |\n";
        cout << "|=======================================|\n";
        cout << "\n=========     Login System     =========\n";
        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        password = "";
        while (true) {
            ch = _getch();
            if (ch == '\r') break;
            else if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password.push_back(ch);
                cout << '*';
            }
        }

        if ((username == "ADMIN" && password == "123456") || (username == "USER" && password == "678910")) {
            loginBerhasil = true;
            isAdmin = (username == "ADMIN");
        }
        else {
            cout << "\nLogin gagal! Silakan coba lagi.\n";
            kelas.enterToContinue();
        }
    }

    kelas.loadData();

    while (true) {
        kelas.clearScreen();
        kelas.headerUtama();
        if (isAdmin) {
            kelas.menuAdmin();
        }
        else {
            kelas.menuUser();
        }
        cout << "Pilih menu: ";
        int choice;
        cin >> choice;

        if (isAdmin) {
            switch (choice) {
            case 1: kelas.inputPenerbangan(); break;
            case 2: kelas.updatePenerbangan(); break;
            case 3: kelas.deletePenerbangan(); break;
            case 4: return 0;
            default: cout << "Pilihan tidak valid!\n"; kelas.enterToContinue();
            }
        }
        else {
            switch (choice) {
            case 1: kelas.tampilkanPenerbangan(); break;
            case 2: kelas.pesanTiket(); break;
            case 3: return 0;
            default: cout << "Pilihan tidak valid!\n"; kelas.enterToContinue();
            }
        }
    }

    return 0;
}
