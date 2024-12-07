#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>
#include<thread>

std::vector<std::vector<char>> getInput(std::fstream& inFile);
void printSurroundings(int i,int j, const std::vector<std::vector<char>>& input);
bool runSim(std::vector<std::vector<char>>& input, int& distinctTiles);

enum dir{
    UP,
    LEFT,
    DOWN,
    RIGHT
};

int main(){
    std::fstream inFile("TestData//06_input.txt");

    std::vector<std::vector<char>> input = getInput(inFile);

    int guardCol = 0;
    int guardRow = 0;

    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++){
            if (input.at(i).at(j) == '^'){
                guardRow = i;
                guardCol = j;
            }
        }
    }

    int distinctTiles = 0;
    int loops = 0;

    bool infLoop = runSim(input, distinctTiles);
    std::cout << "Total Distinct Tiles: " << distinctTiles << std::endl;

    std::vector<std::vector<char>> partOneCacheInput = input;

    input.at(guardRow).at(guardCol) = '^';

    //Part Two:
    int simCounter = 0;
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++){
            char currentChar = input.at(i).at(j);
            if (currentChar == 'x'){
                std::cout << "Running Sim #" << ++simCounter << std::endl;
                input.at(i).at(j) = '#';
                int tiles;
                bool looping = runSim(input, tiles);
                if (looping){
                    loops++;
                }
                input = partOneCacheInput;
                input.at(guardRow).at(guardCol) = '^';
            }
        }
    }

    std::cout << "Total Looping Locations: " << loops << std::endl;

    return 0;
}

bool runSim(std::vector<std::vector<char>>& input, int& distinctTiles){
    dir currentDir = UP;
    distinctTiles = 1; //Init to one due to gaurd's starting tile.
    bool isDone = false;
    int cycles = 0;

    std::pair<int,int> guardPos;
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++){
            if (input.at(i).at(j) == '^'){
                guardPos = {i, j};
            }
        }
    }

    while (!isDone){
        cycles++;

        //Console Visualization:
        //printSurroundings(guardPos.first, guardPos.second, input);

        //Brute Force FTW!!!
        if (cycles > 10000){
            std::cout << "Loop Detected." << std::endl;
            return true;
        }

        char current = input.at(guardPos.first).at(guardPos.second);
        char nextChar = '\0';
        switch(currentDir){
        case UP:
            //check char above
            nextChar = input.at(guardPos.first-1).at(guardPos.second);
            switch(nextChar){
            case '.':
                input.at(guardPos.first-1).at(guardPos.second) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                guardPos = {guardPos.first - 1, guardPos.second};
                distinctTiles++;
                break;
            case 'x':
                input.at(guardPos.first-1).at(guardPos.second) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                guardPos = {guardPos.first - 1, guardPos.second};
                break;
            case '#':
                currentDir = RIGHT;
                break;
            case '@':
                isDone = true;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                break;
            }
            break;
        case LEFT:
            nextChar = input.at(guardPos.first).at(guardPos.second-1);
            switch (nextChar){
            case '.':
                input.at(guardPos.first).at(guardPos.second-1) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                distinctTiles++;
                guardPos = {guardPos.first, guardPos.second - 1};
                break;
            case 'x':
                input.at(guardPos.first).at(guardPos.second-1) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                guardPos = {guardPos.first, guardPos.second - 1};
                break;
            case '#':
                currentDir = UP;
                break;
            case '@':
                isDone = true;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                break;
            }
            break;
        case RIGHT:
            nextChar = input.at(guardPos.first).at(guardPos.second+1);
            switch (nextChar){
            case '.':
                input.at(guardPos.first).at(guardPos.second+1) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                distinctTiles++;
                guardPos = {guardPos.first, guardPos.second + 1};
                break;
            case 'x':
                input.at(guardPos.first).at(guardPos.second + 1 ) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                guardPos = {guardPos.first, guardPos.second + 1};
                break;
            case '#':
                currentDir = DOWN;
                break;
            case '@':
                isDone = true;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                break;
            }
            break;
        case DOWN:
            nextChar = input.at(guardPos.first+1).at(guardPos.second);
            switch (nextChar){
            case '.':
                input.at(guardPos.first+1).at(guardPos.second) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                distinctTiles++;
                guardPos = {guardPos.first + 1, guardPos.second};
                break;
            case 'x':
                input.at(guardPos.first+1).at(guardPos.second) = current;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                guardPos = {guardPos.first + 1, guardPos.second};
                break;
            case '#':
                currentDir = LEFT;
                break;
            case '@':
                isDone = true;
                input.at(guardPos.first).at(guardPos.second) = 'x';
                break;
            }
            break;
        }
    }
    std::cout << "No Loop Detected." << std::endl;
    return false;
}

//Terminal Visualization
void printSurroundings(int i, int j, const std::vector<std::vector<char>>& input) {
    //Linux:
    system("clear");

    //Windows:
    //system("CLS");

    //Settings
    const int viewportWidth = 80;
    const int viewportHeight = 20;
    const int speed = 2500;


    int rows = input.size();
    int cols = input[0].size();
    for (int x = i - viewportHeight; x <= i + viewportHeight; ++x) {
        for (int y = j - viewportWidth; y <= j + viewportWidth; ++y) {
            // Check bounds
            if (x >= 0 && x < rows && y >= 0 && y < cols) {
                std::cout << input.at(x).at(y);
            } else {
                std::cout << ' '; // Print a space for out-of-bounds areas
            }
        }
        std::cout << '\n';
    }
    std::this_thread::sleep_for(std::chrono::microseconds(speed));
}

//2D vector w/ padding (Lets avoid the try-catch monstrosity from day 4 lmao)
std::vector<std::vector<char>> getInput(std::fstream& inFile){
    std::vector<std::vector<char>> input;

    std::string buffer = "";
    int inputWidth = 0;

    while (getline(inFile, buffer)){
        std::vector<char> line;

        inputWidth = buffer.size();
        //Add left padding
        line.push_back('@');


        for (int i = 0; i < buffer.size(); i++){
            line.push_back(buffer.at(i));
        }

        //Add right padding
        line.push_back('@');
        input.push_back(line);
    }

    std::vector<char> padding;

    for(int i = 0; i < inputWidth + 2; i++){
        padding.push_back('@');
    }

    //Add top/bottom padding
    input.insert(input.begin(), padding);
    input.push_back(padding);

    return input;
}
