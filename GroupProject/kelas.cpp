#include "kelas.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Kelass::clearScreen(){
    // Untuk Windows
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    // Untuk Linux/Mac
    #elif defined(__linux__) || defined(__APPLE__)
        system("clear");
    #endif
}

void Kelass::enterToContinue(){
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore();
    cin.get();
}

void Kelass::headerUtama(){
    cout << "Pemesan Tiket Hotel" << endl;
    cout << "-------------------" << endl;
}

void Kelass::menuUtama(){
    cout << "1. Pesan Tiket" << endl;
    cout << "2. Keluar" << endl;
}

void Kelass::pesanTiket(){
    clearScreen();
    //Bagian Input Data
    string namaPemesan, kodePemesan;
    int jumlahMalam;

    cout << "\n--- Input Data Pemesanan ---" << endl;
    cin.ignore();
    cout << "Nama Lengkap Pemesan\t\t: ";
    getline(cin, namaPemesan);
    cout << "Kode Pemesan\t\t\t: ";
    getline(cin, kodePemesan);
    cout << "Jumlah Malam yang Dipesan\t: ";
    cin >> jumlahMalam;

    //Bagian Pemilihan Jenis Kamar
    clearScreen();
    int jenisKamar;
    double hargaKamar = 0.0;
    string namaKamar;

    cout << "\n--- Pilih Jenis Kamar ---" << endl;
    cout << "1. Standar" << endl;
    cout << "2. Superior" << endl;
    cout << "3. Suite" << endl;
    cout << "Pilihan Anda: ";
    cin >> jenisKamar;

    //Penentuan Harga 
    switch (jenisKamar)
    {
    case 1:
        namaKamar = "Standar";
        hargaKamar = 500000;
        break;
    case 2:
        namaKamar = "Superior";
        hargaKamar = 800000;
        break;
    case 3:
        namaKamar = "Suite";
        hargaKamar = 1200000;
    default:
        namaKamar = "Invalid Input!";
        hargaKamar = 0;
        break;
    }

    //Perhitungan Biaya
    clearScreen();
    double totalBayar = hargaKamar * jumlahMalam;

    cout << "\n--- Ringkasan Pesanan ---" << endl;
    cout << "Nama\t\t: " << namaPemesan << endl;
    cout << "Kode Pemesan\t: " << kodePemesan << endl;
    cout << "Jenis Kamar\t: " << namaKamar << endl;
    cout << "Harga per Malam\t: Rp" << fixed << setprecision(0) << hargaKamar << endl;
    cout << "Jumlah Malam\t: " << jumlahMalam << endl;
    cout << "------------------------------" << endl;
    cout << "Total Pembayaran: Rp" << fixed << setprecision(0) << totalBayar << endl; 
}
