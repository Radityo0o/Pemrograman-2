#include "kelas.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

int main()
{
    Kelass kelas;

    string passwordLogin, opsi;

    cout << "Aplikasi Pemesan Hotel" << endl;
    while (true)
    {
        cout << "Password: ";
        cin >> passwordLogin;
        if (passwordLogin == "admin123")
        {
            cout << "Login berhasil!" << endl;
            break;
        } 
        else
        {
            cout << "Password salah, coba lagi!" << endl;
        } 
    }
        
awal:
    while (true)
    {
    kelas.clearScreen();
    kelas.headerUtama();
    kelas.menuUtama();
    cout << "\n-> ";
    cin >> opsi;

    if (opsi == "1")
    {
        kelas.pesanTiket();
    }
    else if (opsi == "2")
    {
        cout << "Program Selesai!" << endl;
        return 0;
    }
    else 
    {
        cout << "Invalid Input!" << endl;
    }
    
    
    kelas.enterToContinue();
    }
akhir:
    return 0;
}
