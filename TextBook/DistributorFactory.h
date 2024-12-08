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
#include "InputHelper.h"
using namespace std;

class DistributorFactory {
public:
    static Distributor createDistributor() {
        string name = InputHelper::getStringInput("Enter distributor name: ");
        string address = InputHelper::getStringInput("Enter distributor address: ");
        string phone = InputHelper::getStringInput("Enter distributor phone: ");
        return Distributor(name, address, phone);
    }
};

