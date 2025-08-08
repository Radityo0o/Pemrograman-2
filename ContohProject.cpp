#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

// Fungsi untuk mendapatkan tanggal dan waktu saat ini
string getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    string date_time = to_string(1900 + ltm->tm_year) + "-" +
        to_string(1 + ltm->tm_mon) + "-" +
        to_string(ltm->tm_mday) + " " +
        to_string(ltm->tm_hour) + ":" +
        to_string(ltm->tm_min) + ":" +
        to_string(ltm->tm_sec);

    return date_time;
}

int main() {
    // --- Bagian Login ---
    string password;
    cout << "Selamat Datang di Aplikasi Pemesanan Tiket Kereta Api" << endl;
    while (true) {
        cout << "Masukkan password: ";
        cin >> password;
        if (password == "admin123") {
            cout << "Login berhasil!" << endl;
            break;
        }
        else {
            cout << "Password salah. Coba lagi." << endl;
        }
    }

    // --- Bagian Input Data ---
    string namaPemesan, kodePemesan;
    int jumlahKursi;

    cout << "\n--- Input Data Pemesanan ---" << endl;
    cin.ignore(); // Membersihkan buffer input
    cout << "Nama Lengkap Pemesan: ";
    getline(cin, namaPemesan);
    cout << "Kode Pemesan: ";
    getline(cin, kodePemesan);
    cout << "Jumlah Kursi yang Dipesan: ";
    cin >> jumlahKursi;

    // --- Bagian Pemilihan Kereta dan Tujuan ---
    int jenisKereta, tujuan;
    double hargaTiket = 0.0;
    string namaKereta, namaTujuan;

    cout << "\n--- Pilih Jenis Kereta ---" << endl;
    cout << "1. Ekonomi" << endl;
    cout << "2. Bisnis" << endl;
    cout << "3. Eksekutif" << endl;
    cout << "Pilihan Anda: ";
    cin >> jenisKereta;

    cout << "\n--- Pilih Tujuan ---" << endl;
    cout << "1. Jakarta" << endl;
    cout << "2. Surabaya" << endl;
    cout << "3. Bandung" << endl;
    cout << "Pilihan Anda: ";
    cin >> tujuan;

    // Menentukan harga berdasarkan pilihan
    if (jenisKereta == 1) {
        namaKereta = "Ekonomi";
        if (tujuan == 1) {
            namaTujuan = "Jakarta";
            hargaTiket = 150000;
        }
        else if (tujuan == 2) {
            namaTujuan = "Surabaya";
            hargaTiket = 200000;
        }
        else if (tujuan == 3) {
            namaTujuan = "Bandung";
            hargaTiket = 120000;
        }
    }
    else if (jenisKereta == 2) {
        namaKereta = "Bisnis";
        if (tujuan == 1) {
            namaTujuan = "Jakarta";
            hargaTiket = 250000;
        }
        else if (tujuan == 2) {
            namaTujuan = "Surabaya";
            hargaTiket = 300000;
        }
        else if (tujuan == 3) {
            namaTujuan = "Bandung";
            hargaTiket = 220000;
        }
    }
    else if (jenisKereta == 3) {
        namaKereta = "Eksekutif";
        if (tujuan == 1) {
            namaTujuan = "Jakarta";
            hargaTiket = 400000;
        }
        else if (tujuan == 2) {
            namaTujuan = "Surabaya";
            hargaTiket = 450000;
        }
        else if (tujuan == 3) {
            namaTujuan = "Bandung";
            hargaTiket = 350000;
        }
    }

    // --- Bagian Perhitungan dan Output ---
    double totalBayar = hargaTiket * jumlahKursi;

    cout << "\n--- Ringkasan Pemesanan ---" << endl;
    cout << "Nama Pemesan: " << namaPemesan << endl;
    cout << "Kode Pemesan: " << kodePemesan << endl;
    cout << "Jenis Kereta: " << namaKereta << endl;
    cout << "Tujuan: " << namaTujuan << endl;
    cout << "Harga Tiket per Kursi: Rp" << hargaTiket << endl;
    cout << "Jumlah Kursi: " << jumlahKursi << endl;
    cout << "---------------------------------" << endl;
    cout << "Total Pembayaran: Rp" << totalBayar << endl;

    // --- Bagian Cetak File ---
    string currentDateTime = getCurrentDateTime();
    cout << "\nSedang mencetak nota dan stock..." << endl;

    // Cetak Nota
    ofstream notaFile("nota.txt");
    if (notaFile.is_open()) {
        notaFile << "========== NOTA PEMESANAN ==========" << endl;
        notaFile << "Tanggal & Waktu: " << currentDateTime << endl;
        notaFile << "------------------------------------" << endl;
        notaFile << "Nama Pemesan: " << namaPemesan << endl;
        notaFile << "Kode Pemesan: " << kodePemesan << endl;
        notaFile << "Jenis Kereta: " << namaKereta << endl;
        notaFile << "Tujuan: " << namaTujuan << endl;
        notaFile << "Jumlah Kursi: " << jumlahKursi << endl;
        notaFile << "Harga Tiket: Rp" << hargaTiket << endl;
        notaFile << "------------------------------------" << endl;
        notaFile << "Total Pembayaran: Rp" << totalBayar << endl;
        notaFile << "====================================" << endl;
        notaFile.close();
        cout << "Nota berhasil dicetak ke file nota.txt" << endl;
    }
    else {
        cout << "Gagal membuka file nota.txt" << endl;
    }

    // Cetak Stock
    ofstream stockFile("stock.txt");
    if (stockFile.is_open()) {
        stockFile << "========== STOCK TIKET ==========" << endl;
        stockFile << "Tanggal & Waktu: " << currentDateTime << endl;
        stockFile << "---------------------------------" << endl;
        stockFile << "Simulasi stock yang tersedia:" << endl;
        stockFile << "- Tiket Ekonomi: 100 kursi" << endl;
        stockFile << "- Tiket Bisnis: 50 kursi" << endl;
        stockFile << "- Tiket Eksekutif: 30 kursi" << endl;
        stockFile << "=================================" << endl;
        stockFile.close();
        cout << "Stock berhasil dicetak ke file stock.txt" << endl;
    }
    else {
        cout << "Gagal membuka file stock.txt" << endl;
    }

    return 0;
}
