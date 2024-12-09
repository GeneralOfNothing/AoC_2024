#include<iostream>
#include<fstream>
#include<vector>
#include<set>

std::vector<std::vector<char>> getInput(std::fstream& inFile);
bool isInBounds(std::pair<int, int> bounds, std::pair<int, int> x);

int main(){
    std::fstream inFile("TestData/08_input.txt");

    std::vector<std::vector<char>> input = getInput(inFile);

    int rows = input.size() - 1;
    int cols = input.at(0).size() - 1;
    std::pair<int,int> bounds = {rows, cols};

    std::vector<std::pair<char, std::pair<int, int>>> antennas;

    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            if (input.at(i).at(j) != '.'){
                antennas.push_back({input.at(i).at(j), {i, j}});
            }
        }
    }

    int validAntitennas = 0;
    std::set<std::pair<int, int>> countedLocations;
    for (int i = 0; i < antennas.size(); ++i) {
        // Check every other antenna with the same char
        for (int j = i + 1; j < antennas.size(); ++j) {
            if (antennas[i].first == antennas[j].first && antennas[i] != antennas[j]) {
                //Get the difference between them
                std::pair<int, int> antennaDiff = {
                    std::abs(antennas[i].second.first - antennas[j].second.first),
                    std::abs(antennas[i].second.second - antennas[j].second.second)
                };

                std::pair<int,int> AntitennaLoc1;
                std::pair<int,int> AntitennaLoc2;

                //Add the difference to each antenna for the antitenna locations.
                if (antennas[i].second.first < antennas[j].second.first && antennas[i].second.second < antennas[j].second.second){
                    AntitennaLoc1 = {
                        antennas[i].second.first - antennaDiff.first,
                        antennas[i].second.second - antennaDiff.second
                    };
                    AntitennaLoc2 = {
                        antennas[j].second.first + antennaDiff.first,
                        antennas[j].second.second + antennaDiff.second
                    };
                }
                if (antennas[i].second.first < antennas[j].second.first && antennas[i].second.second > antennas[j].second.second){
                    AntitennaLoc1 = {
                        antennas[i].second.first - antennaDiff.first,
                        antennas[i].second.second + antennaDiff.second
                    };
                    AntitennaLoc2 = {
                        antennas[j].second.first + antennaDiff.first,
                        antennas[j].second.second - antennaDiff.second
                    };
                }
                if (antennas[i].second.first > antennas[j].second.first && antennas[i].second.second < antennas[j].second.second){
                    AntitennaLoc1 = {
                        antennas[i].second.first + antennaDiff.first,
                        antennas[i].second.second - antennaDiff.second
                    };
                    AntitennaLoc2 = {
                        antennas[j].second.first - antennaDiff.first,
                        antennas[j].second.second + antennaDiff.second
                    };
                }
                if (antennas[i].second.first > antennas[j].second.first && antennas[i].second.second > antennas[j].second.second){
                    AntitennaLoc1 = {
                        antennas[i].second.first + antennaDiff.first,
                        antennas[i].second.second + antennaDiff.second
                    };
                    AntitennaLoc2 = {
                        antennas[j].second.first - antennaDiff.first,
                        antennas[j].second.second - antennaDiff.second
                    };
                }

                //

                //Test each location to see if its in bounds.
                if (isInBounds(bounds, AntitennaLoc1) && countedLocations.count(AntitennaLoc1) == 0){
                    countedLocations.emplace(AntitennaLoc1);
                    validAntitennas++;
                }
                if (isInBounds(bounds, AntitennaLoc2) && countedLocations.count(AntitennaLoc2) == 0){
                    countedLocations.emplace(AntitennaLoc2);
                    validAntitennas++;
                }
            }
        }
    }

    std::cout << "Part One Sum: " << validAntitennas << std::endl;

    return 0;
}

bool isInBounds(std::pair<int, int> bounds, std::pair<int, int> x) {
    return x.first >= 0 && x.first <= bounds.first && x.second >= 0 && x.second <= bounds.second;
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
