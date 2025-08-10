#include "kelas.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

string getCurrentDateTime(){
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
        break;
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

    //Bagian Cetak 
    char opsiCetak;
    cout << "Cetak Kode Booking? (Y/N): "; 
    cin >> opsiCetak;

    if (opsiCetak == 'Y' || opsiCetak == 'y') {
      ofstream notaFile("nota_hotel.txt");
        if (notaFile.is_open()) {
          notaFile << "========== NOTA PEMESANAN HOTEL ==========" << endl;
          //notaFile << "Tanggal & Waktu: " << currentDateTime << endl;
          notaFile << "------------------------------------------" << endl;
          notaFile << "Nama Pemesan\t: " << namaPemesan << endl;
          notaFile << "Kode Pemesan\t: " << kodePemesan << endl;
          notaFile << "Jenis Kamar\t: " << namaKamar << endl;
          notaFile << "Jumlah Malam\t: " << jumlahMalam << endl;
          notaFile << fixed << setprecision(0);
          notaFile << "Harga/malam\t: Rp" << hargaKamar << endl;
          notaFile << "------------------------------------------" << endl;
          notaFile << "Total Pembayaran: Rp" << totalBayar << endl;
          notaFile << "==========================================" << endl;
          notaFile.close();
          cout << "Nota berhasil dicetak ke file nota_hotel.txt" << endl;
        }
        else {
          cout << "Gagal membuka file nota_hotel.txt" << endl;
         } 
    } 
    else if (opsiCetak == 'N' || opsiCetak == 'n') {
      enterToContinue();
    }
}
