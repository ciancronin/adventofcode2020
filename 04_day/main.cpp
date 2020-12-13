#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <bits/stdc++.h> // for unordered set

void readData(std::vector<std::vector<std::string>> &passportData) {

    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName.c_str());
    std::string line;
    std::string keyVal;

    // For part one
    std::unordered_set<std::string> fields;
    int fieldsPresentCount = 0;

    if(inFile.is_open()) {

        std::vector<std::string> passport;
        while(getline(inFile, line)) {
            
            // Iterate over a line to get the keyVal pairings for a single passport
            if (line.empty()) {
                passportData.push_back(passport); // Push back the passport into the vector
                passport.clear(); // Clear the passport for the next one

                // For counting the number of valid passports in part one
                if (fields.size() == 7) {
                    fieldsPresentCount++;
                    fields.clear();
                }
            } else {
                std::istringstream iss(line); // Put into a istringstream to iterate over each 'word' for each passport
                while (iss >> keyVal) {
                    passport.push_back(keyVal);

                    // If not equal to "cid" then add to fields set
                    if (keyVal.substr(0, 3) != "cid") {
                        fields.insert(keyVal.substr(0, 3));
                    }
                }
            }
        }

        // Remember to add back in the final line because the file doesn't end on a newline.
        // I don't want to admit how long it took me to debug this...
        passportData.push_back(passport);
        if (fields.size() == 7) {
            fieldsPresentCount++;
            fields.clear();
        }
    }

    std::cout << "Passports with valid fields: " << fieldsPresentCount << std::endl;
}

void passportValuesCheck(std::vector<std::vector<std::string>> &passportData) {

    int validPassports = 0;
    std::unordered_set<std::string> fields;
    int fieldsPresentCount = 0;

    const std::regex regex("([a-zA-Z0-9_]+):([^\r\n\t\f\v ]+)");

    for (int i = 0; i < passportData.size(); i++) {
        
        bool validPassport = true; // if this is set to false at all, then validPassport is not counted
        for (int j = 0; j < passportData[i].size(); j++) {

            if (passportData[i][j].substr(0, 3) == "byr") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                if (!(value.length() == 4 && std::stoi(value) >= 1920 &&
                    std::stoi(value) <= 2002)) validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) == "iyr") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                if (!(value.length() == 4 && std::stoi(value) >= 2010 &&
                    std::stoi(value) <= 2020)) validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) == "eyr") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                if (!(value.length() == 4 && std::stoi(value) >= 2020 &&
                    std::stoi(value) <= 2030)) validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) == "hgt") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                std::smatch match;
                if (regex_match(value.cbegin(), value.cend(), match, std::regex("([0-9]+)(cm|in)"))) {
                    if (match[2].str() == "cm")
                        if (!(std::stoi(match[1].str()) >= 150 &&
                            std::stoi(match[1].str()) <= 193)) validPassport = false;
                    else if (match[2].str() == "in")
                        if (!(std::stoi(match[1].str()) >= 59 &&
                            std::stoi(match[1].str()) <= 76)) validPassport = false;
                    else validPassport = false;
                }
                else validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) == "hcl") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                if (!(regex_match(value.cbegin(), value.cend(), std::regex("#([0-9]|[a-f]){6}+")))) validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) == "ecl") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                const std::vector<std::string> valid_values{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
                if (std::find(valid_values.begin(), valid_values.end(), value) == valid_values.end()) validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) == "pid") {
                std::string value = passportData[i][j].substr(4, passportData[i][j].length());
                if (!(regex_match(value.cbegin(), value.cend(), std::regex("[0-9]{9}+")))) validPassport = false;
            }
            if (passportData[i][j].substr(0, 3) != "cid") {
                fields.insert(passportData[i][j].substr(0, 3));
            }
        }

        if (validPassport) {
            if (fields.size() == 7) {
                validPassports++;
            }
        }
    }

    std::cout << "Number of Passports with valid fields: " << validPassports << std::endl;
}

int main() {

    // Reference for the first part:
    // byr (Birth Year)
    // iyr (Issue Year)
    // eyr (Expiration Year)
    // hgt (Height)
    // hcl (Hair Color)
    // ecl (Eye Color)
    // pid (Passport ID)
    // cid (Country ID)

    std::vector<std::vector<std::string>> passportData;

    readData(passportData);

    // Reference for teh second part:
    // byr (Birth Year) - four digits; at least 1920 and at most 2002.
    // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    // hgt (Height) - a number followed by either cm or in:
    // If cm, the number must be at least 150 and at most 193.
    // If in, the number must be at least 59 and at most 76.
    // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
    // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    // pid (Passport ID) - a nine-digit number, including leading zeroes.
    // cid (Country ID) - ignored, missing or not.

    passportValuesCheck(passportData);

    return 0;
}