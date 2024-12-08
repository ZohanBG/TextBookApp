#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include "Distributor.h"
#include "TextBook.h"
using namespace std;

class Order {
private:
    Distributor distributor;
    vector<Textbook> textbooks;

public:
    Order(const Distributor& d) : distributor(d) {}

    void addTextbook(Textbook& textbook, int quantity) {
        if (textbook.getCopies() >= quantity) {
            textbooks.push_back(textbook);
            textbook.decreaseCopies(quantity);
        }
        else {
            throw invalid_argument("Not enough copies of the textbook.");
        }
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& textbook : textbooks) {
            total += textbook.getPrice();
        }
        return total;
    }

    void displayOrder() const {
        cout << "Distributor:\n" << distributor << "\n\nTextbooks:\n";
        for (const auto& textbook : textbooks) {
            cout << textbook << "\n\n";
        }
        cout << "Total Price: $" << fixed << setprecision(2) << calculateTotal() << "\n";
    }

    void saveToFile(ofstream& out) const {
        distributor.saveToFile(out);
        out << textbooks.size() << "\n";
        for (const auto& textbook : textbooks) {
            textbook.saveToFile(out);
        }
    }

    void loadFromFile(ifstream& in) {
        distributor.loadFromFile(in);
        size_t numTextbooks;
        in >> numTextbooks;
        in.ignore();
        textbooks.clear();
        for (size_t i = 0; i < numTextbooks; ++i) {
            Textbook t;
            t.loadFromFile(in);
            textbooks.push_back(t);
        }
    }

    void addTextbook(const Textbook& textbook) {
        textbooks.push_back(textbook);
    }
};
