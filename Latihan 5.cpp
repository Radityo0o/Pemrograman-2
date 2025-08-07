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

string getProdiFromNIM(const string& nim) {
	if (nim.length() < 5) return "";

	switch (nim[4]) {
	case '1': return "TMI";
	case '2': return "TMK";
	case '3': return "TPM";
	case '4': return "RTM";
	case '5': return "PM";
	case '6': return "TRMK";
	default:  return "";
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

void printDaftarMahasiswa(const vector<Mahasiswa>& daftar) {
	cout << "\n--- Daftar Mahasiswa ---\n";

	string currentProdi;
	for (const auto& mhs : daftar) {
		if (mhs.prodi != currentProdi) {
			currentProdi = mhs.prodi;
			cout << "\n== PRODI: " << currentProdi << " ==" << endl;
		}

		cout << "Nama:  \t" << mhs.nama << endl;
		cout << "NIM:   \t" << mhs.nim << endl;
		cout << "------------------------" << endl;
	}
}

int main() {
	vector<Mahasiswa> daftarMahasiswa;
	char lanjut;

	do {
		Mahasiswa mhs;
		if (inputMahasiswa(mhs)) {
			daftarMahasiswa.push_back(mhs);
		}

		cout << "Masukkan Data Lagi? (Y/T): ";
		cin >> lanjut;
		cin.ignore();

	} while (lanjut == 'Y' || lanjut == 'y');

	sort(daftarMahasiswa.begin(), daftarMahasiswa.end(), [](const Mahasiswa& a, const Mahasiswa& b) {
		return (a.prodi == b.prodi) ? (a.nim < b.nim) : (a.prodi < b.prodi);
		});

	printDaftarMahasiswa(daftarMahasiswa);
	return 0;
}