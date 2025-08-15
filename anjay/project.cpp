#include "project.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <random>
#pragma warning(disable:4996)

using namespace std;

void Kelass::clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void Kelass::enterToContinue() {
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Kelass::headerUtama() {
    cout << "|=========================================|\n";
    cout << "|             Agus Aerospace              |\n";
    cout << "|=========================================|\n\n";
}

void Kelass::menuAdmin() {
    cout << "1. Input Penerbangan Baru\n";
    cout << "2. Update Penerbangan\n";
    cout << "3. Hapus Penerbangan\n";
    cout << "4. Keluar\n";
}

void Kelass::menuUser() {
    cout << "1. Lihat Penerbangan\n";
    cout << "2. Pesan Tiket\n";
    cout << "3. Keluar\n";
}

void Kelass::inputPenerbangan() {
    clearScreen();
    Penerbangan p;
    cout << "--- Input Data Penerbangan ---\n";
    cin.ignore();
    cout << "Tujuan: "; getline(cin, p.tujuan);
    cout << "Tanggal (YYYY-MM-DD): "; getline(cin, p.tanggal);
    cout << "Waktu (HH:MM): "; getline(cin, p.waktu);
    cout << "Harga Tiket: "; cin >> p.harga;
    cout << "Jumlah Kursi: "; cin >> p.jumlahKursi;

    p.kursiTerisi = vector<bool>(p.jumlahKursi, false);
    daftarPenerbangan.push_back(p);
    saveData();

    cout << "Penerbangan berhasil ditambahkan!\n";
    enterToContinue();
}

void Kelass::tampilkanPenerbangan() {
    clearScreen();
    cout << "--- Daftar Penerbangan ---\n";
    if (daftarPenerbangan.empty()) {
        cout << "Belum ada data penerbangan\n";
    }
    else {
        for (int i = 0; i < daftarPenerbangan.size(); i++) {
            Penerbangan& p = daftarPenerbangan[i];
            cout << i + 1 << ". " << p.tujuan << " | " << p.tanggal << " | " << p.waktu
                << " | Harga: Rp" << fixed << setprecision(0) << p.harga
                << " | Kursi Tersedia: " << count(p.kursiTerisi.begin(), p.kursiTerisi.end(), false) << "/" << p.jumlahKursi << "\n";
        }
    }
    enterToContinue();
}

void Kelass::updatePenerbangan() {
    tampilkanPenerbangan();
    int idx;
    cout << "\nPilih nomor penerbangan yang ingin diupdate: ";
    cin >> idx;
    idx--;

    if (idx < 0 || idx >= daftarPenerbangan.size()) {
        cout << "Invalid input!\n";
        enterToContinue();
        return;
    }

    Penerbangan& p = daftarPenerbangan[idx];
    cin.ignore();
    cout << "Tujuan baru: "; getline(cin, p.tujuan);
    cout << "Tanggal baru: "; getline(cin, p.tanggal);
    cout << "Waktu baru: "; getline(cin, p.waktu);
    cout << "Harga baru: "; cin >> p.harga;
    cout << "Jumlah Kursi Baru: "; cin >> p.jumlahKursi;

    p.kursiTerisi = vector<bool>(p.jumlahKursi, false);
    saveData();
    cout << "Data berhasil diupdate\n";
    enterToContinue();
}

void Kelass::deletePenerbangan() {
    tampilkanPenerbangan();
    int idx;
    cout << "\nPilih nomor penerbangan yang ingin dihapus: ";
    cin >> idx;
    idx--;

    if (idx < 0 || idx >= daftarPenerbangan.size()) {
        cout << "Invalid Input!\n";
    }
    else {
        daftarPenerbangan.erase(daftarPenerbangan.begin() + idx);
        saveData();
        cout << "Data berhasil dihapus\n";
    }
    enterToContinue();
}

void Kelass::pesanTiket() {
    tampilkanPenerbangan();
    int idx;
    cout << "\nPilih nomor penerbangan: ";
    cin >> idx;
    idx--;

    if (idx < 0 || idx >= daftarPenerbangan.size()) {
        cout << "Invalid input!\n";
        enterToContinue();
        return;
    }

    Penerbangan& p = daftarPenerbangan[idx];

    cout << "Masukkan Nama Anda: ";
    cin.ignore();
    string namaUser;
    getline(cin, namaUser);

    vector<int> kursiDipilih;
    double total = 0;

    while (true) {
        int nomorKursi;
        cout << "\nPilih nomor kursi (1 - " << p.jumlahKursi << "): ";
        cin >> nomorKursi;
        nomorKursi--;

        if (nomorKursi < 0 || nomorKursi >= p.jumlahKursi || p.kursiTerisi[nomorKursi]) {
            cout << "Kursi tidak tersedia!\n";
        }
        else {
            p.kursiTerisi[nomorKursi] = true;
            kursiDipilih.push_back(nomorKursi);
            total += p.harga;

            Pembelian pb;
            pb.nama = namaUser;
            pb.idPenerbangan = idx;
            pb.nomorKursi = nomorKursi;
            pb.totalBayar = p.harga;
            daftarPembelian.push_back(pb);

            cout << "Kursi " << nomorKursi + 1 << " berhasil dipesan.\n";
        }

        char lanjut;
        cout << "Ingin memesan kursi lagi? (y/n): ";
        cin >> lanjut;
        if (tolower(lanjut) != 'y') break;
    }

    double diskon = 0;
    if (total > 150000) {
        diskon = total * 0.1;
        total -= diskon;
    }

    cout << fixed << setprecision(0);
    cout << "\n===== RINCIAN PEMBAYARAN =====\n";
    cout << "Jumlah Tiket\t: " << kursiDipilih.size() << endl;
    cout << "Subtotal\t: Rp" << total + diskon << endl;
    if (diskon > 0) cout << "Diskon (10%)\t: -Rp" << diskon << endl;
    cout << "Total Bayar\t: Rp" << total << endl;
    cout << "==============================" << endl;

    double jumlahBayar;
    while (true) {
        cout << "Masukkan jumlah uang Anda: Rp";
        cin >> jumlahBayar;

        if (jumlahBayar < total) {
            cout << "Uang anda tidak cukup!\n";
        }
        else {
            break;
        }
    }

    double kembalian = jumlahBayar - total;

    saveData();

    cout << "\nTiket berhasil dipesan!\n";
    cout << "------------------------------\n";
    cout << "Nama\t\t: " << namaUser << endl;
    cout << "Tujuan\t\t: " << p.tujuan << endl;
    cout << "Tanggal\t\t: " << p.tanggal << endl;
    cout << "Waktu\t\t: " << p.waktu << endl;
    cout << "Kursi\t\t: ";
    for (int k : kursiDipilih) cout << (k + 1) << " ";
    cout << "\nTotal Bayar\t: Rp" << total << endl;
    cout << "Dibayar\t\t: Rp" << jumlahBayar << endl;
    cout << "Kembalian\t: Rp" << kembalian << endl;

    cetakNota(namaUser, total, jumlahBayar, kembalian);
    enterToContinue();
}



void Kelass::saveData() {
    ofstream file("penerbangan.txt");
    for (const auto& p : daftarPenerbangan) {
        file << p.tujuan << "," << p.tanggal << "," << p.waktu << "," << p.harga << "," << p.jumlahKursi << endl;
        for (bool status : p.kursiTerisi) {
            file << status << " ";  
        }
        file << endl;
    }
    file.close();

    ofstream filePembelian("pembelian.txt");
    for (const auto& b : daftarPembelian) {
        filePembelian << b.nama << "," << b.idPenerbangan << "," << b.nomorKursi << "," << b.totalBayar << endl;
    }
    filePembelian.close();
}

void Kelass::loadData() {
    daftarPenerbangan.clear();
    daftarPembelian.clear();

    ifstream file("penerbangan.txt");
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Penerbangan p;
        char koma;
        getline(iss, p.tujuan, ',');
        getline(iss, p.tanggal, ',');
        getline(iss, p.waktu, ',');
        iss >> p.harga >> koma >> p.jumlahKursi;

        p.kursiTerisi.resize(p.jumlahKursi);

        if (getline(file, line)) {
            istringstream kursiStream(line);
            for (int i = 0; i < p.jumlahKursi; i++) {
                int status;
                kursiStream >> status;
                p.kursiTerisi[i] = (status != 0);
            }
        }

        daftarPenerbangan.push_back(p);
    }
    file.close();

    ifstream filePembelian("pembelian.txt");
    while (getline(filePembelian, line)) {
        istringstream iss(line);
        Pembelian b;
        char koma;
        getline(iss, b.nama, ',');
        iss >> b.idPenerbangan >> koma >> b.nomorKursi >> koma >> b.totalBayar;
        daftarPembelian.push_back(b);
    }
    filePembelian.close();
}

void Kelass::cetakNota(const string& nama, double total, double dibayar, double kembalian) {
    string filename = "nota/" + nama;
    replace(filename.begin(), filename.end(), ' ', '_');
    filename += ".txt";

    ofstream notaFile(filename);
    if (!notaFile.is_open()) {
        cout << "Gagal membuat nota\n";
        return;
    }

    time_t now = time(0);
    tm* ltm = localtime(&now);
    char tanggalCetak[30];
    strftime(tanggalCetak, sizeof(tanggalCetak), "%Y-%m-%d %H:%M:%S", ltm);

    notaFile << "===== NOTA PEMBAYARAN TIKET =====\n";
    notaFile << "Nama         : " << nama << endl;
    notaFile << "Total Harga  : Rp" << fixed << setprecision(0) << total << endl;
    notaFile << "Dibayar      : Rp" << dibayar << endl;
    notaFile << "Kembalian    : Rp" << kembalian << endl;
    notaFile << "Tanggal Cetak: " << tanggalCetak << endl;
    notaFile << "=================================\n";

    notaFile.close();

    cout << "\nNota berhasil dicetak ke file: " << filename << endl;
}
