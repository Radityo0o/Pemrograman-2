#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Barang
{
	string nama;
	string kode;
	int stok;
};

bool urutStok(const Barang& a, const Barang& b) {
	return a.stok < b.stok;
}

void cariBarang(const vector<Barang>& daftarBarang) {
	string namaBarang;
	cout << "Masukkan Nama Barang: ";
	getline(cin, namaBarang);

	bool ketemu = false;
	for (const Barang& barang : daftarBarang)
	{
		if (barang.nama.find(namaBarang) != string::npos)
		{
			cout << "Barang Ditemukan!" << endl;
			cout << "Nama : " << barang.nama << endl;
			cout << "Kode : " << barang.kode << endl;
			cout << "Stok : " << barang.stok << endl;
			ketemu = true;
		}
	}
	if (!ketemu)
	{
		cout << "Barang Tidak Ditemukan!";
	}
}

int main()
{
	vector<Barang> daftarBarang;
	char tambahLagi;
	int pilihan;

	do
	{
		Barang barang;

		cout << endl << "Inventaris Barang" << endl;
		cout << endl << "Nama : ";
		getline(cin, barang.nama);
		cout << "Kode : ";
		getline(cin, barang.kode);
		cout << "Stok : ";
		cin >> barang.stok;
		cin.ignore();

		daftarBarang.push_back(barang);

		cout << endl << "Tambah barang lagi? (Y/N) ";
		cin >> tambahLagi;
		cin.ignore();
	} while (tambahLagi == 'Y' || tambahLagi == 'y');

	while (true) {
		cout << "===== MENU =====" << endl;
		cout << "1. Tampilkan Daftar Barang Sesuai Stok" << endl;
		cout << "2. Cari Barang" << endl;
		cout << "3. Keluar" << endl;
		cout << "Pilih Menu (1-3): ";
		cin >> pilihan;
		cin.ignore();

		switch (pilihan) {
		case 1:
			sort(daftarBarang.begin(), daftarBarang.end(), urutStok);

			cout << "\n===== Daftar Barang Sesuai Stok =====\n" << endl << endl;
			for (size_t i = 0; i < daftarBarang.size(); i++)
			{
				cout << endl << "Barang ke- " << i + 1 << endl;
				cout << "Nama : " << daftarBarang[i].nama << endl;
				cout << "Kode : " << daftarBarang[i].kode << endl;
				cout << "Stok : " << daftarBarang[i].stok << endl;
			}
			break;
		case 2:
			cariBarang(daftarBarang);
			break;
		case 3:
			cout << "Terima Kasih!";
			return 0;
		default:
			cout << "Invalid Input!";
		}
	}
}