#include<iostream>
#include<fstream>
#include<vector>
#include<set>

std::vector<std::vector<char>> getInput(std::fstream& inFile);
bool isInBounds(std::pair<int, int> bounds, std::pair<int, int> x);

int main(){
    std::fstream inFile("TestData/08_input.txt");

    std::vector<std::vector<char>> input = getInput(inFile);

    std::vector<std::pair<char, std::pair<int, int>>> antennas;

    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            if (input.at(i).at(j) != '.'){
                antennas.push_back({input.at(i).at(j), {i, j}});
            }
        }
    }



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

