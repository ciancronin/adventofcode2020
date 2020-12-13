
#include <iostream>
#include <fstream>
#include <string>

void ReadData(int* dataInput, int inputSize = 200) {

    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName.c_str());

    if (inFile.is_open()) {

        for (int i = 0; i < inputSize; i++) {

            inFile >> dataInput[i];
        }

        inFile.close(); // Close the input data file.
    }
    else {
        std::cerr << "Can't find input data file." << std::endl;
    }
}

int main() {

    int size = 200;
    int dataInput[size];

    ReadData(dataInput);

    int firstNumber;
    int secondNumber;
    int thirdNumber;

    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {

            for (int k = 0; k < size; k++) {

                if (((dataInput[i] + dataInput[j] + dataInput[k]) == 2020) && (i != j) && (i != k) && (j != k)) {
                    firstNumber = dataInput[i];
                    secondNumber = dataInput[j];
                    thirdNumber = dataInput[k];
                }
            }

            
        }
    }

    std::cout << "First number is: " << firstNumber << std::endl;
    std::cout << "Second number is: " << secondNumber << std::endl;
    std::cout << "Third number is: " << thirdNumber << std::endl;

    std::cout << "Their multiplication is: " << (firstNumber * secondNumber * thirdNumber) << std::endl;

    return 0;
}