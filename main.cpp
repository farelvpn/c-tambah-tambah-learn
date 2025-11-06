/*
Aku mah masih pemula.

Learning C++ With Simple Rekening Bank Sederhana
*/


// Masukan Libnrary yang dibutuhkan
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <algorithm>

// Fungsi untuk membersihkan layar terminal [ Windows and Linux Support anjay ]
void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Fungsi untuk menampilkan menu transaksi dengan tampilan menarik
void displayMenu(int saldo) {
    clearScreen();
    std::cout << "\033[1;33m"; // Warna kuning untuk judul
    std::cout << "===========================" << std::endl;
    std::cout << "     BANK INDONESIA JAYA   " << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "\033[0m"; // Mengembalikan warna ke default

    std::cout << "\033[1;34m"; // Warna biru untuk teks menu
    std::cout << "Saldo: ";
    std::cout << "\033[1;32m"; // Warna hijau untuk saldo

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << saldo; // Mengkonversi saldo ke stringstream dengan 2 angka desimal

    std::string saldoStr = ss.str();
    int length = saldoStr.length();

    int counter = 0;
    std::string formattedSaldo;
    for (int i = length - 1; i >= 0; --i) {
        if (counter % 3 == 0 && counter != 0) // Menambah titik setiap tiga digit dari belakang
            formattedSaldo = "." + formattedSaldo;

        formattedSaldo = saldoStr[i] + formattedSaldo;
        counter++;
    }

    std::cout << "Rp " << formattedSaldo << std::endl;
    std::cout << "\033[0m"; // Mengembalikan warna ke default

    std::cout << "\033[1;34m"; // Warna biru untuk teks menu
    std::cout << "Menu Transaksi:" << std::endl;
    std::cout << "1. Setor Tabungan" << std::endl;
    std::cout << "2. Ambil Tabungan" << std::endl;
    std::cout << "3. Keluar" << std::endl;
    std::cout << "\033[0m"; // Mengembalikan warna ke default
    std::cout << "Pilihan Menu Transaksi (1/2/3): ";
}

// Fungsi untuk menyimpan saldo ke file
void simpanSaldo(int saldo) {
    std::ofstream file(".saldo");
    if (file.is_open()) {
        file << saldo;
        file.close();
    } else {
        std::cerr << "Gagal menyimpan saldo ke file!" << std::endl;
    }
}

// Fungsi untuk membaca saldo dari file
int bacaSaldo() {
    int saldo;
    std::ifstream file(".saldo");
    if (file.is_open()) {
        file >> saldo;
        file.close();
    } else {
        std::cerr << "Gagal membaca saldo dari file!" << std::endl;
        saldo = 0; // Jika gagal membaca, kembalikan nilai default
    }
    return saldo;
}

int main() {
    int saldo = bacaSaldo(); // Baca saldo dari file saat memulai program
    if (saldo == 0) {
        saldo = 100000; // Jika tidak ada saldo yang tersimpan, gunakan saldo awal 100.000
        simpanSaldo(saldo); // Simpan saldo awal ke file
    }
    int pilihan;
    int jumlah;

    do {
        displayMenu(saldo);
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                clearScreen();
                std::cout << "=================================" << std::endl;
                std::cout << "Masukkan jumlah yang akan disetor: ";
                std::cin >> jumlah;
                if (jumlah >= 50000) {
                    saldo += jumlah;
                    simpanSaldo(saldo); // Simpan saldo ke file setelah setoran
                } else {
                    clearScreen();
                    std::cout << "Minimal saldo yang dapat di setorkan adalah 50000" << std::endl;
                }
                break;
            case 2:
                clearScreen();
                std::cout << "=================================" << std::endl;
                std::cout << "Masukkan jumlah yang akan diambil: ";
                std::cin >> jumlah;
                if (saldo - jumlah >= 50000) {
                    saldo -= jumlah;
                    simpanSaldo(saldo); // Simpan saldo ke file setelah penarikan
                } else {
                    clearScreen();
                    std::cout << "Maaf, saldo minimal harus disisakan Rp. 50.000,-" << std::endl;
                }
                break;
            case 3:
                clearScreen();
                std::cout << "=================================" << std::endl;
                std::cout << "Terima kasih telah melakukan transaksi." << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << std::endl;
        }
    } while (pilihan != 3);

    return 0;
}