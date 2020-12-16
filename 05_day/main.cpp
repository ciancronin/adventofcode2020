#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <bits/stdc++.h>

void readData(std::vector<std::string> &data) {
    // Read the data
    std::string inFileName = "data.txt";
    std::ifstream inFile;
    inFile.open(inFileName);
    std::string str;

    if (inFile.is_open()) {
        while (getline(inFile, str)) {
            // Read each line into the vector
            data.push_back(str);
        }
    } else {
        std::cerr << "File not found" << std::endl;
    }
}

void getSeatIds(std::vector<std::string> &data, std::vector<int> &seatIds) {

    // Loop over all of the boarding passes
    for (const auto& line: data) {

        // Init the row and seat possible values
        int startRow = 0;
        int endRow = 127;
        int startSeat = 0;
        int endSeat = 7;
        // Loop over all characters within that boarding pass
        // and calculate their final seating positions
        for (const auto& character: line) {
            if (character == 'F') {
                endRow = ((startRow + endRow + 1) / 2) - 1;
            } else if (character == 'B') {
                startRow = ((startRow + endRow + 1) / 2);
            } else if (character == 'L') {
                endSeat = ((startSeat + endSeat + 1) / 2) - 1;
            } else if (character == 'R') {
                startSeat = ((startSeat + endSeat + 1) / 2);
            } else {
                std::cerr << "Unexpected character in input file" << std::endl;
            }
        }
        
        // Calculate the seatId as ((row * 8) * seat)
        // Note startRow = endRow and startSeat = endSeat for all plane tickets
        int seatId = (startRow * 8) + startSeat;

        // Push element into the seatIds vector
        seatIds.push_back(seatId);
    }
}

int maxSeatId(std::vector<int> &seatIds) {
    
    int max = 0;
    // Loop over the seatId values to get the max seatId
    for (const auto& seatId: seatIds) {
        if (max < seatId)
            max = seatId;
    }

    return max;
}

int getYourSeatId(std::vector<int> &seatIds, std::vector<int> &missingSeatIds) {
    std::set<int> seatIdsOrdered;
    int yourSeatId = 0;

    // Get an ordered set of seatIds
    for (const auto& seatId: seatIds) {
        seatIdsOrdered.insert(seatId);
    }

    int previousSeatId = 83; // Starting at the minumum available seatId
    // Find missing Ids not in start or back of plane
    for (const auto& orderedSeatId: seatIdsOrdered) {

        // The expected seat id is the next one`
        int expectedSeatId = ++previousSeatId;

        // If the expected seat id is not found then mark it as your seat
        if (orderedSeatId != expectedSeatId)
            yourSeatId = expectedSeatId;
        // Overwrite the previousSeatId with the ordered seat id
        previousSeatId = orderedSeatId;
    }

    return yourSeatId;
}

int main() {
    std::vector<std::string> data;
    std::vector<int> seatIds;
    std::vector<int> missingSeatIds;

    readData(data);

    getSeatIds(data, seatIds);

    int maxId = maxSeatId(seatIds);

    // Answer to part one
    // std::cout << "The max seatId value is: " << maxId << std::endl;

    int yourSeat = getYourSeatId(seatIds, missingSeatIds);

    // Answer to part two
    std::cout << "Your seatId is: "<< yourSeat << std::endl;

    
}