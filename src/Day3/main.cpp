#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdint>

//Excuse the laziness.. Globals prefixed with g_ at least.
int g_current = 0;
char g_problemChar = '\0';
std::string g_input;

char Advance();
char ReturnValidChar(char previous);
bool isAtEnd();
char Peek();
bool validateToken(std::string token);
uint64_t sumTokens(std::vector<std::string> tokens);

int main(){

    std::ifstream inFile("TestData//03_input.txt");

    if (!inFile.is_open()){
            std::cerr << "Error: Unable to open input file.\n";
        }

    std::string buffer = "";
    while (getline(inFile, buffer)){
        g_input += buffer;
    }

    std::vector<std::string> tokens;
    int partOneTokens = 0;
    int partTwoTokens = 0;

    std::string token = "";
    char previous = '\0';
    while (!isAtEnd()){
        char currentChar = ReturnValidChar(previous);

        //Discard if null
        if (currentChar == '\0') {
            if (token.size() > 1){
                std::cout << "Large Token (At least 2 char): " << token << " failed due to encountering: " << g_problemChar << std::endl;
            }
            token = "";  
            previous == currentChar;
        }
        //A ')' indicates a completed token
        else if (currentChar == ')') {
            token += currentChar;
            //We need additional validation here to ensure this is a well formed token.
            bool isValid = validateToken(token);
            if (isValid){
                tokens.push_back(token);
                std::cout << "Token " << token << " accepted!\n";

                switch(token.at(0)){
                case 'm':
                    partOneTokens++;
                    break;
                case 'd':
                    partTwoTokens++;
                    break;
                }
            }
            token = "";  
        }
        //We are still in the middle of consuming a possible token.
        else {
            token += currentChar;  
            previous = currentChar;  
        }
    }
    std::cout << partOneTokens << " total Part One tokens (mul(X,Y)).\n";
    std::cout << partTwoTokens << " total Part Two tokens (do() or don't()).\n";
    std::cout << tokens.size() << " total tokens.\n";

    uint64_t total = sumTokens(tokens);

    std::cout << "Total value: " << total << ".\n";
    std::cin.get();

	return 0;
}

uint64_t sumTokens(std::vector<std::string> tokens){
    uint64_t sum = 0;
    bool multiEnabled = true;
    for (int i = 0; i < tokens.size(); i++){
        std::string currentToken = tokens.at(i);
        
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

        if (multiEnabled) {
            sum += (stoul(numOne) * stoul(numTwo));
        }
    }

    return sum;
}

bool isAtEnd(){
    return g_current >= g_input.size();
}

char Advance(){
    return g_input.at(g_current++);
}

//Pretty much the same as advance expect we do not consume the character.
char Peek() {
    return g_input.at(g_current);
}

char ReturnValidChar(char previous) {
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
        if (isdigit(previous) || previous == '(') return c;
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
    g_problemChar = c;  // Store the problematic character for debugging if we need it.
    return '\0';
}

//There is surely a better way of doing this... I'm sorry....
//At least it works for the puzzle input.
bool validateToken(std::string token){
    if (token.at(0) == 'm'){ return true; }
    if (token.at(0) == 'd'){ return true; }
    return false;
}

