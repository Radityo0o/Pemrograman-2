#define _CRT_SECURE_NO_WARNINGS
#include "kelas.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;

string Kelass::getCurrentDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string date_time = to_string(1900 + ltm->tm_year) + "-" +
        (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(1 + ltm->tm_mon) + "-" +
        (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday) + " " +
        (ltm->tm_hour < 10 ? "0" : "") + to_string(ltm->tm_hour) + ":" +
        (ltm->tm_min < 10 ? "0" : "") + to_string(ltm->tm_min) + ":" +
        (ltm->tm_sec < 10 ? "0" : "") + to_string(ltm->tm_sec);
    return date_time;
}

void Kelass::clearScreen() {
    // Untuk Windows
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
    // Untuk Linux/Mac
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#endif
}

void Kelass::enterToContinue() {
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Kelass::headerUtama() {
    cout << "=== Pemesan Kamar Hotel ===" << endl;
    cout << "---------------------------" << endl;
}

void Kelass::menuUtama() {
    cout << "1. Pesan Kamar" << endl;
    cout << "2. Keluar" << endl;
    cout << "---------------------------" << endl;
}

void Kelass::pesanTiket() {
    clearScreen();
    //Bagian Input Data
    string namaPemesan, kodePemesan, bookingDate;
    int jumlahMalam;

    cout << "\n--- Input Data Pemesanan ---" << endl;
    cin.ignore();
    cout << "Nama Lengkap Pemesan\t\t: ";
    getline(cin, namaPemesan);
    cout << "Kode Pemesan\t\t\t: ";
    getline(cin, kodePemesan);

    // Input tanggal booking dengan validasi
    bool validDate = false;
    do {
        cout << "Tanggal Booking (YYYY-MM-DD)\t: ";
        getline(cin, bookingDate);
        validDate = isValidFutureDate(bookingDate);
        if (!validDate) {
            cout << "! Tanggal harus format YYYY-MM-DD dan belum lewat!\n";
            cout << "Tanggal hari ini: " << getCurrentDateTime().substr(0, 10) << endl;
        }
    } while (!validDate);

    cout << "Jumlah Malam yang Dipesan\t: ";
    cin >> jumlahMalam;

    //Bagian Pemilihan Jenis Kamar
    clearScreen();
    int jenisKamar;
    double hargaKamar = 0.0;
    string namaKamar;

    cout << "\n--- Pilih Jenis Kamar ---" << endl;
    cout << "1. Standar (Rp500.000/malam)" << endl;
    cout << "2. Superior (Rp800.000/malam)" << endl;
    cout << "3. Suite (Rp1.200.000/malam)" << endl;
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

    //Ringkasan Pesanan
    clearScreen();
    double totalBayar = hargaKamar * jumlahMalam;

    cout << "\n--- Ringkasan Pesanan ---" << endl;
    cout << getCurrentDateTime() << endl;
    cout << "Nama\t\t: " << namaPemesan << endl;
    cout << "Kode Pemesan\t: " << kodePemesan << endl;
    cout << "Jenis Kamar\t: " << namaKamar << endl;
    cout << "Harga per Malam\t: Rp" << fixed << setprecision(0) << hargaKamar << endl;
    cout << "Untuk Tanggal\t: " << bookingDate << endl;
    cout << "Durasi\t\t: " << jumlahMalam << endl;
    cout << "------------------------------" << endl;
    cout << "Total Pembayaran: Rp" << fixed << setprecision(0) << totalBayar << endl;

    //Bagian Cetak 
    char opsiCetak;
    cout << "Cetak Kode Booking? (Y/N): ";
    cin >> opsiCetak;
    cin.ignore();


    if (opsiCetak == 'Y' || opsiCetak == 'y') {
        string currentDateTime = getCurrentDateTime();
        ofstream notaFile("nota_hotel.txt");
        if (notaFile.is_open()) {
            notaFile << "========== NOTA PEMESANAN HOTEL ==========" << endl;
            notaFile << "Tanggal & Waktu: " << currentDateTime << endl;
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
        return;
    }
}

//Validasi Tanggal Booking
bool Kelass::isValidFutureDate(const string& date)
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    int year, month, day;
    char dash1, dash2;
    istringstream iss(date);
    iss >> year >> dash1 >> month >> dash2 >> day;
    if (dash1 != '-' || dash2 != '-' || iss.fail())
        return false;
    // Validasi dasar bulan dan hari
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    // Validasi khusus bulan
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2) {
        bool leapYear = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
        if (day > (leapYear ? 29 : 28))
            return false;
    }
    // Validasi tanggal harus di masa depan
    time_t now = time(0);
    tm* ltm = localtime(&now);

    if (year < 1900 + ltm->tm_year) return false;
    if (year == 1900 + ltm->tm_year && month < 1 + ltm->tm_mon) return false;
    if (year == 1900 + ltm->tm_year && month == 1 + ltm->tm_mon && day <= ltm->tm_mday) return false;
    return true;
}
