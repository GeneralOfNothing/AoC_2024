#include<iostream>
#include<fstream>
#include<vector>
#include<string>

std::vector<std::pair<unsigned long long, std::vector<int>>> getInput(std::ifstream& inFile);

void printInputs(const std::vector<std::pair<unsigned long long, std::vector<int>>> inputs);
unsigned long long concatenate(unsigned long long i, unsigned long long j);

unsigned long long evaluateInput(std::pair<unsigned long long, std::vector<int>> input);
bool evaluate(unsigned long long target, std::vector<int> operands, int index, unsigned long long currentResult);

unsigned long long evaluateInputPartTwo(std::pair<unsigned long long, std::vector<int>> input);
bool evaluatePartTwo(unsigned long long target, std::vector<int> operands, int index, unsigned long long currentResult);

int main(){
    std::ifstream inFile("TestData//07_input.txt");
    std::vector<std::pair<unsigned long long, std::vector<int>>> inputs = getInput(inFile);

    //printInputs(inputs);

    long long int partOneSum = 0;
    long long int partTwoSum = 0;
    for (int i = 0; i < inputs.size(); i++){
        partOneSum += evaluateInput(inputs.at(i));
    }

    for (int i = 0; i < inputs.size(); i++){
        partTwoSum += evaluateInputPartTwo(inputs.at(i));
    }


    std::cout << "Part One Total: " << partOneSum << std::endl;
    std::cout << "Part Two Total: " << partTwoSum << std::endl;


    return 0;
}

unsigned long long evaluateInput(std::pair<unsigned long long, std::vector<int>> input){
    if (evaluate(input.first, input.second, 1, input.second.at(0))){
        return input.first;
    }
    else { return 0; }
}

unsigned long long evaluateInputPartTwo(std::pair<unsigned long long, std::vector<int>> input){
    if (evaluatePartTwo(input.first, input.second, 1, input.second.at(0))){
        return input.first;
    }
    else { return 0; }
}

bool evaluate(unsigned long long target, std::vector<int> operands, int index, unsigned long long currentResult){
    if (index == operands.size()){
        return currentResult == target;
    }

    long long int nextNumber = operands.at(index);

    //Addition
    if (evaluate(target, operands, index + 1, currentResult + nextNumber)){
        return true;
    }

    //Multiplication
    if (evaluate(target, operands, index + 1, currentResult * nextNumber)){
        return true;
    }

    //Not in this branch.
    return false;
}

bool evaluatePartTwo(unsigned long long target, std::vector<int> operands, int index, unsigned long long currentResult){
    if (index == operands.size()){
        return currentResult == target;
    }

    unsigned long long nextNumber = operands.at(index);

    //Addition
    if (evaluatePartTwo(target, operands, index + 1, currentResult + nextNumber)){
        return true;
    }

    //Multiplication
    if (evaluatePartTwo(target, operands, index + 1, currentResult * nextNumber)){
        return true;
    }

    //Concat
    if (evaluatePartTwo(target, operands, index + 1, concatenate(currentResult, nextNumber))){
        return true;
    }

    //Not in this branch.
    return false;
}

unsigned long long concatenate(unsigned long long i, unsigned long long j) {
    std::string numOne = std::to_string(i);
    std::string numTwo = std::to_string(j);

    return std::stoull(numOne + numTwo);
}

std::vector<std::pair<unsigned long long, std::vector<int>>> getInput(std::ifstream& inFile){
    std::vector<std::pair<unsigned long long, std::vector<int>>> inputs;

    std::string buffer;

    while(std::getline(inFile, buffer)){
        std::pair<unsigned long long, std::vector<int>> currentLine;
        std::string left;
        std::string right;
        bool colonEncountered = false;
        for (int i = 0; i < buffer.size(); i++){
            if (buffer.at(i) == ':'){
                colonEncountered = true;
                continue;
            }

            if (!colonEncountered){
                left += buffer.at(i);
            }
            else{
                right += buffer.at(i);
            }
        }

        //Add a trailing space to right.
        right += " ";

        unsigned long long testNumber = std::stoull(left);

        std::vector<int> operands;
        std::string number;
        for (int i = 0; i < right.size(); i++){
            char current = right.at(i);
            if (isdigit(current)){
                number += current;
            }
            else{
                if(number.size() > 0){
                    operands.push_back(stoi(number));
                }
                number = "";
            }
        }

        currentLine.first = testNumber;
        currentLine.second = operands;
        inputs.push_back(currentLine);
    }
    return inputs;
}

void printInputs(const std::vector<std::pair<unsigned long long, std::vector<int>>> inputs){
    for (int i = 0; i < inputs.size(); i++){
        std::cout << inputs.at(i).first << " : ";
        for (int j = 0; j < inputs.at(i).second.size(); j++){
            std::cout << inputs.at(i).second.at(j) << " ";
        }
        std::cout << std::endl;
    }
}
