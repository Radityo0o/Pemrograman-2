#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    int tabungan[6] = { 0 };
    int penarikan = 0;
    Mahasiswa(string n, string id);
    int totalTabungan() const;
    int saldoAkhir() const;
};


class Koperasi {
private:
    vector<Mahasiswa> dataMahasiswa;

public:
    bool isMember(string nim);
    void enterToContinue() const;
    void clearScreen() const;
    void tambahMahasiswa();
    void tampilkanMahasiswa() const;
    void ubahMahasiswa();
    void inputTabungan();
    void tampilkanSaldo();
    void exportData() const;
    void hapusMahasiswa();
    void menuAdmin(Koperasi& koperasi);
    void menuMahasiswa(Mahasiswa* mhs, Koperasi& koperasi);
    Mahasiswa* loginMahasiswa(const string& nim, const string& pass);
};