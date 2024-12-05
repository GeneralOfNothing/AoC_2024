#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

std::multimap<std::string, std::string> populateRuleMap(std::vector<std::string> rules);
int countValidUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates);
std::vector<std::string> parseUpdate(std::string update);
int fixBadUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates);

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

    int fixedBadUpdates = fixBadUpdates(ruleMap, updates);

    std::cout << "# of Updates: " << updates.size() << std::endl;

    std::cout << "Fixed Bad Updates: " << fixedBadUpdates << std::endl;

    std::cout << "Bad Updates: \n";
    for (int i = 0; i < updates.size(); i++){
        std::cout << updates.at(i) << std::endl;
    }

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

int fixBadUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates){
    int sum = 0;
    for (int i = 0; i < updates.size(); i++){
        std::vector<std::string> update = parseUpdate(updates.at(i));

        bool badNumFound = true;

        while (badNumFound){
            badNumFound = false;
            for (int j = update.size() - 1; j >= 0; j--){
                std::string key = update.at(j);
                auto range = ruleMap.equal_range(key);
                std::vector<std::string> badNums;

                //
                for (auto it = range.first; it != range.second; ++it) {
                    badNums.push_back(it->second);
                }

                //check all nums in front of j to see if it contains a badnum.
                for (int k = j - 1; k >= 0; k--) { // Look at elements *in front* of j
                    std::string candidate = update.at(k);
                    std::string problemNum = "";

                    // Check if the candidate contains any of the bad numbers
                    for (int m = 0; m < badNums.size(); m++) {
                        if (candidate == (badNums.at(m))) {
                            badNumFound = true;
                            problemNum = candidate;
                            //Swap them.
                            iter_swap(update.begin() + k, update.begin() + j);
                            break;
                        }
                    }
                }
            }
            if (!badNumFound){
                std::cout << "Fixed update!" << std::endl;
                std::cout << updates.at(i) << std::endl << " to " << std::endl;
                for (int i = 0; i < update.size(); i++){
                    std::cout << update.at(i) << " ";
                }
                std::cout << std::endl;
                int midpoint = update.size() / 2;
                sum += stoi(update.at(midpoint));

                //Erase updates.at(i)
                updates.erase(updates.begin() + i);
                i--;
            }
        }
    }
    return sum;
}

int countValidUpdates(std::multimap<std::string, std::string>& ruleMap, std::vector<std::string>& updates){
    int sum = 0;
    for (int i = 0; i < updates.size(); i++){
        //std::cout << "Attempting to check update " << updates.at(i) << std::endl;
        std::vector<std::string> update = parseUpdate(updates.at(i));

        bool badNumFound = false;

        for (int j = update.size() - 1; j >= 0; j--){
            std::string key = update.at(j);
            auto range = ruleMap.equal_range(key);
            std::vector<std::string> badNums;

            //
            for (auto it = range.first; it != range.second; ++it) {
                badNums.push_back(it->second);
            }

            //check all nums in front of j to see if it contains a badnum.
            for (int k = j - 1; k >= 0; k--) { // Look at elements *in front* of j
                std::string candidate = update.at(k);
                std::string problemNum = "";

                // Check if the candidate contains any of the bad numbers
                for (int m = 0; m < badNums.size(); m++) {
                    if (candidate == (badNums.at(m))) {
                        problemNum = candidate;
                        badNumFound = true;
                        break;
                    }
                }

                if (badNumFound) {
                    std::cout << "Update Rejected:\n";
                    for (int b = 0; b < update.size(); b++){
                        std::cout << update.at(b) << " ";
                    }
                    std::cout << std::endl;
                    std::cout << "Due to " << problemNum << " being in front of " << update.at(j);
                    std::cout << std::endl;
                    break; // No need to check further once a bad number is found
                }
            }
        }
        if (!badNumFound){
            //std::cout << "Update " << updates.at(i) << " accepted!\n";
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


