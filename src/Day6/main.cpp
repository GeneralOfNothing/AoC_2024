#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>
#include<thread>

std::vector<std::vector<char>> getInput(std::fstream& inFile);
void printSurroundings(int i,int j, const std::vector<std::vector<char>>& input);

enum dir{
    UP,
    LEFT,
    DOWN,
    RIGHT
};

int main(){
    std::fstream inFile("TestData//06_input.txt");

    std::vector<std::vector<char>> input = getInput(inFile);

    dir currentDir = UP;
    int distinctTiles = 1; //Init to one due to gaurd's starting tile.
    bool isDone = false;

    while (!isDone){
        for (int i = 0; i < input.size(); i++){
            for (int j = 0; j < input.size(); j++){
                char current = input.at(i).at(j);
                if (current == '^'){
                    printSurroundings(i, j, input);
                    char nextChar = '\0';
                    switch(currentDir){
                    case UP:
                        //check char above
                        nextChar = input.at(i-1).at(j);
                        switch(nextChar){
                        case '.':
                            input.at(i-1).at(j) = current;
                            input.at(i).at(j) = 'x';
                            distinctTiles++;
                            break;
                        case 'x':
                            input.at(i-1).at(j) = current;
                            input.at(i).at(j) = 'x';
                            break;
                        case '#':
                            currentDir = RIGHT;
                            //input.at(i).at(j+1) = current;
                            //input.at(i).at(j) = 'x';
                            break;
                        case '@':
                            isDone = true;
                            input.at(i).at(j) = 'x';
                            break;
                        }
                        break;
                    case LEFT:
                        nextChar = input.at(i).at(j-1);
                        switch (nextChar){
                        case '.':
                            input.at(i).at(j-1) = current;
                            input.at(i).at(j) = 'x';
                            distinctTiles++;
                            break;
                        case 'x':
                            input.at(i).at(j-1) = current;
                            input.at(i).at(j) = 'x';
                            break;
                        case '#':
                            currentDir = UP;
                            //input.at(i-1).at(j) = current;
                            //input.at()
                            break;
                        case '@':
                            isDone = true;
                            input.at(i).at(j) = 'x';
                            break;
                        }
                        break;
                    case RIGHT:
                        nextChar = input.at(i).at(j+1);
                        switch (nextChar){
                        case '.':
                            input.at(i).at(j+1) = current;
                            input.at(i).at(j) = 'x';
                            distinctTiles++;
                            break;
                        case 'x':
                            input.at(i).at(j+1) = current;
                            input.at(i).at(j) = 'x';
                            break;
                        case '#':
                            currentDir = DOWN;
                            break;
                        case '@':
                            isDone = true;
                            input.at(i).at(j) = 'x';
                            break;
                        }
                        break;
                    case DOWN:
                        nextChar = input.at(i+1).at(j);
                        switch (nextChar){
                        case '.':
                            input.at(i+1).at(j) = current;
                            input.at(i).at(j) = 'x';
                            distinctTiles++;
                            break;
                        case 'x':
                            input.at(i+1).at(j) = current;
                            input.at(i).at(j) = 'x';
                            break;
                        case '#':
                            currentDir = LEFT;
                            break;
                        case '@':
                            isDone = true;
                            input.at(i).at(j) = 'x';
                            break;
                        break;
                        }
                        break;
                    }
                }
            }
        }
    }

    //Output Display:
    std::cout << "Day Six's Output:\n";
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.at(i).size(); j++){
            std::cout << input.at(i).at(j);
        }
        std::cout << std::endl;
    }

    std::cout << "Total Distinct Tiles: " << distinctTiles << std::endl;

    return 0;
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
    const int speed = 50;


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
    std::this_thread::sleep_for(std::chrono::milliseconds(speed));
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
