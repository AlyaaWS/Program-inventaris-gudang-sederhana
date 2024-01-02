#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct BarangInventaris {
    string namaBarang;
    int jumlahBarang, hargaBarang;
};

struct Admin {
    string username;
    string password;
};

vector<Admin> bacaDataAdmin() {
    vector<Admin> admins;
    ifstream file("data_admin.txt");

    if (file.is_open()) {
        string username, password;
        while (file >> username >> password) {
            admins.push_back({username, password});
        }
        file.close();
    } else {
        cout << "File data admin tidak ditemukan. Membuat file baru.\n";
    }

    return admins;
}

void simpanDataAdmin(const vector<Admin>& admins) {
    ofstream file("data_admin.txt");

    if (file.is_open()) {
        for (const auto& admin : admins) {
            file << admin.username << " " << admin.password << endl;
        }
        file.close();
    } else {
        cout << "Gagal membuka file untuk menyimpan data admin.\n";
    }
}

vector<Admin> tambah_admin(vector<Admin> admins) {
    cout << endl << "Akun Admin Baru: " << endl;
    string usernameBaru, passwordBaru;
    cout << "Username admin baru: ";
    cin >> usernameBaru;
    cout << "Password admin baru: ";
    cin >> passwordBaru;

    bool ada = false;
    for (const auto& admin : admins) {
        if (admin.username == usernameBaru) {
            ada = true;
            break;
        }
    }

    if (!ada) {
        admins.push_back({usernameBaru, passwordBaru});
        cout << "Admin baru berhasil ditambahkan!\n";
    } else {
        cout << "Gagal menambahkan admin. Username sudah ada.\n";
    }
    simpanDataAdmin(admins);

    return admins;
}

int cariBarang(const vector<BarangInventaris>& inventaris, const string& namaCari) {
    for (size_t i = 0; i < inventaris.size(); i++) {
        if (inventaris[i].namaBarang == namaCari) {
            return i;  // Mengembalikan indeks barang yang ditemukan
        }
    }
    return -1;  // Mengembalikan -1 jika barang tidak ditemukan
}

void pencarian(const vector<BarangInventaris>& inventaris) {
    string cariBrg;
    cout << "Masukkan nama barang yang ingin dicari: ";
    cin.ignore();
    getline(cin, cariBrg);

    int indeks = cariBarang(inventaris, cariBrg);
    if (indeks != -1) {
        cout << "Barang ditemukan di rak: " << indeks + 1 << endl;
        cout << "Detail Barang: " << inventaris[indeks].namaBarang << ", "
             << inventaris[indeks].jumlahBarang << ", " << inventaris[indeks].hargaBarang << endl;
    } else {
        cout << "Barang tidak ditemukan" << endl;
    }
}

void tampilkanInventaris(const vector<BarangInventaris>& inventaris) {
    cout << "\nList Barang Tersedia di Gudang:\n";
    cout << "-----------------------------------------------------------\n";
    cout << "No. | Nama         | Jumlah | Harga\n";
    cout << "-----------------------------------------------------------\n";

    for (size_t i = 0; i < inventaris.size(); i++) {
        cout << setw(3) << i + 1 << "  | " << setw(12) << inventaris[i].namaBarang << " | "
             << setw(6) << inventaris[i].jumlahBarang << " | " << inventaris[i].hargaBarang << endl;
    }

    cout << "-----------------------------------------------------------\n";
}

void DeQueue(vector<BarangInventaris>& inventaris) {
    if (inventaris.empty()) {
        cout << "Antrian Kosong!" << endl;
    } else {
        cout << "Barang yang keluar: " << inventaris.front().namaBarang << ", "
             << inventaris.front().jumlahBarang << ", " << inventaris.front().hargaBarang << endl;

        inventaris.erase(inventaris.begin());

        cout << "Barang berhasil dikeluarkan dari gudang.\n";
    }
}

void tambahdataBarang(vector<BarangInventaris>& inventaris) {
    cout << "Barang yang ingin dimasukkan berjumlah : ";
    int brng;
    cin >> brng;

    for (int i = 0; i < brng; i++) {
        BarangInventaris barang;
        cout << "Masukkan nama barang : ";
        cin.ignore();
        getline(cin, barang.namaBarang);
        cout << "Jumlah barang : ";
        cin >> barang.jumlahBarang;
        cout << "Harga barang : ";
        cin >> barang.hargaBarang;

        inventaris.push_back(barang);
    }
}

int main() {
    vector<Admin> admins = bacaDataAdmin();
    vector<BarangInventaris> inventaris = {
        {"Ciki Taro", 100, 1500},
        {"Tango", 95, 4500},
        {"Beng-beng", 40, 1500},
        {"Momogi", 60, 1000}
    };

    cout << "\n=== Selamat Datang di Aplikasi Manajemen Inventaris Gudang CV. Sumber Snack ===\n\n";
    cout << "Tentang Perusahaan" << endl;
    cout << "CV. Sumber Snack merupakan badan usaha yang berfokus pada penjualan makanan ringan" << endl;
    cout << "Tahun berdiri: 2015" << endl;

    int percobaanLogin = 3;
    bool isAdmin = false;

    cout << endl << "Silahkan Login Terlebih Dahulu" << endl;
    while (percobaanLogin > 0) {
        string usernameInput, passwordInput;
        cout << endl;
        cout << "Username: ";
        cin >> usernameInput;
        cout << "Password: ";
        cin >> passwordInput;

        for (const auto& admin : admins) {
            if (admin.username == usernameInput && admin.password == passwordInput) {
                isAdmin = true;
                cout << "Login berhasil!\n";
                cout << endl << "Hai! " << admin.username << endl;
                percobaanLogin = 0; // Login berhasil, set percobaanLogin ke 0 untuk keluar dari loop
                break;
            }
        }

        if (!isAdmin) {
            percobaanLogin--;
            if (percobaanLogin > 0) {
                cout << "Login gagal. Sisa kesempatan login: " << percobaanLogin << endl;
            } else {
                cout << "Proses login gagal. Program selesai.\n";
                return 0;
            }
        }
    }

    char lanjut;

    do {
        cout << endl << "List Menu Aplikasi: " << endl;
        cout << "1. Tambah Admin Baru" << endl;
        cout << "2. Tampilkan List Produk" << endl;
        cout << "3. Menambah Data Produk" << endl;
        cout << "4. Pencarian Manual Data Produk" << endl;
        cout << "5. Hapus Data Produk" << endl;
        int pilihan;
        cout << "Masukkan Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                admins = tambah_admin(admins);
                break;
            case 2:
                tampilkanInventaris(inventaris);
                break;
            case 3:
                tambahdataBarang(inventaris);
                break;
            case 4:
                pencarian(inventaris);
                break;
            case 5:
                DeQueue(inventaris);
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

        cout << endl << "Ingin memilih menu lain? (y/n): ";
        cin >> lanjut;

        if (lanjut != 'y' && lanjut != 'Y') {
            break;
        }
    } while (true);

    return 0;
}
