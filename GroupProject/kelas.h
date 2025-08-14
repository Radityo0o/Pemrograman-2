#include <string>
#include <vector>
using namespace std;

// Struktur untuk data pemesanan
struct Booking {
    string namaPemesan;
    string kodePemesan;
    string bookingDate;
    int jumlahMalam;
    string namaKamar;
    double hargaKamar;
    double totalBayar;
};

// Struktur untuk data stok kamar
struct RoomStock {
    string jenisKamar;
    int stokTersedia;
    int hargaPerMalam;
};

class Kelass {
private:
    vector<Booking> bookings;
    string filename = "bookings.txt";

public:
    // Fungsi dasar
    void headerUtama();
    void menuUtama();
    void clearScreen();
    void enterToContinue();
    string generateRandomCode();
    string getCurrentDateTime();
    bool isValidFutureDate(const string& date);

    // Fungsi pemesanan
    void pesanTiket();
    void readBookings();
    void updateBooking();
    void deleteBooking();

    // Fungsi update detail
    void updateKamar(Booking& booking);
    void updateTanggal(Booking& booking);
    void updateJumlahMalam(Booking& booking);

    // Fungsi file I/O
    void saveToFile();
    void loadFromFile();
    void printNota(const Booking& booking);

    // Fungsi stok kamar (BARU)
    void displayRoomStock();          // Menampilkan stok kamar
    void manageStock();               // Mengelola stok (admin)
    void saveStockToFile();           // Menyimpan stok ke file
    void loadStockFromFile();         // Memuat stok dari file
    void updateStock(const string& jenisKamar, int jumlah, bool isBooking);
    bool checkStockAvailability(const string& jenisKamar, int jumlahKamar);
};
