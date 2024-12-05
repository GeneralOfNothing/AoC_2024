#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

std::map<int, std::vector<int>> populateRuleMap(std::vector<std::string> rules);
int countValidUpdates(std::map<int, std::vector<int>>& ruleMap, std::vector<std::string>& updates);
std::vector<std::string> parseUpdate(std::string update);
int countInvalidUpdates(std::map<int, std::vector<int>>& ruleMap, std::vector<std::string>& updates);
std::vector<int> getInvalidNumbersForKey(std::map<int, std::vector<int>>& ruleMap, std::string key);

int main(){
    std::ifstream inFile("TestData/05_input.txt");

    if (!inFile.is_open()){
        std::cerr << "Error: Unable to open input file." << std::endl;
    }

    std::vector<std::string> rules;
    std::vector<std::string> updates;
    std::string buffer = "";
    while (getline(inFile, buffer)){
        if (buffer.size() == 5){
            rules.push_back(buffer);
        }
        else if (buffer.size() > 0){
            updates.push_back(buffer);
        }
    }

    std::map<int, std::vector<int>> ruleMap = populateRuleMap(rules);

    int validUpdates = countValidUpdates(ruleMap, updates);

    std::cout << "Part One Valid Updates Sum: " << validUpdates << std::endl;

    int fixedBadUpdates = countInvalidUpdates(ruleMap, updates);

    std::cout << "Part Two Fixed Bad Updates Sum: " << fixedBadUpdates << std::endl;

    return 0;
}

std::vector<std::string> parseUpdate(std::string update){
    char c = '\0';
    std::string number = "";
    std::vector<std::string> nums;
    for (int i = 0; i < update.size(); i++){
        c = update.at(i);
        if (c == ','){
            nums.push_back(number);
            number = "";
        }
        else{
            number.push_back(c);
        }
    }
    //Consume the final number and return.
    nums.push_back(number);
    return nums;
}

std::vector<int> getInvalidNumbersForKey(std::map<int, std::vector<int>>& ruleMap, std::string key){
    return ruleMap[std::stoi(key)];
}

int countInvalidUpdates(std::map<int, std::vector<int>>& ruleMap, std::vector<std::string>& updates){
    int sum = 0;
    int numOfSwaps = 0;
    for (int i = 0; i < updates.size(); i++){
        std::vector<std::string> update = parseUpdate(updates.at(i));

        bool invalidNumFound = true;

        while (invalidNumFound){
            invalidNumFound = false;
            for (int j = update.size() - 1; j >= 0; j--){
                //Get the invalid numbers for this value.
                std::string key = update.at(j);
                std::vector<int> invalidNums = getInvalidNumbersForKey(ruleMap, key);

                //check all nums in front of j to see if it contains an invalid value.
                for (int k = j - 1; k >= 0; k--) {
                    int candidate = stoi(update.at(k));
                    int invalidNum = 0;

                    // Check if the candidate contains any of the bad numbers
                    for (int m = 0; m < invalidNums.size(); m++) {
                        if (candidate == (invalidNums.at(m))) {
                            invalidNumFound = true;
                            invalidNum = candidate;

                            //Swap them.
                            std::swap(update[k], update[j]);
                            numOfSwaps++;

                            break;
                        }
                    }
                }
            }
            if (!invalidNumFound){
                int midpoint = update.size() / 2;
                sum += stoi(update.at(midpoint));

                //Erase updates.at(i)
                updates.erase(updates.begin() + i);
                i--;
            }
        }
    }
    std::cout << "NUMBER OF SWAPS TO FIX ALL UPDATES: " << numOfSwaps << std::endl;
    return sum;
}

int countValidUpdates(std::map<int, std::vector<int>>& ruleMap, std::vector<std::string>& updates){
    int sum = 0;
    for (int i = 0; i < updates.size(); i++){
        std::vector<std::string> update = parseUpdate(updates.at(i));

        bool invalidNumFound = false;

        for (int j = update.size() - 1; j >= 0; j--){
            std::string key = update.at(j);
            std::vector<int> invalidNums = getInvalidNumbersForKey(ruleMap, key);

            //check all nums in front of j to see if it contains a invalidNum.
            for (int k = j - 1; k >= 0; k--) { // Look at elements *in front* of j
                int candidate = stoi(update.at(k));
                int invalidNum = 0;

                // Check if the candidate contains any of the invalid numbers
                for (int m = 0; m < invalidNums.size(); m++) {
                    if (candidate == (invalidNums.at(m))) {
                        invalidNum = candidate;
                        invalidNumFound = true;
                        break;
                    }
                }

                if (invalidNumFound) {
                    break; // No need to check further once a bad number is found
                }
            }
        }
        if (!invalidNumFound){
            int midpoint = update.size() / 2;
            sum += stoi(update.at(midpoint));

            //Erase updates.at(i)
            updates.erase(updates.begin() + i);
            i--;
        }
    }
    return sum;
}

std::map<int, std::vector<int>> populateRuleMap(std::vector<std::string> rules){
    std::map<int, std::vector<int>> map;
    for (int i = 0; i < rules.size(); i++){
        bool pipeEncountered = false;
        std::string left;
        std::string right;
        for (int j = 0; j < rules.at(i).size(); j++){
            char c = rules.at(i).at(j);
            if (c == '|'){
                pipeEncountered = true;
                continue;
            }
            if (!pipeEncountered){
                left += c;
            }
            else{
                right += c;
            }
        }
        map[std::stoi(left)].push_back(std::stoi(right));
    }
    return map;
}


