#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::vector<std::vector<char>> getInput(std::fstream& inFile);
std::vector<std::string> collectXMASTokens(std::vector<std::vector<char>>& input);
std::vector<std::string> collectX_MASTokens(std::vector<std::vector<char>>& input);

int main(){
    std::fstream inFile("TestData//input.txt");
    if (!inFile.is_open()){
        std::cout << "Error: Unable to open input file.\n";
    }

    std::vector<std::vector<char>> input = getInput(inFile);


    //Input Display:
    std::cout << "Day Four's Input:\n";
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            std::cout << input.at(i).at(j);
        }
        std::cout << std::endl;
    }

    std::vector<std::string> tokens = collectXMASTokens(input);
    std::vector<std::string> masTokens = collectX_MASTokens(input);

    std::cout << "Total Valid Part One Tokens: " << tokens.size() << std::endl;
    std::cout << "Total Valid Part Two Tokens: " << masTokens.size() << std::endl;

    std::cin.get();

    return 0;
}

std::vector<std::string> parseXMASToken(std::vector<std::vector<char>>& input, int row, int col) {
    std::vector<std::string> tokens;

    // If the letter is not 'X', return nothing.
    if (input.at(row).at(col) != 'X') {
        return tokens;
    }

    try {
        // TopLeft
        try {
            if (input.at(row - 1).at(col - 1) == 'M' &&
                input.at(row - 2).at(col - 2) == 'A' &&
                input.at(row - 3).at(col - 3) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "TopLeft out of range: " << e.what() << std::endl;
        }

        // Top
        try {
            if (input.at(row - 1).at(col) == 'M' &&
                input.at(row - 2).at(col) == 'A' &&
                input.at(row - 3).at(col) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "Top out of range: " << e.what() << std::endl;
        }

        // TopRight
        try {
            if (input.at(row - 1).at(col + 1) == 'M' &&
                input.at(row - 2).at(col + 2) == 'A' &&
                input.at(row - 3).at(col + 3) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "TopRight out of range: " << e.what() << std::endl;
        }

        // Left
        try {
            if (input.at(row).at(col - 1) == 'M' &&
                input.at(row).at(col - 2) == 'A' &&
                input.at(row).at(col - 3) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "Left out of range: " << e.what() << std::endl;
        }

        // Right
        try {
            if (input.at(row).at(col + 1) == 'M' &&
                input.at(row).at(col + 2) == 'A' &&
                input.at(row).at(col + 3) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "Right out of range: " << e.what() << std::endl;
        }

        // BottomLeft
        try {
            if (input.at(row + 1).at(col - 1) == 'M' &&
                input.at(row + 2).at(col - 2) == 'A' &&
                input.at(row + 3).at(col - 3) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "BottomLeft out of range: " << e.what() << std::endl;
        }

        // Bottom
        try {
            if (input.at(row + 1).at(col) == 'M' &&
                input.at(row + 2).at(col) == 'A' &&
                input.at(row + 3).at(col) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "Bottom out of range: " << e.what() << std::endl;
        }

        // BottomRight
        try {
            if (input.at(row + 1).at(col + 1) == 'M' &&
                input.at(row + 2).at(col + 2) == 'A' &&
                input.at(row + 3).at(col + 3) == 'S') {
                tokens.push_back("XMAS");
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "BottomRight out of range: " << e.what() << std::endl;
        }
    } catch (std::out_of_range& e) {
        // This shouldn't be hit if all individual try-catch blocks are used.
        std::cerr << "General out of range error: " << e.what() << std::endl;
    }

    return tokens;
}

std::string parseX_MASTokens(std::vector<std::vector<char>>& input, int row, int col) {

    // If the letter is not 'X', return nothing.
    if (input.at(row).at(col) != 'A') {
        return "INVALIDTOKEN";
    }

    int validMASCount = 0;

    try {
        //DiagDownForward
        try {
            if (input.at(row - 1).at(col - 1) == 'M' &&
                input.at(row + 1).at(col + 1) == 'S') {
                validMASCount++;
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "DiagDownForward out of range: " << e.what() << std::endl;
        }

        // DiagDownBackward
        try {
            if (input.at(row - 1).at(col + 1) == 'M' &&
                input.at(row + 1).at(col - 1) == 'S') {
                validMASCount++;
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "DiagDownBackward out of range: " << e.what() << std::endl;
        }

        // DiagUpForward
        try {
            if (input.at(row + 1).at(col - 1) == 'M' &&
                input.at(row - 1).at(col + 1) == 'S') {
                validMASCount++;
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "DiagUpForward out of range: " << e.what() << std::endl;
        }

        // DiagUpBackward
        try {
            if (input.at(row + 1).at(col + 1) == 'M' &&
                input.at(row - 1).at(col - 1) == 'S') {
                validMASCount++;
            }
        } catch (std::out_of_range& e) {
            //std::cerr << "DiagUpBackward out of range: " << e.what() << std::endl;
        }


    } catch (std::out_of_range& e) {
        // This shouldn't be hit if all individual try-catch blocks are used.
        std::cerr << "General out of range error: " << e.what() << std::endl;
    }

    if (validMASCount >= 2){
        return "MAS";
    }

    return "INVALIDTOKEN";
}

std::vector<std::string> collectXMASTokens(std::vector<std::vector<char>>& input){
    std::vector<std::vector<std::string>> rawTokens;

    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            rawTokens.push_back(parseXMASToken(input, i, j));
        }
    }

    std::vector<std::string> cookedTokens;

    for (int i = 0; i < rawTokens.size(); i++){
        for (int j = 0; j < rawTokens.at(i).size(); j++){
            if (rawTokens.at(i).at(j) == "XMAS"){
                cookedTokens.push_back(rawTokens.at(i).at(j));
            }
        }
    }
    return cookedTokens;
}

std::vector<std::string> collectX_MASTokens(std::vector<std::vector<char>>& input){
    std::vector<std::string> rawTokens;

    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            rawTokens.push_back(parseX_MASTokens(input, i, j));
        }
    }

    std::vector<std::string> cookedTokens;

    for (int i = 0; i < rawTokens.size(); i++){
        if (rawTokens.at(i) == "MAS"){
            cookedTokens.push_back(rawTokens.at(i));
        }
    }
    return cookedTokens;
}

std::vector<std::vector<char>> getInput(std::fstream& inFile){
    std::vector<std::vector<char>> input;

    std::string buffer = "";
    while (getline(inFile, buffer)){
        std::vector<char> line;

        for (int i = 0; i < buffer.size(); i++){
            line.push_back(buffer.at(i));
        }

        input.push_back(line);
    }

    return input;
}

