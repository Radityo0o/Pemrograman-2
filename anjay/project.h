#include <string>
#include <vector>
using namespace std;

struct Penerbangan {
    string tujuan;
    string tanggal;
    string waktu;
    double harga;
    int jumlahKursi;
    vector<bool> kursiTerisi;
};

struct Pembelian {
    string nama;
    int idPenerbangan;
    int nomorKursi;
    double totalBayar;
};

class Kelass {
private:
    vector<Penerbangan> daftarPenerbangan;
    vector<Pembelian> daftarPembelian;

public:
    void clearScreen();
    void enterToContinue();
    void headerUtama();
    void menuAdmin();
    void menuUser();

    void inputPenerbangan();
    void tampilkanPenerbangan();
    void updatePenerbangan();
    void deletePenerbangan();

    void pesanTiket();

    void loadData();
    void saveData();
    void cetakNota(const string& nama, double total, double dibayar, double kembalian);
};
