#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <iomanip>
using namespace std;

class Textbook {
private:
    string title;
    string author;
    int edition;
    string isbn;
    string releaseDate;
    int copies;
    bool approved;
    string approvalDate;
    double price;

    bool validateISBN(const string& isbn) const {
        regex pattern("\\d{3}-\\d{3}-\\d{3}");
        return regex_match(isbn, pattern);
    }

    bool validateDate(const string& date) const {
        regex pattern("\\d{4}-\\d{2}-\\d{2}");
        return regex_match(date, pattern);
    }

public:
    Textbook() : edition(0), copies(0), approved(false), price(0.0) {}

    Textbook(string t, string a, int e, string i, string r, int c, double p)
        : title(t), author(a), edition(e), isbn(i), releaseDate(r), copies(c), price(p), approved(false) {
        if (t.empty() || a.empty()) throw invalid_argument("Title and author cannot be empty.");
        if (!validateISBN(i)) throw invalid_argument("Invalid ISBN format. Use XXX-XXX-XXX.");
        if (e <= 0) throw invalid_argument("Edition must be positive.");
        if (p <= 0) throw invalid_argument("Price must be positive.");
    }

    string getTitle() const { return title; }
    void setTitle(const string& t) { if (t.empty()) throw invalid_argument("Title cannot be empty."); title = t; }

    string getAuthor() const { return author; }
    void setAuthor(const string& a) { if (a.empty()) throw invalid_argument("Author cannot be empty."); author = a; }

    int getEdition() const { return edition; }
    void setEdition(int e) { if (e <= 0) throw invalid_argument("Edition must be positive."); edition = e; }

    string getISBN() const { return isbn; }
    void setISBN(const string& i) { if (!validateISBN(i)) throw invalid_argument("Invalid ISBN format. Use XXX-XXX-XXX."); isbn = i; }

    string getReleaseDate() const { return releaseDate; }
    void setReleaseDate(const string& r) { if (!validateDate(r)) throw invalid_argument("Invalid date format. Use YYYY-MM-DD."); releaseDate = r; }

    int getCopies() const { return copies; }
    void setCopies(int c) { if (c < 0) throw invalid_argument("Copies cannot be negative."); copies = c; }

    bool isApproved() const { return approved; }
    void approve(const string& date) {
        if (!validateDate(date)) throw invalid_argument("Invalid date format. Use YYYY-MM-DD.");
        approved = true;
        approvalDate = date;
    }

    string getApprovalDate() const { return approvalDate; }
    double getPrice() const { return price; }
    void setPrice(double p) { if (p <= 0) throw invalid_argument("Price must be positive."); price = p; }

    friend ostream& operator<<(ostream& os, const Textbook& t) {
        os << "Title: " << t.title << "\n"
            << "Author: " << t.author << "\n"
            << "Edition: " << t.edition << "\n"
            << "ISBN: " << t.isbn << "\n"
            << "Release Date: " << t.releaseDate << "\n"
            << "Copies: " << t.copies << "\n"
            << "Approved: " << (t.approved ? "Yes" : "No") << "\n"
            << "Approval Date: " << (t.approved ? t.approvalDate : "N/A") << "\n"
            << fixed << setprecision(2) << "Price: $" << t.price;
        return os;
    }

    void saveToFile(ofstream& out) const {
        out << title << "\n" << author << "\n" << edition << "\n" << isbn << "\n"
            << releaseDate << "\n" << copies << "\n" << approved << "\n"
            << approvalDate << "\n" << price << "\n";
    }

    void loadFromFile(ifstream& in) {
        getline(in, title);
        getline(in, author);
        in >> edition;
        in.ignore();
        getline(in, isbn);
        getline(in, releaseDate);
        in >> copies;
        in.ignore();
        in >> approved;
        in.ignore();
        getline(in, approvalDate);
        in >> price;
        in.ignore();
    }

    void decreaseCopies(int quantity) {
        if (quantity > copies) throw invalid_argument("Not enough copies available.");
        copies -= quantity;
    }
};
