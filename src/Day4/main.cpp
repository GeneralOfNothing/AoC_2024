#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::vector<std::vector<char>> getInput(std::fstream& inFile);

int main(){
    std::fstream inFile("TestData//input.txt");
    if (!inFile.is_open()){
        std::cout << "Error: Unable to open input file.\n";
    }

    std::vector<std::vector<char>> input = getInput(inFile);

    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            std::cout << input.at(i).at(j);
        }
        std::cout << std::endl;
    }

    std::cin.get();

    return 0;
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

