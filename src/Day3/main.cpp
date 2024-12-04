#include<iostream>
#include<fstream>
#include<string>
#include<vector>

int current = 0;
char problemChar = '\0';
std::string input;
std::string output;

char Advance();
char AddToken(char previous);
bool isAtEnd();
uint sumTokens(std::vector<std::string> tokens);

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
            if (token.size() > 0){
                if (token.at(0) == 'm'){
                    std::cout << "M Token " << token << " failed due to encountering " << problemChar << std::endl;
                }
            }
            token = "";  // Reset token if AddToken fails.
            previous == currentChar;
        } else if (currentChar == '.') {
            token += ')';  // Complete the token.
            if (!token.empty() && token.at(0) == 'm') {
                tokens.push_back(token);
                std::cout << "Token " << token << " accepted!\n";
            }
            token = "";  // Reset for the next token.
        } else {
            token += currentChar;  // Add valid character to the token.
            previous = currentChar;  // Update previous only for valid characters.
        }
    }
    std::cout << tokens.size() << " total tokens.\n";

    uint total = sumTokens(tokens);

    std::cout << "Total: " << total << ".\n";

	return 0;
}

uint sumTokens(std::vector<std::string> tokens){
    uint sum = 0;
    for (int i = 0; i < tokens.size(); i++){
        std::string currentToken = tokens.at(i);
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
        sum += (stoul(numOne) * stoul(numTwo));
    }

    return sum;
}

bool isAtEnd(){
    return current >= input.size();
}

//Return the current char and advance the current.
char Advance(){
    return input.at(current++);
}

char AddToken(char previous) {
    char c = Advance();  // Fetch the current character.

    switch (c) {
    case 'm':
        return c;
    case 'u':
        if (previous == 'm') return c;
        break;  // Invalid state: Break instead of returning immediately.
    case 'l':
        if (previous == 'u') return c;
        break;
    case '(':
        if (previous == 'l') return c;
        break;
    case ')':
        if (isdigit(previous)) return '.';
        break;
    case ',':
        if (isdigit(previous)) return c;
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

