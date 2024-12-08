#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include "TextBook.h"
#include "Distributor.h"
#include "Order.h"
#include "TextbookFactory.h"
#include "DistributorFactory.h"
#include "OrderFactory.h"

using namespace std;

int main() {
    try {
        ifstream textbookFile("textbooks.txt");
        ifstream distributorFile("distributors.txt");
        ofstream orderFile("orders.txt");

        vector<Textbook> textbooks;
        vector<Distributor> distributors;
        vector<Order> orders;

        // Load textbooks from file
        if (textbookFile) {
            while (!textbookFile.eof()) {
                Textbook t;
                t.loadFromFile(textbookFile);
                if (!textbookFile.eof()) textbooks.push_back(t);
            }
        }

        // Load distributors from file
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
            cin.ignore(); // Clear the input buffer

            if (choice == 1) {
                try {
                    Textbook newTextbook = TextbookFactory::createTextbook();
                    textbooks.push_back(newTextbook);
                    cout << "Textbook added successfully.\n";
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }
            else if (choice == 2) {
                try {
                    Distributor newDistributor = DistributorFactory::createDistributor();
                    distributors.push_back(newDistributor);
                    cout << "Distributor added successfully.\n";
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }
            else if (choice == 3) {
                try {
                    Order newOrder = OrderFactory::createOrder(distributors, textbooks);
                    orders.push_back(newOrder);
                    newOrder.displayOrder();
                    newOrder.saveToFile(orderFile);
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }
            else if (choice == 4) {
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }

        // Save textbooks to file
        ofstream textbookSaveFile("textbooks.txt");
        for (const auto& textbook : textbooks) {
            textbook.saveToFile(textbookSaveFile);
        }

        // Save distributors to file
        ofstream distributorSaveFile("distributors.txt");
        for (const auto& distributor : distributors) {
            distributor.saveToFile(distributorSaveFile);
        }

        cout << "Data saved successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}