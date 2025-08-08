#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

struct Mahasiswa
{
    string nama;
    string nim;
    string prodi;
    string bulan[6] = { "Januari", "Februari", "Maret", "April", "Mei", "Juni" };
    double tabungan[6] = { 0.0 };
    double saldoTotal = 0.0;

    Mahasiswa() {}
};

void pressEnterToContinue() {
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore();
    cin.get();
}

void clearScreen() {
    system(CLEAR_SCREEN);
}

string getProdiFromNIM(const string& nim) {
    if (nim.length() >= 5) {
        char prodiCode = nim[4];
        switch (prodiCode) {
        case '1': return "TMI";
        case '2': return "TMK";
        case '3': return "TPM";
        case '4': return "RTM";
        case '5': return "PM";
        case '6': return "TRMK";
        }
    }
    return "Invalid Input!";
}

void viewHeader() {
    cout << "=================================================" << endl;
    cout << "|\tKoperasi Mahasiswa Politeknik ATMI\t|" << endl;
    cout << "=================================================" << endl;
}

void viewMenu() {
    cout << "\n\t\t--- Menu Utama ---\n";
    cout << "1. Tambah Anggota" << "\t\t" << "5. Tampilkan Total Saldo" << endl;
    cout << "2. Tampilkan Data Anggota" << "\t" << "6. Export Data" << endl;
    cout << "3. Ubah Data Anggota" << "\t\t" << "7. Hapus Data Mahasiswa" << endl;
    cout << "4. Input Tabungan Anggota" << "\t" << "8. Exit" << endl;
}

void addMahasiswa(vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    cout << "--- Tambah Anggota Baru ---\n";
    string nama, nim;
    char lanjut;

    do {
        Mahasiswa mhs;
        cout << "Masukkan Nama: ";
        cin.ignore();
        getline(cin, nama);
        cout << "Masukkan NIM: ";
        cin >> nim;

        string prodi = getProdiFromNIM(nim);
        if (prodi == "Invalid Input!") {
            cout << "NIM tidak valid. Data tidak ditambahkan.\n";
        }
        else {
            mhs.nama = nama;
            mhs.nim = nim;
            mhs.prodi = prodi;
            mahasiswa.push_back(mhs);
            cout << "Anggota berhasil ditambahkan!\n";
        }
        cout << "Tambah anggota lagi? (Y/T): ";
        cin >> lanjut;
    } while (lanjut == 'Y' || lanjut == 'y');
}

void displayMahasiswa(const vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    if (mahasiswa.empty()) {
        cout << "\nBelum ada data anggota.\n";
        return;
    }

    cout << "--- Daftar Anggota Koperasi ---\n";
    for (size_t i = 0; i < mahasiswa.size(); ++i) {
        cout << "\nAnggota ke-" << i + 1 << endl;
        cout << "Nama\t\t: " << mahasiswa[i].nama << endl;
        cout << "NIM\t\t: " << mahasiswa[i].nim << endl;
        cout << "Prodi\t\t: " << mahasiswa[i].prodi << endl;
        cout << "Saldo Total\t: Rp " << fixed << setprecision(2) << mahasiswa[i].saldoTotal << endl;
        cout << "---------------------------------\n";
    }
}

void updateMahasiswa(vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    cout << "--- Ubah Data Anggota ---\n";
    if (mahasiswa.empty()) {
        cout << "\nBelum ada data anggota untuk diubah.\n";
        return;
    }

    string nim;
    cout << "\nMasukkan NIM anggota yang akan diubah: ";
    cin.ignore();
    getline(cin, nim);

    bool found = false;
    for (auto& mhs : mahasiswa) {
        if (mhs.nim == nim) {
            found = true;
            cout << "Data ditemukan. Masukkan data baru:\n";
            cout << "Nama baru: ";
            getline(cin, mhs.nama);
            cout << "NIM baru: ";
            getline(cin, mhs.nim);
            mhs.prodi = getProdiFromNIM(mhs.nim);
            cout << "Data berhasil diubah!\n";
            break;
        }
    }

    if (!found) {
        cout << "NIM tidak ditemukan.\n";
    }
}

void inputTabungan(vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    cout << "--- Input Tabungan Anggota ---\n";
    if (mahasiswa.empty()) {
        cout << "\nBelum ada data anggota.\n";
        return;
    }

    string nim;
    cout << "\nMasukkan NIM anggota untuk input tabungan: ";
    cin.ignore();
    getline(cin, nim);

    bool found = false;
    for (auto& mhs : mahasiswa) {
        if (mhs.nim == nim) {
            found = true;
            cout << "Input tabungan untuk 6 bulan (dalam Rp):\n";
            mhs.saldoTotal = 0.0;
            for (int i = 0; i < 6; ++i) {
                cout << "Tabungan bulan " << mhs.bulan[i] << ": ";
                cin >> mhs.tabungan[i];
                mhs.saldoTotal += mhs.tabungan[i];
            }
            cout << "Tabungan berhasil diinput!\n";
            break;
        }
    }
    if (!found) {
        cout << "NIM tidak ditemukan.\n";
    }
}

void displaySaldo(const vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    cout << "--- Saldo Total Anggota ---\n";
    if (mahasiswa.empty()) {
        cout << "\nBelum ada data anggota.\n";
        return;
    }

    for (const auto& mhs : mahasiswa) {
        cout << "Nama: " << mhs.nama << ", NIM: " << mhs.nim << ", Total Saldo: Rp " << fixed << setprecision(2) << mhs.saldoTotal << endl;
    }
}

void exportData(const vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    cout << "--- Export Data ke TXT ---\n";
    if (mahasiswa.empty()) {
        cout << "\nTidak ada data untuk diexport.\n";
        return;
    }

    ofstream file("data_koperasi_mahasiswa.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file!\n";
        return;
    }

    file << "NIM,Nama,Prodi,Januari,Februari,Maret,April,Mei,Juni,Total Saldo\n";
    for (const auto& mhs : mahasiswa) {
        file << mhs.nim << "," << mhs.nama << "," << mhs.prodi;
        for (int i = 0; i < 6; ++i) {
            file << "," << mhs.tabungan[i];
        }
        file << "," << mhs.saldoTotal << "\n";
    }

    file.close();
    cout << "\nData berhasil diexport ke file 'data_koperasi_mahasiswa.txt'\n";
}

void deleteMahasiswa(vector<Mahasiswa>& mahasiswa) {
    clearScreen();
    cout << "--- Hapus Data Mahasiswa ---\n";
    if (mahasiswa.empty()) {
        cout << "\nBelum ada data anggota untuk dihapus.\n";
        return;
    }

    string nim;
    cout << "\nMasukkan NIM anggota yang akan dihapus: ";
    cin.ignore();
    getline(cin, nim);

    auto it = remove_if(mahasiswa.begin(), mahasiswa.end(), [&](const Mahasiswa& mhs) {
        return mhs.nim == nim;
        });

    if (it != mahasiswa.end()) {
        mahasiswa.erase(it, mahasiswa.end());
        cout << "Data dengan NIM " << nim << " berhasil dihapus.\n";
    }
    else {
        cout << "NIM tidak ditemukan.\n";
    }
}

int main() {
    vector<Mahasiswa> mahasiswa;
    int opsi;

    while (true) {
        clearScreen();
        viewHeader();
        viewMenu();
        cout << "\n--> ";
        cin >> opsi;

        switch (opsi) {
        case 1:
            addMahasiswa(mahasiswa);
            break;
        case 2:
            displayMahasiswa(mahasiswa);
            break;
        case 3:
            updateMahasiswa(mahasiswa);
            break;
        case 4:
            inputTabungan(mahasiswa);
            break;
        case 5:
            displaySaldo(mahasiswa);
            break;
        case 6:
            exportData(mahasiswa);
            break;
        case 7:
            deleteMahasiswa(mahasiswa);
            break;
        case 8:
            cout << "\nProgram Selesai!\n";
            return 0;
        default:
            cout << "\nInvalid Input!\n";
        }
        pressEnterToContinue();
    }
    return 0;
}
