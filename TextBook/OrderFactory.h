#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "Distributor.h"
#include "TextBook.h"
#include "InputHelper.h"
#include "Order.h"
using namespace std;

class OrderFactory {
public:
    static Order createOrder(const vector<Distributor>& distributors, vector<Textbook>& textbooks) {
        if (distributors.empty()) {
            throw runtime_error("No distributors available.");
        }
        if (textbooks.empty()) {
            throw runtime_error("No textbooks available.");
        }

        cout << "Available Distributors:\n";
        for (size_t i = 0; i < distributors.size(); ++i) {
            cout << i + 1 << ". " << distributors[i].getName() << "\n";
        }

        int distributorIndex = InputHelper::getIntInput("Select a distributor (by index): ");
        while (distributorIndex < 1 || distributorIndex > distributors.size()) {
            cout << "Error: Invalid distributor index.\n";
            distributorIndex = InputHelper::getIntInput("Select a distributor (by index): ");
        }

        Order order(distributors[distributorIndex - 1]);

        cout << "Available Textbooks:\n";
        for (size_t i = 0; i < textbooks.size(); ++i) {
            cout << i + 1 << ". " << textbooks[i].getTitle() << " ($" << textbooks[i].getPrice() << ")\n";
        }

        cout << "Enter indexes of textbooks to order (0 to finish):\n";
        int textbookIndex;
        while (true) {
            textbookIndex = InputHelper::getIntInput("Enter textbook index: ");
            if (textbookIndex == 0) break;

            if (textbookIndex < 1 || textbookIndex > textbooks.size()) {
                cout << "Error: Invalid textbook index.\n";
                continue;
            }

            int quantity = InputHelper::getIntInput("Enter quantity: ");
            try {
                textbooks[textbookIndex - 1].decreaseCopies(quantity);
                order.addTextbook(textbooks[textbookIndex - 1]);

                cout << "Textbook added to order sucessfully you can press 0 to finish.\n";
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        }

        return order;
    }
};
