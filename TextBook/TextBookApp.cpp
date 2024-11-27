#include <iostream>
#include <vector>
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

int main() {
    try {

        ifstream textbookFile("textbooks.txt");
        if (!textbookFile) {
            cerr << "Error: Could not open textbooks.txt for reading!" << endl;
            return 1; 
        }

        ifstream distributorFile("distributors.txt");
        if (!distributorFile) {
            cerr << "Error: Could not open distributors.txt for reading!" << endl;
            return 1;
        }

        ofstream orderFile("orders.txt");


        vector<Textbook> textbooks;
        vector<Distributor> distributors;
        vector<Order> orders;

        if (textbookFile) {
            while (!textbookFile.eof()) {
                Textbook t;
                t.loadFromFile(textbookFile);
                if (!textbookFile.eof()) textbooks.push_back(t);
            }
        }
        if (distributorFile) {
            while (!distributorFile.eof()) {
                Distributor d;
                d.loadFromFile(distributorFile);
                if (!distributorFile.eof()) distributors.push_back(d);
            }
        }

        int choice;
        while (true) {
            cout << "Menu:\n1. Add Textbook\n2. Add Distributor\n3. Create Order\n4. Exit\nEnter choice: ";
            cin >> choice;
            if (choice == 1) {
                string title, author, isbn, releaseDate;
                int edition, copies;
                double price;

                cout << "Enter title: ";
                cin.ignore();
                getline(cin, title);

                cout << "Enter author: ";
                getline(cin, author);

                cout << "Enter edition: ";
                cin >> edition;

                cout << "Enter ISBN (format: XXX-XXX-XXX): ";
                cin >> isbn;

                cout << "Enter release date (YYYY-MM-DD): ";
                cin >> releaseDate;

                cout << "Enter number of copies: ";
                cin >> copies;

                cout << "Enter price: ";
                cin >> price;

                textbooks.push_back(Textbook(title, author, edition, isbn, releaseDate, copies, price));
                cout << "Textbook added successfully.\n";
            }
            else if (choice == 2) {
                string name, address, phone;

                cout << "Enter distributor name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter distributor address: ";
                getline(cin, address);

                cout << "Enter distributor phone: ";
                getline(cin, phone);

                distributors.push_back(Distributor(name, address, phone));
                cout << "Distributor added successfully.\n";
            }
            else if (choice == 3) {
                if (distributors.empty()) {
                    cout << "No distributors available.\n";
                    continue;
                }
                if (textbooks.empty()) {
                    cout << "No textbooks available.\n";
                    continue;
                }
                cout << "Available Distributors:\n";
                for (size_t i = 0; i < distributors.size(); ++i) {
                    cout << i + 1 << ". " << distributors[i].getName() << "\n";
                }
                int distributorIndex;
                cout << "Select a distributor: ";
                cin >> distributorIndex;
                if (distributorIndex < 1 || distributorIndex > distributors.size()) {
                    cout << "Invalid distributor.\n";
                    continue;
                }
                Order order(distributors[distributorIndex - 1]);
                cout << "Available Textbooks:\n";
                for (size_t i = 0; i < textbooks.size(); ++i) {
                    cout << i + 1 << ". " << textbooks[i].getTitle() << " ($" << textbooks[i].getPrice() << ")\n";
                }
                cout << "Enter indexes of textbooks to order (0 to finish):\n";
                int textbookIndex;
                while (cin >> textbookIndex && textbookIndex != 0) {
                    if (textbookIndex < 1 || textbookIndex > textbooks.size()) {
                        cout << "Invalid textbook.\n";
                        continue;
                    }
                    order.addTextbook(textbooks[textbookIndex - 1]);
                }
                order.displayOrder();

                order.saveToFile(orderFile);

            }
            else if (choice == 4) {
                break;
            }
        }

        ofstream textbookSaveFile("textbooks.txt");
        for (const auto& textbook : textbooks) {
            textbook.saveToFile(textbookSaveFile);
        }
        textbookSaveFile.close();

        ofstream distributorSaveFile("distributors.txt");
        for (const auto& distributor : distributors) {
            distributor.saveToFile(distributorSaveFile);
        }
        distributorSaveFile.close();

        orderFile.close();

        cout << "Data saved successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
