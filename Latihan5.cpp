#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Mahasiswa {
	string nim;
	string nama;
	string prodi;
};

void menuAwal() {
	cout << "--------------------------------" << endl;
	cout << "Daftar Mahasiswa Politeknik ATMI" << endl;
	cout << "--------------------------------" << endl;
}

string getProdiFromNIM(const string& nim) {
	if (nim.length() < 5) return "";

	switch (nim[4]) {
	case '1': return "D3 TMI";
	case '2': return "D3 TMK";
	case '3': return "D3 TPM";
	case '4': return "D4 RTM";
	case '5': return "D4 PM";
	case '6': return "D4 TRMK";
	default: return "";
	}
}

bool inputMahasiswa(Mahasiswa& mhs) {
	cout << "Masukkan Nama: ";
	getline(cin, mhs.nama);

	cout << "Masukkan NIM: ";
	cin >> mhs.nim;
	cin.ignore();

	mhs.prodi = getProdiFromNIM(mhs.nim);

	if (mhs.prodi.empty()) {
		cout << "NIM tidak valid atau prodi tidak dikenali!\n";
		return false;
	}

	return true;
}

void printDaftarMahasiswa(vector<Mahasiswa>& daftar) {
	if (daftar.empty()) {
		cout << "\nDaftar mahasiswa masih kosong.\n";
		return;
	}

	sort(daftar.begin(), daftar.end(), [](const Mahasiswa& a, const Mahasiswa& b) {
		return (a.prodi == b.prodi) ? (a.nim < b.nim) : (a.prodi < b.prodi);
		});

	cout << "\nDaftar Mahasiswa\n";
	cout << "------------------------" << endl;

	string currentProdi;
	for (const auto& mhs : daftar) {
		if (mhs.prodi != currentProdi) {
			currentProdi = mhs.prodi;
			cout << "\n--> PRODI: " << currentProdi << endl;
		}

		cout << "Nama:\t" << mhs.nama << endl;
		cout << "NIM:\t" << mhs.nim << endl;
		cout << "------------------------" << endl;
	}
}

int main() {
	vector<Mahasiswa> daftarMahasiswa;
	int pilihan;

	menuAwal();

	while (true) {
		cout << "\n--- MENU UTAMA ---" << endl;
		cout << "1. Input Mahasiswa" << endl;
		cout << "2. Tampilkan Daftar Mahasiswa" << endl;
		cout << "3. Keluar Program" << endl;
		cout << "Pilih menu: ";
		cin >> pilihan;
		cin.ignore();

		switch (pilihan) {
		case 1: {
			char lanjut;
			do {
				Mahasiswa mhs;
				if (inputMahasiswa(mhs)) {
					daftarMahasiswa.push_back(mhs);
					cout << "Data berhasil ditambahkan!\n";
				}
				cout << "Masukkan data lagi? (Y/T): ";
				cin >> lanjut;
				cin.ignore();
			} while (lanjut == 'Y' || lanjut == 'y');
			break;
		}
		case 2:
			printDaftarMahasiswa(daftarMahasiswa);
			cout << "\nTekan Enter untuk kembali ke menu utama...";
			cin.get();
			break;
		case 3:
			cout << "Terima kasih telah menggunakan program ini!\n";
			return 0;
		default:
			cout << "Pilihan tidak valid! Silakan coba lagi.\n";
		}
	}

	return 0;
}
