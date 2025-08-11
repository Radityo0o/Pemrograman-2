#pragma once
#include <string>
using namespace std;
class Kelass {
public:
    void clearScreen();
    void enterToContinue();
    void headerUtama();
    void menuUtama();
    void pesanTiket();
    string getCurrentDateTime();
    bool isValidFutureDate(const string& date);
};
