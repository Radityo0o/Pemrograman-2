#define _CRT_SECURE_NO_WARNINGS
#include "menupesan.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include<random>

using namespace std;

/* Struktur untuk menyimpan data stok kamar
struct RoomStock {
    string jenisKamar;
    int stokTersedia;
    int hargaPerMalam;
};*/

// Inisialisasi stok kamar default
vector<RoomStock> roomStock = {
    {"Standar", 20, 500000},
    {"Superior", 15, 800000},
    {"Suite", 10, 1200000}
};

// Fungsi untuk menyimpan stok ke file
void Kelass::saveStockToFile() {
    ofstream file("stock.txt");
    if (file.is_open()) {
        for (const auto& stock : roomStock) {
            file << stock.jenisKamar << endl;
            file << stock.stokTersedia << endl;
            file << stock.hargaPerMalam << endl;
        }
        file.close();
    }
}

// Fungsi untuk memuat stok dari file
void Kelass::loadStockFromFile() {
    ifstream file("stock.txt");
    if (file.is_open()) {
        roomStock.clear();
        RoomStock stock;
        while (getline(file, stock.jenisKamar) &&
            file >> stock.stokTersedia &&
            file >> stock.hargaPerMalam) {
            file.ignore();
            roomStock.push_back(stock);
        }
        file.close();
    }
    else {
        // Jika file tidak ada, buat dengan stok default
        roomStock = {
            {"Standar", 20, 500000},
            {"Superior", 15, 800000},
            {"Suite", 10, 1200000}
        };
        saveStockToFile();
    }
}

// Fungsi untuk menampilkan stok kamar
void Kelass::displayRoomStock() {
    loadStockFromFile();
    clearScreen();
    cout << "|=======================================|\n";
    cout << "|                                       |\n";
    cout << "|      Booking Hotel? Disini Aja        |\n";
    cout << "|                                       |\n";
    cout << "|=======================================|\n";
    cout << endl;
    cout << "\n---     Stok Kamar Tersedia      ---" << endl;
    cout << "=========================================" << endl;
    cout << left << setw(12) << "Jenis Kamar"
        << setw(15) << "Stok Tersedia"
        << setw(15) << "Harga/Malam" << endl;
    cout << "=========================================" << endl;

    for (const auto& stock : roomStock) {
        cout << left << setw(12) << stock.jenisKamar
            << setw(15) << stock.stokTersedia
            << "Rp" << fixed << setprecision(0) << stock.hargaPerMalam << endl;
    }

    cout << "=========================================" << endl;
    enterToContinue();
}

// Fungsi untuk mengupdate stok setelah pemesanan
void Kelass::updateStock(const string& jenisKamar, int jumlah, bool isBooking) {
    loadStockFromFile();
    for (auto& stock : roomStock) {
        if (stock.jenisKamar == jenisKamar) {
            if (isBooking) {
                stock.stokTersedia -= jumlah; // Kurangi stok saat booking
            }
            else {
                stock.stokTersedia += jumlah; // Tambah stok saat cancel
            }
            break;
        }
    }
    saveStockToFile();
}

// Fungsi untuk mengecek ketersediaan stok
bool Kelass::checkStockAvailability(const string& jenisKamar, int jumlahKamar) {
    loadStockFromFile();
    for (const auto& stock : roomStock) {
        if (stock.jenisKamar == jenisKamar) {
            return stock.stokTersedia >= jumlahKamar;
        }
    }
    return false;
}

// Fungsi untuk mengelola stok (admin)
void Kelass::manageStock() {
    loadStockFromFile();
    clearScreen();
    cout << "\n--- Kelola Stok Kamar ---" << endl;
    cout << "1. Tampilkan Stok" << endl;
    cout << "2. Tambah Stok" << endl;
    cout << "3. Kurangi Stok" << endl;
    cout << "4. Kembali ke Menu Utama" << endl;
    cout << "Pilihan: ";

    int pilihan;
    cin >> pilihan;

    switch (pilihan) {
    case 1:
        displayRoomStock();
        break;
    case 2:
    case 3: {
        cout << "\nPilih jenis kamar:" << endl;
        for (int i = 0; i < roomStock.size(); i++) {
            cout << (i + 1) << ". " << roomStock[i].jenisKamar << endl;
        }
        cout << "Pilihan: ";

        int jenisKamar;
        cin >> jenisKamar;

        if (jenisKamar < 1 || jenisKamar > roomStock.size()) {
            cout << "Pilihan tidak valid!" << endl;
            enterToContinue();
            return;
        }

        int jumlah;
        cout << "Masukkan jumlah: ";
        cin >> jumlah;

        if (pilihan == 2) {
            roomStock[jenisKamar - 1].stokTersedia += jumlah;
            cout << "Stok berhasil ditambah!" << endl;
        }
        else {
            if (roomStock[jenisKamar - 1].stokTersedia >= jumlah) {
                roomStock[jenisKamar - 1].stokTersedia -= jumlah;
                cout << "Stok berhasil dikurangi!" << endl;
            }
            else {
                cout << "Stok tidak mencukupi!" << endl;
            }
        }
        saveStockToFile();
        enterToContinue();
        break;
    }
    case 4:
        return;
    default:
        cout << "Pilihan tidak valid!" << endl;
        enterToContinue();
    }
}

string Kelass::generateRandomCode() {
    // Menggunakan modern random generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999); // 6 digit code

    int randomNum = dis(gen);
    return to_string(randomNum);
}

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
    cout << "|=========================================|\n";
    cout << "|                                         |\n";
    cout << "|       Booking Hotel? Disini Aja         |\n";
    cout << "|                                         |\n";
    cout << "|=========================================|\n";
    cout << endl;
    cout << "=          Silahkan Pilih Menu           =" << endl;
    cout << "------------------------------------------" << endl;
}

void Kelass::menuUtama() {
    cout << "1. Pesan Kamar" << endl;
    cout << "2. Keluar" << endl;
    cout << "3. Lihat Pemesanan" << endl;
    cout << "4. Update Pemesanan" << endl;
    cout << "5. Hapus Pemesanan" << endl;
    cout << "6. Lihat Stok Kamar" << endl;        // Menu baru
    cout << "7. Kelola Stok (Admin)" << endl;     // Menu admin
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
        notaFile << "Tanggal & Waktu: " << this->getCurrentDateTime() << endl;
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

void Kelass::updateKamar(Booking& booking) {
    clearScreen();
    int jenisKamar;
    cout << "\n--- Update Jenis Kamar ---" << endl;
    cout << "Jenis Kamar saat ini: " << booking.namaKamar << endl;

    // Tampilkan stok tersedia untuk setiap jenis kamar
    loadStockFromFile();
    cout << "\nStok kamar tersedia:" << endl;
    for (int i = 0; i < roomStock.size(); i++) {
        cout << (i + 1) << ". " << roomStock[i].jenisKamar
            << " (Rp" << roomStock[i].hargaPerMalam << "/malam) - Stok: "
            << roomStock[i].stokTersedia << endl;
    }

    cout << "Pilihan Anda: ";
    cin >> jenisKamar;

    if (jenisKamar < 1 || jenisKamar > roomStock.size()) {
        cout << "Pilihan tidak valid! Jenis kamar tidak berubah." << endl;
        enterToContinue();
        return;
    }

    string newRoomType = roomStock[jenisKamar - 1].jenisKamar;

    // Cek apakah kamar tersedia
    if (!checkStockAvailability(newRoomType, 1)) {
        cout << "Maaf, kamar " << newRoomType << " tidak tersedia!" << endl;
        enterToContinue();
        return;
    }

    // Kembalikan stok kamar lama
    updateStock(booking.namaKamar, 1, false);

    // Update data booking
    booking.namaKamar = newRoomType;
    booking.hargaKamar = roomStock[jenisKamar - 1].hargaPerMalam;
    booking.totalBayar = booking.hargaKamar * booking.jumlahMalam;

    // Kurangi stok kamar baru
    updateStock(booking.namaKamar, 1, true);

    cout << "Jenis kamar berhasil diupdate!" << endl;
}

void Kelass::updateTanggal(Booking& booking) {
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

void Kelass::updateJumlahMalam(Booking& booking) {
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
    cout << "|=======================================|\n";
    cout << "|                                       |\n";
    cout << "|      Booking Hotel? Disini Aja        |\n";
    cout << "|                                       |\n";
    cout << "|=======================================|\n";
    cout << endl;
    cout << "\n---       Input Data Pemesanan      ---" << endl;
    cin.ignore();
    cout << "Nama Lengkap Pemesan\t\t: ";
    getline(cin, newBooking.namaPemesan);

    newBooking.kodePemesan = generateRandomCode();
    cout << "Kode Pemesan Anda\t\t: " << newBooking.kodePemesan << endl;

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
    cout << "|=======================================|\n";
    cout << "|                                       |\n";
    cout << "|      Booking Hotel? Disini Aja        |\n";
    cout << "|                                       |\n";
    cout << "|=======================================|\n";
    cout << endl;
    cout << "\n---        Pilih Jenis Kamar       ---" << endl;

    // Tampilkan stok tersedia
    loadStockFromFile();
    for (int i = 0; i < roomStock.size(); i++) {
        cout << (i + 1) << ". " << roomStock[i].jenisKamar
            << " (Rp" << roomStock[i].hargaPerMalam << "/malam) - Stok: "
            << roomStock[i].stokTersedia << endl;
    }

    cout << "Pilihan Anda: ";
    cin >> jenisKamar;

    if (jenisKamar < 1 || jenisKamar > roomStock.size()) {
        cout << "Pilihan tidak valid!" << endl;
        enterToContinue();
        return;
    }

    string selectedRoom = roomStock[jenisKamar - 1].jenisKamar;

    // Cek ketersediaan stok
    if (!checkStockAvailability(selectedRoom, 1)) {
        cout << "Maaf, kamar " << selectedRoom << " tidak tersedia!" << endl;
        enterToContinue();
        return;
    }

    newBooking.namaKamar = selectedRoom;
    newBooking.hargaKamar = roomStock[jenisKamar - 1].hargaPerMalam;
    newBooking.totalBayar = newBooking.hargaKamar * newBooking.jumlahMalam;

    // Kurangi stok
    updateStock(newBooking.namaKamar, 1, true);

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

    auto it = find_if(bookings.begin(), bookings.end(), [&](const Booking& b) {
        return b.kodePemesan == kodePemesan;
        });

    if (it != bookings.end()) {
        // Kembalikan stok kamar
        updateStock(it->namaKamar, 1, false);

        bookings.erase(it);
        saveToFile();
        cout << "Data berhasil dihapus dan stok kamar dikembalikan!" << endl;

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

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2) {
        bool leapYear = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
        if (day > (leapYear ? 29 : 28))
            return false;
    }

    time_t now = time(0);
    tm* ltm = localtime(&now);

    if (year < 1900 + ltm->tm_year) return false;
    if (year == 1900 + ltm->tm_year && month < 1 + ltm->tm_mon) return false;
    if (year == 1900 + ltm->tm_year && month == 1 + ltm->tm_mon && day <= ltm->tm_mday) return false;

    return true;
}
