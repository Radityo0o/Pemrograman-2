#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Booking {
    string namaPemesan;
    string kodePemesan;
    string bookingDate;
    int jumlahMalam;
    string namaKamar;
    double hargaKamar;
    double totalBayar;
};

class Kelass {
public:
    void clearScreen();
    void enterToContinue();
    void headerUtama();
    void menuUtama();
    void pesanTiket();
    void readBookings();
    void updateBooking();
    void deleteBooking();
    string getCurrentDateTime();
    bool isValidFutureDate(const string& date);
    void saveToFile();
    void loadFromFile();
    void printNota(const Booking& booking);
    void updateKamar(Booking& booking);
    void updateTanggal(Booking& booking);
    void updateJumlahMalam(Booking& booking);

private:
    vector<Booking> bookings;
    const string filename = "bookings.txt";
};
