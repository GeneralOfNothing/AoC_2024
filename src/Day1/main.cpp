#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

int main(){
    std::fstream inFile("TestData//01_input.txt");

    std::vector<int> listLeft;
    std::vector<int> listRight;

    std::string number;
    int numbersParsed = 0;
    while(inFile >> number){
        int swap = numbersParsed % 2;
        if (swap == 0){
            listLeft.push_back(stoi(number));
        }
        else{
            listRight.push_back(stoi(number));
        }
        numbersParsed++;
    }

    for (int i = 0; i < listLeft.size(); i++){
        std::cout << listRight.at(i) << std::endl;
    }

    std::sort(listLeft.begin(), listLeft.end());
    std::sort(listRight.begin(), listRight.end());

    //Part One:
    int difference = 0;
    if (listLeft.size() == listRight.size()){
        for (int i = 0; i < listLeft.size(); i++){
            if (listLeft.at(i) > listRight.at(i)){
                difference += (listLeft.at(i) - listRight.at(i));
            }
            else{
                difference += (listRight.at(i) - listLeft.at(i));
            }
        }
    }

    std::cout << "Difference score: " << difference << std::endl;

    //Part two:
    int similarity = 0;
    for (int i = 0; i < listLeft.size(); i++) {
        int count = 0;
        for (int j = 0; j < listRight.size(); j++) {
            if (listLeft.at(i) == listRight.at(j)) {
                count++;
            }
        }
        similarity += (listLeft.at(i) * count);
    }

    std::cout << "Similarity score: " << similarity << std::endl;

    return 0;
}
