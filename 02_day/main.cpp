#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void ReadAndParseStringLocations(std::vector<int> &firstNumber, std::vector<int> &secondNumber, std::vector<char> &character, std::vector<std::string> &password) {

    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName.c_str());
    std::string str;

    if (inFile.is_open()) {

        int dashLoc;
        int spaceLoc;
        // int colonLoc;
        while (getline(inFile, str)) {
            dashLoc = str.find("-");
            spaceLoc = str.find(" ");
            // colonLoc = str.find(":");

            firstNumber.push_back(stoi(str.substr(0, dashLoc)));
            secondNumber.push_back(stoi(str.substr((dashLoc + 1), spaceLoc)));
            character.push_back((char)str.substr((spaceLoc + 1), 1)[0]);
            password.push_back(str.substr((spaceLoc + 4), str.length()));

            // std::cout << stoi(str.substr(0, dashLoc)) << " - " << stoi(str.substr((dashLoc + 1), spaceLoc)) << " - " << str.substr((spaceLoc + 1), 1) << " - " << str.substr((spaceLoc + 4), str.length()) << std::endl;
        }

        inFile.close(); // Close the input data file.
    }
    else {
        std::cerr << "Can't find input data file." << std::endl;
    }
}

int CheckPasswords(std::vector<int> &firstNumber, std::vector<int> &secondNumber, std::vector<char> &character, std::vector<std::string> &password) {

    int validPasswords = 0;

    int n1;
    int n2;
    char c;
    for (int i = 0; i < password.size(); i++) {
        n1 = firstNumber[i] - 1; // To take into account index 0
        n2 = secondNumber[i] - 1; // To take into account index 0
        c = character[i];

        if (password[i][n1] == c && password[i][n2] != c) validPasswords++;
        else if (password[i][n1] != c && password[i][n2] == c) validPasswords++;

    }
    return validPasswords;
}

int main() {

    // Initialising string parsed output arrays
    std::vector<int> firstNumber;
    std::vector<int> secondNumber;
    std::vector<char> character;
    std::vector<std::string> password;

    // Read the data input file and get relevant data points
    ReadAndParseStringLocations(firstNumber, secondNumber, character, password);

    // Calculate the number of valid passwords
    int validPasswords = CheckPasswords(firstNumber, secondNumber, character, password);

    // Print out the number of valid passwords
    std::cout << validPasswords << std::endl;
}