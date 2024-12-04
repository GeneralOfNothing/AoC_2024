#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdint>

int current = 0;
char problemChar = '\0';
std::string input;

char Advance();
char AddToken(char previous);
bool isAtEnd();
char Peek();

uint64_t sumTokens(std::vector<std::string> tokens);

int main(){

    std::ifstream inFile("TestData//input.txt");

    if (!inFile.is_open()){
            std::cout << "Error: Unable to open input file.\n";
        }

    std::string buffer = "";
    while (getline(inFile, buffer)){
        input += buffer;
    }

    std::vector<std::string> tokens;

    std::string token = "";
    char previous = '\0';
    while (!isAtEnd()){
        char currentChar = AddToken(previous);
        if (currentChar == '\0') {
            if (token.size() > 2){
                //std::cout << "Large Token " << token << " failed due to encountering " << problemChar << std::endl;
            }
            token = "";  
            previous == currentChar;
        } else if (currentChar == '.') {
            token += ')';
            if (!token.empty()) {
                if (token.at(0) == 'm' || token.at(0) == 'd') {
                    tokens.push_back(token);
                    if (token.at(0) != 'd') {
                        std::cout << "Token " << token << " accepted!\n";
                    }
                }
            }
            token = "";  
        } else {
            token += currentChar;  
            previous = currentChar;  
        }
    }
    std::cout << tokens.size() << " total tokens.\n";

    uint64_t total = sumTokens(tokens);

    std::cout << "Total: " << total << ".\n";
    std::cin.get();

	return 0;
}

uint64_t sumTokens(std::vector<std::string> tokens){
    uint64_t sum = 0;
    bool multiEnabled = true;
    for (int i = 0; i < tokens.size(); i++){
        std::string currentToken = tokens.at(i);
        std::cout << "summing token: " << currentToken << std::endl;
        
        if (currentToken == "do()") {
            multiEnabled = true;
            continue;
        }
        if (currentToken == "don't()") {
            multiEnabled = false;
            continue;
        }

        std::string numOne;
        std::string numTwo;

        //First digit will always be at index 4
        int strIndex = 4;
        char c = currentToken.at(strIndex);
        bool secondNumber = false;
        while (c != ')'){
            if (c == ','){
                secondNumber = true;
                c = currentToken.at(++strIndex);
            }

            if (!secondNumber){
                numOne += c;
            }
            else{
                numTwo += c;
            }

            c = currentToken.at(++strIndex);
        }
        std::cout << currentToken << std::endl;
        std::cout << stoul(numOne) << " * " << stoul(numTwo) << std::endl << std::endl;

        if (multiEnabled) {
            sum += (stoul(numOne) * stoul(numTwo));
        }
    }

    return sum;
}

bool isAtEnd(){
    return current >= input.size();
}

char Advance(){
    return input.at(current++);
}

//Pretty much the same as advance expect we do not consume the character.
char Peek() {
    return input.at(current);
}

char AddToken(char previous) {
    char c = Advance();  // Fetch the current character.

    switch (c) {
        //Part Two:
    case 'd':
        return c;
    case 'o':
        if (previous == 'd') return c;
        break;
    case 'n':
        if (previous == 'o') return c;
        break;
    case '\'':
        if (previous == 'n') return c;
        break;
    case 't':
        if (previous == '\'') return c;
        break;
        //Part One:
    case 'm':
        return c;
    case 'u':
        if (previous == 'm') return c;
        break;
    case 'l':
        if (previous == 'u') return c;
        break;
    case '(':
        if (previous == 'l' || previous == 'o' || previous == 't') return c;
        break;
    case ')':
        if (isdigit(previous) || previous == '(') return '.';
        break;
    case ',':
        if (isdigit(previous) && isdigit(Peek())) return c;
        break;
    default:
        if (isdigit(c)) {
            if (isdigit(previous) || previous == '(' || previous == ',') return c;
            break;
        }
    }

    // If we reach here, the character is invalid for the current token.
    problemChar = c;  // Store the problematic character for debugging.
    return '\0';      // Indicate failure.
}

