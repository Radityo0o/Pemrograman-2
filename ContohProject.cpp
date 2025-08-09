#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

using namespace std;

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
    string password;
    cout << "Selamat Datang di Aplikasi Pemesanan Hotel" << endl;
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
    int jumlahMalam;

    cout << "\n--- Input Data Pemesanan ---" << endl;
    cin.ignore(); // Membersihkan buffer input
    cout << "Nama Lengkap Pemesan: ";
    getline(cin, namaPemesan);
    cout << "Kode Pemesan: ";
    getline(cin, kodePemesan);
    cout << "Jumlah Malam yang Dipesan: ";
    cin >> jumlahMalam;

    // --- Bagian Pemilihan Jenis Kamar ---
    int jenisKamar;
    double hargaKamar = 0.0;
    string namaKamar;

    cout << "\n--- Pilih Jenis Kamar ---" << endl;
    cout << "1. Standar" << endl;
    cout << "2. Superior" << endl;
    cout << "3. Suite" << endl;
    cout << "Pilihan Anda: ";
    cin >> jenisKamar;

    // Menentukan harga berdasarkan pilihan
    if (jenisKamar == 1) {
        namaKamar = "Standar";
        hargaKamar = 500000;
    }
    else if (jenisKamar == 2) {
        namaKamar = "Superior";
        hargaKamar = 800000;
    }
    else if (jenisKamar == 3) {
        namaKamar = "Suite";
        hargaKamar = 1200000;
    }

    // --- Bagian Perhitungan dan Output ---
    double totalBayar = hargaKamar * jumlahMalam;

    cout << "\n--- Ringkasan Pemesanan ---" << endl;
    cout << "Nama Pemesan: " << namaPemesan << endl;
    cout << "Kode Pemesan: " << kodePemesan << endl;
    cout << "Jenis Kamar: " << namaKamar << endl;
    cout << "Harga per Malam: Rp" << fixed << setprecision(0) <<hargaKamar << endl;
    cout << "Jumlah Malam: " << jumlahMalam << endl;
    cout << "---------------------------------" << endl;
    cout << "Total Pembayaran: Rp" << fixed << setprecision(0) <<totalBayar << endl;

    // --- Bagian Cetak File ---
    string currentDateTime = getCurrentDateTime();
    cout << "\nSedang mencetak nota dan stock..." << endl;

    // Cetak Nota
    ofstream notaFile("nota_hotel.txt");
    if (notaFile.is_open()) {
        notaFile << "========== NOTA PEMESANAN HOTEL ==========" << endl;
        notaFile << "Tanggal & Waktu: " << currentDateTime << endl;
        notaFile << "------------------------------------------" << endl;
        notaFile << "Nama Pemesan: " << namaPemesan << endl;
        notaFile << "Kode Pemesan: " << kodePemesan << endl;
        notaFile << "Jenis Kamar: " << namaKamar << endl;
        notaFile << "Jumlah Malam: " << jumlahMalam << endl;
        notaFile << "Harga Kamar per Malam: Rp" << hargaKamar << endl;
        notaFile << "------------------------------------------" << endl;
        notaFile << "Total Pembayaran: Rp" << totalBayar << endl;
        notaFile << "==========================================" << endl;
        notaFile.close();
        cout << "Nota berhasil dicetak ke file nota_hotel.txt" << endl;
    }
    else {
        cout << "Gagal membuka file nota_hotel.txt" << endl;
    }

    // Cetak Stock
    ofstream stockFile("stock_hotel.txt");
    if (stockFile.is_open()) {
        stockFile << "========== STOCK KAMAR ==========" << endl;
        stockFile << "Tanggal & Waktu: " << currentDateTime << endl;
        stockFile << "---------------------------------" << endl;
        stockFile << "Simulasi stock yang tersedia:" << endl;
        stockFile << "- Kamar Standar: 20 kamar" << endl;
        stockFile << "- Kamar Superior: 10 kamar" << endl;
        stockFile << "- Kamar Suite: 5 kamar" << endl;
        stockFile << "=================================" << endl;
        stockFile.close();
        cout << "Stock berhasil dicetak ke file stock_hotel.txt" << endl;
    }
    else {
        cout << "Gagal membuka file stock_hotel.txt" << endl;
    }

    return 0;
}
