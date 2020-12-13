#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void answerQuestions() {

    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName);
    std::string str;

    int noOfTrees[] = {0, 0, 0, 0, 0};

    if(inFile.is_open()) {

        int hPos = 0;
        while(std::getline(inFile, str)) {

            if (str.empty()) break;
            int lineLength = str.length();

            // If the hPos is a tree, increase noOfTree count
            if (str[hPos % lineLength] == '#') noOfTrees[0]++;
            if (str[(hPos * 3) % lineLength] == '#') noOfTrees[1]++;
            if (str[(hPos * 5) % lineLength] == '#') noOfTrees[2]++;
            if (str[(hPos * 7) % lineLength] == '#') noOfTrees[3]++;
            if (str[(hPos / 2) % lineLength] == '#' && hPos % 2 == 0) noOfTrees[4]++; // Divide by 2 due to 2 hPos skip

            // Move the next hPos trackers over
            hPos++;
        }
    } else {
        std::cerr << "Data file not found." << std::endl;
    }

    int64_t product{1}; // Overflow on an unsigned int
    for (int i : noOfTrees) {std::cout << i << "\n"; product *= i;}

    std::cout << "Product: " << product << std::endl;

}

int main() {
    answerQuestions();

    return 0;
}