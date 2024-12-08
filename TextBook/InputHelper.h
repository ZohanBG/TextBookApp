#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>
#include <fstream>
#include <iomanip>
#include "Distributor.h"
#include "TextBook.h"
using namespace std;

class InputHelper {
public:
    static string getStringInput(const string& prompt, const string& errorMessage = "Input cannot be empty.") {
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);
            if (!input.empty()) return input;
            cout << "Error: " << errorMessage << "\n";
        }
    }

    static int getIntInput(const string& prompt, const string& errorMessage = "Invalid integer. Please try again.") {
        int input;
        while (true) {
            cout << prompt;
            if (cin >> input) {
                cin.ignore();
                return input;
            }
            cout << "Error: " << errorMessage << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static double getDoubleInput(const string& prompt, const string& errorMessage = "Invalid number. Please try again.") {
        double input;
        while (true) {
            cout << prompt;
            if (cin >> input) {
                cin.ignore();
                return input;
            }
            cout << "Error: " << errorMessage << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static string getRegexValidatedInput(const string& prompt, const regex& pattern, const string& errorMessage) {
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);
            if (regex_match(input, pattern)) return input;
            cout << "Error: " << errorMessage << "\n";
        }
    }
};
