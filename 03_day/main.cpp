#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void readData(std::vector<std::string> &data) {

    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName);
    std::string str;

    if(inFile.is_open()) {

        while(getline(inFile, str)) {
            // Do Something
        }
    } else {
        std::cerr << "Data file not found." << std::endl;
    }

}

int main() {
    // open squares (.) and trees (#)
}