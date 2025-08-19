#include "project.h"

int main() {
    Project app;
    vector<Mahasiswa> mahasiswa;
    int pilihan;

    do {
        app.mainHeader();
        app.mainMenu();
        cin >> pilihan;

        switch (pilihan) {
        case 1: app.addMahasiswa(mahasiswa); break;
        case 2: app.displayMahasiswa(mahasiswa); break;
        case 3: app.inputJam(mahasiswa); break;
		case 4: app.deleteMahasiswa(mahasiswa); break;
        case 5: app.exportData(mahasiswa); break;
        case 6: cout << "Keluar dari program.\n"; break;
        default: cout << "Pilihan tidak valid!\n"; break;
        }

        if (pilihan != 6) app.entertocontinue();

    } while (pilihan != 6);

    return 0;
}
