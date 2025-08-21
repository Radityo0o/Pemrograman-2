#include "Koperasi.h"
#include <fstream>
#include <iomanip>
#include <limits>

Mahasiswa::Mahasiswa(string n, string id) {
    nama = n;
    nim = id;
    penarikan = 0;
    for (int& t : tabungan) t = 0;
}

int Mahasiswa::totalTabungan() const {
    int total = 0;
    for (int i = 0; i < 6; ++i) total += tabungan[i];
    return total;
}

int Mahasiswa::saldoAkhir() const {
    return totalTabungan() - penarikan;
}

bool Koperasi::isMember(string nim) {
    for (const auto& mhs : dataMahasiswa) {
        if (mhs.nim == nim) return true;
    }
    return false;
}

void Koperasi::enterToContinue() const
{
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Koperasi::clearScreen() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Koperasi::tambahMahasiswa() {
    clearScreen();
    string nama, nim;

    cout << "=== Tambah Mahasiswa Baru ===\n";
    cin.ignore();
    cout << "Nama: ";
    getline(cin, nama);
    cout << "NIM: ";
    cin >> nim;

    if (isMember(nim)) {
        cout << "Mahasiswa sudah terdaftar!\n";
        enterToContinue();
        return;
    }

    dataMahasiswa.emplace_back(nama, nim);
    cout << "Mahasiswa berhasil ditambahkan!\n";
    enterToContinue();
}


void Koperasi::tampilkanMahasiswa() const {
    clearScreen();
    cout << "=== Daftar Mahasiswa Koperasi ===\n";
    cout << left << setw(20) << "Nama" << setw(15) << "NIM" << endl;
    cout << string(35, '-') << endl;

    for (const auto& mhs : dataMahasiswa) {
        cout << left << setw(20) << mhs.nama << setw(15) << mhs.nim << endl;
    }

    enterToContinue();
}

void Koperasi::ubahMahasiswa() {
    clearScreen();
    string nim;
    cout << "=== Ubah Data Mahasiswa ===\n";
    cout << "Masukkan NIM Mahasiswa: ";
    cin >> nim;

    for (auto& mhs : dataMahasiswa) {
        if (mhs.nim == nim) {
            cout << "Data ditemukan.\nNama Baru: ";
            cin.ignore();
            getline(cin, mhs.nama);
            cout << "Data berhasil diperbarui!\n";
            enterToContinue();
            return;
        }
    }

    cout << "Mahasiswa tidak ditemukan!\n";
    enterToContinue();
}

void Koperasi::inputTabungan() {
    clearScreen();
    string nim;
    cout << "=== Input Tabungan Mahasiswa ===\n";
    cout << "Masukkan NIM Mahasiswa: ";
    cin >> nim;

    for (auto& mhs : dataMahasiswa){
        if (mhs.nim == nim) {
            cout << "Masukkan tabungan per bulan (Januari - Juni):\n";
            for (int i = 0; i < 6; ++i) {
                cout << "Bulan ke-" << i + 1 << ": ";
                cin >> mhs.tabungan[i];
            }
            cout << "Tabungan berhasil diinput!\n";
            enterToContinue();
            return;
        }
    }

    cout << "Mahasiswa tidak ditemukan!\n";
    enterToContinue();
}


void Koperasi::tampilkanSaldo() {
    clearScreen();
    cout << "=== Total Saldo Mahasiswa ===\n";
    cout << left << setw(20) << "Nama" << setw(15) << "NIM" << setw(15) << "Saldo Akhir" << endl;
    cout << string(50, '-') << endl;

    for (const auto& mhs : dataMahasiswa) {
        cout << left << setw(20) << mhs.nama << setw(15) << mhs.nim << setw(15) << mhs.saldoAkhir() << endl;
    }

    enterToContinue();
}

void Koperasi::exportData() const {
    clearScreen();
    ofstream file("data_saldo_mahasiswa.txt");
    if (!file) {
        cout << "Gagal membuat file!\n";
        enterToContinue();
        return;
    }

    file << left << setw(20) << "Nama" << setw(15) << "NIM" << setw(15) << "Saldo Akhir" << endl;
    for (const auto& mhs : dataMahasiswa) {
        file << left << setw(20) << mhs.nama << setw(15) << mhs.nim << setw(15) << mhs.saldoAkhir() << endl;
    }

    file.close();
    cout << "Data berhasil diekspor ke 'data_saldo_mahasiswa.txt'\n";
    enterToContinue();
}

void Koperasi::hapusMahasiswa() {
    clearScreen();
    string nim;
    cout << "=== Hapus Mahasiswa ===\n";
    cout << "Masukkan NIM Mahasiswa: ";
    cin >> nim;

    for (auto it = dataMahasiswa.begin(); it != dataMahasiswa.end(); ++it) {
        if (it->nim == nim) {
            dataMahasiswa.erase(it);
            cout << "Mahasiswa berhasil dihapus!\n";
            enterToContinue();
            return;
        }
    }

    cout << "Mahasiswa tidak ditemukan!\n";
    enterToContinue();
}

Mahasiswa* Koperasi::loginMahasiswa(const string& nim, const string& pass) {
    for (auto& mhs : dataMahasiswa) {
        if (mhs.nim == nim && pass == nim) {
            return &mhs;
        }
    }
    return nullptr;
}

void Koperasi::menuAdmin(Koperasi& koperasi) {
    int pilih;
    do {
        koperasi.clearScreen();
        cout << "===== MENU ADMIN =====\n";
        cout << "1. Tambah Peserta Koperasi\n";
        cout << "2. Tampilkan Data Peserta\n";
        cout << "3. Ubah Data Peserta\n";
        cout << "4. Input Tabungan Peserta (Jan - Jun)\n";
        cout << "5. Tampilkan Total Saldo Peserta\n";
        cout << "6. Export Data ke File TXT\n";
        cout << "7. Hapus Peserta\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        koperasi.clearScreen();

        switch (pilih) {
        case 1:
            koperasi.tambahMahasiswa();
            break;
        case 2:
            koperasi.tampilkanMahasiswa();
            break;
        case 3:
            koperasi.ubahMahasiswa();
            break;
        case 4:
            koperasi.inputTabungan();
            break;
        case 5:
            koperasi.tampilkanSaldo();
            break;
        case 6:
            koperasi.exportData();
            break;
        case 7:
            koperasi.hapusMahasiswa();
            break;
        case 8:
            cout << "Keluar dari menu admin...\n";
            koperasi.enterToContinue();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            koperasi.enterToContinue();
            break;
        }
    } while (pilih != 8);
}


void Koperasi::menuMahasiswa(Mahasiswa* mhs, Koperasi& koperasi) {
    int pilih;
    do {
        koperasi.clearScreen();
        cout << "===== MENU MAHASISWA =====\n";
        cout << "Selamat datang, " << mhs->nama << " (" << mhs->nim << ")\n";
        cout << "1. Tampilkan Tabungan Jan-Jun\n";
        cout << "2. Tampilkan Saldo Total\n";
        cout << "3. Tarik Uang\n";
        cout << "4. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        koperasi.clearScreen();

        switch (pilih) {
        case 1:
            cout << "Tabungan Bulanan:\n";
            for (int i = 0; i < 6; ++i) {
                cout << "Bulan ke-" << (i + 1) << ": " << mhs->tabungan[i] << endl;
            }
            koperasi.enterToContinue();
            break;
        case 2:
            cout << "Saldo Total: " << mhs->saldoAkhir() << endl;
            koperasi.enterToContinue();
            break;
        case 3: {
            int tarik;
            cout << "Masukkan jumlah uang yang ingin ditarik: ";
            cin >> tarik;
            if (tarik <= mhs->saldoAkhir()) {
                mhs->penarikan += tarik;
                cout << "Penarikan berhasil!\n";
            }
            else {
                cout << "Saldo tidak mencukupi!\n";
            }
            koperasi.enterToContinue();
            break;
        }
        case 4:
            cout << "Keluar dari menu mahasiswa...\n";
            koperasi.enterToContinue();
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            koperasi.enterToContinue();
        }
    } while (pilih != 4);
}