#include "Koperasi.h"

int main() {
    Koperasi koperasi;
    int role;

    do {
        koperasi.clearScreen();
        cout << "\n===== Sistem Koperasi Mahasiswa =====\n";
        cout << "1. Login Admin\n";
        cout << "2. Login Mahasiswa\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> role;

        koperasi.clearScreen();

        if (role == 1) {
            string user, pass;
            cout << "===== Login Admin =====\n";
            cout << "Username: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;

            if (user == "admin" && pass == "123") {
                koperasi.menuAdmin(koperasi);
            }
            else {
                cout << "Login admin gagal!\n";
                koperasi.enterToContinue();
            }
        }
        else if (role == 2) {
            string nim, pass;
            cout << "===== Login Mahasiswa =====\n";
            cout << "NIM: ";
            cin >> nim;
            cout << "Password (NIM): ";
            cin >> pass;

            Mahasiswa* mhs = koperasi.loginMahasiswa(nim, pass);
            if (mhs) {
                koperasi.menuMahasiswa(mhs, koperasi);
            }
            else {
                cout << "Pastikan NIM terdaftar!\n";
                koperasi.enterToContinue();
            }
        }
        else if (role == 3) {
            cout << "Terima kasih!\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
            koperasi.enterToContinue();
        }

    } while (role != 3);

    return 0;
}
