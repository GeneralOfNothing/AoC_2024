#include<iostream>
#include<fstream>
#include<string>

int main(){
    std::ifstream inFile("TestData/05_input.txt");

    if (!inFile.is_open()){
        std::cerr << "Error: Unable to open input file." << std::endl;
    }

    std::cout << "Hello from day 5!" << std::endl;;

    return 0;
}
