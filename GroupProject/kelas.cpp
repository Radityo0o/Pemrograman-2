#define _CRT_SECURE_NO_WARNINGS
#include "kelas.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>

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
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
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
    cout << "3. Lihat Pemesanan" << endl;
    cout << "4. Update Pemesanan" << endl;
    cout << "5. Hapus Pemesanan" << endl;
    cout << "---------------------------" << endl;
}

void Kelass::saveToFile() {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& booking : bookings) {
            file << booking.namaPemesan << endl;
            file << booking.kodePemesan << endl;
            file << booking.bookingDate << endl;
            file << booking.jumlahMalam << endl;
            file << booking.namaKamar << endl;
            file << booking.hargaKamar << endl;
            file << booking.totalBayar << endl;
        }
        file.close();
    }
}

void Kelass::loadFromFile() {
    ifstream file(filename);
    if (file.is_open()) {
        bookings.clear();
        Booking booking;
        while (getline(file, booking.namaPemesan) &&
            getline(file, booking.kodePemesan) &&
            getline(file, booking.bookingDate) &&
            file >> booking.jumlahMalam &&
            file.ignore() &&
            getline(file, booking.namaKamar) &&
            file >> booking.hargaKamar &&
            file >> booking.totalBayar) {
            file.ignore();
            bookings.push_back(booking);
        }
        file.close();
    }
}

void Kelass::printNota(const Booking& booking) {
    string notaFilename = "nota_" + booking.kodePemesan + ".txt";
    ofstream notaFile(notaFilename);
    if (notaFile.is_open()) {
        notaFile << "========== NOTA PEMESANAN HOTEL ==========" << endl;
        notaFile << "Tanggal & Waktu: " << this->getCurrentDateTime() << endl;  // Tambahkan this->
        notaFile << "------------------------------------------" << endl;
        notaFile << "Nama Pemesan\t: " << booking.namaPemesan << endl;
        notaFile << "Kode Pemesan\t: " << booking.kodePemesan << endl;
        notaFile << "Jenis Kamar\t: " << booking.namaKamar << endl;
        notaFile << "Jumlah Malam\t: " << booking.jumlahMalam << endl;
        notaFile << "Tanggal Pesan\t:" << booking.bookingDate << endl;
        notaFile << fixed << setprecision(0);
        notaFile << "Harga/malam\t: Rp" << booking.hargaKamar << endl;
        notaFile << "------------------------------------------" << endl;
        notaFile << "Total Pembayaran: Rp" << booking.totalBayar << endl;
        notaFile << "==========================================" << endl;
        notaFile.close();
        cout << "Nota berhasil dicetak ke file " << notaFilename << endl;
    }
    else {
        cout << "Gagal membuka file nota" << endl;
    }
}

void Kelass::updateKamar(Booking& booking)
{
    clearScreen();
    int jenisKamar;
    cout << "\n--- Update Jenis Kamar ---" << endl;
    cout << "Jenis Kamar saat ini: " << booking.namaKamar << endl;
    cout << "1. Standar (Rp500.000/malam)" << endl;
    cout << "2. Superior (Rp800.000/malam)" << endl;
    cout << "3. Suite (Rp1.200.000/malam)" << endl;
    cout << "Pilihan Anda: ";
    cin >> jenisKamar;
    switch (jenisKamar) {
    case 1:
        booking.namaKamar = "Standar";
        booking.hargaKamar = 500000;
        break;
    case 2:
        booking.namaKamar = "Superior";
        booking.hargaKamar = 800000;
        break;
    case 3:
        booking.namaKamar = "Suite";
        booking.hargaKamar = 1200000;
        break;
    default:
        cout << "Pilihan tidak valid! Jenis kamar tidak berubah." << endl;
        enterToContinue();
        return;
    }
    booking.totalBayar = booking.hargaKamar * booking.jumlahMalam;
    cout << "Jenis kamar berhasil diupdate!" << endl;
}

void Kelass::updateTanggal(Booking& booking)
{
    clearScreen();
    cout << "\n--- Update Tanggal Booking ---" << endl;
    cout << "Tanggal saat ini: " << booking.bookingDate << endl;

    bool validDate = false;
    string newDate;
    do {
        cout << "Tanggal Booking Baru (YYYY-MM-DD): ";
        cin >> newDate;
        validDate = isValidFutureDate(newDate);
        if (!validDate) {
            cout << "! Tanggal harus format YYYY-MM-DD dan belum lewat!" << endl;
        }
    } while (!validDate);

    booking.bookingDate = newDate;
    cout << "Tanggal booking berhasil diupdate!" << endl;
}

void Kelass::updateJumlahMalam(Booking& booking)
{
    clearScreen();
    cout << "\n--- Update Jumlah Malam ---" << endl;
    cout << "Jumlah malam saat ini: " << booking.jumlahMalam << endl;
    cout << "Masukkan jumlah malam baru: ";
    cin >> booking.jumlahMalam;
    booking.totalBayar = booking.hargaKamar * booking.jumlahMalam;
    cout << "Jumlah malam berhasil diupdate!" << endl;
}


void Kelass::pesanTiket() {
    clearScreen();
    Booking newBooking;

    cout << "\n--- Input Data Pemesanan ---" << endl;
    cin.ignore();
    cout << "Nama Lengkap Pemesan\t\t: ";
    getline(cin, newBooking.namaPemesan);
    cout << "Kode Pemesan\t\t\t: ";
    getline(cin, newBooking.kodePemesan);

    bool validDate = false;
    do {
        cout << "Tanggal Booking (YYYY-MM-DD)\t: ";
        getline(cin, newBooking.bookingDate);
        validDate = isValidFutureDate(newBooking.bookingDate);
        if (!validDate) {
            cout << "! Tanggal harus format YYYY-MM-DD dan belum lewat!\n";
            cout << "Tanggal hari ini: " << getCurrentDateTime().substr(0, 10) << endl;
        }
    } while (!validDate);

    cout << "Jumlah Malam yang Dipesan\t: ";
    cin >> newBooking.jumlahMalam;

    clearScreen();
    int jenisKamar;
    cout << "\n--- Pilih Jenis Kamar ---" << endl;
    cout << "1. Standar (Rp500.000/malam)" << endl;
    cout << "2. Superior (Rp800.000/malam)" << endl;
    cout << "3. Suite (Rp1.200.000/malam)" << endl;
    cout << "Pilihan Anda: ";
    cin >> jenisKamar;

    switch (jenisKamar) {
    case 1:
        newBooking.namaKamar = "Standar";
        newBooking.hargaKamar = 500000;
        break;
    case 2:
        newBooking.namaKamar = "Superior";
        newBooking.hargaKamar = 800000;
        break;
    case 3:
        newBooking.namaKamar = "Suite";
        newBooking.hargaKamar = 1200000;
        break;
    default:
        cout << "Pilihan tidak valid!" << endl;
        enterToContinue();
        return;
    }

    newBooking.totalBayar = newBooking.hargaKamar * newBooking.jumlahMalam;

    bookings.push_back(newBooking);
    saveToFile();
    printNota(newBooking);

    cout << "\nPemesanan berhasil dibuat!" << endl;
    enterToContinue();
}


void Kelass::readBookings() {
    loadFromFile();
    clearScreen();
    cout << "\n--- Daftar Pemesanan ---" << endl;
    if (bookings.empty()) {
        cout << "Tidak ada pemesanan yang tersedia." << endl;
    }
    else {
        for (const auto& booking : bookings) {
            cout << "Kode Pemesan: " << booking.kodePemesan << endl;
            cout << "Nama Pemesan: " << booking.namaPemesan << endl;
            cout << "Tanggal: " << booking.bookingDate << endl;
            cout << "Jenis Kamar: " << booking.namaKamar << endl;
            cout << "Total: Rp" << fixed << setprecision(0) << booking.totalBayar << endl;
            cout << "------------------------------" << endl;
        }
    }
    enterToContinue();
}

void Kelass::updateBooking() {
    loadFromFile();
    clearScreen();
    string kodePemesan;
    cout << "Masukkan Kode Pemesan untuk diupdate: ";
    cin >> kodePemesan;
    auto it = find_if(bookings.begin(), bookings.end(), [&](const Booking& b) {
        return b.kodePemesan == kodePemesan;
        });
    if (it != bookings.end()) {
        while (true) {
            clearScreen();
            cout << "\nData saat ini:" << endl;
            cout << "Nama: " << it->namaPemesan << endl;
            cout << "Kode: " << it->kodePemesan << endl;
            cout << "Tanggal: " << it->bookingDate << endl;
            cout << "Jenis Kamar: " << it->namaKamar << endl;
            cout << "Harga/malam: Rp" << fixed << setprecision(0) << it->hargaKamar << endl;
            cout << "Jumlah Malam: " << it->jumlahMalam << endl;
            cout << "Total: Rp" << fixed << setprecision(0) << it->totalBayar << endl;

            cout << "\nMenu Update:" << endl;
            cout << "1. Update Jenis Kamar" << endl;
            cout << "2. Update Tanggal Booking" << endl;
            cout << "3. Update Jumlah Malam" << endl;
            cout << "4. Selesai Update" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;

            switch (pilihan) {
            case 1:
                updateKamar(*it);
                break;
            case 2:
                updateTanggal(*it);
                break;
            case 3:
                updateJumlahMalam(*it);
                break;
            case 4:
                saveToFile();
                printNota(*it);
                cout << "Update selesai. Data telah disimpan." << endl;
                enterToContinue();
                return;
            default:
                cout << "Pilihan tidak valid!" << endl;
                enterToContinue();
            }
        }
    }
    else {
        cout << "Kode pemesan tidak ditemukan!" << endl;
        enterToContinue();
    }
}

void Kelass::deleteBooking() {
    loadFromFile();
    clearScreen();
    string kodePemesan;
    cout << "Masukkan Kode Pemesan untuk dihapus: ";
    cin >> kodePemesan;

    auto it = remove_if(bookings.begin(), bookings.end(), [&](const Booking& b) {
        return b.kodePemesan == kodePemesan;
        });

    if (it != bookings.end()) {
        bookings.erase(it, bookings.end());
        saveToFile();
        cout << "Data berhasil dihapus!" << endl;

        // Delete nota file
        string notaFilename = "nota_" + kodePemesan + ".txt";
        if (remove(notaFilename.c_str()) != 0) {
            cout << "Gagal menghapus file nota" << endl;
        }
    }
    else {
        cout << "Kode pemesan tidak ditemukan!" << endl;
    }
    enterToContinue();
}

bool Kelass::isValidFutureDate(const string& date) {
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

    return true; // Pastikan untuk mengembalikan true jika semua validasi berhasil
}
