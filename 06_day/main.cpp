#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <bits/stdc++.h> // Needed for unordered_set<std::string>

void readData(std::vector<std::vector<std::string>> &groupAnswers) {
    
    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName);
    std::string str;
    std::vector<std::string>  answers;

    if (inFile.is_open()) {
        
        while(inFile >> str) {

            if (str.empty()) {
                groupAnswers.push_back(answers);
                answers.clear();
            } else {
                answers.push_back(str);
            }
        }

    } else {
        std::cerr << "Could not find input file." << std::endl;
    }

    if (!answers.empty()) {
        groupAnswers.push_back(answers);
    }
}

void distinctValuesPerGroup(std::vector<std::vector<std::string>> &groupAnswers, std::vector<std::unordered_set<std::string>> &uniqueYesAnswers) {
    
    std::unordered_set<std::string> groupYesAnswers;
    for (const auto& personAnswer : groupAnswers) {
        for (const auto& answer: personAnswer) {
            groupYesAnswers.insert(answer);
        }

        // Add the group 
        uniqueYesAnswers.push_back(groupYesAnswers);
        groupYesAnswers.clear();
    }
}

int main() {
    std::vector<std::vector<std::string>> groupAnswers;
    std::vector<std::unordered_set<std::string>> uniqueYesAnswers;

    readData(groupAnswers);

    distinctValuesPerGroup(groupAnswers, uniqueYesAnswers);

    return 0;
}