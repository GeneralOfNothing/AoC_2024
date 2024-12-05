#include<iostream>
#include<string>
#include<fstream>
#include<vector>

bool isInOrder(std::vector<int> levels);
bool isGradual(std::vector<int> levels);
bool isValid(std::vector<int> levels);
bool isNaturallyValid(std::vector<int> levels);
int calculateDifference(int numOne, int numTwo);

int main() {
    std::ifstream inFile("TestData/02_input.txt");
	std::vector<std::string> reports;

    std::string line;
    while (!inFile.eof()){
        while (getline(inFile, line)) {
            reports.push_back(line);
        }
    }

	std::cout << "Number of reports: " << reports.size() << std::endl;

	int safeReports = 0;
	int naturallySafeReports = 0;

	for (int i = 0; i < reports.size(); i++) {
		std::vector<int> levels;
		std::string report = reports.at(i);

		std::string level;
        for (int j = 0; j < report.size(); j++) {
			if (isdigit(report.at(j))) {
				level += report.at(j);
			}
            else {
				levels.push_back(stoi(level));
				level = "";
			}
		}
		//Consume the final number in level:
        levels.push_back(stoi(level));

		if (isNaturallyValid(levels)) {
			naturallySafeReports++;
		}

		if (isValid(levels)) {
			safeReports++;
		}
	}

	std::cout << "Number of naturally safe reports (Part One): " << naturallySafeReports << std::endl;
	std::cout << "Number of safe reports (Part Two): " << safeReports << std::endl;
	
	return 0;
}

bool isNaturallyValid(std::vector<int> levels) {

	if (isInOrder(levels) && isGradual(levels)) {
		return true;
	}

	return false;
}

bool isValid(std::vector<int> levels) {
	//Part One:
	if (isInOrder(levels) && isGradual(levels)) {
		return true;
	}

	//Part Two: (Allow removal of one element)
	for (int i = 0; i < levels.size(); i++) {
		std::vector<int> retry = levels;
		retry.erase(retry.begin() + i);

		if (isInOrder(retry) && isGradual(retry)) {
			return true;
		}
	}

	return false;
}

//Report should either be all increasing or all decreasing
bool isInOrder(std::vector<int> levels)
{
	bool isIncreasing = true;

	if (levels.at(0) > levels.at(1)) {
		isIncreasing = false;
	}

	switch (isIncreasing) {
	case true:
		for (int i = 0; i < levels.size() - 1; i++) {
			if (levels.at(i) >= levels.at(i + 1)) {
				return false;
			}
		}
		return true;
	case false:
		for (int i = 0; i < levels.size() - 1; i++) {
			if (levels.at(i) <= levels.at(i + 1)) {
				return false;
			}
		}
		return true;
	}
}

//Any two adjacent levels should differ by at least one and at most three.
bool isGradual(std::vector<int> levels)
{
	for (int i = 0; i < levels.size() - 1; i++) {
		int diff = calculateDifference(levels.at(i), levels.at(i + 1));
		if (diff > 3 || diff < 1) {
			return false;
		}
	}
	return true;
}

int calculateDifference(int numOne, int numTwo) {
	return abs(numOne - numTwo);
}
