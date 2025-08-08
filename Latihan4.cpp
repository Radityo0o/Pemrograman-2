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
	cout << "\nMasukkan Nama Barang: ";
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
		cout << "Barang Tidak Ditemukan!" << endl;
	}
}

int main()
{
	vector<Barang> daftarBarang;
	int pilihan;

	while (true) {
		cout << "\n--- Inventaris Barang ---" << endl;
		cout << "1. Tambah Barang" << endl;
		cout << "2. Tampilkan Daftar Barang Sesuai Stok" << endl;
		cout << "3. Cari Barang" << endl;
		cout << "4. Keluar" << endl;
		cout << "Pilih Menu (1-4): ";
		cin >> pilihan;
		cin.ignore();

		switch (pilihan) {
		case 1: {
			char tambahLagi;
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
			break;
		}
		case 2: {
			if (daftarBarang.empty()) {
				cout << "\nDaftar barang masih kosong!" << endl;
			}
			else {
				sort(daftarBarang.begin(), daftarBarang.end(), urutStok);

				cout << "\n--- Daftar Barang Sesuai Stok ---\n" << endl;
				for (size_t i = 0; i < daftarBarang.size(); i++)
				{
					cout << endl << "Barang ke-" << i + 1 << endl;
					cout << "Nama\t: " << daftarBarang[i].nama << endl;
					cout << "Kode\t: " << daftarBarang[i].kode << endl;
					cout << "Stok\t: " << daftarBarang[i].stok << endl;
				}
			}
			cout << "\nTekan Enter untuk kembali ke menu utama...";
			cin.get();
			break;
		}
		case 3: {
			cariBarang(daftarBarang);
			cout << "\nTekan Enter untuk kembali ke menu utama...";
			cin.get();
			break;
		}
		case 4:
			cout << "\nTerima Kasih!" << endl;
			return 0;
		default:
			cout << "\nInput Tidak Valid!" << endl;
		}
	}
}
