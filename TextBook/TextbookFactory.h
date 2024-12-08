#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include "TextBook.h"
#include "InputHelper.h"
using namespace std;

class TextbookFactory {
public:
    static Textbook createTextbook() {
        string title = InputHelper::getStringInput("Enter title: ");
        string author = InputHelper::getStringInput("Enter author: ");
        int edition = InputHelper::getIntInput("Enter edition (positive integer): ",
            "Edition must be a positive integer.");
        string isbn = InputHelper::getRegexValidatedInput(
            "Enter ISBN (format: XXX-XXX-XXX): ",
            regex("\\d{3}-\\d{3}-\\d{3}"),
            "Invalid ISBN format. Use XXX-XXX-XXX."
        );
        string releaseDate = InputHelper::getRegexValidatedInput(
            "Enter release date (YYYY-MM-DD): ",
            regex("\\d{4}-\\d{2}-\\d{2}"),
            "Invalid date format. Use YYYY-MM-DD."
        );
        int copies = InputHelper::getIntInput("Enter number of copies (non-negative integer): ",
            "Copies must be a non-negative integer.");
        double price = InputHelper::getDoubleInput("Enter price (positive number): ",
            "Price must be a positive number.");

        return Textbook(title, author, edition, isbn, releaseDate, copies, price);
    }
};
