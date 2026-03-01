#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Service;

struct Customer {
    string nama;
    int umur;
    string gender;
    string telepon;
    string alamat;
    Service* headService;
    Customer* next;
};

struct Service {
    string model;
    string merek;
    string kendala;
    string montir;
    Customer* customer;
    Service* next;
};

Customer* headCustomer = NULL;
Service* headService = NULL;

// ================= CARI CUSTOMER =================
Customer* cariCustomer(string nama) {
    Customer* temp = headCustomer;
    while (temp != NULL) {
        if (temp->nama == nama) return temp;
        temp = temp->next;
    }
    return NULL;
}


Customer* tambahCustomer(string nama, int umur, string gender, string telepon, string alamat) {
    Customer* baru = new Customer();
    baru->nama = nama;
    baru->umur = umur;
    baru->gender = gender;
    baru->telepon = telepon;
    baru->alamat = alamat;
    baru->headService = NULL;
    baru->next = NULL;

    if (headCustomer == NULL)
        headCustomer = baru;
    else {
        Customer* temp = headCustomer;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }

    return baru;
}


void tambahService(string model, string merek, string kendala, string montir, Customer* cust) {
    Service* baru = new Service();
    baru->model = model;
    baru->merek = merek;
    baru->kendala = kendala;
    baru->montir = montir;
    baru->customer = cust;
    baru->next = NULL;

    if (headService == NULL)
        headService = baru;
    else {
        Service* temp = headService;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }

    if (cust->headService == NULL)
        cust->headService = baru;
    else {
        Service* temp = cust->headService;
        while (temp->next != NULL) temp = temp->next;
        temp->next = baru;
    }
}


void saveData() {
    ofstream fileC("pelanggan.csv");
    Customer* c = headCustomer;
    while (c != NULL) {
        fileC << c->nama << "," << c->umur << "," << c->gender << ","
              << c->telepon << "," << c->alamat << endl;
        c = c->next;
    }
    fileC.close();

    ofstream fileS("servis.csv");
    Service* s = headService;
    while (s != NULL) {
        fileS << s->model << "," << s->merek << "," << s->kendala << ","
              << s->montir << "," << s->customer->nama << endl;
        s = s->next;
    }
    fileS.close();
}


void loadData() {
    ifstream fileC("pelanggan.csv");
    string line;

    while (getline(fileC, line)) {
        if (line == "") continue;
        stringstream ss(line);
        string nama, umurStr, gender, telp, alamat;

        getline(ss, nama, ',');
        getline(ss, umurStr, ',');
        getline(ss, gender, ',');
        getline(ss, telp, ',');
        getline(ss, alamat, ',');

        tambahCustomer(nama, stoi(umurStr), gender, telp, alamat);
    }
    fileC.close();

    ifstream fileS("servis.csv");
    while (getline(fileS, line)) {
        if (line == "") continue;
        stringstream ss(line);
        string model, merek, kendala, montir, nama;

        getline(ss, model, ',');
        getline(ss, merek, ',');
        getline(ss, kendala, ',');
        getline(ss, montir, ',');
        getline(ss, nama, ',');

        Customer* cust = cariCustomer(nama);
        if (cust != NULL)
            tambahService(model, merek, kendala, montir, cust);
    }
    fileS.close();
}


void tampilSemuaServis() {
    Service* temp = headService;

    if (temp == NULL) {
        cout << "Belum ada data servis.\n";
        return;
    }

    while (temp != NULL) {
        cout << "-----------------------\n";
        cout << "Model: " << temp->model << endl;
        cout << "Merek: " << temp->merek << endl;
        cout << "Kendala: " << temp->kendala << endl;
        cout << "Montir: " << temp->montir << endl;
        cout << "Customer: " << temp->customer->nama << endl;
        cout << "-----------------------\n";
        temp = temp->next;
    }
}


void riwayatMontir(string montir) {
    Service* temp = headService;
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->montir == montir) {
            ditemukan = true;
            cout << "-----------------------\n";
            cout << "Model: " << temp->model << endl;
            cout << "Merek: " << temp->merek << endl;
            cout << "Kendala: " << temp->kendala << endl;
            cout << "Customer: " << temp->customer->nama << endl;
            cout << "-----------------------\n";
        }
        temp = temp->next;
    }

    if (!ditemukan)
        cout << "Tidak ada job untuk montir tersebut.\n";
}


void tampilSemuaCustomer() {
    Customer* c = headCustomer;

    if (c == NULL) {
        cout << "Belum ada data customer.\n";
        return;
    }

    while (c != NULL) {
        cout << "-----------------------\n";
        cout << "Nama: " << c->nama << endl;
        cout << "Telepon: " << c->telepon << endl;
        cout << "Alamat: " << c->alamat << endl;
        cout << "-----------------------\n";
        c = c->next;
    }
}


void tampilDetailCustomer() {
    string nama;
    cout << "Masukkan Nama Customer: ";
    getline(cin, nama);

    Customer* c = cariCustomer(nama);

    if (c == NULL) {
        cout << "Customer tidak ditemukan.\n";
        return;
    }

    cout << "\nNama: " << c->nama << endl;
    cout << "Telepon: " << c->telepon << endl;
    cout << "Umur: " << c->umur << endl;
    cout << "Gender: " << c->gender << endl;
    cout << "Alamat: " << c->alamat << endl;

    Service* s = c->headService;
    if (s == NULL) {
        cout << "Belum ada riwayat servis.\n";
        return;
    }

    cout << "\nRiwayat Servis:\n";
    while (s != NULL) {
        cout << "-----------------------\n";
        cout << "Mobil: " << s->model << endl;
        cout << "Kendala: " << s->kendala << endl;
        cout << "Montir: " << s->montir << endl;
        cout << "-----------------------\n";
        s = s->next;
    }
}


int main() {
    loadData();

    int menu;
    do {
        cout << "\n====== Welcome To Lognuts ======\n";
        cout << "1. Servis\n2. Semua Data Pelanggan\n3. Data Pelanggan\n4. Keluar\n";
        cout << "Pilihan: ";
        cin >> menu;
        cin.ignore();

        if (menu == 1) {
            int sub;
            cout << "\n1. Semua Servis\n2. Servis Baru\n3. Riwayat Montir\n";
            cout << "Pilihan: ";
            cin >> sub;
            cin.ignore();

            if (sub == 1) {
                tampilSemuaServis();
            }
            else if (sub == 2) {
                string model, merek, kendala, montir, nama;
                cout << "Model: "; getline(cin, model);
                cout << "Merek: "; getline(cin, merek);
                cout << "Kendala: "; getline(cin, kendala);
                cout << "Montir: "; getline(cin, montir);
                cout << "Nama Customer: "; getline(cin, nama);

                Customer* cust = cariCustomer(nama);

                if (cust == NULL) {
                    string telp, alamat, gender;
                    int umur;
                    cout << "Telepon: "; getline(cin, telp);
                    cout << "Alamat: "; getline(cin, alamat);
                    cout << "Umur: "; cin >> umur; cin.ignore();
                    cout << "Gender: "; getline(cin, gender);
                    cust = tambahCustomer(nama, umur, gender, telp, alamat);
                }

                tambahService(model, merek, kendala, montir, cust);
                saveData();
                cout << "Servis berhasil dicatat.\n";
            }
            else if (sub == 3) {
                string montir;
                cout << "Nama Montir: ";
                getline(cin, montir);
                riwayatMontir(montir);
            }
        }
        else if (menu == 2) {
            tampilSemuaCustomer();
        }
        else if (menu == 3) {
            tampilDetailCustomer();
        }

    } while (menu != 4);

    return 0;
}