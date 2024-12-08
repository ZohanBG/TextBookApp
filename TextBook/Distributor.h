#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <iomanip>
using namespace std;


class Distributor {
private:
    string name;
    string address;
    string phone;

public:
    Distributor() = default;
    Distributor(string n, string a, string p) : name(n), address(a), phone(p) {
        if (n.empty() || a.empty() || p.empty()) throw invalid_argument("Distributor details cannot be empty.");
    }

    string getName() const { return name; }
    void setName(const string& n) { if (n.empty()) throw invalid_argument("Name cannot be empty."); name = n; }

    string getAddress() const { return address; }
    void setAddress(const string& a) { if (a.empty()) throw invalid_argument("Address cannot be empty."); address = a; }

    string getPhone() const { return phone; }
    void setPhone(const string& p) { if (p.empty()) throw invalid_argument("Phone cannot be empty."); phone = p; }

    friend ostream& operator<<(ostream& os, const Distributor& d) {
        os << "Distributor Name: " << d.name << "\n"
            << "Address: " << d.address << "\n"
            << "Phone: " << d.phone;
        return os;
    }

    void saveToFile(ofstream& out) const {
        out << name << "\n" << address << "\n" << phone << "\n";
    }

    void loadFromFile(ifstream& in) {
        getline(in, name);
        getline(in, address);
        getline(in, phone);
    }
};

