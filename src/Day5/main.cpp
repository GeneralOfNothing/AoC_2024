#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

std::multimap<std::string, std::string> populateRuleMap(std::vector<std::string> rules);
int countValidUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates);
std::vector<std::string> parseUpdate(std::string update);
int countInvalidUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates);
std::vector<std::string> getInvalidNumbersForKey(std::multimap<std::string, std::string>& ruleMap, std::string key);

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

    /*
    for (int i = 0; i < rules.size(); i++){
        std::cout << rules.at(i) << std::endl;
    }


    for (int i = 0; i < updates.size(); i++){
        std::cout << updates.at(i) << std::endl;
    }
    */

    std::multimap<std::string, std::string> ruleMap = populateRuleMap(rules);

    std::cout << "# of Updates: " << updates.size() << std::endl;

    int validUpdates = countValidUpdates(ruleMap, updates);

    std::cout << "# of Updates: " << updates.size() << std::endl;

    std::cout << "Valid Updates: " << validUpdates << std::endl;

    //Remaining bad updates are in updates.
    //TODO: Part 2 is to fix the updates and return the midpoint sum again.
    std::cout << "Bad Updates: \n";
    for (int i = 0; i < updates.size(); i++){
        std::cout << updates.at(i) << std::endl;
    }

    int fixedBadUpdates = countInvalidUpdates(ruleMap, updates);

    std::cout << "# of Updates: " << updates.size() << std::endl;

    std::cout << "Fixed Bad Updates: " << fixedBadUpdates << std::endl;

    std::cout << "Bad Updates: \n";
    for (int i = 0; i < updates.size(); i++){
        std::cout << updates.at(i) << std::endl;
    }

    return 0;
}

/*
 * parseUpdate
 * SUMMARY : Splits an update from one string into a vector of strings containing each digit.
 * RETURNS : vector<string> containing each number of the update.
 * PARAM : string containing a single update (eg: "56, 20, 13, 40, 50")
 */
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

/*
 * getInvalidNumbersForKey
 * SUMMARY : Looks up all of the numbers that must *NOT* be before key value.
 * RETURNS : vector<string> containing all invalid values.
 * PARAM : multimap<string,string>& containing the ruleset.
 * PARAM : string containing the key to lookup.
 */
std::vector<std::string> getInvalidNumbersForKey(std::multimap<std::string, std::string>& ruleMap, std::string key){
    std::vector<std::string> invalidNums;

    auto range = ruleMap.equal_range(key);
    for (auto it = range.first; it != range.second; it++){
        invalidNums.push_back(it->second);
    }

    return invalidNums;
}

int countInvalidUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates){
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
                std::vector<std::string> invalidNums = getInvalidNumbersForKey(ruleMap, key);

                //check all nums in front of j to see if it contains an invalid value.
                for (int k = j - 1; k >= 0; k--) {
                    std::string candidate = update.at(k);
                    std::string invalidNum = "";

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

int countValidUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates){
    int sum = 0;
    for (int i = 0; i < updates.size(); i++){
        std::vector<std::string> update = parseUpdate(updates.at(i));

        bool invalidNumFound = false;

        for (int j = update.size() - 1; j >= 0; j--){
            std::string key = update.at(j);
            std::vector<std::string> invalidNums = getInvalidNumbersForKey(ruleMap, key);

            //check all nums in front of j to see if it contains a invalidNum.
            for (int k = j - 1; k >= 0; k--) { // Look at elements *in front* of j
                std::string candidate = update.at(k);
                std::string invalidNum = "";

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

std::multimap<std::string, std::string> populateRuleMap(std::vector<std::string> rules){
    std::multimap<std::string, std::string> map;
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
        //std::cout << "Attempting to emplace: " << left << " | " << right << std::endl;
        map.emplace(left, right);
        //std::cout << "Success!" << std::endl;
    }
    return map;
}


